/*
	Copyright 2022 Efabless Corp.

	Author: Mohamed Shalan (mshalan@efabless.com)
	
	Licensed under the Apache License, Version 2.0 (the "License"); 
	you may not use this file except in compliance with the License. 
	You may obtain a copy of the License at:
	http://www.apache.org/licenses/LICENSE-2.0
	Unless required by applicable law or agreed to in writing, software 
	distributed under the License is distributed on an "AS IS" BASIS, 
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
	See the License for the specific language governing permissions and 
	limitations under the License.
*/
/* 
    A wrapper around the spi_master module by Ubixum, Inc.
*/

`timescale        1ns/1ps
`default_nettype  none

module EF_SPI #(parameter 
                    CDW=8,
                    FAW=4
) (
    input wire              clk,
    input wire              rst_n,
    input wire              CPOL,
    input wire              CPHA,
    input wire [CDW-1:0]    clk_divider,  
    input wire              wr,
    input wire              rd,      
    input wire [7:0]        datai,
    output wire [7:0]       datao,
    input wire              enable,
    input wire              rx_en,
    input wire              rx_flush,   
    input wire  [FAW-1:0]   rx_threshold,
    output wire             rx_empty,
    output wire             rx_full,
    output wire             rx_level_above,
    output wire [FAW-1:0]   rx_level,
    
    input wire              tx_flush,
    input wire  [FAW-1:0]   tx_threshold,
    output wire             tx_empty,
    output wire             tx_full,
    output wire             tx_level_below,
    output wire [FAW-1:0]   tx_level,

    output wire             busy,
    output wire             done,

    input  wire             miso,
    output wire             mosi,
    output wire             csb,
    input  wire             ss,
    output wire             sclk
);

    localparam FDW = 8;
    
    // TX Side
    wire        tx_wr       = wr;
    wire        tx_rd       = !tx_empty & !busy;
    wire        spi_go      = !tx_empty & !busy;
    //wire        tx_empty;
    //wire [7:0]  datai;
    wire [7:0]  tx_wdata    = datai;
    wire [7:0]  tx_rdata;
    
    // RX Side
    wire        done_pe;
    wire        rx_wr       = rx_en & done_pe;
    wire        rx_rd       = rd;
    //wire        rx_empty;
    wire [7:0]  f_datao;
    wire [7:0]  rx_wdata    = f_datao;
    wire [7:0]  rx_rdata;
    assign datao = rx_rdata;

    assign      tx_level_below = tx_level < tx_threshold;
    assign      rx_level_above = rx_level > rx_threshold;

    assign      csb = ~ss;
    
    ef_util_ped done_ed (
        .clk(clk),
        .in(done),
        .out(done_pe)
    );

    ef_util_fifo #(
        .DW(FDW), 
        .AW(FAW)
    ) rx_fifo (
        .clk(clk),
        .rst_n(rst_n),
        .rd(rx_rd),
        .wr(rx_wr),
        .flush(rx_flush),
        .wdata(rx_wdata),
        .empty(rx_empty),
        .full(rx_full),
        .rdata(rx_rdata),
        .level(rx_level)    
    );

    ef_util_fifo #(
        .DW(FDW), 
        .AW(FAW)
    ) tx_fifo (
        .clk(clk),
        .rst_n(rst_n),
        .rd(tx_rd),
        .wr(tx_wr),
        .flush(tx_flush),
        .wdata(tx_wdata),
        .empty(tx_empty),
        .full(tx_full),
        .rdata(tx_rdata),
        .level(tx_level)
    );

    spi_master#(
        .DATA_WIDTH(8),
        .CLK_DIVIDER_WIDTH(CDW),
        .NUM_PORTS(1),
        .SAMPLE_PHASE(0)
    ) spi_master (
        .clk(clk),
        .resetb(rst_n),
        .CPOL(CPOL),
        .CPHA(CPHA),
        .clk_divider(clk_divider),
        .go(spi_go),
        .enable(enable),
        .datai(tx_rdata),
        .datao(f_datao),
        .busy(busy),
        .done(done),
        .dout(miso),
        .din(mosi),
        // .csb(csb),
        .sclk(sclk)
   );

endmodule



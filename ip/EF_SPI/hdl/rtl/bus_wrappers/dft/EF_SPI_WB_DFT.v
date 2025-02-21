/*
	Copyright 2024 Efabless Corp.

	Author: Efabless Corp. (ip_admin@efabless.com)

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	    www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

*/

/* THIS FILE IS GENERATED, DO NOT EDIT */

`timescale 1ns / 1ps
`default_nettype none

module EF_SPI_WB #(
    parameter CDW = 8,
    FAW = 4
) (

    input  wire         sc_testmode,
    input  wire         clk_i,
    input  wire         rst_i,
    input  wire [ 31:0] adr_i,
    input  wire [ 31:0] dat_i,
    output wire [ 31:0] dat_o,
    input  wire [  3:0] sel_i,
    input  wire         cyc_i,
    input  wire         stb_i,
    output reg          ack_o,
    input  wire         we_i,
    output wire         IRQ,
    input  wire [1-1:0] miso,
    output wire [1-1:0] mosi,
    output wire [1-1:0] csb,
    output wire [1-1:0] sclk
);

  localparam RXDATA_REG_OFFSET = 16'h0000;
  localparam TXDATA_REG_OFFSET = 16'h0004;
  localparam CFG_REG_OFFSET = 16'h0008;
  localparam CTRL_REG_OFFSET = 16'h000C;
  localparam PR_REG_OFFSET = 16'h0010;
  localparam STATUS_REG_OFFSET = 16'h0014;
  localparam RX_FIFO_LEVEL_REG_OFFSET = 16'hFE00;
  localparam RX_FIFO_THRESHOLD_REG_OFFSET = 16'hFE04;
  localparam RX_FIFO_FLUSH_REG_OFFSET = 16'hFE08;
  localparam TX_FIFO_LEVEL_REG_OFFSET = 16'hFE10;
  localparam TX_FIFO_THRESHOLD_REG_OFFSET = 16'hFE14;
  localparam TX_FIFO_FLUSH_REG_OFFSET = 16'hFE18;
  localparam IM_REG_OFFSET = 16'hFF00;
  localparam MIS_REG_OFFSET = 16'hFF04;
  localparam RIS_REG_OFFSET = 16'hFF08;
  localparam IC_REG_OFFSET = 16'hFF0C;

  reg [0:0] GCLK_REG;
  wire clk_g;

  wire clk_gated_en = sc_testmode ? 1'b1 : GCLK_REG[0];
  ef_util_gating_cell clk_gate_cell (

      // USE_POWER_PINS
      .clk(clk_i),
      .clk_en(clk_gated_en),
      .clk_o(clk_g)
  );

  wire           clk = clk_g;
  wire           rst_n = (~rst_i);

  wire           wb_valid = cyc_i & stb_i;
  wire           wb_we = we_i & wb_valid;
  wire           wb_re = ~we_i & wb_valid;
  wire [    3:0] wb_byte_sel = sel_i & {4{wb_we}};

  wire [  1-1:0] CPOL;
  wire [  1-1:0] CPHA;
  wire [CDW-1:0] clk_divider;
  wire [  1-1:0] wr;
  wire [  1-1:0] rd;
  wire [  8-1:0] datai;
  wire [  8-1:0] datao;
  wire [  1-1:0] rx_en;
  wire [  1-1:0] rx_flush;
  wire [FAW-1:0] rx_threshold;
  wire [  1-1:0] rx_empty;
  wire [  1-1:0] rx_full;
  wire [  1-1:0] rx_level_above;
  wire [FAW-1:0] rx_level;
  wire [  1-1:0] tx_flush;
  wire [FAW-1:0] tx_threshold;
  wire [  1-1:0] tx_empty;
  wire [  1-1:0] tx_full;
  wire [  1-1:0] tx_level_below;
  wire [FAW-1:0] tx_level;
  wire [  1-1:0] ss;
  wire [  1-1:0] enable;
  wire [  1-1:0] done;
  wire [  1-1:0] busy;

  // Register Definitions
  wire [  8-1:0] RXDATA_WIRE;

  wire [  8-1:0] TXDATA_WIRE;

  reg  [    1:0] CFG_REG;
  assign CPOL = CFG_REG[0 : 0];
  assign CPHA = CFG_REG[1 : 1];
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) CFG_REG <= 0;
    else if (wb_we & (adr_i[16-1:0] == CFG_REG_OFFSET)) CFG_REG <= dat_i[2-1:0];

  reg [2:0] CTRL_REG;
  assign ss = CTRL_REG[0 : 0];
  assign enable = CTRL_REG[1 : 1];
  assign rx_en = CTRL_REG[2 : 2];
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) CTRL_REG <= 0;
    else if (wb_we & (adr_i[16-1:0] == CTRL_REG_OFFSET)) CTRL_REG <= dat_i[3-1:0];

  reg [CDW-1:0] PR_REG;
  assign clk_divider = PR_REG;
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) PR_REG <= 'h2;
    else if (wb_we & (adr_i[16-1:0] == PR_REG_OFFSET)) PR_REG <= dat_i[CDW-1:0];

  wire [8-1:0] STATUS_WIRE;
  assign STATUS_WIRE[0 : 0] = tx_empty;
  assign STATUS_WIRE[1 : 1] = tx_full;
  assign STATUS_WIRE[2 : 2] = rx_empty;
  assign STATUS_WIRE[3 : 3] = rx_full;
  assign STATUS_WIRE[4 : 4] = tx_level_below;
  assign STATUS_WIRE[5 : 5] = rx_level_above;
  assign STATUS_WIRE[6 : 6] = busy;
  assign STATUS_WIRE[7 : 7] = done;

  wire [FAW-1:0] RX_FIFO_LEVEL_WIRE;
  assign RX_FIFO_LEVEL_WIRE[(FAW-1) : 0] = rx_level;

  reg [FAW-1:0] RX_FIFO_THRESHOLD_REG;
  assign rx_threshold = RX_FIFO_THRESHOLD_REG[(FAW-1) : 0];
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) RX_FIFO_THRESHOLD_REG <= 0;
    else if (wb_we & (adr_i[16-1:0] == RX_FIFO_THRESHOLD_REG_OFFSET))
      RX_FIFO_THRESHOLD_REG <= dat_i[FAW-1:0];

  reg [0:0] RX_FIFO_FLUSH_REG;
  assign rx_flush = RX_FIFO_FLUSH_REG[0 : 0];
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) RX_FIFO_FLUSH_REG <= 0;
    else if (wb_we & (adr_i[16-1:0] == RX_FIFO_FLUSH_REG_OFFSET)) RX_FIFO_FLUSH_REG <= dat_i[1-1:0];
    else RX_FIFO_FLUSH_REG <= 1'h0 & RX_FIFO_FLUSH_REG;

  wire [FAW-1:0] TX_FIFO_LEVEL_WIRE;
  assign TX_FIFO_LEVEL_WIRE[(FAW-1) : 0] = tx_level;

  reg [FAW-1:0] TX_FIFO_THRESHOLD_REG;
  assign tx_threshold = TX_FIFO_THRESHOLD_REG[(FAW-1) : 0];
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) TX_FIFO_THRESHOLD_REG <= 0;
    else if (wb_we & (adr_i[16-1:0] == TX_FIFO_THRESHOLD_REG_OFFSET))
      TX_FIFO_THRESHOLD_REG <= dat_i[FAW-1:0];

  reg [0:0] TX_FIFO_FLUSH_REG;
  assign tx_flush = TX_FIFO_FLUSH_REG[0 : 0];
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) TX_FIFO_FLUSH_REG <= 0;
    else if (wb_we & (adr_i[16-1:0] == TX_FIFO_FLUSH_REG_OFFSET)) TX_FIFO_FLUSH_REG <= dat_i[1-1:0];
    else TX_FIFO_FLUSH_REG <= 1'h0 & TX_FIFO_FLUSH_REG;

  localparam GCLK_REG_OFFSET = 16'hFF10;
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) GCLK_REG <= 0;
    else if (wb_we & (adr_i[16-1:0] == GCLK_REG_OFFSET)) GCLK_REG <= dat_i[1-1:0];

  reg  [  5:0] IM_REG;
  reg  [  5:0] IC_REG;
  reg  [  5:0] RIS_REG;

  wire [6-1:0] MIS_REG = RIS_REG & IM_REG;
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) IM_REG <= 0;
    else if (wb_we & (adr_i[16-1:0] == IM_REG_OFFSET)) IM_REG <= dat_i[6-1:0];
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) IC_REG <= 6'b0;
    else if (wb_we & (adr_i[16-1:0] == IC_REG_OFFSET)) IC_REG <= dat_i[6-1:0];
    else IC_REG <= 6'd0;

  wire [0:0] TXE = tx_empty;
  wire [0:0] TXF = tx_full;
  wire [0:0] RXE = rx_empty;
  wire [0:0] RXF = rx_full;
  wire [0:0] TXB = tx_level_below;
  wire [0:0] RXA = rx_level_above;

  integer _i_;
  always @(posedge clk_i or posedge rst_i)
    if (rst_i) RIS_REG <= 0;
    else begin
      for (_i_ = 0; _i_ < 1; _i_ = _i_ + 1) begin
        if (IC_REG[_i_]) RIS_REG[_i_] <= 1'b0;
        else if (TXE[_i_-0] == 1'b1) RIS_REG[_i_] <= 1'b1;
      end
      for (_i_ = 1; _i_ < 2; _i_ = _i_ + 1) begin
        if (IC_REG[_i_]) RIS_REG[_i_] <= 1'b0;
        else if (TXF[_i_-1] == 1'b1) RIS_REG[_i_] <= 1'b1;
      end
      for (_i_ = 2; _i_ < 3; _i_ = _i_ + 1) begin
        if (IC_REG[_i_]) RIS_REG[_i_] <= 1'b0;
        else if (RXE[_i_-2] == 1'b1) RIS_REG[_i_] <= 1'b1;
      end
      for (_i_ = 3; _i_ < 4; _i_ = _i_ + 1) begin
        if (IC_REG[_i_]) RIS_REG[_i_] <= 1'b0;
        else if (RXF[_i_-3] == 1'b1) RIS_REG[_i_] <= 1'b1;
      end
      for (_i_ = 4; _i_ < 5; _i_ = _i_ + 1) begin
        if (IC_REG[_i_]) RIS_REG[_i_] <= 1'b0;
        else if (TXB[_i_-4] == 1'b1) RIS_REG[_i_] <= 1'b1;
      end
      for (_i_ = 5; _i_ < 6; _i_ = _i_ + 1) begin
        if (IC_REG[_i_]) RIS_REG[_i_] <= 1'b0;
        else if (RXA[_i_-5] == 1'b1) RIS_REG[_i_] <= 1'b1;
      end
    end

  assign IRQ = |MIS_REG;

  EF_SPI #(
      .CDW(CDW),
      .FAW(FAW)
  ) instance_to_wrap (
      .clk(clk),
      .rst_n(rst_n),
      .CPOL(CPOL),
      .CPHA(CPHA),
      .clk_divider(clk_divider),
      .wr(wr),
      .rd(rd),
      .datai(datai),
      .datao(datao),
      .rx_en(rx_en),
      .rx_flush(rx_flush),
      .rx_threshold(rx_threshold),
      .rx_empty(rx_empty),
      .rx_full(rx_full),
      .rx_level_above(rx_level_above),
      .rx_level(rx_level),
      .tx_flush(tx_flush),
      .tx_threshold(tx_threshold),
      .tx_empty(tx_empty),
      .tx_full(tx_full),
      .tx_level_below(tx_level_below),
      .tx_level(tx_level),
      .ss(ss),
      .enable(enable),
      .done(done),
      .busy(busy),
      .miso(miso),
      .mosi(mosi),
      .csb(csb),
      .sclk(sclk)
  );

  assign	dat_o = 
			(adr_i[16-1:0] == RXDATA_REG_OFFSET)	? RXDATA_WIRE :
			(adr_i[16-1:0] == TXDATA_REG_OFFSET)	? TXDATA_WIRE :
			(adr_i[16-1:0] == CFG_REG_OFFSET)	? CFG_REG :
			(adr_i[16-1:0] == CTRL_REG_OFFSET)	? CTRL_REG :
			(adr_i[16-1:0] == PR_REG_OFFSET)	? PR_REG :
			(adr_i[16-1:0] == STATUS_REG_OFFSET)	? STATUS_WIRE :
			(adr_i[16-1:0] == RX_FIFO_LEVEL_REG_OFFSET)	? RX_FIFO_LEVEL_WIRE :
			(adr_i[16-1:0] == RX_FIFO_THRESHOLD_REG_OFFSET)	? RX_FIFO_THRESHOLD_REG :
			(adr_i[16-1:0] == RX_FIFO_FLUSH_REG_OFFSET)	? RX_FIFO_FLUSH_REG :
			(adr_i[16-1:0] == TX_FIFO_LEVEL_REG_OFFSET)	? TX_FIFO_LEVEL_WIRE :
			(adr_i[16-1:0] == TX_FIFO_THRESHOLD_REG_OFFSET)	? TX_FIFO_THRESHOLD_REG :
			(adr_i[16-1:0] == TX_FIFO_FLUSH_REG_OFFSET)	? TX_FIFO_FLUSH_REG :
			(adr_i[16-1:0] == IM_REG_OFFSET)	? IM_REG :
			(adr_i[16-1:0] == MIS_REG_OFFSET)	? MIS_REG :
			(adr_i[16-1:0] == RIS_REG_OFFSET)	? RIS_REG :
			(adr_i[16-1:0] == IC_REG_OFFSET)	? IC_REG :
			32'hDEADBEEF;

  always @(posedge clk_i or posedge rst_i)
    if (rst_i) ack_o <= 1'b0;
    else if (wb_valid & ~ack_o) ack_o <= 1'b1;
    else ack_o <= 1'b0;
  assign RXDATA_WIRE = datao;
  assign rd = ack_o & (wb_re & (adr_i[16-1:0] == RXDATA_REG_OFFSET));
  assign datai = dat_i;
  assign wr = ack_o & (wb_we & (adr_i[16-1:0] == TXDATA_REG_OFFSET));
endmodule

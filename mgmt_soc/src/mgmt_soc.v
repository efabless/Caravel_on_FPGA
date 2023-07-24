/*
 *  SPDX-FileCopyrightText: 2015 Clifford Wolf
 *  PicoSoC - A simple example SoC using PicoRV32
 *
 *  Copyright (C) 2017  Clifford Wolf <clifford@clifford.at>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *  Revision 1,  July 2019:  Added signals to drive flash_clk and flash_csb
 *  output enable (inverted), tied to reset so that the flash is completely
 *  isolated from the processor when the processor is in reset.
 *
 *  Also: Made ram_wenb a 4-bit bus so that the memory access can be made
 *  byte-wide for byte-wide instructions.
 *
 *  SPDX-License-Identifier: ISC
 */


`default_nettype none
	

module mgmt_soc (
`ifdef USE_POWER_PINS
    inout VPWR,	    /* 1.8V domain */
    inout VGND,
`endif
    // Clock and reset
    input wire fpga_clk,
    input wire RSTB,

    // GPIO (one pin)
    inout wire gpio_inout_pad,	// Connect to gpio pad


    // Flash memory control (SPI master)
    output wire flash_csb,
    output wire flash_clk,

    inout wire flash_io0_dio,
    inout wire flash_io1_dio,
    inout wire flash_io2_dio,
    inout wire flash_io3_dio,

    // Module status
    output wire qspi_enabled,
    output wire uart_enabled,
    output wire spi_enabled,
    output wire debug_mode,

    // Module I/O
    output wire ser_tx,
    input  wire ser_rx,
    output wire tx_out,
    output wire rx_out,
    output wire spi_csb,
    output wire spi_sck,
    output wire spi_sdo,
    output wire spi_sdoenb,
    input  wire spi_sdi,
    input  wire debug_in,
    output wire debug_out,
    output wire debug_oeb,

    // Trap state from CPU
    output wire trap
);
    assign tx_out = ser_tx;
    assign rx_out = ser_rx;
    //assign debug_out = debug_in;

    wire gpio_out_pad;	// Connect to out on gpio pad
    wire  gpio_in_pad;		// Connect to in on gpio pad
    wire gpio_mode0_pad;	// Connect to dm[0] on gpio pad
    wire gpio_mode1_pad;	// Connect to dm[2] on gpio pad
    wire gpio_outenb_pad;	// Connect to oe_n on gpio pad
    wire gpio_inenb_pad;	// Connect to inp_dis on gpio pad

    wire flash_io0_do;
    wire flash_io1_do;
    wire flash_io2_do;
    wire flash_io3_do;

    wire flash_io0_di;
    wire flash_io1_di;
    wire flash_io2_di;
    wire flash_io3_di;

    wire flash_io0_oeb;
    wire flash_io1_oeb;
    wire flash_io2_oeb;
    wire flash_io3_oeb; 

    wire core_clk_10MHz;

    //clk_wiz_12_to_40 clk_wiz_12_to_40MHz (.clk_out1(core_clk_40MHz), .reset(RSTB), .locked(), .clk_in1(fpga_clk));
    //clk_wiz_100_to_40 clk_wiz_100_to_40MHz (.clk_out1(core_clk_40MHz), .reset(RSTB), .locked(), .clk_in1(fpga_clk));
    //clk_wiz_12_to_10 clk_wiz_12_to_10MHz (.clk_out1(core_clk_10MHz), .reset(RSTB), .locked(), .clk_in1(fpga_clk));


    wire core_rst;
    wire core_rstn;
    reset_sync rst_sync (.clk(fpga_clk), .rst_n(RSTB), .rst_sync_n(core_rst));
    assign core_rstn = ~core_rst;


    io_buf #(
        .WIDTH(1)
    ) gpio_bidir (
        .dio_buf(gpio_inout_pad),
        .din_i(gpio_out_pad),
        .dout_o(gpio_in_pad),
        .in_not_out_i(gpio_inenb_pad)
    );

    io_buf #(
        .WIDTH(1)
    ) flash_bidir_0 (
        .dio_buf(flash_io0_dio),
        .din_i(flash_io0_do),
        .dout_o(flash_io0_di),
        .in_not_out_i(flash_io0_oeb)
    );

    io_buf #(
        .WIDTH(1)
    ) flash_bidir_1 (
        .dio_buf(flash_io1_dio),
        .din_i(flash_io1_do),
        .dout_o(flash_io1_di),
        .in_not_out_i(flash_io1_oeb)
    );

    io_buf #(
        .WIDTH(1)
    ) flash_bidir_2 (
        .dio_buf(flash_io2_dio),
        .din_i(flash_io2_do),
        .dout_o(flash_io2_di),
        .in_not_out_i(flash_io2_oeb)
    );

    io_buf #(
        .WIDTH(1)
    ) flash_bidir_3 (
        .dio_buf(flash_io3_dio),
        .din_i(flash_io3_do),
        .dout_o(flash_io3_di),
        .in_not_out_i(flash_io3_oeb)
    );

mgmt_core_wrapper soc (
	`ifdef USE_POWER_PINS
		.VPWR		  (VDD1V8),
		.VGND		  (VSS),
	`endif
		//.core_clk(core_clk_10MHz),
		.core_clk(fpga_clk),
    	.core_rstn(core_rstn),
        //.core_rstn(RSTB),

    	.gpio_out_pad(gpio_out_pad),		
    	.gpio_in_pad(gpio_in_pad),		
    	.gpio_mode0_pad(gpio_mode0_pad),	
    	.gpio_mode1_pad(gpio_mode1_pad),	
    	.gpio_outenb_pad(gpio_outenb_pad),	
    	.gpio_inenb_pad(gpio_inenb_pad),

		.la_input(128'b0),			
        .la_output(),			
        .la_oenb(),			
        .la_iena(),

		.flash_csb(flash_csb),
        .flash_clk(flash_clk),

        .flash_io0_oeb(flash_io0_oeb),
        .flash_io1_oeb(flash_io1_oeb),
        .flash_io2_oeb(flash_io2_oeb),
        .flash_io3_oeb(flash_io3_oeb),

        .flash_io0_do(flash_io0_do),
        .flash_io1_do(flash_io1_do),
        .flash_io2_do(flash_io2_do),
        .flash_io3_do(flash_io3_do),

        .flash_io0_di(flash_io0_di),
        .flash_io1_di(flash_io1_di),
        .flash_io2_di(flash_io2_di),
        .flash_io3_di(flash_io3_di),

        .mprj_wb_iena(),
        .mprj_ack_i(1'b0),
        .mprj_dat_i(32'b0),
        .mprj_cyc_o(),
        .mprj_stb_o(),
        .mprj_we_o(),
        .mprj_sel_o(),
        .mprj_adr_o(),
        .mprj_dat_o(),

        .hk_cyc_o(),
        .hk_stb_o(),
        .hk_dat_i(32'b0),
		.hk_ack_i(1'b0),

        .irq(6'b0),
        .user_irq_ena(),

        .qspi_enabled(qspi_enabled),
        .uart_enabled(uart_enabled),
        .spi_enabled(spi_enabled),
        .debug_mode(debug_mode),

		.ser_tx(ser_tx),
    	.ser_rx(ser_rx),
    	.spi_csb(spi_csb),
    	.spi_sck(spi_sck),
    	.spi_sdo(spi_sdo),
    	.spi_sdoenb(spi_sdoenb),
    	.spi_sdi(1'b0),
        .debug_in(debug_in),
        //.debug_in(1'b1),
    	.debug_out(debug_out),
    	.debug_oeb(debug_oeb),

        /*.sram_ro_csb(),
        .sram_ro_clk(),
        .sram_ro_addr(8'b0),
        .sram_ro_data(),*/

        .trap(trap)        
	);
    

endmodule
`default_nettype wire

module io_buf #(parameter WIDTH=1) (
    inout  wire [WIDTH-1:0] dio_buf,
    input  wire [WIDTH-1:0] din_i,
    output wire [WIDTH-1:0] dout_o,
    input  wire [WIDTH-1:0] in_not_out_i         // high: input, low: output
);

//`ifdef USE_IO_BUF_BEH
    assign dout_o  = dio_buf;
    generate
        genvar i;
        for (i=0; i<WIDTH; i=i+1)
        begin
            assign dio_buf[i] = in_not_out_i[i] ? 1'bz : din_i[i];
        end
    endgenerate
/*`else
    IOBUF io_data [WIDTH-1:0] (
        .O (dout_o),        // data from the pad to the fabric
        .IO(dio_buf),       // connects to the pad
        .I (din_i),         // data from the fabric to tha pad
        .T (in_not_out_i)   // when 1 puts the IO pin in tri-state
    );
`endif*/
endmodule
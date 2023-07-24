`include "defines.v"
`define FPGA

`ifndef FPGA
`default_nettype none
`else
`default_nettype wire
`endif

module chip_io_FPGA(
`ifndef FPGA
	// Package Pins
	inout  wire vddio_pad,		// Common padframe/ESD supply
	inout  wire vddio_pad2,
	inout  wire vssio_pad,		// Common padframe/ESD ground
	inout  wire vssio_pad2,
	inout  wire vccd_pad,		// Common 1.8V supply
	inout  wire vssd_pad,		// Common digital ground
	inout  wire vdda_pad,		// Management analog 3.3V supply
	inout  wire vssa_pad,		// Management analog ground
	inout  wire vdda1_pad,		// User area 1 3.3V supply
	inout  wire vdda1_pad2,		
	inout  wire vdda2_pad,		// User area 2 3.3V supply
	inout  wire vssa1_pad,		// User area 1 analog ground
	inout  wire vssa1_pad2,
	inout  wire vssa2_pad,		// User area 2 analog ground
	inout  wire vccd1_pad,		// User area 1 1.8V supply
	inout  wire vccd2_pad,		// User area 2 1.8V supply
	inout  wire vssd1_pad,		// User area 1 digital ground
	inout  wire vssd2_pad,		// User area 2 digital ground

	// Core Side
	inout  wire vddio,		// Common padframe/ESD supply
	inout  wire vssio,		// Common padframe/ESD ground
	inout  wire vccd,		// Common 1.8V supply
	inout  wire vssd,		// Common digital ground
	inout  wire vdda,		// Management analog 3.3V supply
	inout  wire vssa,		// Management analog ground
	inout  wire vdda1,		// User area 1 3.3V supply
	inout  wire vdda2,		// User area 2 3.3V supply
	inout  wire vssa1,		// User area 1 analog ground
	inout  wire vssa2,		// User area 2 analog ground
	inout  wire vccd1,		// User area 1 1.8V supply
	inout  wire vccd2,		// User area 2 1.8V supply
	inout  wire vssd1,		// User area 1 digital ground
	inout  wire vssd2,		// User area 2 digital ground
`endif 

	inout  wire gpio,
	input  wire clock,
	input  wire resetb,
	output wire flash_csb,
	output wire flash_clk,
	inout  wire flash_io0,
	inout  wire flash_io1,

	// Chip Core Interface
	input  wire porb_h,
	input  wire por,
	output wire resetb_core_h,
	output wire clock_core,
	input  wire gpio_out_core,  //
	output wire gpio_in_core,   //
	input  wire gpio_mode0_core,
	input  wire gpio_mode1_core,
	input  wire gpio_outenb_core,   
	input  wire gpio_inenb_core,    //
	input  wire flash_csb_core,     //
	input  wire flash_clk_core,     //
	input  wire flash_csb_oeb_core,
	input  wire flash_clk_oeb_core,
	input  wire flash_io0_oeb_core,     //
	input  wire flash_io1_oeb_core,     //
	input  wire flash_csb_ieb_core,	// NOTE: unused, fix me!
	input  wire flash_clk_ieb_core,	// NOTE: unused, fix me!
	input  wire flash_io0_ieb_core,
	input  wire flash_io1_ieb_core,
	input  wire flash_io0_do_core,      //
	input  wire flash_io1_do_core,      //
	output wire flash_io0_di_core,      //
	output wire flash_io1_di_core,      //
	// User project IOs
	inout wire [`MPRJ_IO_PADS-1:0]  mprj_io,       //
	input wire [`MPRJ_IO_PADS-1:0]  mprj_io_out,   //
	input wire [`MPRJ_IO_PADS-1:0]  mprj_io_oeb,   //
	input wire [`MPRJ_IO_PADS-1:0]  mprj_io_inp_dis,
	input wire [`MPRJ_IO_PADS-1:0]  mprj_io_ib_mode_sel,
	input wire [`MPRJ_IO_PADS-1:0]  mprj_io_vtrip_sel,
	input wire [`MPRJ_IO_PADS-1:0]  mprj_io_slow_sel,
	input wire [`MPRJ_IO_PADS-1:0]  mprj_io_holdover,
	input wire [`MPRJ_IO_PADS-1:0]  mprj_io_analog_en,
	input wire [`MPRJ_IO_PADS-1:0]  mprj_io_analog_sel,
	input wire [`MPRJ_IO_PADS-1:0]  mprj_io_analog_pol,
	input wire [`MPRJ_IO_PADS*3-1:0]  mprj_io_dm,
	output wire [`MPRJ_IO_PADS-1:0]  mprj_io_in,    //
	// User project direct access to gpio pad connections for analog
	// (all but the lowest-numbered 7 pads)
	inout wire [`MPRJ_IO_PADS-10:0]  mprj_analog_io
);

assign resetb_core_h = resetb;
assign clock_core = clock;

io_buf #(
        .WIDTH(1)
    ) gpio_bidir (
        .dio_buf(gpio),
        .din_i(gpio_out_core),
        .dout_o(gpio_in_core),
        .in_not_out_i(gpio_inenb_core)
    );

assign flash_csb = flash_csb_core;
assign flash_clk = flash_clk_core;

    io_buf #(
        .WIDTH(1)
    ) flash_bidir_0 (
        .dio_buf(flash_io0),
        .din_i(flash_io0_do_core),
        .dout_o(flash_io0_di_core),
        .in_not_out_i(flash_io0_oeb_core)
    );

    io_buf #(
        .WIDTH(1)
    ) flash_bidir_1 (
        .dio_buf(flash_io1),
        .din_i(flash_io1_do_core),
        .dout_o(flash_io1_di_core),
        .in_not_out_i(flash_io1_oeb_core)
    );

	 io_buf #(
        .WIDTH(38)
    ) mprj_ios_2 (
        .dio_buf(mprj_io),
        .din_i(mprj_io_out),
        .dout_o(mprj_io_in),
        .in_not_out_i(mprj_io_oeb)
    );



endmodule

`default_nettype wire
`define USE_IO_BUF_BEH
`default_nettype none
`timescale 1ns/1ns

module gpio_bidir #(parameter WIDTH=1) (
    inout  wire [WIDTH-1:0] dio_buf,
    input  wire [WIDTH-1:0] din_i,
    output wire [WIDTH-1:0] dout_o,
    input  wire [WIDTH-1:0] in_not_out_i         // high: input, low: output
);

`ifdef USE_IO_BUF_BEH
    assign dout_o  = dio_buf;
    generate
        genvar i;
        for (i=0; i<WIDTH; i=i+1)
            assign dio_buf[i] = in_not_out_i[i] ? 1'bz : din_i[i];
    endgenerate
`else
    IOBUF io_data [WIDTH-1:0] (
        .O (dout_o),        // data from the pad to the fabric
        .IO(dio_buf),       // connects to the pad
        .I (din_i),         // data from the fabric to tha pad
        .T (in_not_out_i)   // when 1 puts the IO pin in tri-state
    );
`endif
endmodule

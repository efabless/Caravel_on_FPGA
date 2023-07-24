`default_nettype wire

module io_buf (
    inout io,
    input o,
    output i,
    input oe,
    input ie
);

    assign io = oe ? o : 'bz;
    assign i = ie ? io : 'b0;

endmodule
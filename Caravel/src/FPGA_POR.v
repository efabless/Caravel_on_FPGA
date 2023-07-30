`timescale 1ns / 1ps
module FPGA_POR(
    input wire clk,
    output wire por
    );
    reg   [7:0]  reset_vec = 8'hff;
    reg   reset;

    // 8 clock cycles of active-high reset.
    always @(posedge clk) begin
        reset_vec       <= { reset_vec[6:0], 1'b0 };     
    end

    always @(posedge clk) begin
        reset       <= reset_vec[7];
    end

    assign por = reset;
endmodule
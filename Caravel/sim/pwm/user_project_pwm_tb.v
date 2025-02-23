`timescale 1ns / 1ps
`default_nettype none

module user_project_tb;

    // Parameters
    parameter BITS = 32;
    parameter CLK_PERIOD = 100;  // 

    // Signals for the DUT (Device Under Test)
    reg wb_clk_i;
    reg wb_rst_i;
    reg wbs_stb_i;
    reg wbs_cyc_i;
    reg wbs_we_i;
    reg [BITS-1:0] wbs_adr_i;
    reg [BITS-1:0] wbs_dat_i;
    reg [3:0] wbs_sel_i;
    wire wbs_ack_o;
    wire [BITS-1:0] wbs_dat_o;
    wire wbs_err_o;

    wire [37:0] io_out;
    wire [37:0] io_oeb;

    // Instantiate the DUT
    user_project_wrapper dut (
        .wb_clk_i(wb_clk_i),
        .wb_rst_i(wb_rst_i),
        .wbs_stb_i(wbs_stb_i),
        .wbs_cyc_i(wbs_cyc_i),
        .wbs_we_i(wbs_we_i),
        .wbs_adr_i(wbs_adr_i),
        .wbs_dat_i(wbs_dat_i),
        .wbs_sel_i(wbs_sel_i),
        .wbs_ack_o(wbs_ack_o),
        .wbs_dat_o(wbs_dat_o),
        .wbs_err_o(wbs_err_o),
        .io_out(io_out),
        .io_oeb(io_oeb)
    );

    // Clock generation
    initial begin
        wb_clk_i = 0;
        forever #(CLK_PERIOD / 2) wb_clk_i = ~wb_clk_i;
    end

    // Task: Wishbone Write Operation
    task wb_write;
        input [BITS-1:0] addr;
        input [BITS-1:0] data;
        begin
            @(posedge wb_clk_i);
            wbs_adr_i = addr;
            wbs_dat_i = data;
            wbs_we_i = 1;
            wbs_stb_i = 1;
            wbs_cyc_i = 1;
            wbs_sel_i = 4'b1111; // Full-word write
            @(posedge wb_clk_i);
            while (!wbs_ack_o) @(posedge wb_clk_i);  // Wait for acknowledgment
            wbs_stb_i = 0;
            wbs_cyc_i = 0;
            wbs_we_i = 0;
        end
    endtask

    // Task: Reset the DUT
    task reset_dut;
        begin
            wb_rst_i = 1;
            #999
            @(posedge wb_clk_i);
            wb_rst_i = 0;
        end
    endtask

    // Test sequence
    initial begin
        // Initial values
        wbs_stb_i = 0;
        wbs_cyc_i = 0;
        wbs_we_i = 0;
        wbs_adr_i = 0;
        wbs_dat_i = 0;
        wbs_sel_i = 0;

        // Reset the DUT
        reset_dut();

        // Configure PWM peripherals:
        // Each PWM will have a different period and duty cycle
        // Assuming:
        // - Address offset 0x00 -> Control register (enable)
        // - Address offset 0x04 -> Period register
        // - Address offset 0x08 -> Duty cycle register

        // PWM 0: 50% duty cycle, 1000 period
        wb_write(32'h3000_0000 + 32'h14, 4'b00_00);                       // Disable Timer
        wb_write(32'h3000_0000 + 32'h04, 32'd10);                         // Reload
        wb_write(32'h3000_0000 + 32'h08, 32'd1);                          // Set prescale
        wb_write(32'h3000_0000 + 32'h18, 3'b1_11);                        // Set Cfg
        wb_write(32'h3000_0000 + 32'h0c, 3'd5);                           // Cmpx
        wb_write(32'h3000_0000 + 32'h10, 3'd5);                           // Cmpy
        wb_write(32'h3000_0000 + 32'h1c, 12'b11_00_11_00_11_11);          // pwm0cfg
        //wb_write(32'h3000_0000 + 32'h1c, 12'b01_00_10_00_01_10);          // pwm0cfg
        wb_write(32'h3000_0000 + 32'h20, 12'b01_11_11_11_11_01);          // pwm1cfg
        wb_write(32'h3000_0000 + 32'h14, 4'b11_01);                       // Ctrl - Enable PWM

        // PWM 1: 25% duty cycle, 2000 period
        wb_write(32'h3000_1000 + 32'h04, 32'd2000);
        wb_write(32'h3000_1000 + 32'h08, 32'd500);
        wb_write(32'h3000_1000 + 32'h0e, 32'b11_01);
        wb_write(32'h3000_1000 + 32'h0e, 32'b11_01);

        // PWM 2: 75% duty cycle, 500 period
        wb_write(32'h3000_2000 + 32'h04, 32'd500);
        wb_write(32'h3000_2000 + 32'h08, 32'd375);
        wb_write(32'h3000_2000 + 32'h0e, 32'hc);

        // PWM 3: 10% duty cycle, 4000 period
        wb_write(32'h3000_3000 + 32'h04, 32'd4000);
        wb_write(32'h3000_3000 + 32'h08, 32'd400);
        wb_write(32'h3000_3000 + 32'h0e, 32'hc);

        // Run simulation for some time
        #25_000;  // Let the PWM signals run for some time

        // Finish simulation
        $display("Simulation complete.");
        $finish;
    end

    // Monitor PWM Outputs
    initial begin
        $dumpfile("user_project_tb.vcd");
		$dumpvars(0, user_project_tb);
        $monitor("Time = %0t | PWM0 = %b | PWM1 = %b | PWM2 = %b | PWM3 = %b",
                 $time, io_out[0], io_out[1], io_out[2], io_out[3]);
    end

endmodule
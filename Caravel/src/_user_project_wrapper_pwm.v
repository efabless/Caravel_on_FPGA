`include "defines.v"
`default_nettype wire

module user_project_wrapper #(
    parameter BITS = 32
)(
    // Wishbone Slave Ports (Caravel <-> User Project)
    input  wire                      wb_clk_i,
    input  wire                      wb_rst_i,
    input  wire                      wbs_stb_i,
    input  wire                      wbs_cyc_i,
    input  wire                      wbs_we_i,
    input  wire [BITS-1:0]           wbs_adr_i,
    input  wire [BITS-1:0]           wbs_dat_i,
    input  wire [3:0]                wbs_sel_i,
    output wire                      wbs_ack_o,
    output wire [BITS-1:0]           wbs_dat_o,
    output wire                      wbs_err_o,

    // Logic Analyzer Signals
    input  wire [127:0]              la_data_in,
    output wire [127:0]              la_data_out,
    input  wire [127:0]              la_oenb,

    // IOs
    inout  wire [37:0]               io_in,
    inout  wire [37:0]               io_out,
    inout  wire [37:0]               io_oeb,

    // Analog (not used in this example)
    inout  wire [27:0]               analog_io,

    // Independent clock (not used in this example)
    input  wire                      user_clock2,

    // User maskable interrupt signals
    output wire [2:0]                user_irq
);

    // Internal signals for Wishbone bus splitter
    wire [BITS-1:0] s_wb_adr_0, s_wb_adr_1, s_wb_adr_2, s_wb_adr_3;
    wire [BITS-1:0] s_wb_dat_w_0, s_wb_dat_w_1, s_wb_dat_w_2, s_wb_dat_w_3;
    wire [BITS-1:0] s_wb_dat_r_0, s_wb_dat_r_1, s_wb_dat_r_2, s_wb_dat_r_3;
    wire s_wb_cyc_0, s_wb_cyc_1, s_wb_cyc_2, s_wb_cyc_3;
    wire s_wb_stb_0, s_wb_stb_1, s_wb_stb_2, s_wb_stb_3;
    wire s_wb_we_0, s_wb_we_1, s_wb_we_2, s_wb_we_3;
    wire [3:0] s_wb_sel_0, s_wb_sel_1, s_wb_sel_2, s_wb_sel_3;
    wire s_wb_ack_0, s_wb_ack_1, s_wb_ack_2, s_wb_ack_3;
    wire s_wb_err_0, s_wb_err_1, s_wb_err_2, s_wb_err_3;

    // IRQ signals from each PWM module
    wire irq_0, irq_1, irq_2, irq_3;

    // PWM Outputs
    wire pwm0_0, pwm1_0, pwm0_1, pwm1_1, pwm0_2, pwm1_2, pwm0_3, pwm1_3;

    // PWM Fault Inputs (can be driven externally or tied to logic)
    wire pwm_fault_0 = 1'b0;
    wire pwm_fault_1 = 1'b0;
    wire pwm_fault_2 = 1'b0;
    wire pwm_fault_3 = 1'b0;

    // Define Base Addresses for EF_TMR32
    localparam [BITS-1:0] BASE_ADDR_0 = 32'h3000_0000;  // PWM 0
    localparam [BITS-1:0] BASE_ADDR_1 = 32'h3000_1000;  // PWM 1
    localparam [BITS-1:0] BASE_ADDR_2 = 32'h3000_2000;  // PWM 2
    localparam [BITS-1:0] BASE_ADDR_3 = 32'h3000_3000;  // PWM 3

    localparam [BITS-1:0] ADDR_MASK = 32'hFFFF_F000;    // Mask for 4KB regions

    // Wishbone Bus Splitter Instance
    wishbone_bus_splitter bus_splitter_inst (
        .clk(wb_clk_i),
        .rst(wb_rst_i),
        .m_wb_adr(wbs_adr_i),
        .m_wb_dat_w(wbs_dat_i),
        .m_wb_dat_r(wbs_dat_o),
        .m_wb_we(wbs_we_i),
        .m_wb_sel(wbs_sel_i),
        .m_wb_cyc(wbs_cyc_i),
        .m_wb_stb(wbs_stb_i),
        .m_wb_ack(wbs_ack_o),
        .m_wb_err(wbs_err_o),
        .s_wb_adr_0(s_wb_adr_0),
        .s_wb_dat_w_0(s_wb_dat_w_0),
        .s_wb_dat_r_0(s_wb_dat_r_0),
        .s_wb_we_0(s_wb_we_0),
        .s_wb_sel_0(s_wb_sel_0),
        .s_wb_cyc_0(s_wb_cyc_0),
        .s_wb_stb_0(s_wb_stb_0),
        .s_wb_ack_0(s_wb_ack_0),
        .s_wb_err_0(s_wb_err_0),
        .s_wb_adr_1(s_wb_adr_1),
        .s_wb_dat_w_1(s_wb_dat_w_1),
        .s_wb_dat_r_1(s_wb_dat_r_1),
        .s_wb_we_1(s_wb_we_1),
        .s_wb_sel_1(s_wb_sel_1),
        .s_wb_cyc_1(s_wb_cyc_1),
        .s_wb_stb_1(s_wb_stb_1),
        .s_wb_ack_1(s_wb_ack_1),
        .s_wb_err_1(s_wb_err_1),
        .s_wb_adr_2(s_wb_adr_2),
        .s_wb_dat_w_2(s_wb_dat_w_2),
        .s_wb_dat_r_2(s_wb_dat_r_2),
        .s_wb_we_2(s_wb_we_2),
        .s_wb_sel_2(s_wb_sel_2),
        .s_wb_cyc_2(s_wb_cyc_2),
        .s_wb_stb_2(s_wb_stb_2),
        .s_wb_ack_2(s_wb_ack_2),
        .s_wb_err_2(s_wb_err_2),
        .s_wb_adr_3(s_wb_adr_3),
        .s_wb_dat_w_3(s_wb_dat_w_3),
        .s_wb_dat_r_3(s_wb_dat_r_3),
        .s_wb_we_3(s_wb_we_3),
        .s_wb_sel_3(s_wb_sel_3),
        .s_wb_cyc_3(s_wb_cyc_3),
        .s_wb_stb_3(s_wb_stb_3),
        .s_wb_ack_3(s_wb_ack_3),
        .s_wb_err_3(s_wb_err_3)
    );

    // PWM Peripheral Instances (EF_TMR32_WB)
    EF_TMR32_WB pwm_timer_0 (
        .clk_i(wb_clk_i),
        .rst_i(wb_rst_i),
        .adr_i(s_wb_adr_0),
        .dat_i(s_wb_dat_w_0),
        .dat_o(s_wb_dat_r_0),
        .sel_i(s_wb_sel_0),
        .cyc_i(s_wb_cyc_0),
        .stb_i(s_wb_stb_0),
        .ack_o(s_wb_ack_0),
        .we_i(s_wb_we_0),
        .IRQ(irq_0),
        .pwm0(pwm0_0),
        .pwm1(pwm1_0),
        .pwm_fault(pwm_fault_0)
    );

    EF_TMR32_WB pwm_timer_1 (
        .clk_i(wb_clk_i),
        .rst_i(wb_rst_i),
        .adr_i(s_wb_adr_1),
        .dat_i(s_wb_dat_w_1),
        .dat_o(s_wb_dat_r_1),
        .sel_i(s_wb_sel_1),
        .cyc_i(s_wb_cyc_1),
        .stb_i(s_wb_stb_1),
        .ack_o(s_wb_ack_1),
        .we_i(s_wb_we_1),
        .IRQ(irq_1),
        .pwm0(pwm0_1),
        .pwm1(pwm1_1),
        .pwm_fault(pwm_fault_1)
    );

    EF_TMR32_WB pwm_timer_2 (
        .clk_i(wb_clk_i),
        .rst_i(wb_rst_i),
        .adr_i(s_wb_adr_2),
        .dat_i(s_wb_dat_w_2),
        .dat_o(s_wb_dat_r_2),
        .sel_i(s_wb_sel_2),
        .cyc_i(s_wb_cyc_2),
        .stb_i(s_wb_stb_2),
        .ack_o(s_wb_ack_2),
        .we_i(s_wb_we_2),
        .IRQ(irq_2),
        .pwm0(pwm0_2),
        .pwm1(pwm1_2),
        .pwm_fault(pwm_fault_2)
    );

    EF_TMR32_WB pwm_timer_3 (
        .clk_i(wb_clk_i),
        .rst_i(wb_rst_i),
        .adr_i(s_wb_adr_3),
        .dat_i(s_wb_dat_w_3),
        .dat_o(s_wb_dat_r_3),
        .sel_i(s_wb_sel_3),
        .cyc_i(s_wb_cyc_3),
        .stb_i(s_wb_stb_3),
        .ack_o(s_wb_ack_3),
        .we_i(s_wb_we_3),
        .IRQ(irq_3),
        .pwm0(pwm0_3),
        .pwm1(pwm1_3),
        .pwm_fault(pwm_fault_3)
    );

    // Assign PWM outputs to IO pins (First four GPIOs)
    assign io_out[0] = pwm0_0;
    assign io_out[1] = pwm1_0;
    assign io_out[2] = pwm0_1;
    assign io_out[3] = pwm1_1;
    assign io_out[4] = pwm0_2;
    assign io_out[5] = pwm1_2;
    assign io_out[6] = pwm0_3;
    assign io_out[7] = pwm1_3;

    // Configure GPIOs as outputs
    assign io_oeb[7:0] = 8'b0; // Enable outputs for first 8 pins

    // Combine IRQs from all PWM modules
    assign user_irq[0] = irq_0;
    assign user_irq[1] = irq_1;
    assign user_irq[2] = irq_2;

endmodule
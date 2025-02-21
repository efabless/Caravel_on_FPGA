`default_nettype none

module wishbone_bus_splitter #(
    parameter ADDR_WIDTH = 32,
    parameter DATA_WIDTH = 32,
    parameter SEL_WIDTH = DATA_WIDTH / 8,

    // Base Addresses and Address Masks for 4 peripherals
    parameter [ADDR_WIDTH-1:0] BASE_ADDR_0 = 32'h3000_0000,
    parameter [ADDR_WIDTH-1:0] BASE_ADDR_1 = 32'h3000_1000,
    parameter [ADDR_WIDTH-1:0] BASE_ADDR_2 = 32'h3000_2000,
    parameter [ADDR_WIDTH-1:0] BASE_ADDR_3 = 32'h3000_3000,
    parameter [ADDR_WIDTH-1:0] ADDR_MASK   = 32'hFFFF_F000
)(
    input  wire                      clk,
    input  wire                      rst,

    // Master Wishbone Interface
    input  wire [ADDR_WIDTH-1:0]     m_wb_adr,
    input  wire [DATA_WIDTH-1:0]     m_wb_dat_w,
    output reg  [DATA_WIDTH-1:0]     m_wb_dat_r,
    input  wire                      m_wb_we,
    input  wire [SEL_WIDTH-1:0]      m_wb_sel,
    input  wire                      m_wb_cyc,
    input  wire                      m_wb_stb,
    output reg                       m_wb_ack,
    output reg                       m_wb_err,

    // Slave Wishbone Interface for Peripheral 0
    output reg  [ADDR_WIDTH-1:0]     s_wb_adr_0,
    output reg  [DATA_WIDTH-1:0]     s_wb_dat_w_0,
    input  wire [DATA_WIDTH-1:0]     s_wb_dat_r_0,
    output reg                       s_wb_we_0,
    output reg  [SEL_WIDTH-1:0]      s_wb_sel_0,
    output reg                       s_wb_cyc_0,
    output reg                       s_wb_stb_0,
    input  wire                      s_wb_ack_0,
    input  wire                      s_wb_err_0,

    // Slave Wishbone Interface for Peripheral 1
    output reg  [ADDR_WIDTH-1:0]     s_wb_adr_1,
    output reg  [DATA_WIDTH-1:0]     s_wb_dat_w_1,
    input  wire [DATA_WIDTH-1:0]     s_wb_dat_r_1,
    output reg                       s_wb_we_1,
    output reg  [SEL_WIDTH-1:0]      s_wb_sel_1,
    output reg                       s_wb_cyc_1,
    output reg                       s_wb_stb_1,
    input  wire                      s_wb_ack_1,
    input  wire                      s_wb_err_1,

    // Slave Wishbone Interface for Peripheral 2
    output reg  [ADDR_WIDTH-1:0]     s_wb_adr_2,
    output reg  [DATA_WIDTH-1:0]     s_wb_dat_w_2,
    input  wire [DATA_WIDTH-1:0]     s_wb_dat_r_2,
    output reg                       s_wb_we_2,
    output reg  [SEL_WIDTH-1:0]      s_wb_sel_2,
    output reg                       s_wb_cyc_2,
    output reg                       s_wb_stb_2,
    input  wire                      s_wb_ack_2,
    input  wire                      s_wb_err_2,

    // Slave Wishbone Interface for Peripheral 3
    output reg  [ADDR_WIDTH-1:0]     s_wb_adr_3,
    output reg  [DATA_WIDTH-1:0]     s_wb_dat_w_3,
    input  wire [DATA_WIDTH-1:0]     s_wb_dat_r_3,
    output reg                       s_wb_we_3,
    output reg  [SEL_WIDTH-1:0]      s_wb_sel_3,
    output reg                       s_wb_cyc_3,
    output reg                       s_wb_stb_3,
    input  wire                      s_wb_ack_3,
    input  wire                      s_wb_err_3
);

    // Internal signal to track selected peripheral
    reg [1:0] selected;

    // Address Decoder (Select which peripheral based on address range)
    always @(*) begin
        if ((m_wb_adr & ADDR_MASK) == BASE_ADDR_0)
            selected = 2'b00;
        else if ((m_wb_adr & ADDR_MASK) == BASE_ADDR_1)
            selected = 2'b01;
        else if ((m_wb_adr & ADDR_MASK) == BASE_ADDR_2)
            selected = 2'b10;
        else if ((m_wb_adr & ADDR_MASK) == BASE_ADDR_3)
            selected = 2'b11;
        else
            selected = 2'bxx;  // Invalid address
    end

    // Bus Multiplexing Logic
    always @(*) begin
        // Default assignments
        m_wb_dat_r = 0;
        m_wb_ack = 0;
        m_wb_err = 0;

        s_wb_cyc_0 = 0; s_wb_stb_0 = 0; s_wb_adr_0 = 0; s_wb_dat_w_0 = 0; s_wb_we_0 = 0; s_wb_sel_0 = 0;
        s_wb_cyc_1 = 0; s_wb_stb_1 = 0; s_wb_adr_1 = 0; s_wb_dat_w_1 = 0; s_wb_we_1 = 0; s_wb_sel_1 = 0;
        s_wb_cyc_2 = 0; s_wb_stb_2 = 0; s_wb_adr_2 = 0; s_wb_dat_w_2 = 0; s_wb_we_2 = 0; s_wb_sel_2 = 0;
        s_wb_cyc_3 = 0; s_wb_stb_3 = 0; s_wb_adr_3 = 0; s_wb_dat_w_3 = 0; s_wb_we_3 = 0; s_wb_sel_3 = 0;

        case (selected)
            2'b00: begin
                s_wb_cyc_0 = m_wb_cyc;
                s_wb_stb_0 = m_wb_stb;
                s_wb_adr_0 = m_wb_adr;
                s_wb_dat_w_0 = m_wb_dat_w;
                s_wb_we_0 = m_wb_we;
                s_wb_sel_0 = m_wb_sel;
                m_wb_dat_r = s_wb_dat_r_0;
                m_wb_ack = s_wb_ack_0;
                m_wb_err = s_wb_err_0;
            end
            2'b01: begin
                s_wb_cyc_1 = m_wb_cyc;
                s_wb_stb_1 = m_wb_stb;
                s_wb_adr_1 = m_wb_adr;
                s_wb_dat_w_1 = m_wb_dat_w;
                s_wb_we_1 = m_wb_we;
                s_wb_sel_1 = m_wb_sel;
                m_wb_dat_r = s_wb_dat_r_1;
                m_wb_ack = s_wb_ack_1;
                m_wb_err = s_wb_err_1;
            end
            2'b10: begin
                s_wb_cyc_2 = m_wb_cyc;
                s_wb_stb_2 = m_wb_stb;
                s_wb_adr_2 = m_wb_adr;
                s_wb_dat_w_2 = m_wb_dat_w;
                s_wb_we_2 = m_wb_we;
                s_wb_sel_2 = m_wb_sel;
                m_wb_dat_r = s_wb_dat_r_2;
                m_wb_ack = s_wb_ack_2;
                m_wb_err = s_wb_err_2;
            end
            2'b11: begin
                s_wb_cyc_3 = m_wb_cyc;
                s_wb_stb_3 = m_wb_stb;
                s_wb_adr_3 = m_wb_adr;
                s_wb_dat_w_3 = m_wb_dat_w;
                s_wb_we_3 = m_wb_we;
                s_wb_sel_3 = m_wb_sel;
                m_wb_dat_r = s_wb_dat_r_3;
                m_wb_ack = s_wb_ack_3;
                m_wb_err = s_wb_err_3;
            end
            default: begin
                m_wb_err = 1'b1;  // Trigger error if address is out of range
            end
        endcase
    end

endmodule
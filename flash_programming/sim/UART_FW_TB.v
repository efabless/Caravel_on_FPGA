`timescale 1ns/1ns

`define CLK_PERIOD 83.3333333
`define BITTIME  8000
`define FETCH_FROM_FLASH
`define USE_RESET_BTN
`ifdef USE_RESET_BTN
    `define RESET_DELAY  1000
    `define RESET_VAL    1     // when button is pressed
`else
    `define RESET_DELAY 800
    `define RESET_VAL   0
`endif
module UART_FW_TB;

    localparam  WE_OFF = 32'h00000000,
                SS_OFF = 32'h00000004,
                SCK_OFF= 32'h00000008,
                OE_OFF = 32'h0000000C,
                SO_OFF = 32'h00000010,
                SI_OFF = 32'h00000014,
                ID_OFF = 32'h00000018; 

    reg HCLK, RST;
    reg  TX;
    wire RX;
    
    wire [3:0]      fdio;
    wire          	fsclk;
    wire          	fcen;

    `ifdef FETCH_FROM_FLASH
        // Program Flash 
        sst26wf080b FLASH(
            .SCK(fsclk),
            .SIO(fdio),
            .CEb(fcen)
        );
         defparam FLASH.I0.Tsce = 25_000;
         defparam FLASH.I0.Tpp = 1_000;
    `endif

    uart_flash_writer uart_fw (

        .HCLK(HCLK),
        .RST(RST),

        .UART_MASTER_RX(TX),
        .UART_MASTER_TX(RX),
        
        .fdio(fdio),
        .fsclk(fsclk),
        .fcen(fcen)
    );

    // Clock and Rest Generation
    initial begin
        //Inputs initialization
        HCLK = 0;
        RST = 1'b0;    
        //M_clk =0;    
        #500;
        RST = `RESET_VAL;
        #(`RESET_DELAY)
        @(posedge HCLK);
        RST <= ~(`RESET_VAL);
    end

    always #(`CLK_PERIOD / 2.00) HCLK = ~ HCLK;
    //always #(`BITIME) M_clk = ~ M_clk;


    // Test Case
    reg[31:0] data;
                   
    initial begin               
    TX = 1;
    #2000;
    FW_RD(ID_OFF, data);
    //$finish;
    FW_ENABLE;       
    SPI_OE(4'b0001);
    SPI_STATRT;
    SPI_BYTE_WR(8'hFF);
    SPI_STOP;
    SPI_STATRT;
    SPI_BYTE_WR(8'h9F);
    SPI_BYTE_RD(data);
    $display("JEDEC Byte 0:%x", data);
    SPI_BYTE_RD(data);
    $display("JEDEC Byte 1:%x", data);
    SPI_BYTE_RD(data);
    $display("JEDEC Byte 2:%x", data);
    SPI_STOP;
    #50000;
    $finish;
    end 


    UART_MON MON (.RX(TX));
localparam BITTIME = 8000 ; //baud rate 125000
task UART_SEND (input [7:0] data);
            begin : task_body
                integer i;
                #BITTIME;
                @(posedge HCLK);
                TX = 0;
                #BITTIME;
                for(i=0; i<8; i=i+1) begin
                    TX = data[i];
                    #BITTIME;
                end
                TX = 1;
                //#BITTIME;
            end
        endtask
    
        task UART_REC (output [7:0] data);
            begin : task_body
                integer i;
                @(negedge RX);
                #(BITTIME+(BITTIME/2));
                for(i=0; i<8; i=i+1) begin
                    data[i] = RX;
                    #BITTIME;
                end
            end
        endtask
    
        task FW_WR(input [31:0] A, input [31:0] D);
            begin
                UART_SEND(8'hA3);
                UART_SEND(A[7:0]);
                UART_SEND(A[15:8]);
                UART_SEND(A[23:16]);
                UART_SEND(A[31:24]);
                UART_SEND(D[7:0]);
                UART_SEND(D[15:8]);
                UART_SEND(D[23:16]);
                UART_SEND(D[31:24]);
            end
        endtask
    
        task FW_RD(input [31:0] A, output [31:0] D); //4c000018
            begin
                UART_SEND(8'hA5);
                
                UART_SEND(A[7:0]);
                
                UART_SEND(A[15:8]);
                
                UART_SEND(A[23:16]);
                
                UART_SEND(A[31:24]);
                
                UART_REC(D[7:0]);
                UART_REC(D[15:8]);
                UART_REC(D[23:16]);
                UART_REC(D[31:24]);
            end
        endtask
    
        task SPI_STATRT;
            FW_WR(SS_OFF, 0);
        endtask
    
        task SPI_STOP;
            FW_WR(SS_OFF, 1);
        endtask
    
        task SPI_OE(input [3:0] data);
            FW_WR(OE_OFF, data);
        endtask
    
        task FW_ENABLE;
            FW_WR(WE_OFF,32'hA5A85501);
        endtask
    
        task SPI_BYTE_WR(input [7:0] data);
            begin : task_body
                integer i;
                for(i=7; i>=0; i=i-1) begin
                    FW_WR(SO_OFF, data[i]);
                    FW_WR(SCK_OFF, 1);
                    FW_WR(SCK_OFF, 0);
                end
            end
        endtask
    
        task SPI_WORD_WR(input [32:0] data);
            begin 
                SPI_BYTE_WR(data[7:0]);
                SPI_BYTE_WR(data[15:8]);
                SPI_BYTE_WR(data[23:16]);
                SPI_BYTE_WR(data[31:24]);
            end
        endtask
    
        task SPI_BYTE_RD(output [7:0] data);
            begin : task_body
                integer i;
                reg [31:0] word;
                for(i=7; i>=0; i=i-1) begin
                    FW_WR(SCK_OFF, 1);
                    FW_RD(SI_OFF, word);
                    data[i] = word[0];
                    FW_WR(SCK_OFF, 0);
                end
            end
        endtask
    task FLASH_WEN;
                begin : task_body
                    SPI_OE(4'b0001);
                    SPI_STATRT;
                    SPI_BYTE_WR(8'h06); // write enable
                    SPI_STOP;
                end
            endtask
            
  
            
  task READ_ST_REG(output [7:0] data);
                       
                            begin : task_body
                                SPI_OE(4'b0001);
                                SPI_STATRT;
                                SPI_BYTE_WR(8'h35); 
                                SPI_BYTE_RD(data);
                                SPI_STOP;
                            end
                        endtask
        
            task FLASH_PROT_UNLK;
                begin : task_body
                    SPI_OE(4'b0001);
                    SPI_STATRT;
                    SPI_BYTE_WR(8'h98); // global protection unlock
                    SPI_STOP;
                end
            endtask
          task ENABLE_QE (input[7:0]data);
                            begin : task_body
                                FLASH_WEN;
                                SPI_OE(4'b0001);
                                SPI_STATRT;
                                SPI_BYTE_WR(8'h01); // global protection unlock
                                SPI_BYTE_WR(data);
                                SPI_BYTE_WR(data);
                                SPI_STOP;
                            end
                        endtask
        
            task FLASH_WDI;
                begin : task_body
                    SPI_OE(4'b0001);
                    SPI_STATRT;
                    SPI_BYTE_WR(8'h04);
                    SPI_STOP;
                end
            endtask
            
            task FLASH_CHIP_ERASE;
                begin : task_body
                    SPI_OE(4'b0001);
                    SPI_STATRT;
                    SPI_BYTE_WR(8'hC7);
                    SPI_STOP;
                end
            endtask
        
            // Page program 
            // Re-implement
            task FLASH_WORD_PROG(input[23:0] A, input[31:0] D);
                begin : task_body
                    SPI_OE(4'b0001);
                    SPI_STATRT;
                    SPI_BYTE_WR(8'h02);
                    SPI_BYTE_WR(A[23:16]);
                    SPI_BYTE_WR(A[15:8]);
                    SPI_BYTE_WR(A[7:0]);
                    SPI_BYTE_WR(D[7:0]);
                    SPI_BYTE_WR(D[15:8]);
                    SPI_BYTE_WR(D[23:16]);
                    SPI_BYTE_WR(D[31:24]);
                    SPI_STOP;
                end
            endtask
   task FLASH_WORD_RD(input[23:0] A, output[31:0] D);
                            begin : task_body
                                SPI_OE(4'b0001);
                                SPI_STATRT;
                                SPI_BYTE_WR(8'h0B);
                                SPI_BYTE_WR(A[23:16]);
                                SPI_BYTE_WR(A[15:8]);
                                SPI_BYTE_WR(A[7:0]);
                                SPI_BYTE_RD(D[7:0]);
                                                    SPI_BYTE_RD(D[15:8]);
                                                    SPI_BYTE_RD(D[23:16]);
                                                    SPI_BYTE_RD(D[31:24]);
                                SPI_STOP;
                            end
                        endtask

endmodule



module UART_MON #(parameter BITTIME=8000)(input wire RX);
//module UART_MON #(parameter BITTIME=52083.3)(input RX);
    reg [7:0] data;
    integer i;
    initial begin
        forever begin
            @(negedge RX);
            #BITTIME;
            for(i=0; i<8; i=i+1) begin
                data = {RX, data[7:1]};
                #BITTIME;
            end
            #BITTIME;
            //$write("%c", data);
            $display("0x%X", data);
        end
    end

endmodule

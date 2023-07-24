## This file is a general .xdc for the CmodA7 rev. B
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project

## Timing Constraints
#create_clock -name core_clk -period 25.0000 [get_ports {core_clk}]
#set_clock_transition 0.1500 [get_clocks {core_clk}]
#set_clock_uncertainty 0.2500 core_clk

#create_clock -add -name core_clk -period 25.0 -waveform {0 12.5} [get_ports {fpga_clk}];
create_clock -add -name fpga_clk -period 83.333 -waveform {0 41.666} [get_ports {fpga_clk}];
#create_clock -name core_clk -period 25 -waveform {0 12.5} [get_pins clk_wiz_12_to_40MHz/clk_out1]

# Outputs
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {debug_mode}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {debug_oeb}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {debug_out}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {flash_clk}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {flash_csb}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {hk_cyc_o}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {hk_stb_o}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {la_iena[*]}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {la_oenb[*]}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {la_output[*]}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {mprj_adr_o[*]}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {mprj_cyc_o}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {mprj_dat_o[*]}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {mprj_sel_o[*]}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {mprj_stb_o}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {mprj_wb_iena}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {mprj_we_o}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {qspi_enabled}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {ser_tx}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {spi_csb}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {spi_enabled}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {spi_sck}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {spi_sdo}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {spi_sdoenb}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {sram_ro_data[*]}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {trap}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {uart_enabled}];
#set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {user_irq_ena[*]}];

# Inputs
#set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {core_rstn}];
#set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {debug_in}];
#set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {hk_ack_i}];
#set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {hk_dat_i[*]}];
#set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {irq[*]}];
#set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {la_input[*]}];
#set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {mprj_ack_i}];
#set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {mprj_dat_i[*]}];
set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {ser_rx}];
set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {spi_sdi}];
set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {debug_in}];
#set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {sram_ro_clk}];
#set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {sram_ro_csb}];

# Bidirectional
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {flash_io0_dio}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {flash_io1_dio}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {flash_io2_dio}];
set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {flash_io3_dio}];
set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {flash_io0_dio}];
set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {flash_io1_dio}];
set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {flash_io2_dio}];
 set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {flash_io3_dio}];

set_output_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {gpio_inout_pad}];
set_input_delay 5.0000 -clock [get_clocks {core_clk}] -add_delay [get_ports {gpio_inout_pad}];

## 12 MHz Clock Signal
set_property PACKAGE_PIN L17 [get_ports {fpga_clk}]; #IO_L12P_T1_MRCC_14 Sch=gclk
set_property IOSTANDARD LVCMOS33 [get_ports {fpga_clk}]; #IO_L12P_T1_MRCC_14 Sch=gclk

## LEDs
set_property  PACKAGE_PIN A17 [get_ports { gpio_inout_pad}]; #IO_L12N_T1_MRCC_16 Sch=led[1]
set_property  IOSTANDARD LVCMOS33  [get_ports { gpio_inout_pad }]; #IO_L12N_T1_MRCC_16 Sch=led[1]

#set_property PACKAGE_PIN C16 [get_ports { GPIO_Sys0_S2[0] }]; #IO_L13P_T2_MRCC_16 Sch=led[2]
#set_property IOSTANDARD LVCMOS33 [get_ports { GPIO_Sys0_S2[0] }]; #IO_L12N_T1_MRCC_16 Sch=led[1]

## RGB LED
#set_property -dict { PACKAGE_PIN B17   IOSTANDARD LVCMOS33 } [get_ports { led0_b }]; #IO_L14N_T2_SRCC_16 Sch=led0_b
#set_property -dict { PACKAGE_PIN B16   IOSTANDARD LVCMOS33 } [get_ports { led0_g }]; #IO_L13N_T2_MRCC_16 Sch=led0_g
#set_property -dict { PACKAGE_PIN C17   IOSTANDARD LVCMOS33 } [get_ports { led0_r }]; #IO_L14P_T2_SRCC_16 Sch=led0_r

## Buttons
set_property PACKAGE_PIN A18     [get_ports { RSTB }]; #IO_L19N_T3_VREF_16 Sch=btn[0]
set_property IOSTANDARD LVCMOS33 [get_ports { RSTB }]; #IO_L19N_T3_VREF_16 Sch=btn[0]

#set_property -dict { PACKAGE_PIN B18   IOSTANDARD LVCMOS33 } [get_ports { btn[1] }]; #IO_L19P_T3_16 Sch=btn[1]

## Pmod Header JA
#set_property -dict { PACKAGE_PIN G17   IOSTANDARD LVCMOS33 } [get_ports { ja[0] }]; #IO_L5N_T0_D07_14 Sch=ja[1]
#set_property -dict { PACKAGE_PIN G19   IOSTANDARD LVCMOS33 } [get_ports { ja[1] }]; #IO_L4N_T0_D05_14 Sch=ja[2]
#set_property -dict { PACKAGE_PIN N18   IOSTANDARD LVCMOS33 } [get_ports { ja[2] }]; #IO_L9P_T1_DQS_14 Sch=ja[3]
#set_property -dict { PACKAGE_PIN L18   IOSTANDARD LVCMOS33 } [get_ports { ja[3] }]; #IO_L8P_T1_D11_14 Sch=ja[4]
#set_property -dict { PACKAGE_PIN H17   IOSTANDARD LVCMOS33 } [get_ports { ja[4] }]; #IO_L5P_T0_D06_14 Sch=ja[7]
#set_property -dict { PACKAGE_PIN H19   IOSTANDARD LVCMOS33 } [get_ports { ja[5] }]; #IO_L4P_T0_D04_14 Sch=ja[8]
#set_property -dict { PACKAGE_PIN J19   IOSTANDARD LVCMOS33 } [get_ports { ja[6] }]; #IO_L6N_T0_D08_VREF_14 Sch=ja[9]
#set_property -dict { PACKAGE_PIN K18   IOSTANDARD LVCMOS33 } [get_ports { ja[7] }]; #IO_L8N_T1_D12_14 Sch=ja[10]

## Analog XADC Pins
## Only declare these if you want to use pins 15 and 16 as single ended analog inputs. pin 15 -> vaux4, pin16 -> vaux12
#set_property -dict { PACKAGE_PIN G2    IOSTANDARD LVCMOS33 } [get_ports { xa_n[0] }]; #IO_L1N_T0_AD4N_35 Sch=ain_n[15]
#set_property -dict { PACKAGE_PIN G3    IOSTANDARD LVCMOS33 } [get_ports { xa_p[0] }]; #IO_L1P_T0_AD4P_35 Sch=ain_p[15]
#set_property -dict { PACKAGE_PIN J2    IOSTANDARD LVCMOS33 } [get_ports { xa_n[1] }]; #IO_L2N_T0_AD12N_35 Sch=ain_n[16]
#set_property -dict { PACKAGE_PIN H2    IOSTANDARD LVCMOS33 } [get_ports { xa_p[1] }]; #IO_L2P_T0_AD12P_35 Sch=ain_p[16]

## GPIO Pins
## Pins 15 and 16 should remain commented if using them as analog inputs
set_property PACKAGE_PIN M3  [get_ports {flash_csb}]; #IO_L8N_T1_AD14N_35 Sch=pio[01]
#set_property PACKAGE_PIN L3  [get_ports {flash_io3_dio}]; #IO_L8P_T1_AD14P_35 Sch=pio[02]
#set_property PACKAGE_PIN A16 [get_ports {flash_io2_dio}]; #IO_L12P_T1_MRCC_16 Sch=pio[03]
#set_property PACKAGE_PIN K3  [get_ports {flash_io1_dio}]; #IO_L7N_T1_AD6N_35 Sch=pio[04]
#set_property PACKAGE_PIN C15 [get_ports {flash_io0_dio}]; #IO_L11P_T1_SRCC_16 Sch=pio[05]
set_property PACKAGE_PIN H1  [get_ports {flash_clk}]; #IO_L3P_T0_DQS_AD5P_35 Sch=pio[06]
set_property PACKAGE_PIN A15 [get_ports {flash_io0_dio}]; #IO_L6N_T0_VREF_16 Sch=pio[07]
#set_property PACKAGE_PIN B15 [get_ports {flash_io2_dio}]; #IO_L11N_T1_SRCC_16 Sch=pio[08]
set_property PACKAGE_PIN A14 [get_ports {flash_io1_dio}]; #IO_L6P_T0_16 Sch=pio[09]
set_property PACKAGE_PIN J3  [get_ports {flash_io2_dio}]; #IO_L7P_T1_AD6P_35 Sch=pio[10]
set_property PACKAGE_PIN J1  [get_ports {flash_io3_dio}]; #IO_L3N_T0_DQS_AD5N_35 Sch=pio[11]
#set_property PACKAGE_PIN K2  [get_ports {GPIO_Sys0_S2[14]}]; #IO_L5P_T0_AD13P_35 Sch=pio[12]
#set_property PACKAGE_PIN L1  [get_ports {GPIO_Sys0_S2[13]}]; #IO_L6N_T0_VREF_35 Sch=pio[13]
#set_property PACKAGE_PIN L2  [get_ports {GPIO_Sys0_S2[12]}]; #IO_L5N_T0_AD13N_35 Sch=pio[14]
set_property PACKAGE_PIN M1  [get_ports { debug_in }]; #IO_L9N_T1_DQS_AD7N_35 Sch=pio[17]
set_property PACKAGE_PIN N3  [get_ports { debug_out }]; #IO_L12P_T1_MRCC_35 Sch=pio[18]
set_property PACKAGE_PIN P3  [get_ports { debug_oeb }]; #IO_L12N_T1_MRCC_35 Sch=pio[19]
set_property PACKAGE_PIN M2  [get_ports { debug_mode }]; #IO_L9P_T1_DQS_AD7P_35 Sch=pio[20]
#set_property PACKAGE_PIN N1  [get_ports { GPIO_Sys0_S2[7] }]; #IO_L10N_T1_AD15N_35 Sch=pio[21]
#set_property PACKAGE_PIN N2  [get_ports { GPIO_Sys0_S2[6] }]; #IO_L10P_T1_AD15P_35 Sch=pio[22]

set_property PACKAGE_PIN P1  [get_ports { trap }]; #IO_L19N_T3_VREF_35 Sch=pio[23]
#set_property PACKAGE_PIN R3  [get_ports { debug_mode }]; #IO_L2P_T0_34 Sch=pio[26]
set_property PACKAGE_PIN T3 [get_ports { spi_enabled }]; #IO_L2N_T0_34 Sch=pio[27]
set_property PACKAGE_PIN R2 [get_ports { uart_enabled }]; #IO_L1P_T0_34 Sch=pio[28]
set_property PACKAGE_PIN T1 [get_ports { qspi_enabled }]; #IO_L3P_T0_DQS_34 Sch=pio[29]
set_property PACKAGE_PIN T2 [get_ports { tx_out }]; #IO_L1N_T0_34 Sch=pio[30]
set_property PACKAGE_PIN U1 [get_ports { rx_out }]; #IO_L3N_T0_DQS_34 Sch=pio[31]
# set_property PACKAGE_PIN W2 [get_ports { NMI }]; #IO_L5N_T0_34 Sch=pio[32]

 #set_property PACKAGE_PIN U1 [get_ports { UART_MASTER_RX }]; #IO_L3N_T0_DQS_34 Sch=pio[31]
 #set_property PACKAGE_PIN W2 [get_ports { UART_MASTER_TX }]; #IO_L5N_T0_34 Sch=pio[32]

#set_property PACKAGE_PIN V2 [get_ports { ser_rx }]; #IO_L5P_T0_34 Sch=pio[33]
#set_property PACKAGE_PIN W3 [get_ports { ser_tx }]; #IO_L6N_T0_VREF_34 Sch=pio[34]
set_property PACKAGE_PIN V3 [get_ports { spi_sdi }]; #IO_L6P_T0_34 Sch=pio[35]
#set_property PACKAGE_PIN W5 [get_ports { MSI_Sys0_SS0_S3[0] }]; #IO_L12P_T1_MRCC_34 Sch=pio[36]
set_property PACKAGE_PIN V4 [get_ports { spi_sdo }]; #IO_L11N_T1_SRCC_34 Sch=pio[37]
#set_property PACKAGE_PIN U4 [get_ports { MSO_Sys0_SS0_S3[0] }]; #IO_L11P_T1_SRCC_34 Sch=pio[38]
#set_property PACKAGE_PIN V5 [get_ports { pwm_Sys0_SS0_S6[0] }]; #IO_L16N_T2_34 Sch=pio[39]
#set_property PACKAGE_PIN W4 [get_ports { pwm_Sys0_SS0_S7[0] }]; #IO_L12N_T1_MRCC_34 Sch=pio[40]
#set_property PACKAGE_PIN U5 [get_ports { scl_Sys0_SS0_S4[0] }]; #IO_L16P_T2_34 Sch=pio[41]
#set_property PACKAGE_PIN U2 [get_ports { scl_Sys0_SS0_S5[0] }]; #IO_L9N_T1_DQS_34 Sch=pio[42]
set_property PACKAGE_PIN W6 [get_ports { spi_sck }]; #IO_L13N_T2_MRCC_34 Sch=pio[43]
#set_property PACKAGE_PIN U3 [get_ports { SCLK_Sys0_SS0_S3[0] }]; #IO_L9P_T1_DQS_34 Sch=pio[44]
#set_property PACKAGE_PIN U7 [get_ports { sda_Sys0_SS0_S4[0] }]; #IO_L19P_T3_34 Sch=pio[45]
set_property PACKAGE_PIN W7 [get_ports { spi_csb }]; #IO_L13P_T2_MRCC_34 Sch=pio[46]
set_property PACKAGE_PIN U8 [get_ports { spi_sdoenb }]; #IO_L14P_T2_SRCC_34 Sch=pio[47]
#set_property PACKAGE_PIN V8 [get_ports { SSn_Sys0_SS0_S3[0] }]; #IO_L14N_T2_SRCC_34 Sch=pio[48]


set_property IOSTANDARD LVCMOS33  [get_ports {flash_csb}]; #IO_L8N_T1_AD14N_35 Sch=pio[01]
#set_property IOSTANDARD LVCMOS33  [get_ports {flash_io3_dio}]; #IO_L8P_T1_AD14P_35 Sch=pio[02]
#set_property IOSTANDARD LVCMOS33 [get_ports {flash_io2_dio}]; #IO_L12P_T1_MRCC_16 Sch=pio[03]
#set_property IOSTANDARD LVCMOS33  [get_ports {flash_io1_dio}]; #IO_L7N_T1_AD6N_35 Sch=pio[04]
#set_property IOSTANDARD LVCMOS33 [get_ports {flash_io0_dio}]; #IO_L11P_T1_SRCC_16 Sch=pio[05]
set_property IOSTANDARD LVCMOS33  [get_ports {flash_clk}]; #IO_L3P_T0_DQS_AD5P_35 Sch=pio[06]
set_property IOSTANDARD LVCMOS33 [get_ports {flash_io0_dio}]; #IO_L6N_T0_VREF_16 Sch=pio[07]
#set_property IOSTANDARD LVCMOS33 [get_ports {flash_io1_dio}]; #IO_L11N_T1_SRCC_16 Sch=pio[08]
set_property IOSTANDARD LVCMOS33 [get_ports {flash_io1_dio}]; #IO_L6P_T0_16 Sch=pio[09]
set_property IOSTANDARD LVCMOS33  [get_ports {flash_io2_dio}]; #IO_L7P_T1_AD6P_35 Sch=pio[10]
set_property IOSTANDARD LVCMOS33  [get_ports {flash_io3_dio}]; #IO_L3N_T0_DQS_AD5N_35 Sch=pio[11]
#set_property IOSTANDARD LVCMOS33  [get_ports {GPIO_Sys0_S2[14]}]; #IO_L5P_T0_AD13P_35 Sch=pio[12]
#set_property IOSTANDARD LVCMOS33  [get_ports {GPIO_Sys0_S2[13]}]; #IO_L6N_T0_VREF_35 Sch=pio[13]
#set_property IOSTANDARD LVCMOS33  [get_ports {GPIO_Sys0_S2[12]}]; #IO_L5N_T0_AD13N_35 Sch=pio[14]
set_property IOSTANDARD LVCMOS33  [get_ports {debug_in}]; #IO_L9N_T1_DQS_AD7N_35 Sch=pio[17]
set_property IOSTANDARD LVCMOS33  [get_ports { debug_out }]; #IO_L12P_T1_MRCC_35 Sch=pio[18]
set_property IOSTANDARD LVCMOS33  [get_ports { debug_oeb }]; #IO_L12N_T1_MRCC_35 Sch=pio[19]
set_property IOSTANDARD LVCMOS33  [get_ports { debug_mode }]; #IO_L9P_T1_DQS_AD7P_35 Sch=pio[20]
#set_property IOSTANDARD LVCMOS33  [get_ports { GPIO_Sys0_S2[7] }]; #IO_L10N_T1_AD15N_35 Sch=pio[21]
#set_property IOSTANDARD LVCMOS33  [get_ports { GPIO_Sys0_S2[6] }]; #IO_L10P_T1_AD15P_35 Sch=pio[22]
set_property IOSTANDARD LVCMOS33  [get_ports { trap }]; #IO_L19N_T3_VREF_35 Sch=pio[23]
#set_property IOSTANDARD LVCMOS33  [get_ports { debug_mode }]; #IO_L2P_T0_34 Sch=pio[26]
set_property IOSTANDARD LVCMOS33 [get_ports { spi_enabled }]; #IO_L2N_T0_34 Sch=pio[27]
set_property IOSTANDARD LVCMOS33 [get_ports { uart_enabled }]; #IO_L1P_T0_34 Sch=pio[28]
set_property IOSTANDARD LVCMOS33 [get_ports { qspi_enabled }]; #IO_L3P_T0_DQS_34 Sch=pio[29]
set_property IOSTANDARD LVCMOS33 [get_ports { tx_out }]; #IO_L1N_T0_34 Sch=pio[30]
set_property IOSTANDARD LVCMOS33 [get_ports { rx_out }]; #IO_L3N_T0_DQS_34 Sch=pio[31]
#set_property IOSTANDARD LVCMOS33 [get_ports { UART_MASTER_TX }]; #IO_L5N_T0_34 Sch=pio[32]
 
set_property IOSTANDARD LVCMOS33 [get_ports { ser_rx }]; #IO_L5P_T0_34 Sch=pio[33]
set_property IOSTANDARD LVCMOS33 [get_ports { ser_tx }]; #IO_L6N_T0_VREF_34 Sch=pio[34]
set_property IOSTANDARD LVCMOS33 [get_ports { spi_sdi }]; #IO_L6P_T0_34 Sch=pio[35]
#set_property IOSTANDARD LVCMOS33 [get_ports { MSI_Sys0_SS0_S3[0] }]; #IO_L12P_T1_MRCC_34 Sch=pio[36]
set_property IOSTANDARD LVCMOS33 [get_ports { spi_sdo }]; #IO_L11N_T1_SRCC_34 Sch=pio[37]
#set_property IOSTANDARD LVCMOS33 [get_ports { MSO_Sys0_SS0_S3[0] }]; #IO_L11P_T1_SRCC_34 Sch=pio[38]
#set_property IOSTANDARD LVCMOS33 [get_ports { pwm_Sys0_SS0_S6[0] }]; #IO_L16N_T2_34 Sch=pio[39]
#set_property IOSTANDARD LVCMOS33 [get_ports { pwm_Sys0_SS0_S7[0] }]; #IO_L12N_T1_MRCC_34 Sch=pio[40]
#set_property IOSTANDARD LVCMOS33 [get_ports { scl_Sys0_SS0_S4[0] }]; #IO_L16P_T2_34 Sch=pio[41]
#set_property IOSTANDARD LVCMOS33 [get_ports { scl_Sys0_SS0_S5[0] }]; #IO_L9N_T1_DQS_34 Sch=pio[42]
set_property IOSTANDARD LVCMOS33 [get_ports { spi_sck }]; #IO_L13N_T2_MRCC_34 Sch=pio[43]
#set_property IOSTANDARD LVCMOS33 [get_ports { SCLK_Sys0_SS0_S3[0] }]; #IO_L9P_T1_DQS_34 Sch=pio[44]
#set_property IOSTANDARD LVCMOS33 [get_ports { sda_Sys0_SS0_S4[0] }]; #IO_L19P_T3_34 Sch=pio[45]
set_property IOSTANDARD LVCMOS33 [get_ports { spi_csb }]; #IO_L13P_T2_MRCC_34 Sch=pio[46]
set_property IOSTANDARD LVCMOS33 [get_ports { spi_sdoenb }]; #IO_L14P_T2_SRCC_34 Sch=pio[47]
#set_property IOSTANDARD LVCMOS33 [get_ports { SSn_Sys0_SS0_S3[0] }]; #IO_L14N_T2_SRCC_34 Sch=pio[48]

## UART 
set_property PACKAGE_PIN J18 [get_ports { ser_tx }]; #IO_L7N_T1_D10_14 Sch=uart_rxd_out
set_property PACKAGE_PIN J17 [get_ports { ser_rx }]; #IO_L7P_T1_D09_14 Sch=uart_txd_in

#set_property IOSTANDARD LVCMOS33 [get_ports { RsRx_Sys0_SS0_S0[0] }]; #IO_L7N_T1_D10_14 Sch=uart_rxd_out
#set_property IOSTANDARD LVCMOS33 [get_ports { RsTx_Sys0_SS0_S0[0] }]; #IO_L7P_T1_D09_14 Sch=uart_txd_in

## Crypto 1 Wire Interface
#set_property -dict { PACKAGE_PIN D17   IOSTANDARD LVCMOS33 } [get_ports { crypto_sda }]; #IO_0_14 Sch=crypto_sda

## QSPI
#set_property -dict { PACKAGE_PIN K19   IOSTANDARD LVCMOS33 } [get_ports { qspi_cs    }]; #IO_L6P_T0_FCS_B_14 Sch=qspi_cs
#set_property -dict { PACKAGE_PIN D18   IOSTANDARD LVCMOS33 } [get_ports { qspi_dq[0] }]; #IO_L1P_T0_D00_MOSI_14 Sch=qspi_dq[0]
#set_property -dict { PACKAGE_PIN D19   IOSTANDARD LVCMOS33 } [get_ports { qspi_dq[1] }]; #IO_L1N_T0_D01_DIN_14 Sch=qspi_dq[1]
#set_property -dict { PACKAGE_PIN G18   IOSTANDARD LVCMOS33 } [get_ports { qspi_dq[2] }]; #IO_L2P_T0_D02_14 Sch=qspi_dq[2]
#set_property -dict { PACKAGE_PIN F18   IOSTANDARD LVCMOS33 } [get_ports { qspi_dq[3] }]; #IO_L2N_T0_D03_14 Sch=qspi_dq[3]

## Cellular RAM
#set_property -dict { PACKAGE_PIN M18   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[0]  }]; #IO_L11P_T1_SRCC_14 Sch=sram- a[0]
#set_property -dict { PACKAGE_PIN M19   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[1]  }]; #IO_L11N_T1_SRCC_14 Sch=sram- a[1]
#set_property -dict { PACKAGE_PIN K17   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[2]  }]; #IO_L12N_T1_MRCC_14 Sch=sram- a[2]
#set_property -dict { PACKAGE_PIN N17   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[3]  }]; #IO_L13P_T2_MRCC_14 Sch=sram- a[3]
#set_property -dict { PACKAGE_PIN P17   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[4]  }]; #IO_L13N_T2_MRCC_14 Sch=sram- a[4]
#set_property -dict { PACKAGE_PIN P18   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[5]  }]; #IO_L14P_T2_SRCC_14 Sch=sram- a[5]
#set_property -dict { PACKAGE_PIN R18   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[6]  }]; #IO_L14N_T2_SRCC_14 Sch=sram- a[6]
#set_property -dict { PACKAGE_PIN W19   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[7]  }]; #IO_L16N_T2_A15_D31_14 Sch=sram- a[7]
#set_property -dict { PACKAGE_PIN U19   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[8]  }]; #IO_L15P_T2_DQS_RDWR_B_14 Sch=sram- a[8]
#set_property -dict { PACKAGE_PIN V19   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[9]  }]; #IO_L15N_T2_DQS_DOUT_CSO_B_14 Sch=sram- a[9]
#set_property -dict { PACKAGE_PIN W18   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[10] }]; #IO_L16P_T2_CSI_B_14 Sch=sram- a[10]
#set_property -dict { PACKAGE_PIN T17   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[11] }]; #IO_L17P_T2_A14_D30_14 Sch=sram- a[11]
#set_property -dict { PACKAGE_PIN T18   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[12] }]; #IO_L17N_T2_A13_D29_14 Sch=sram- a[12]
#set_property -dict { PACKAGE_PIN U17   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[13] }]; #IO_L18P_T2_A12_D28_14 Sch=sram- a[13]
#set_property -dict { PACKAGE_PIN U18   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[14] }]; #IO_L18N_T2_A11_D27_14 Sch=sram- a[14]
#set_property -dict { PACKAGE_PIN V16   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[15] }]; #IO_L19P_T3_A10_D26_14 Sch=sram- a[15]
#set_property -dict { PACKAGE_PIN W16   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[16] }]; #IO_L20P_T3_A08_D24_14 Sch=sram- a[16]
#set_property -dict { PACKAGE_PIN W17   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[17] }]; #IO_L20N_T3_A07_D23_14 Sch=sram- a[17]
#set_property -dict { PACKAGE_PIN V15   IOSTANDARD LVCMOS33 } [get_ports { MemAdr[18] }]; #IO_L21P_T3_DQS_14 Sch=sram- a[18]
#set_property -dict { PACKAGE_PIN W15   IOSTANDARD LVCMOS33 } [get_ports { MemDB[0]   }]; #IO_L21N_T3_DQS_A06_D22_14 Sch=sram-dq[0]
#set_property -dict { PACKAGE_PIN W13   IOSTANDARD LVCMOS33 } [get_ports { MemDB[1]   }]; #IO_L22P_T3_A05_D21_14 Sch=sram-dq[1]
#set_property -dict { PACKAGE_PIN W14   IOSTANDARD LVCMOS33 } [get_ports { MemDB[2]   }]; #IO_L22N_T3_A04_D20_14 Sch=sram-dq[2]
#set_property -dict { PACKAGE_PIN U15   IOSTANDARD LVCMOS33 } [get_ports { MemDB[3]   }]; #IO_L23P_T3_A03_D19_14 Sch=sram-dq[3]
#set_property -dict { PACKAGE_PIN U16   IOSTANDARD LVCMOS33 } [get_ports { MemDB[4]   }]; #IO_L23N_T3_A02_D18_14 Sch=sram-dq[4]
#set_property -dict { PACKAGE_PIN V13   IOSTANDARD LVCMOS33 } [get_ports { MemDB[5]   }]; #IO_L24P_T3_A01_D17_14 Sch=sram-dq[5]
#set_property -dict { PACKAGE_PIN V14   IOSTANDARD LVCMOS33 } [get_ports { MemDB[6]   }]; #IO_L24N_T3_A00_D16_14 Sch=sram-dq[6]
#set_property -dict { PACKAGE_PIN U14   IOSTANDARD LVCMOS33 } [get_ports { MemDB[7]   }]; #IO_25_14 Sch=sram-dq[7]
#set_property -dict { PACKAGE_PIN P19   IOSTANDARD LVCMOS33 } [get_ports { RamOEn     }]; #IO_L10P_T1_D14_14 Sch=sram-oe
#set_property -dict { PACKAGE_PIN R19   IOSTANDARD LVCMOS33 } [get_ports { RamWEn     }]; #IO_L10N_T1_D15_14 Sch=sram-we
#set_property -dict { PACKAGE_PIN N19   IOSTANDARD LVCMOS33 } [get_ports { RamCEn     }]; #IO_L9N_T1_DQS_D13_14 Sch=sram-ce
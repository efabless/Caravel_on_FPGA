# Caravel_on_FPGA
This repo ...
## Step 1: Flash Programming 
In Caravel, the program which will be running on the vexriscv core in the mangament SoC can be read from an external flash module. However, the flash needs first to be programmed with the hex file of the compiled C program. This can be done by having a flash writer slave which talks to the flash and program it. For the flash writer to do this, it needs a master. The master used here is a uart master which receives commands from PC and program the flash writer which will eventually program the flash. The uart master and flash writer modules rtl code was based on [this](https://github.com/shalan/SoCBUS) repository. A python script is used to program the uart master and it is based on [this](https://github.com/nabadawy/Chameleon_SoC_with-SST26VF080A-flash-/tree/main) repository where you can also find an explanation of the commands used to program the flash.

#### Here are the steps of the flash programming:
1) First you need the hex file you will program the flash with. In order to compile the c program, you can do this using the [caravel management soc repo](https://github.com/efabless/caravel_mgmt_soc_litex). You can run ``make hex`` inside any test in the directory ``caravel_mgmt_soc_litex/verilog/dv/tests-caravel/<test-name>`` but before this, make sure you have done the following exports:
```
export CARAVEL_ROOT=<path_to_caravel_root>
export CARAVEL_VERILOG_PATH=<path_to_caravel_verilog>
export CORE_VERILOG_PATH=<path_to_mgmt_soc_verilog>
export GCC_PATH=<path_to_gcc>
export GCC_PREFIX=<gcc_prefix>
export PDK_ROOT=<path_to_PDK>
export PDK= sky130A
```
you will find the hex file generated in the same directory of the test. For this tutorial, you can modify the ``gpio_mgmt`` test to have [this](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/C_program) C program  which toggles the mgmt gpio pin and enables the debug interface. 

2) Use Vivado to add the source files you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/flash_programming/src), along with the constraints file you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/flash_programming/constr) then click on "generate bitstream" you can find under "PROGRAM AND DEBUG" in the side bar. You can also use the ready bitstream you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/flash_programming/bit_file)
  
3) To program the FPGA with the bit file. You can either do it through Vivado by clicking on "program device" under "Open Hardware Target Manager" or you can use [Digilent Adept](https://digilent.com/shop/software/digilent-adept/) to program the FPGA and use this command:
```
djtgcfg prog -d CmodA7 -i 0 -f uart_flash_writer.bit
```
4) For the hardware connections:
   * FPGA pin 5 will be connected to CS pin in flash module
   * FPGA pin 6 will be connected to CLK pin in flash module
   * FPGA pin 7 will be connected to IO0 pin in flash module
   * FPGA pin 9 will be connected to IO1 pin in flash module
   * FPGA pin 10 will be connected to IO2 pin in flash module
   * FPGA pin 11 will be connected to IO3 pin in flash module
   * FPGA PMOD VCC will be connected to 3v3 pin in flash module
   * FPGA PMOD GND will be connected to GND pin in flash module

    Notice that the uart ports (TX and RX ) are connected to the UART-USB bridge of the Cmod FPGA. This means that the micro USB cable connected to the PC used to      program the FPGA will be also used to talk to the UART master.   

5) Now the uart master flash writer design is implemnted on the FPGA and the hardware connections are ready, all you need is to run the python script you can find [here]() which talks to the uart master of the design. Make sure to change in the python script the name of the hex file you want to program the flash with and change the port name. For the tutorial, you can use [this]() ready hex file which is the compilation of [this](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/C_program) C program. 
  
6) The python script reads the program in the flash after writing it. You can check if they are the same. 

## Step 2: Caravel implementation on FPGA
Now, that the flash is programmed with the program we want to run on Caravel, we can run this program on Caravel implemented on FPGA. You can find the source and constraints files for the management SoC alone [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/mgmt_soc) and the files for the whole Caravel could be found [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel) 



## Step 3: Using GDB to debug program running on Caravel 

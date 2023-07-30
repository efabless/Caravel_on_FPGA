# Caravel_on_FPGA
In this repo you will be shown how to implement Cravel on FPGA and use its debug interface to debug a program running on Caravel's management SoC using GDB.
## Hardware Tools used:
* Cmod Artix 7-35T
* QSPI SST26VF080A Flash module
* two micro USB cable
* Analog Discovery kit (optional for debugging)
* Jumper wires for connecting
* Raspberry pi pico (if you want to program the flash using the housekeeping SPI)
  
![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/c9aac42d-5d43-4030-bcca-50d65617d6ba)


## Software Tools used:
* Xilinx Vivado for synthesizing, implementing, and generating the bit stream of the RTL design
* Digilent Adept for programming the FPGA with the bit file
* Digilent Waveforms for using the analog discovery kit logic analyzer
* Thony (if you want to program the flash using the housekeeping SPI)
  
![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/b47b65dd-1cd1-44c1-a9ad-e066a5f25ec7)

## Steps for debugging a program running on CaraveL using GDB:

### Step 1: Flash Programming 
In Caravel, the program which will be running on the vexriscv core in the mangament SoC can be read from an external flash module. However, the flash needs first to be programmed with the hex file of the compiled C program. You have two options to do this. 

The first option is to use another RTL design which have a UART master and a flash writer slave and implement it on FPGA and use [this](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/blob/main/flash_programming/flash_programming_script.py) python script to send commands from PC through the USB-UART bridge in the FPGA. The advantage of this option is that you wouldn't need to use the Raspberry pi pico if not availble. 
Note: The uart master and flash writer modules rtl code was based on [this](https://github.com/shalan/SoCBUS) repository. 

The second option is to use Caravel's housekeeping SPI interface to make the Caravel in management pass through mode which means the housekeeping SPI signals which are on gpios from 1 to 4 will be connected to the flash interface signals. In this case we will need an SPI master to talk to the housekeeping SPI slave. The SPI interface in Raspberry pi pico is used in this tutorial along with a micropython script you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/Micropython_scripts) The advantage of this option is that you wouldn't need another design other than Caravel to be implemneted on FPGA. 

#### First option steps (flash programming using UART master and flash writer):
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

2) Use Vivado to add UART master flash writer source files you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/flash_programming/src), along with the constraint file you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/flash_programming/constr) then click on "generate bitstream" you can find under "PROGRAM AND DEBUG" in the side bar. You can also use the ready bitstream you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/flash_programming/bit_file)
  
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

5) Now the uart master flash writer design is implemnted on the FPGA and the hardware connections are ready, all you need is to run the python script you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/flash_programming) which talks to the uart master of the design. Make sure to change in the python script the name of the hex file you want to program the flash with and change the port name. For the tutorial, you can use [this](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/blob/main/Caravel/hex_file/debug_gpio.hex) ready hex file which is the compilation of [this](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/C_program) C program. 
  
6) The python script reads the program in the flash after writing it. You can check if they are the same. 
Note: The python script used to program the uart master is based on [this](https://github.com/nabadawy/Chameleon_SoC_with-SST26VF080A-flash-/tree/main) repository where you can also find an explanation of the commands used to program the flash.

#### Second option steps (flash programming using hk SPI and Raspberry pi pico):
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

2) Use Vivado to add Caravel's source files you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/src), along with the constraint file you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/constr) then click on "generate bitstream" you can find under "PROGRAM AND DEBUG" in the side bar. You can also use the ready bitstream you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/bit_file)
  
3) To program the FPGA with the bit file. You can either do it through Vivado by clicking on "program device" under "Open Hardware Target Manager" or you can use [Digilent Adept](https://digilent.com/shop/software/digilent-adept/) to program the FPGA and use this command:
```
djtgcfg prog -d CmodA7 -i 0 -f caravel.bit
```
4) For the hardware connections:
   * FPGA pin 1 will be connected to CS pin in flash module
   * FPGA pin 6 will be connected to CLK pin in flash module
   * FPGA pin 7 will be connected to IO0 pin in flash module
   * FPGA pin 9 will be connected to IO1 pin in flash module
   * FPGA PMOD VCC will be connected to 3v3 pin in flash module
   * FPGA PMOD GND will be connected to GND pin in flash module
   * FPGA pin 11 (mprj_io[1]/SDO) will be connected to pin 6 in Raspberry pi pico (MISO/ SPIO RX)
   * FPGA pin 12 (mprj_io[2]/SDI) will be connected to pin 5 in Raspberry pi pico (MOSI/ SPIO TX)
   * FPGA pin 13 (mprj_io[3]/CSB) will be connected to pin 7 in Raspberry pi pico (SPIO CSn)
   * FPGA pin 18 (mprj_io[4]/SCK) will be connected to pin 4 in Raspberry pi pico (SPIO SCK)
  

5) Now the Caravel design is implemnted on the FPGA and the hardware connections are ready, you need to run micropython on the raspberry pi pico. You will find the scripts [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/Micropython_scripts). You Can use [Thony](https://thonny.org/) inorder to run the micropython script on the raspberry pi pico easily. You can install Thony on Ubuntu using ``sudo apt install thonny`` and then use the instructions [here](https://core-electronics.com.au/guides/how-to-setup-a-raspberry-pi-pico-and-code-with-thonny/#install) to setup raspberrypi pico with Thony.

![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/fd25238f-dae3-4d01-8a54-cb66f0c38457)

   
6) Make sure that you saved the [main.py](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/blob/main/Caravel/Micropython_scripts/main.py) ,[flash.py](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/blob/main/Caravel/Micropython_scripts/flash.py) and [debug_gpio.hex](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/blob/main/Caravel/Micropython_scripts/debug_gpio.hex) (or the hex file of the program you want to run) files in the raspberrypi pico (when you click save as you will have the option to save on your PC or on the pico).

![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/87b9c6ed-8f7b-4250-bc7c-641c69a94778)


7) Then run using the green arrow
   
![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/8efd786c-7a27-4f78-b6eb-039787e22a86)

You should see the following output in the Thony's Shell
```
Caravel data:
   mfg        = 0456
   product    = 11
   project ID = 00000000
 
Resetting Flash...
status = 0x02
 
JEDEC = b'ef4017'
Erasing chip...
done
status = 0x0
 
Caravel data:
   mfg        = 0456
   product    = 11
   project ID = 00000000
 
Resetting Flash...
 
JEDEC = b'ef4017'
setting address to 00000000
addr 0x0: flash page write successful (1)
addr 0x100: flash page write successful (1)
addr 0x200: flash page write successful (1)
addr 0x300: flash page write successful (2)

total_bytes = 892
^^^^^^^^ verifying  ^^^^^^^^
setting address to 00000000
addr 0x0: read compare successful
addr 0x100: read compare successful
addr 0x200: read compare successful
addr 0x300: read compare successful

total_bytes = 892
```
You should also see the FPGA LED toggling 

### Step 2: Caravel implementation on FPGA
Now, that the flash is programmed with the program we want to run on Caravel, we can run this program on Caravel implemented on FPGA. You can find the source and constraints files for the management SoC alone [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/mgmt_soc) and the source files for the whole Caravel could be found [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel) 

In order to test the debug interface in Caravel, you need to understand how it works. The debugging needs to be enabled first and this should be done using the C code by writing one to the CSR_DEBUG_MODE_OUT_ADDR register. Before that, you need to set the debug output enable bar to 1 to make the direction of the gpio 0 to be input. The default configuartion for gpio 0 is also changed in the RTL to be input instead of bidirectional. For the debug to be enabled through the uart pins (gpio 5 and 6), gpio 0 must be set to 1. This could be done using logic analyzer by generating signal high to one of the IOs and connect it to the relative FPGA pin. Then the UART-USB bridge in the FPGA connected to uart gpios 5 and 6 can be used for the PC to send command to the UART. You can find a test bench for the debug verification [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/sim/debug). This test bench runs the program which toggles the mgmt gpio while enabling the debug interface. Then uses the debug uart in order to write a word in the SRAM then read it again. In order to test the debug interface in hardware, there is a python script to write and read a word through the debug you can find it [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/blob/main/Caravel/debug_uart_script.py). 

Notice: The FPGA clock is 12 MHz so we need to adjust the baudrate and bit time of the uart accordingly. This is the equation used to calculate the bit time in nano seconds, given the clock period in nanoseconds 
```
bit time (ns) = (100000 * clock period (ns) )/ 1152 
```
So in case of 12 MHz clock which is a period of 83.333 ns, the bit time will be 7234 and the baudrate will be 138236  

#### Steps to test debug on caravel 
1) Program the flash module with the debug_gpio.hex file you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/blob/main/Caravel/hex_file/debug_gpio.hex) as shown in the step 1
2) Use Vivado to add the source files you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/src), along with the constraint file you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/constr) then click on "generate bitstream" you can find under "PROGRAM AND DEBUG" in the side bar. You can also use the ready bitstream you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/tree/main/Caravel/bit_file)
  
3) For the hardware connections:
   * FPGA pin 1 will be connected to CS pin in flash module
   * FPGA pin 6 will be connected to CLK pin in flash module
   * FPGA pin 7 will be connected to IO0 pin in flash module
   * FPGA pin 9 will be connected to IO1 pin in flash module
   * FPGA PMOD VCC will be connected to 3v3 pin in flash module
   * FPGA PMOD GND will be connected to GND pin in flash module
   * FPGA pin  10 (mprj_io[0]) connected to a logig analyzer IO with generated pattern with logic high
   * FPGA pin 14 (mprj_io[5]) connected to a logig analyzer IO
   * FPGA pin 17 (mprj_io[5]) connected to a logig analyzer IO 

  Notice that the uart ports ( gpio pin 5 and gpio pin 6 ) are connected to the UART-USB bridge of the Cmod FPGA. This means that the micro    USB cable connected to the PC used to program the FPGA will be also used to talk to the debug UART. 

4) Generate a constant pattern of 1 using [Digilent WaveForms](https://digilent.com/shop/software/digilent-waveforms/) on FPGA pin 10 (gpio 0). You can do this by clicking on "patterns" , "Add", "Signal", "DIOX" (choose the DIO connected to FPGA pin 10), choose type "constant", and parameter "1" as follows:
![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/8b998d4b-dd90-478d-bc4c-cc824a4bebdc)

5) To program the FPGA with the bit file. You can either do it through Vivado by clicking on "program device" under "Open Hardware Target Manager" or you can use [Digilent Adept](https://digilent.com/shop/software/digilent-adept/) to program the FPGA and use this command:
```
djtgcfg prog -d CmodA7 -i 0 -f caravel.bit
```
After programming the FPGA with the caravel chip, you should be able to see one of the LEDs toggling. 

6) You can also see the bytes sent and recieved through the logic analyzer and [Digilent WaveForms](https://digilent.com/shop/software/digilent-waveforms/) by connecting FPGA pins 14 and 17 to two logic analyzer IOs. Those two pins are connected to gpios 5 and 6 in the RTL to make sure that they are passed correctly.
You can check the data read on Digilent Waveforms by choosing "Logic", "Add", "UART", "DIOX" and choose the format to be hexadecimal and choose the trigger to be "edge" and do this to both DIOs connected to FPGA pins 14 and 17. Change the mode to recorded instead of repeated and change the rate to be 1 MHz and then press Record as follows:
![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/18bf6dc4-b1d2-421d-a3dc-3453bb512e8c)

7) Now you should run the debug uart python script, you can find [here] (https://github.com/NouranAbdelaziz/Caravel_on_FPGA/blob/main/Caravel/debug_uart_script.py).If you can see the word read correctly as below on the waveform and outputed in the python script.
![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/9215dc91-8990-42c6-b5f4-24409b634f51)

This means that the debug interface is functional and the connections are correct. You can now use Litex server, OpenOCD, and GDB to actually debug a program running on Caravel's management SoC  

### Step 3: Using GDB to debug program running on Caravel 
In order to debug a program running on a chip using GDB, a specific version of [OpenOCD](https://github.com/SpinalHDL/openocd_riscv) from SpinalHDL is used. OpenOCD which stands for Open On Chip Debugger translates GDB high level commands to commands which can be understood by different interfaces and CPUs. Litex server is used in order to let an Litex SoC communicate with OpenOCD through a UART bridge. You can read more about this setup in this [repo](https://github.com/enjoy-digital/litex/wiki/Use-GDB-with-VexRiscv-CPU)

Since Caravel's managemnt SoC is generated using Litex, we will use the Litex server and OpanOCD to debug the code running on Caravel.

#### The steps needed for debug using GDB:
1) Have caravel implemented on FPGA with flash module connected to it while have the debug_gpio.hex file. This should be achieved after steps 1 and 2. To make sure that this step was done correctly. You should be seeing one of the LEDs toggling and be able to read and write word using the debug uart python script. 
2) Install OpenOCD using the following commands:
```
git clone https://github.com/SpinalHDL/openocd_riscv.git
cd openocd_riscv
wget https://raw.githubusercontent.com/litex-hub/pythondata-cpu-vexriscv/master/pythondata_cpu_vexriscv/verilog/VexRiscv_Debug.yaml
mv VexRiscv_Debug.yaml cpu0.yaml
./bootstrap
./configure --enable-dummy
make
```
3) Install Litex through the instructions [here](https://github.com/enjoy-digital/litex)
4) Install GDB which is part of the riscv gnu toolchain
5) In a terminal, run Litex server and replace X with the port name you are using with the FPGA USB. Notice that the baudrate used here is 138236 which was shown how it was calculated above. 
```
litex_server --uart --uart-port=/dev/ttyUSBX --uart-baudrate=138236
```
You should see this output:
```
[CommUART] port: /dev/ttyUSB1 / baudrate: 138236 / tcp port: 1234
```
Note: you need to comment the line  ``self._send_server_info(client_socket)In litex_server.py`` for OpenOCD to be able to connect to litex server successfully according to [this issue](https://github.com/enjoy-digital/litex/issues/1532) 

6) In another terminal, go to the directory where OpenOCD is installed and run:
```
./src/openocd -c 'interface dummy' \
              -c 'adapter_khz 1' \
              -c 'jtag newtap lx cpu -irlen 4' \
              -c 'target create lx.cpu0 vexriscv -endian little -chain-position lx.cpu -dbgbase 0xF00F0000' \
              -c 'vexriscv cpuConfigFile cpu0.yaml' \
              -c 'vexriscv networkProtocol etherbone' \
              -c 'init' \
              -c 'reset halt'
```
You should be seeing this output in the OpenOCD terminal:
```
Open On-Chip Debugger 0.11.0+dev-04033-g058dfa50d (2023-06-25-16:38)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
DEPRECATED! use 'adapter driver' not 'interface'
Info : only one transport option; autoselect 'jtag'
DEPRECATED! use 'adapter speed' not 'adapter_khz'
adapter speed: 1 kHz

4027514880
Info : clock speed 1 kHz
Info : TAP lx.cpu does not have valid IDCODE (idcode=0x0)
Info : TAP auto0.tap does not have valid IDCODE (idcode=0x80000000)
Info : TAP auto1.tap does not have valid IDCODE (idcode=0xc0000000)
Info : TAP auto2.tap does not have valid IDCODE (idcode=0xe0000000)
Info : TAP auto3.tap does not have valid IDCODE (idcode=0xf0000000)
Info : TAP auto4.tap does not have valid IDCODE (idcode=0xf8000000)
Info : TAP auto5.tap does not have valid IDCODE (idcode=0xfc000000)
Info : TAP auto6.tap does not have valid IDCODE (idcode=0xfe000000)
Info : TAP auto7.tap does not have valid IDCODE (idcode=0xff000000)
Info : TAP auto8.tap does not have valid IDCODE (idcode=0xff800000)
Info : TAP auto9.tap does not have valid IDCODE (idcode=0xffc00000)
Info : TAP auto10.tap does not have valid IDCODE (idcode=0xffe00000)
Info : TAP auto11.tap does not have valid IDCODE (idcode=0xfff00000)
Info : TAP auto12.tap does not have valid IDCODE (idcode=0xfff80000)
Info : TAP auto13.tap does not have valid IDCODE (idcode=0xfffc0000)
Info : TAP auto14.tap does not have valid IDCODE (idcode=0xfffe0000)
Info : TAP auto15.tap does not have valid IDCODE (idcode=0xffff0000)
Info : TAP auto16.tap does not have valid IDCODE (idcode=0xffff8000)
Info : TAP auto17.tap does not have valid IDCODE (idcode=0xffffc000)
Info : TAP auto18.tap does not have valid IDCODE (idcode=0xffffe000)
Info : TAP auto19.tap does not have valid IDCODE (idcode=0xfffff000)
Warn : Unexpected idcode after end of chain: 21 0xfffff800
Error: double-check your JTAG setup (interface, speed, ...)
Error: Trying to use configured scan chain anyway...
Error: lx.cpu: IR capture error; saw 0x0f not 0x01
Warn : Bypassing JTAG setup events due to errors
[lx.cpu0] Target successfully examined.
Info : starting gdb server for lx.cpu0 on 3333
Info : Listening on port 3333 for gdb connections
Error: JTAG scan chain interrogation failed: all ones
Error: Check JTAG interface, timings, target power, etc.
Error: Trying to use configured scan chain anyway...
Error: lx.cpu: IR capture error; saw 0x0f not 0x01
Warn : Bypassing JTAG setup events due to errors
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
```
You will also notice that the LED stopped toggling which means the program running on the CPU was halted 

7) Generate the elf file of the C program. You can do this using the [caravel management soc repo](https://github.com/efabless/caravel_mgmt_soc_litex). You can run ``make <test_name.elf>`` inside any test in the directory ``caravel_mgmt_soc_litex/verilog/dv/tests-caravel/<test-name>``
Before this, make sure to remove the ``--strip-debug`` flag used in the compilation of the c program. You can find it in ``caravel_mgmt_soc_litex/verilog/dv/make/sim.makefile`` in line 43. You can also use the ready elf file you can find [here](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/blob/main/Caravel/elf_file/gpio_mgmt.elf)

8) In a third terminal, run GDB using this command: (replace the .elf file with the location of your generated elf file)
```
/opt/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-gdb /home/nouran/new_mgmt_soc/caravel_mgmt_soc_litex/verilog/dv/tests-caravel/gpio_mgmt/gpio_mgmt.elf -ex 'target extended-remote localhost:3333'
```
You should see this output in the GDB:
```
GNU gdb (SiFive GDB-Metal 10.1.0-2020.12.7) 10.1
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=x86_64-linux-gnu --target=riscv64-unknown-elf".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://github.com/sifive/freedom-tools/issues>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from /home/nouran/new_mgmt_soc/caravel_mgmt_soc_litex/verilog/dv/tests-caravel/gpio_mgmt/gpio_mgmt.elf...
Remote debugging using localhost:3333
_start () at /home/nouran/new_mgmt_soc/caravel_mgmt_soc_litex/verilog/dv/firmware/crt0_vex.S:6
6	  j crt_init
(gdb)
```
This means GDB is waiting for commands to be sent to it. You can try this:
```
(gdb) continue
```
You should be able to see the LED continue toggling again. 

Or you can run line by line by running:
```
(gdb) next
```
You can also set breakpoints and send any gdb commands you want. 

You can also use GDB in Visual Studio Code instead of using the command line to do so. To do this, open the Debug panel (CTRL + SHIFT + D) and select “Add Configuration > GDB” through the top left dropdown arrow. Create a GDB configuration in launch.json and add the following:

```
{
    "version": "0.2.0",
        "configurations": [
            {
                "name": "GDB",
                "type": "gdb",
                "request": "launch",
                "cwd": "${workspaceRoot}",
                "target": "/home/nouran/new_mgmt_soc/caravel_mgmt_soc_litex/verilog/dv/tests-caravel/gpio_mgmt/gpio_mgmt.elf",
                "gdbpath" : "/opt/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-gdb",
                "autorun": [
                    "target extended-remote localhost:3333",
                    "symbol-file /home/nouran/new_mgmt_soc/caravel_mgmt_soc_litex/verilog/dv/tests-caravel/gpio_mgmt/gpio_mgmt.elf"
                    ]
            }
            
        ]
    }
```

Change the "target" and the "symbol-file" to be the path for the .elf file of the program. Then run the debugger using the "Start Debugging" green arrow button. 

![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/31b21c6a-1cfd-4bd1-be4c-ec77e4334fdf)

Then in the Debug Console, type the command "interrupt" inorder to halt the CPU to be able to execute line by line

![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/51a4b4c5-da5d-4a3c-ae7e-b6be33752a4b)


After that, you can use the debug control buttons to restart, step over, step back, continue.

![image](https://github.com/NouranAbdelaziz/Caravel_on_FPGA/assets/79912650/cdb52bc6-5999-4005-aed6-5ed6eccd7c6e)

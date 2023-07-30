/*
 * SPDX-FileCopyrightText: 2020 Efabless Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <defs.h>   

// --------------------------------------------------------

/*
 *	Management SoC GPIO Pin Test
 *		Tests writing to the GPIO pin.
 */

void main()
{
    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 1;

    reg_gpio_ien = 1;
    reg_gpio_oe = 1;

    reg_gpio_out = 1;
    reg_gpio_out = 0;

	int i;

	reg_gpio_out = 0;
    reg_gpio_ien = 1;
	reg_gpio_oe = 1;
//	reg_gpio_pu = 0;
//	reg_gpio_pd = 0;

	/*for (i = 0; i < 10; i++) {
		// Fast blink for simulation
		reg_gpio_out = 1;
		reg_gpio_out = 1;
		reg_gpio_out = 0;
	}*/
//
	//enable debug 
	/*reg_wb_enable =1; // for enable writing to reg_debug_1 and reg_debug_2
	reg_debug_1 = 0;
	reg_debug_2 = 0;*/

	// set the mode for debug uart gpios 5 and 6 
	//reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
	//reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;
	/*reg_mprj_io_0 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

	reg_mprj_xfer = 1;
    while ((reg_mprj_xfer&0x1) == 1);*/

	debug_oeb_out_write(1);

	(*(volatile uint32_t*) CSR_DEBUG_MODE_OUT_ADDR ) = 1; // enable debug mode

	/*for (int i=0;i < 10000; i++){
        continue;
    }*/

	//reg_uart_enable = 1;
   

	while (1) {
		// Slow blink for demonstration board 
		for (i = 0; i < 10000; i++) {
			reg_gpio_out = 1;
		}
		for (i = 0; i < 50000; i++) {
			reg_gpio_out = 0;
		}
	}
}

/*
	Copyright 2024 Efabless Corp.

	Author: Efabless Corp. (ip_admin@efabless.com)

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	    www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

*/

#ifndef EF_SPIREGS_H
#define EF_SPIREGS_H

 
/******************************************************************************
* Includes
******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Macros and Constants
******************************************************************************/

#ifndef IO_TYPES
#define IO_TYPES
#define   __R     volatile const uint32_t
#define   __W     volatile       uint32_t
#define   __RW    volatile       uint32_t
#endif

#define EF_SPI_RXDATA_REG_RXDATA_BIT	((uint32_t)0)
#define EF_SPI_RXDATA_REG_RXDATA_MASK	((uint32_t)0xff)
#define EF_SPI_RXDATA_REG_MAX_VALUE	((uint32_t)0xFF)

#define EF_SPI_TXDATA_REG_TXDATA_BIT	((uint32_t)0)
#define EF_SPI_TXDATA_REG_TXDATA_MASK	((uint32_t)0xff)
#define EF_SPI_TXDATA_REG_MAX_VALUE	((uint32_t)0xFF)

#define EF_SPI_CFG_REG_CPOL_BIT	((uint32_t)0)
#define EF_SPI_CFG_REG_CPOL_MASK	((uint32_t)0x1)
#define EF_SPI_CFG_REG_CPHA_BIT	((uint32_t)1)
#define EF_SPI_CFG_REG_CPHA_MASK	((uint32_t)0x2)
#define EF_SPI_CFG_REG_MAX_VALUE	((uint32_t)0x3)

#define EF_SPI_CTRL_REG_SS_BIT	((uint32_t)0)
#define EF_SPI_CTRL_REG_SS_MASK	((uint32_t)0x1)
#define EF_SPI_CTRL_REG_ENABLE_BIT	((uint32_t)1)
#define EF_SPI_CTRL_REG_ENABLE_MASK	((uint32_t)0x2)
#define EF_SPI_CTRL_REG_RX_EN_BIT	((uint32_t)2)
#define EF_SPI_CTRL_REG_RX_EN_MASK	((uint32_t)0x4)
#define EF_SPI_CTRL_REG_MAX_VALUE	((uint32_t)0x7)

#define EF_SPI_PR_REG_PR_BIT	((uint32_t)0)
#define EF_SPI_PR_REG_PR_MASK	((uint32_t)0xff)
#define EF_SPI_PR_REG_MAX_VALUE	((uint32_t)0xFF)

#define EF_SPI_STATUS_REG_TX_E_BIT	((uint32_t)0)
#define EF_SPI_STATUS_REG_TX_E_MASK	((uint32_t)0x1)
#define EF_SPI_STATUS_REG_TX_F_BIT	((uint32_t)1)
#define EF_SPI_STATUS_REG_TX_F_MASK	((uint32_t)0x2)
#define EF_SPI_STATUS_REG_RX_E_BIT	((uint32_t)2)
#define EF_SPI_STATUS_REG_RX_E_MASK	((uint32_t)0x4)
#define EF_SPI_STATUS_REG_RX_F_BIT	((uint32_t)3)
#define EF_SPI_STATUS_REG_RX_F_MASK	((uint32_t)0x8)
#define EF_SPI_STATUS_REG_TX_B_BIT	((uint32_t)4)
#define EF_SPI_STATUS_REG_TX_B_MASK	((uint32_t)0x10)
#define EF_SPI_STATUS_REG_RX_A_BIT	((uint32_t)5)
#define EF_SPI_STATUS_REG_RX_A_MASK	((uint32_t)0x20)
#define EF_SPI_STATUS_REG_BUSY_BIT	((uint32_t)6)
#define EF_SPI_STATUS_REG_BUSY_MASK	((uint32_t)0x40)
#define EF_SPI_STATUS_REG_DONE_BIT	((uint32_t)7)
#define EF_SPI_STATUS_REG_DONE_MASK	((uint32_t)0x80)
#define EF_SPI_STATUS_REG_MAX_VALUE	((uint32_t)0xFF)

#define EF_SPI_RX_FIFO_LEVEL_REG_LEVEL_BIT	((uint32_t)0)
#define EF_SPI_RX_FIFO_LEVEL_REG_LEVEL_MASK	((uint32_t)0xf)
#define EF_SPI_RX_FIFO_LEVEL_REG_MAX_VALUE	((uint32_t)0xF)

#define EF_SPI_RX_FIFO_THRESHOLD_REG_THRESHOLD_BIT	((uint32_t)0)
#define EF_SPI_RX_FIFO_THRESHOLD_REG_THRESHOLD_MASK	((uint32_t)0xf)
#define EF_SPI_RX_FIFO_THRESHOLD_REG_MAX_VALUE	((uint32_t)0xF)

#define EF_SPI_RX_FIFO_FLUSH_REG_FLUSH_BIT	((uint32_t)0)
#define EF_SPI_RX_FIFO_FLUSH_REG_FLUSH_MASK	((uint32_t)0x1)
#define EF_SPI_RX_FIFO_FLUSH_REG_MAX_VALUE	((uint32_t)0x1)

#define EF_SPI_TX_FIFO_LEVEL_REG_LEVEL_BIT	((uint32_t)0)
#define EF_SPI_TX_FIFO_LEVEL_REG_LEVEL_MASK	((uint32_t)0xf)
#define EF_SPI_TX_FIFO_LEVEL_REG_MAX_VALUE	((uint32_t)0xF)

#define EF_SPI_TX_FIFO_THRESHOLD_REG_THRESHOLD_BIT	((uint32_t)0)
#define EF_SPI_TX_FIFO_THRESHOLD_REG_THRESHOLD_MASK	((uint32_t)0xf)
#define EF_SPI_TX_FIFO_THRESHOLD_REG_MAX_VALUE	((uint32_t)0xF)

#define EF_SPI_TX_FIFO_FLUSH_REG_FLUSH_BIT	((uint32_t)0)
#define EF_SPI_TX_FIFO_FLUSH_REG_FLUSH_MASK	((uint32_t)0x1)
#define EF_SPI_TX_FIFO_FLUSH_REG_MAX_VALUE	((uint32_t)0x1)


#define EF_SPI_TXE_FLAG	((uint32_t)0x1)
#define EF_SPI_TXF_FLAG	((uint32_t)0x2)
#define EF_SPI_RXE_FLAG	((uint32_t)0x4)
#define EF_SPI_RXF_FLAG	((uint32_t)0x8)
#define EF_SPI_TXB_FLAG	((uint32_t)0x10)
#define EF_SPI_RXA_FLAG	((uint32_t)0x20)


          
/******************************************************************************
* Typedefs and Enums
******************************************************************************/
          
typedef struct _EF_SPI_TYPE_ {
	__R 	RXDATA;
	__W 	TXDATA;
	__W 	CFG;
	__W 	CTRL;
	__W 	PR;
	__R 	STATUS;
	__R 	reserved_0[16250];
	__R 	RX_FIFO_LEVEL;
	__W 	RX_FIFO_THRESHOLD;
	__W 	RX_FIFO_FLUSH;
	__R 	reserved_1[1];
	__R 	TX_FIFO_LEVEL;
	__W 	TX_FIFO_THRESHOLD;
	__W 	TX_FIFO_FLUSH;
	__R 	reserved_2[57];
	__RW	IM;
	__R 	MIS;
	__R 	RIS;
	__W 	IC;
	__W 	GCLK;
} EF_SPI_TYPE;

typedef struct _EF_SPI_TYPE_ *EF_SPI_TYPE_PTR;     // Pointer to the register structure

  
/******************************************************************************
* Function Prototypes
******************************************************************************/



/******************************************************************************
* External Variables
******************************************************************************/




#endif

/******************************************************************************
* End of File
******************************************************************************/
          
          

/*
 * main.h
 *
 *  Created on: Sep 16, 2024
 *      Author: bogdsece
 */
#include <stdint.h>

#ifndef MAIN_H_
#define MAIN_H_

typedef struct
{
	uint32_t GPIO_AEN:1;
	uint32_t GPIO_BEN:1;
	uint32_t GPIO_CEN:1;
	uint32_t GPIO_DEN:1;
	uint32_t GPIO_EEN:1;
	uint32_t GPIO_FEN:1;
	uint32_t GPIO_GEN:1;
	uint32_t GPIO_HEN:1;
	uint32_t GPIO_IEN:1;
	uint32_t GPIO_JEN:1;
	uint32_t GPIO_KEN:1;
	uint32_t RESERVED_0:1;
	uint32_t CRCEN:1;
	uint32_t RESERVED_1:5;
	uint32_t BKPSR_AMEN:1;
	uint32_t RESERVED_2:1;
	uint32_t CCMDAT_ARAMEN:1;
	uint32_t DMA1_EN:1;
	uint32_t DMA2_EN:1;
	uint32_t DMA2_DEN:1;
	uint32_t RESERVED_3:1;
	uint32_t ETHMAC_EN:1;
	uint32_t ETHMAC_TXEN:1;
	uint32_t ETHMAC_RXE_N:1;
	uint32_t ETHMAC_PTP_EN:1;
	uint32_t OTGHSEN:1;
	uint32_t OTGHSULPIEN:1;
	uint32_t RESERVED_4:1;

}RCC_AHB1ENR_t;

typedef struct
{
	/*
	These bits are written by software to configure the I/O direction mode.
	00: Input (reset state)
	01: General purpose output mode
	10: Alternate function mode
	11: Analog mode
	*/
	uint32_t PIN_0:2;
	uint32_t PIN_1:2;
	uint32_t PIN_2:2;
	uint32_t PIN_3:2;
	uint32_t PIN_4:2;
	uint32_t PIN_5:2;
	uint32_t PIN_6:2;
	uint32_t PIN_7:2;
	uint32_t PIN_8:2;
	uint32_t PIN_9:2;
	uint32_t PIN_10:2;
	uint32_t PIN_11:2;
	uint32_t PIN_12:2;
	uint32_t PIN_13:2;
	uint32_t PIN_14:2;
	uint32_t PIN_15:2;
}GPIOx_MODE_t;

typedef struct
{
	uint32_t PIN_0:1;
	uint32_t PIN_1:1;
	uint32_t PIN_2:1;
	uint32_t PIN_3:1;
	uint32_t PIN_4:1;
	uint32_t PIN_5:1;
	uint32_t PIN_6:1;
	uint32_t PIN_7:1;
	uint32_t PIN_8:1;
	uint32_t PIN_9:1;
	uint32_t PIN_10:1;
	uint32_t PIN_11:1;
	uint32_t PIN_12:1;
	uint32_t PIN_13:1;
	uint32_t PIN_14:1;
	uint32_t PIN_15:1;
	uint32_t RESERVED:16;
}GPIOx_PIN_t;

#endif /* MAIN_H_ */

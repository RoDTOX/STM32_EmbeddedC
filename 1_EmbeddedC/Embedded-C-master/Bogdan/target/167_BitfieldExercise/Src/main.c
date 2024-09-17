/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include "main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

extern void initialise_monitor_handles(void);

int main(void)
{
	initialise_monitor_handles();
    /* Loop forever */
	printf("sizeof struct RCC_AHB1ENR_t = %d\n",sizeof(RCC_AHB1ENR_t));
	printf("Size of short = %d\n", sizeof(short));
	printf("Size of int = %d\n", sizeof(int));
	printf("Size of long = %d\n", sizeof(long));
	printf("Size of long long = %d\n", sizeof(long long));
	printf("Size of double = %d\n", sizeof(double));

	//0. Set registers according to Cortex M4 datasheet
	RCC_AHB1ENR_t volatile * const pClockControl = 	(RCC_AHB1ENR_t *)0x40023830;
	GPIOx_MODE_t volatile * const pPortDMode = 		(GPIOx_MODE_t *)0x40020C00;
	GPIOx_PIN_t volatile * const pPortDOut = 		(GPIOx_PIN_t *)0x40020C14;
	//1. Enable the clock for GPIOD pheripheral in the ahb1enr + SET 3rd bit position
	pClockControl->GPIO_DEN = 1;

	//2. Configure the mode of the IO pin as output:
	//a. clear the 24th and 25th bit positions (CLEAR)
	//b. make 24th bit position as 1 (SET)
	pPortDMode->PIN_12 = 0b01;

	while(1)
	{
		//3.SET 12th bit of the output data register to make I/O pin-12 as HIGH
		pPortDOut->PIN_12 = 1;

		//introduce small human observable delay
		//This loop executes for 10K times
		for(uint32_t i=0 ; i < 300000 ; i++ );

		//Tun OFF the LED
		pPortDOut->PIN_12 = 0;

		for(uint32_t i=0 ; i < 300000 ; i++ );
	}


	return 0;
	for(;;);
}
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

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
void generate_interrupt();

int main(void)
{
	printf("In thread mode before interrupt;\n");
	generate_interrupt();
	printf("In thread mode after interrupt;\n");
    /* Loop forever */
	for(;;);

}

void generate_interrupt()
{
	uint32_t *pSTIR 	= (uint32_t *)0xE000EF00;
	uint32_t *PISER0 	= (uint32_t *)0xE000E100;

	*PISER0 |= (1<<3);		//enable IRQ3
	*pSTIR = (3 & 0x1FF);	//activate SW interrupt for IRQ3

}

void RTC_WKUP_IRQHandler(void){
	printf("In handler mode\n");
}

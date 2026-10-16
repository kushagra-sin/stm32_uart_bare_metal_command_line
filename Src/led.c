/*
 * led.c
 *
 *  Created on: Oct 15, 2026
 *      Author: sangeetkar
 */
#include <stdint.h>
#include <stm32f4xx.h>

void LED_init(void) {
	RCC->AHB1ENR |= ((1<<0) | (1<<2));//Enable AHB1 RCC Clock for GPIOA and GPIOC

	GPIOA->MODER &= ~(3u<<10); //Clear GPIOA 10th and 11th BIT [3u = 0x0011]
	GPIOA->MODER |= (1u<<10); //Set GPIOA 10th and 11th BIT to output mode [01 = General Purpose Output Mode]
	GPIOC->MODER &= ~(3u<<26); //Clear GPIOA 10th and 11th BIT [3u = 0x0011]
	GPIOC->MODER |= (0u<<26); //Set GPIOA 10th and 11th BIT to input mode [00 = Input/Reset Mode]
}

void LED_ON(void) {
	GPIOA->BSRR |= (1<<5);
}

void LED_OFF(void) {
	GPIOA->BSRR |= (1<<21);
}

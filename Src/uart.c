/*
 * uart.c
 *
 *  Created on: Oct 15, 2026
 *      Author: sangeetkar
 */
#include <stdio.h>
#include <stm32f4xx.h>
/*USART2 is Virtual COM Port. It is connected to APB1 Bus
 * RCC APB1 USART2 Pin is 17th Bit
 * Alternative Func: USART2 TX = PA2 [AF7] and USART2 RX = PA3 [AF7]
 * To use GPIO PA2 and PA3 we need to enable AHB1 also since PA2 and PA3 are under ABH1 Bus
 * Set Baud Rate Register. Formula for Baud Rate= (P + B/2) / B [B = Baud Rate (Eg 115200) and P = Peripheral Clock Freq]
 * Enable TX, RX and USART in USART2 Control Register. TE = 3rd Bit, RE = 2nd Bit and USARTEN = 13th Bit
 * We send data in UART via Data Register. But first we check if TX is Empty using Status Register
 * Status Register TX Empty = 7th
 */
#define GPIOAEN (1<<0)
#define USART2EN (1<<17)

#define PERIPCLK 16000000
#define BAUDRATE 115200

#define TXEN (1<<3)
#define RXEN (1<<2)
#define USARTEN (1<<13)

#define SR_TXE (1<<7)
#define SR_RXNE (1<<5)

void UART_Send_CH(int ch);
static uint16_t calc_baud_rate(uint32_t peripclk, uint32_t baudrate);
int __io_putchar(int ch);

void uart_init(void){
	RCC->AHB1ENR |= GPIOAEN;
	RCC->APB1ENR |= USART2EN;

	GPIOA->MODER &= ~(3u<<4); //PA2 Reset
	GPIOA->MODER |= (2u<<4); //PA2 Set to Alternative Function Mode
	GPIOA->MODER &= ~(3u<<6); //PA3 Reset
	GPIOA->MODER |= (2u<<6); //PA3 Set to Alternative Function Mode

	GPIOA->AFR[0] &= ~(15u<<8); //Clears Bit 8 [PA2] in Alternate Function Register
	GPIOA->AFR[0] |= (7u<<8); //PA2 set to AF7 in Alternate Function Register
	GPIOA->AFR[0] &= ~(15u<<12); //Clears Bit 12 [PA3] in Alternate Function Register
	GPIOA->AFR[0] |= (7u<<12); //PA3 set to AF7 in Alternate Function Register

	USART2->BRR = calc_baud_rate(PERIPCLK, BAUDRATE);
	USART2->CR1 = USARTEN;
	USART2->CR1 |= TXEN | RXEN;
}

char UART_Read_CH(void){
	while(!(USART2->SR & SR_RXNE));
	return USART2->DR;
}
void UART_Send_CH(int ch){
	while(!(USART2->SR & SR_TXE));
	USART2->DR = (ch & 0xFF);
}

int __io_putchar(int ch){
	UART_Send_CH(ch);
	return ch;
}
static uint16_t calc_baud_rate(uint32_t peripclk, uint32_t baudrate) {
	return ((peripclk + (baudrate/2))/baudrate);
}


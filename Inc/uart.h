/*
 * uart.h
 *
 *  Created on: Oct 15, 2026
 *      Author: sangeetkar
 */
#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <stm32f4xx.h>

void uart_init(void);
char UART_Read_CH(void);

#endif /* UART_H_ */

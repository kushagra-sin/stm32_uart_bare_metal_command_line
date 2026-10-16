#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx.h>
#include "uart.h"
#include "led.h"

char ip;

int main(void)
{
	uart_init();
	LED_init();
    /* Loop forever */
	while(1){
		printf("\r\n===INTERACTIVE TERMINAL USING STM32 UART BARE METAL===\r\n");
		printf("---Press 1 to turn ON LED\r\n");
		printf("---Press ANY KEY to turn OFF LED\r\n");
		ip = UART_Read_CH();
		if(ip=='1'){
			printf("\r\n==You entered 1, LED ON==\r\n");
			LED_ON();
		}
		else{
			printf("\r\n==You entered %c, LED OFF==\r\n", ip);
			LED_OFF();
		}
	}
}

#include <stdio.h>
#include "stm32f401xc.h"

// DBGMCU_BASE

void USART1_write(uint8_t data){
	// Bit 7 TXE: Transmit data register empty
	// 0: Data is not transferred to the shift register
	// 1: Data is transferred to the shift register
	while(!((USART1->SR)&(1<<7)));
	USART1->DR = data;
}

void iterate(uint8_t* data){
	while(*data){
		USART1_write(*data++);
	}
}

uint32_t a;

int main(){

	RCC->APB2ENR |= (1U<< 4); // Bit 4 USART1EN: USART1 clock enable
	RCC->AHB1ENR |= (1U<< 0); // Bit 0 GPIOAEN: IO port A clock enable

	GPIOA->MODER &=~(3<<18); // setting 10: Alternate function mode at PA9
	GPIOA->MODER |= (2<<18);


	GPIOA -> AFR[1]  |= (7 << 4); // TX 0111: AF7 for UART 1..2 AF-> Alternate Function
	// Clock speed 16MHz
	USART1->BRR = (104<<4)|2; //9600 BAUD RATE
	USART1->CR1 |= (1U << 3); // TRASMITTER ENABLE
	USART1->CR1 |= (1U << 13); // USART ENABLE

	uint32_t *deviceDataAdd = (uint32_t*)DBGMCU_BASE;

	uint32_t deviceId = *deviceDataAdd & DBGMCU_IDCODE_DEV_ID_Msk;
	uint32_t revId = *deviceDataAdd & DBGMCU_IDCODE_REV_ID_Msk;

	if(revId == 0x10000){
	iterate("RevZ\r\n");
	} else if(revId == 0x1001 ){
	iterate("RevA\r\n");
	}

	if(deviceId == 0x423){
	iterate("B/C\r\n");
	} else if(deviceId == 0x433) {
	iterate("D/E");
	}
}


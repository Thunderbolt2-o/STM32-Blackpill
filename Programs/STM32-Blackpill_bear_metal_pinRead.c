#include <stdio.h>

// These are base addresses taken form memory map

uint32_t pRccClkBaseAdd = 0x40023800;
uint32_t pGPIOCBaseAdd =  0x40020800;
uint32_t pGPIOABaseAdd = 0x40020000;

int main(){
	
	uint32_t *RCC_AHB1ENR = (uint32_t*)(pRccClkBaseAdd + 0x30); // adding offset for the register
	
	*RCC_AHB1ENR |= (1U<<2); // GPIOC Enabled
	
    uint32_t *GPIOC_MODER = (uint32_t*)(pGPIOCBaseAdd + 0x00); // adding offset for GPIOC mode register
    
    *GPIOC_MODER |= (1U<<26);
    *GPIOC_MODER &=~(1U<<27);
    
	*RCC_AHB1ENR |= (1U<<0); // GPIOA Enabled
	
	uint32_t *GPIOA_MODER = (uint32_t*)(0x40020000 + 0x00); // adding offset for GPIOA mode register
   
	*GPIOA_MODER &=~(1U<<1);
    *GPIOA_MODER &=~(1U<<0);
    
    uint32_t *GPIOC_ODR = (uint32_t*)(pGPIOCBaseAdd + 0x14); // adding offset for GPIOC output data register
    uint32_t *GPIOA_IDR = (uint32_t*)(pGPIOABaseAdd + 0x10); // adding offset for GPIOA input data register
    
    *GPIOC_ODR &= ~(1U<<13);
	while(1){
		if(*GPIOA_IDR & 1){
			*GPIOC_ODR &= ~(1U<<13);
		}else{
			*GPIOC_ODR = (1U<<13);
		}
}
}

/* Main thing learnt from this exercise is understanding the addresses for different registers,
 * the base address is main for different ports, so based on port base address register offsets 
 * are set so we will get for portA register from its base address and port c from its base address
 * and naming is needed to be kept in mind 
 * 
 */ 

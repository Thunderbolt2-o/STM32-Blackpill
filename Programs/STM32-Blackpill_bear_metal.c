#include <stdio.h>

// These are base addresses taken form memory map
uint32_t pRccClkBaseAdd = 0x40023800;
uint32_t pGPIOCBaseAdd =  0x40020800;

int main(){
	uint32_t *RCC_AHB1ENR = (uint32_t*)(pRccClkBaseAdd + 0x30); // adding offset for the register
	*RCC_AHB1ENR |= (1U<<2);
    uint32_t *GPIOx_MODER = (uint32_t*)(pGPIOCBaseAdd + 0x00); // adding offset for GPIOC mode register
    *GPIOx_MODER |= (1U<<26);
    *GPIOx_MODER &=~(1U<<27);
    uint32_t *GPIOx_ODR = (uint32_t*)(pGPIOCBaseAdd + 0x14); // adding offset for GPIOC output data register
	while(1){
		*GPIOx_ODR ^= (1U<<13);
		for(int i=0;i<500000;i++){}
	}
}

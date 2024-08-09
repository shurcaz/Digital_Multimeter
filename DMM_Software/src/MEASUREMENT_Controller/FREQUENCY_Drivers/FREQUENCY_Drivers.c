#include "FREQUENCY_Drivers.h"

//Sets up TIM2 in external clock mode with its counting clock being the incoming frequency to be measured.
//Based on the current SysTick timings (in our case - 500ms), returns the timer's count after calculation.
void FRQ_init(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	//Set PA0 to alternate function mode to be used as an external clock.
	GPIOA->MODER &= 0xFFFFFFFC;
	GPIOA->MODER |= 0x00000002;

	//Set PA0's alternate function to AF1
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL0_Msk;
	GPIOA->AFR[0] |= 0x00000001;

	//Set TIM2 to external clock mode
	TIM2->SMCR |= TIM_SMCR_ECE;

	//Preload the auto reload register with default values
	TIM2->ARR = 0xFFFFFFFF;
}

//Set of functions to enable and disable the timer when not in use.
void FRQ_DisableTimer(void){
	TIM2->CR1 &= ~TIM_CR1_CEN;
	TIM2->CNT = 0;
}

void FRQ_EnableTimer(void){
	TIM2->CR1 |= TIM_CR1_CEN;
}


//Based on the amount counted within a period of time (ms), return the frequency.
uint32_t FRQ_getFrequency(double period_ms){
	count = TIM2->CNT;
	TIM2->CNT = 0;
	
	double frequency = count * 1 / (period_ms / 1000);
	
	frequency *= 0.997; //Offset of around 0.3%
	return (uint32_t)frequency;
}

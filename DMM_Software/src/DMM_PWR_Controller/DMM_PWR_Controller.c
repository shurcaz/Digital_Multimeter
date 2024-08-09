#include "DMM_PWR_Controller.h"
#include "stm32f407xx.h"

void configure(void);
void reconfigure(void);

void configure(void) {
	// Allow access to RTC
	
	// Set to enter standby mode
	// Set PWR_CR_PDDS to 0
	PWR->CR &= ~PWR_CR_PDDS;
	
	// set voltage regulator to low-power mode during stop mode
	// Set PWR_CR_LPDS to 0
	PWR->CR |= PWR_CR_LPDS;
	
	// Disable hardware enable signal
	GPIOB->BSRR |= GPIO_BSRR_BR4;
	
	// Disable clocks
	RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN;
	RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
	
	// Disable systick
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	
}

void reconfigure(void) {
	// Enable systick
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	// Enable clocks
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
	// Enable hardware enable signal
	GPIOB->BSRR &= ~GPIO_BSRR_BS4;
	GPIOB->BSRR |= GPIO_BSRR_BS4;
}

void PWR_enterStopMode(void) {
	configure();
	
  // Set SLEEPDEEP bit of Cortex System Control Register
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  
	// Request Wait For Event
	__WFI();
	
  // Reset SLEEPDEEP bit of Cortex System Control Register
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;  
	
	reconfigure();
	
}

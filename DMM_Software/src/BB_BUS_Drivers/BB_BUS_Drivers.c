#include "stm32f407xx.h"
#include "BB_BUS_Drivers.h"


// BUS INITIALISERS

// Configure J5 5-bit bus
// Configure PB4, PB5, PB7, PB8 and PB15 to
// GP outputs with PP for bus output
void BusJ5_init(void) {
	// Enable clock to port B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
	// MODER: "01", OTYPER: '0', PUPDR: "00"
	// configure simultaneously: PB4, PB5, PB7, PB8, PB15
	// Below format is longer than standard hex assignment but more readable
	GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER7 | GPIO_MODER_MODER8 | GPIO_MODER_MODER15))
									| (0x01 << GPIO_MODER_MODER4_Pos)
									| (0x01 << GPIO_MODER_MODER5_Pos)
									| (0x01 << GPIO_MODER_MODER7_Pos)
									| (0x01 << GPIO_MODER_MODER8_Pos)
									| (0x01 << GPIO_MODER_MODER15_Pos);
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT4 | GPIO_OTYPER_OT5 | GPIO_OTYPER_OT7 | GPIO_OTYPER_OT8 | GPIO_OTYPER_OT15);
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD4 | GPIO_PUPDR_PUPD5 | GPIO_PUPDR_PUPD7 | GPIO_PUPDR_PUPD8 | GPIO_PUPDR_PUPD15);
}


// BUS SETTERS


// Set Bus J5 to value num where num is a 5-bit number
void BusJ5_set(uint32_t num) {
	// Enable clock to port B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
	// Clear current value
	GPIOB->BSRR |= 0x81B00000;
	GPIOB->BSRR &= ~0x81B00000;
	
	// Set J5 pins 3,4,5,6,7
	// Where 3 is the most significant bit
	
	// so if num = 4, writes 0b00100 to the bus
	GPIOB->BSRR |= (num & 0x10) << (GPIO_BSRR_BS4_Pos - 4);
	GPIOB->BSRR |= (num & 0x8) << (GPIO_BSRR_BS5_Pos - 3);
	GPIOB->BSRR |= (num & 0x4) << (GPIO_BSRR_BS7_Pos - 2);
	GPIOB->BSRR |= (num & 0x2) << (GPIO_BSRR_BS8_Pos - 1);
	GPIOB->BSRR |= (num & 0x1) << GPIO_BSRR_BS15_Pos;
}

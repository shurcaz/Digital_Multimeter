/*----------------------------------------------------------------------------
 * Name:    STM32F4 Digital Multimeter Software
 * Purpose: main controller for the DCT Multimeter Project
 * Note(s): v0.0
 *----------------------------------------------------------------------------
 * Supplied under the terms of the MIT Open-Source License:
 *
 * Copyright (c) 2022 Electronic Engineering, Year 2, Team 2
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *
 *  STM32F4 Main Controller
 *  Digital Multimeter hardware must be connected to the board according to:
 *		- J5_3 to J5_7 where J5_3 is the most significant bit for the selector
 *		- +/-3V output to J6_3
 *		- +/-100mV output to J6_4
 *
 *
 *		- Selector[0]										to			J5_3
 *		- Selector[1]										to			J5_4
 *		- Selector[2]										to			J5_5
 *		- +/-3V ouput										to			J6_3
 *		- +/-100mV output 							to			J6_4
 *
 *    - external button for modes     to      PE4 (J7_3)
 *    - external frequency clock      to      PA0
 *
 *----------------------------------------------------------------------------*/


#include "stm32f407xx.h"

// Modules
#include "MEASUREMENT_Controller/MEASUREMENT_Controller.h"
#include "BB_BUS_Drivers/BB_BUS_Drivers.h"
#include "MULTIMETER_LCD_Drivers/MULTIMETER_LCD_Drivers.h"
#include "DMM_PWR_Controller/DMM_PWR_Controller.h"
 
 
//////////////////////////////////////////////	GLOBAL VARIABLES	 //////////////////////////////////////////////


//Defines the current number of modes.
#define NUM_OF_MODES 5

//Default starting mode.
#define DEFAULT_MODE VOLTAGE

//Used to indicate which mode the multimeter will be in.
//Changes based on an interrupt triggered by the blue button connected to PA0 on the discovery board.
//More modes can be added here and then appended to the MODE_Switch_XXX functions with their required functionality.
typedef enum {
	VOLTAGE,
	CURRENT,
	RESISTANCE,
	AC,
	FREQUENCY
} MODE;

//Set to VOLTAGE by default, in future will read from memory to switch to last used state before powering off.
static MODE Mode = DEFAULT_MODE;

//Current SysTick intervals (ms)
#define SYSTICK_MS 500

// Debounce count
#define SISTICKS_BETWEEN_MODE_UPDATES 2
static int debounceCount = 0;

// Low power mode state
static int lowPowerOn = 1;
static int inactiveCount = 0;

//////////////////////////////////////////////	FUNCTION DECLARATIONS	 //////////////////////////////////////////////


// DMM declarations
void DMM_init(void);
void DMM_setMode(void);

// Systick Functions
void MODE_Switch_SysTick_Init(void);
void SysTick_Handler(void);

//Mode_Switch definitions
void EXTI4_IRQHandler(void);
void MODE_Switch_Init(void);
void MODE_Switch_Write(void);
void incrementInactiveCount(void);


///////////////////////////////////////////////////	 MAIN	 //////////////////////////////////////////////


int main(void){
	DMM_init();
	DMM_setMode();
	
	while (1) {}
}

void DMM_init(void) {
	MEASUREMENT_CONTROLLER_INIT();
	MODE_Switch_Init();
	MODE_Switch_SysTick_Init();
	MM_LCD_Init();
	BusJ5_init();
}

void MODE_Switch_Init(void){
	//Enabling write clock to GPIOE port and SYSCFG registers.
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* GPIO Configuration for PE4 - Input with a pull-down resistor and default settings
	MODER   -> 0x00 - Input
	OTYPER  -> 0x00 - Output Push-pull (default)
	OSPEEDR -> 0x00 - Low Speed (default)
	PUPDR   -> 0x10 - Configured to have a pull-down resistor
	*/

	GPIOE->MODER &= ~GPIO_MODER_MODER4;

	GPIOE->OTYPER &= ~GPIO_OTYPER_OT4;
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4;

	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD4_Msk;
	GPIOE->PUPDR |= 0x00000200;

	/*Interrupt Configurations*/

	//Configures SYSCFG_EXTICR1 to take interrupts from PE3.
	SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI4;
 	SYSCFG->EXTICR[1] |= 0x04;

	//This interrupt is set to not be masked by the IMR.
	EXTI->IMR |= EXTI_IMR_MR4;

	//Set to trigger the interrupt on a falling-edge.
	EXTI->FTSR |= EXTI_FTSR_TR4;

	//Enables interrupt EXTI4_IRQ within the main interrupt controller NVIC.
	NVIC_EnableIRQ(EXTI4_IRQn); //EXTI4_IRQHandler will then be used to run the funtion upon being triggered.
}

//Interrupt which is triggered upon a falling-edge state change on PA0, in this case pressing the blue button.
void EXTI4_IRQHandler (void) {
	//Resets the interrupt.
	EXTI->PR = EXTI_PR_PR4;
	
	if (debounceCount == 0) {
		
		if (lowPowerOn) {
			lowPowerOn = 0;
		} else {
			//Increments to the next mode and if it exceeds the current max amount of modes, loops back around to VOLTAGE mode.
			Mode++;
			if (Mode > NUM_OF_MODES-1){
				Mode = DEFAULT_MODE;
			}
			
			DMM_setMode();
		}
		
		debounceCount = SISTICKS_BETWEEN_MODE_UPDATES;
	}
	
}

void DMM_setMode(void) {
	switch(Mode){
		case VOLTAGE:
			BusJ5_set(0x10); // Voltage (10000) (first bit is enable)
			MM_SET_DC();
			break;
		
		case RESISTANCE:
			BusJ5_set(0x18); // resistance (11000)
			MM_SET_Resistance();
			break;
		
		case CURRENT:
			BusJ5_set(0x14); // Current (10100)
			MM_SET_Current();
			break;
		
		case AC:
			BusJ5_set(0x10); // Voltage (10000)
			MM_SET_AC();
			break;
		
		case FREQUENCY:
			BusJ5_set(0x1C); // Frequency (11100)
			MM_SET_FREQUENCY();
			break;
	}
}

//SysTick section

//Initialises and configues the SysTick interrupt.
void MODE_Switch_SysTick_Init(){
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/2); //500ms
}

//On every tick of the SysTick interrupt it will output the corresponding mode's values onto the LCD.
void SysTick_Handler(void) {
	MODE_Switch_Write();
	if (debounceCount > 0) --debounceCount;
}

//LCD Section

//Writes the corresponding output to the LCD based on the current mode.
void MODE_Switch_Write(void){
	double result;
	
	if(Mode == FREQUENCY) FRQ_ToggleTimer(1);
  else FRQ_ToggleTimer(0);
	
	switch(Mode){
		// VOLTAGE //
		case VOLTAGE:
			result = getVoltage();
		
			if (result > -0.001 && result < 0.001) {
				incrementInactiveCount();
			}
			
			MM_WRITE_DC( result );
			break;
		
		// RESISTANCE //
		case RESISTANCE:
			result = getResistance();
		
			if (result > 4000000) {
				incrementInactiveCount();
			}
		
			MM_WRITE_Resistance( getResistance() );
			break;
		
		// CURRENT //
		case CURRENT:
			result = getCurrent();
		
			if (result > -0.001 && result < 0.001) {
				incrementInactiveCount();
			}
			
			MM_WRITE_Current( result );
			break;
		
		// AC //
		case AC:
			MM_WRITE_AC( getACVoltage() );
			break;
		
		// FREQUENCY //
		case FREQUENCY:
			result = getFrequency( SYSTICK_MS );
			if (result < 0.1) {
				incrementInactiveCount();
			}
			MM_WRITE_FREQUENCY(getFrequency( SYSTICK_MS ));
			break;
			
	}
}

void incrementInactiveCount(void) {
	if (inactiveCount == 20) {
		inactiveCount = 0;
		lowPowerOn = 1;
		MM_WRITE_lowPower();
		PWR_enterStopMode();
	} else {
		++inactiveCount;
	}
}

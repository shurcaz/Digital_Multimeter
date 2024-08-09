#include "MULTIMETER_LCD_Drivers.h"
#include "stm32f407xx.h"
#include "../PB_LCD_Drivers/PB_LCD_Drivers.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Defines the maximum buffer size that will be streamed into the LCD_WriteString.
//Covers an entire row of the LCD display.
#define BUFFERSIZE 16

//Main buffer that will be used to append any incoming data into.
static char LCD_Output [BUFFERSIZE];

// EXTERNAL FUNCTIONS //

//Re-uses the PB_LCD_Init function to initialise the LCD.
//Then sets up initial text on the LCD.
void MM_LCD_Init(void){
	PB_LCD_Init();
}

void MM_SET_DC(void) {
	// Clear Display
	PB_LCD_Clear();
	
	// Writing Voltage Reading to LCD Line 1
	// Writing word "Voltage" to display
	PB_LCD_GoToXY(0,0);
	PB_LCD_WriteString("Voltage: ", BUFFERSIZE);
}

// Display DC
void MM_WRITE_DC(double voltageReading){
	MM_SET_DC();
	
	// Clear string buffer
	memset(LCD_Output, 0, BUFFERSIZE);
	
	// Displaying with mV units if less than 1V, written to buffer
	if (fabs(voltageReading) < 1){
		snprintf(LCD_Output, BUFFERSIZE, "%.1lf mV        ", (voltageReading * 1000));
	} else {
		snprintf(LCD_Output, BUFFERSIZE, "%.3lf V         ", voltageReading);
	}
	// Write Buffer to display
	PB_LCD_GoToXY(0,1);
	PB_LCD_WriteString(LCD_Output, BUFFERSIZE);
}

void MM_SET_Current(void) {
	// Clear Display
	PB_LCD_Clear();
	
	// Writing Current Reading to LCD Line 1
	// Writing word "Current" to display
	PB_LCD_GoToXY(0,0);
	PB_LCD_WriteString("Current: ", BUFFERSIZE);
}

// Display Current
void MM_WRITE_Current(double currentReading){
	MM_SET_Current();
	
	// Clear string buffer
	memset(LCD_Output, 0, BUFFERSIZE);
	
	// Displaying with mA units if less than 1A, written to buffer
	snprintf(LCD_Output, BUFFERSIZE, "%.1lf mA        ", (currentReading * 1000));
	
	// Write Buffer to display
	PB_LCD_GoToXY(0,1);
	PB_LCD_WriteString(LCD_Output, BUFFERSIZE);
}

void MM_SET_Resistance(void) {
	// Clear Display
	PB_LCD_Clear();
	
	// Writing Resistance Reading to Both LCD Lines
	// Writing word "Resistance" to display line 1
	PB_LCD_GoToXY(0,0);
	PB_LCD_WriteString("Resistance: ", BUFFERSIZE);
}

// Display Resistance
void MM_WRITE_Resistance(double resistanceReading){
	MM_SET_Resistance();
	
	// Clear string buffer
	memset(LCD_Output, 0, BUFFERSIZE);

	// Displaying with correct SI multiplier + Ohm units
	// creating local int variable to store a comparitor for the largest reading
	double absReading = fabs(resistanceReading);
	
	// switch between units with if statements
	if (absReading < 1000){
		snprintf(LCD_Output, BUFFERSIZE, "%.0lf Ohms        ", resistanceReading);
	} else if (absReading < 1000000) {
		snprintf(LCD_Output, BUFFERSIZE, "%.3lfk Ohms        ", (resistanceReading / 1000));
	} else if (absReading < 1000000000) {
		snprintf(LCD_Output, BUFFERSIZE, "%.3lfM Ohms        ", (resistanceReading / 1000000));
	} else {
		snprintf(LCD_Output, BUFFERSIZE, "%.0lf Ohms        ", resistanceReading);
	}
	
	// Write Buffer to display
	PB_LCD_GoToXY(0,1);
	PB_LCD_WriteString(LCD_Output, BUFFERSIZE);
}

void MM_SET_AC(void) {
	// Clear Display
	PB_LCD_Clear();
	
	// Writing Voltage Reading to LCD Line 0
	PB_LCD_GoToXY(0,0);
	PB_LCD_WriteString("Vrms: ", BUFFERSIZE);
}

// Display AC
void MM_WRITE_AC(double Vrms){
	MM_SET_AC();
	// Displaying with correct SI multiplier + V units
	
	// Clear string buffer
	memset(LCD_Output, 0, BUFFERSIZE);
	
	// Displaying with mV units if less than 1V, written to buffer
	if (fabs(Vrms) < 1){
		snprintf(LCD_Output, BUFFERSIZE, "%.1lf mV        ", (Vrms * 1000));
	} else {
		snprintf(LCD_Output, BUFFERSIZE, "%.3f V          ", Vrms);
	}
	// Write Buffer to display
	PB_LCD_GoToXY(0,1);
	PB_LCD_WriteString(LCD_Output, BUFFERSIZE);
}

void MM_WRITE_lowPower(void) {
	PB_LCD_Clear();
	PB_LCD_GoToXY(0,0);
	PB_LCD_WriteString("Low-power ON", BUFFERSIZE);
	PB_LCD_GoToXY(0,1);
	PB_LCD_WriteString("Press To Wake Up", BUFFERSIZE);
}

void MM_SET_FREQUENCY(void) {
	// Clear Display
	PB_LCD_Clear();

	// Writing Frequency Reading to LCD Line 1
	PB_LCD_GoToXY(0,0);
	PB_LCD_WriteString("Frequency:", BUFFERSIZE);
}

void MM_WRITE_FREQUENCY(double freq) {
	// Displaying with correct SI multiplier + Hz units
	MM_SET_FREQUENCY();
	
	// Clear string buffer
	memset(LCD_Output, 0, BUFFERSIZE);
	
	// switch between units with if statements
	if (freq < 1000){
		snprintf(LCD_Output, BUFFERSIZE, "%.0lf Hz         ", freq);
	} else if (freq < 1000000) {
		snprintf(LCD_Output, BUFFERSIZE, "%.3lf kHz        ", (freq / 1000));
	} else if (freq < 1000000000) {
		snprintf(LCD_Output, BUFFERSIZE, "%.3lf MHz        ", (freq / 1000000));
	} else {
		snprintf(LCD_Output, BUFFERSIZE, "%.0lf Hz         ", freq);
	}
	
	PB_LCD_GoToXY(0,1);
	PB_LCD_WriteString(LCD_Output, BUFFERSIZE);
}

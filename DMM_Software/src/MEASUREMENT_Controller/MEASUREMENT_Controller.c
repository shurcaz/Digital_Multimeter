#include "stm32f407xx.h"
#include "MEASUREMENT_Controller.h"
#include "ADC_Drivers/ADC_Drivers.h"
#include "CONVERSION_Lib/CONVERSION_Lib.h"
#include "FREQUENCY_Drivers/FREQUENCY_Drivers.h"
#include <math.h>


// INTERNAL FUNCTIONS //


static double V_highRange(void) {
	return convertToVoltage_highRange( ADC1_getConversion(14) );
}


static double V_lowRange(void) {
	return convertToVoltage_lowRange( ADC1_getConversion(15) );
}


// EXTERNAL FUNCTIONS //


void MEASUREMENT_CONTROLLER_INIT(void) {
	ADC1_init();
	FRQ_init();
}


double getVoltage(void) {
	
	// take initial sample
	double V_REAL = V_highRange();
	// ADC input 14 is -/+ 10V range
	// ADC input 15 is -/+ 100mV range
	
	if (V_REAL < 0.1 && V_REAL > -0.1) {
		// if in +/- 100mV range
		return V_lowRange();
		
	} else {
		// if in +/- 10V range
		return V_REAL;
	}
}


double getCurrent(void) {
	// no need to convert as conversion is
	// V_ADC / 1 ohm
	return V_lowRange();
}


double getResistance(void) {
	return convertToResistance(getVoltage());
}


double getACVoltage() {
	ADC1_setSampleSize(1);
	
	// Stats version
	// ~ 250nS per conversion
	//int freq = 10000;
	double VsquaredTotal = 0;
	int n = 1000;
	
	for (int i = 0; i < n; ++i) {
		VsquaredTotal += pow(getVoltage(), 2);
	}
	
	ADC1_resetSampleSize();
	double result = sqrt(VsquaredTotal / n);
	return (1.2197 * result) + 0.0015;
}


void FRQ_ToggleTimer(int enable){
	if(enable) FRQ_EnableTimer();
	else FRQ_DisableTimer();
}

uint32_t getFrequency(double period_ms){
	return FRQ_getFrequency( period_ms );
}

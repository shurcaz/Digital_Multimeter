#include "CONVERSION_Lib.h"
#include <math.h>

// Hardware Error
// High Voltage Error
#define VHIGH_SLOPE_ERROR 0.0879
#define VHIGH_OFFSET_ERROR 0.0623

// Low Voltage Error
#define VLOW_SLOPE_ERROR -0.0007
#define VLOW_OFFSET_ERROR 0.0057

// Current Error
#define CURRENT_SLOPE_ERROR 0
#define CURRENT_OFFSET_ERROR 0

// Resistance Error
#define RESISTANCE_SLOPE_ERROR -0.1053
#define RESISTANCE_OFFSET_ERROR -744.36


#define CALIBRATION_MODE 0 // 1 == calibration mode


// Calibrates final reading according to our slope and offset error
static double calibrate(double value, double slope, double offset) {
	if (!CALIBRATION_MODE) {
		return ((1 + slope) * value) + offset;
	} else {
		return value;
	}
}

// Converts ADC output to +/-10V voltage reading
double convertToVoltage_highRange(double V_ADC) {
	double V_REAL = (V_ADC - 1.5) * (20/3);
	return calibrate(V_REAL, VHIGH_SLOPE_ERROR, VHIGH_OFFSET_ERROR);
}


// Converts ADC output to +/- 100mV voltage reading
double convertToVoltage_lowRange(double V_ADC) {
	double V_REAL = (V_ADC - 1.5) / 15;
	return calibrate(V_REAL, VLOW_SLOPE_ERROR, VLOW_OFFSET_ERROR);
}


// Converts ADC output to current reading
double convertToCurrent(double V_ADC) {
	// just same result as voltage in milli range
	return calibrate(V_ADC, CURRENT_SLOPE_ERROR, CURRENT_OFFSET_ERROR);
}


// Converts ADC output to resistance reading
double convertToResistance(double V_ADC) {
	// Resistance = Voltage measured by hardware / 9.3uA
	double Resitance = V_ADC / (9.3 * pow(10,-6));
	return calibrate(Resitance, RESISTANCE_SLOPE_ERROR, RESISTANCE_OFFSET_ERROR);
}
	

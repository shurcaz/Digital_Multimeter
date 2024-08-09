/*----------------------------------------------------------------------------
 * Name:    CONVERSION_Lib.h
 * Purpose: Conversion formulas for the DCT Multimeter Project
 * Note(s): v0.0
 *----------------------------------------------------------------------------
 * Supplied under the terms of the MIT Open-Source License:
 *
 * Copyright (c) 2022 Connall Shurey
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

#ifndef __CONVERSION_LIB_H
#define __CONVERSION_LIB_H

// Functions to convert read voltage to the value read 
// by the hardware according to the mode


// Converts ADC output to +/-10V voltage reading
extern double convertToVoltage_highRange(double V_ADC);


// Converts ADC output to +/- 100mV voltage reading
extern double convertToVoltage_lowRange(double V_ADC);


// Converts ADC voltage to current measured by hardware
// takes a voltage input of type double
// returns current value of type double
extern double convertToCurrent(double V_ADC);


// Converts ADC voltage to resistance measured by hardware
// takes a voltage input of type double
// returns resistance value of type double
double convertToResistance(double V_ADC);

#endif

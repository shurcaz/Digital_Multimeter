/*----------------------------------------------------------------------------
 * Name:    ADC_Drivers.h
 * Purpose: Low-level driver functions for the ADC on the STM3207-- devices
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
 
#ifndef __ADC_DRIVERS_H
#define __ADC_DRIVERS_H

#include "stm32f407xx.h"

// ADC Definitions

// Initialise ADC 1
// Sets configuration registers and enables ADC 1
extern void ADC1_init(void);


// converts input n of the ADC to voltage
// takes ADC input n of type uint
// returns calibrated conversion as double in Volts
extern double ADC1_getConversion(uint32_t n);


// sets number of samples to be taken in ADC averaging function
// the higher the number of samples, the higher the accuracy
// Takes sample number of type uint
extern void ADC1_setSampleSize(uint32_t n);


// resets sample size to init value
extern void ADC1_resetSampleSize(void);

#endif

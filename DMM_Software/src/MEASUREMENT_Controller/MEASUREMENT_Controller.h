/*----------------------------------------------------------------------------
 * Name:    CONVERSION_Lib.h
 * Purpose: Measurement controller for the DCT Multimeter Project
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

#ifndef __MEASUREMENT_CONTROLLER_H
#define __MEASUREMENT_CONTROLLER_H

#include "stm32f407xx.h"

extern void MEASUREMENT_CONTROLLER_INIT(void);

extern double getVoltage(void);
extern double getCurrent(void);
extern double getResistance(void);
extern double getACVoltage(void);

extern void FRQ_ToggleTimer(int enable);
extern uint32_t getFrequency(double period_ms);

#endif

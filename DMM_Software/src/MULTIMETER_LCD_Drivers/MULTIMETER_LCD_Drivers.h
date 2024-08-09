/*----------------------------------------------------------------------------
 * Name:    MULTIMETER_LCD_Drivers.h
 * Purpose: Writes both identifier text and readings onto the LCD for the Multimeter
 * Note(s): v0.0
 *----------------------------------------------------------------------------
 * Supplied under the terms of the MIT Open-Source License:
 *
 * Copyright (c) 2022 Nojus Jukna
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
 
#ifndef __MULTIMETER_LCD_DRIVERS_H
#define __MULTIMETER_LCD_DRIVERS_H

#include "stm32f407xx.h"

//MULTIMETER LCD DEFINITIONS//

// Initialises the LCD
extern void MM_LCD_Init(void);

// Writes formatted versions of readings.
extern void MM_WRITE_DC(double voltageReading);

extern void MM_WRITE_AC(double voltageReading);

extern void MM_WRITE_Current(double currentReading);

extern void MM_WRITE_Resistance(double resistanceReading);

extern void MM_WRITE_FREQUENCY(double frequencyReading);



extern void MM_WRITE_lowPower(void);

// Sets mode format
extern void MM_SET_DC(void);

extern void MM_SET_AC(void);

extern void MM_SET_Current(void);

extern void MM_SET_Resistance(void);

extern void MM_SET_FREQUENCY(void);


#endif

/*----------------------------------------------------------------------------
 * Name:    PB_LCD_Drivers.h
 * Purpose: Low-level driver functions for the Busses on the York Processor
						Board Edge Connector
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

#ifndef __BB_BUS_DRIVERS_H
#define __BB_BUS_DRIVERS_H

#include "stm32f407xx.h"

// Bus Definitions

// BUS INITIALISER DECLARATIONS
extern void BusJ5_init(void);
extern void BusJ6_init(void);
extern void BusJ7_init(void);


// BUS SETTER DECLARATIONS
// takes a number and sets the bus
// to that value in binary

// set 5-bit bus J5
// writes to J5 signals 3 - 7
// where 3 is the most sig bit
extern void BusJ5_set(uint32_t num);

// set 2-bit bus J6
// writes to J6 signals 5 - 6
// where 5 is the most sig bit
extern void BusJ6_set(uint32_t num);

// set 5-bit bus J7
// writes to J7 signals 2 - 6
// where 2 is the most sig bit
extern void BusJ7_set(uint32_t num);

#endif

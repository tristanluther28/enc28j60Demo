//-----------------------------------------------------------------------------
//
//  main.c
//
//  Swallowtail LACK Enclosure Temperature Sensor Firmware
//  AVR (ATmega328P) LACK Enclosure Temperature Sensor Firmware
//
//  Copyright (c) 2021 Swallowtail Electronics
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sub-license,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//  Web:    http://tristanluther.com
//  Email:  tristanluther28@gmail.com
//
//-----------------------------------------------------------------------------

/******************** Macros *****************************/

#ifndef F_CPU
#define F_CPU 16000000UL //Set clock speed to 16MHz
#endif

#define BIT_SET(byte, bit) (byte & (1<<bit))

/******************** Includes ***************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "USART.h"
#include "ENC28J60.h"

/******************* Globals *****************************/

//Add volatile keyword so the compiler won't optimize these variables out if only used in ISR
//Add static keyword so the compiler won't erase this memory once we enter a new stack frame

/******************** Functions **************************/


/******************** Interrupt Service Routines *********/


/******************** Main *******************************/
int main(void)
{
	//DEBUG Initialize the USART Output
	USART_Init(9600);
	USART_WriteString("ENC28J60 Ethernet Controller\n\r");
	
	//Initialize the ENC28J60
	
	
	/* State machine loop */
	while (1)
	{
		
	}
}


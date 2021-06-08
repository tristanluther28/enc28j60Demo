//-----------------------------------------------------------------------------
//
//  ENC28J60.h
//
//  Swallowtail ENC28J60 Firmware
//  AVR ENC28J60 Firmware
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

/******************** Include Guard **************************/

#ifndef ENC28J60_H_
#define ENC28J60_H_

#include <avr/io.h>
#include "SPI.h"

enum tempunits {KELVIN, CELSUIS, FAHRENHEIT};

/******************* Macros **********************************/

#define BIT_SET(byte, bit) (byte & (1<<bit))

#define IPv4 0x08

#define RCR 0x00	//Read Control Register
#define RBM 0x3A	//Read Buffer Memory
#define WCR 0x40	//Write Control Register
#define WBM 0x7A	//Write Buffer Memory (Constant argument. Added here already)
#define BFS 0x80	//Bit Field Set
#define BFC 0xA0	//Bit Field Clear
#define Reset 0xFF	//System Reset command (Constant argument. Added here already)

//Common Bank
#define ECON1 0x1F	//Bank Selection Register
#define ECON2 0x1E
#define ESTAT 0x1D
#define EIE 0x1B
#define EIR 0x1C

//Bank 0
#define ERDPTL 0x00
#define ERDPTH 0x01
#define EWRPTL 0x02
#define EWRPTH 0x03
#define ERXSTL 0x08
#define ERXSTH 0x09
#define ERXNDL 0x0A
#define ERXNDH 0x0B
#define ERXRDPTL 0x0C
#define ERXRDPTH 0x0D
#define ERXWRPTL 0x0E
#define ERXWRPTH 0x0F
#define ETXSTL 0x04
#define ETXSTH 0x05
#define ETXNDL 0x06
#define ETXNDH 0x07


//Bank 1
#define ERXFCON 0x18
#define EPKTCNT 0x19

//Bank 2
#define MACON1 0x00
#define MACON3 0x02
#define MACON4 0x03
#define MABBIPG 0x04
#define MAIPGL 0x06
#define MAIPGH 0x07
#define MACLCON1 0x08
#define MACLCON2 0x09
#define MAMXFLL 0x0A
#define MAMXFLH 0x0B
#define MIREGADR 0x14
#define MICMD 0x12
#define MIRDH 0x19
#define MIRDL 0x18
#define MIWRH 0x17
#define MIWRL 0x16


//Bank 3
#define MAADR5 0x00
#define MAADR6 0x01
#define MAADR3 0x02
#define MAADR4 0x03
#define MAADR1 0x04
#define MAADR2 0x05
#define MISTAT 0x0A
#define REVID 0x12

//PHY Registers
#define PHCON1 0x00
#define PHCON2 0x10
#define PHLCON 0x14

/******************* Function Declarations *******************/

void EN28J60_Init();
uint8_t ENC28J60_Transfer(uint8_t);
uint8_t ENC28J60_Transfer_Dummy(uint8_t);
uint16_t EN28J60_PHY_Read(uint8_t);

#endif
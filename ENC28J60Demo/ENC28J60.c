//-----------------------------------------------------------------------------
//
//  ENC28J60.c
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

/******************** Includes ***************************/

#include "ENC28J60.h"

/******************* Globals *****************************/

//MAC Address
char MAC[6] = {0x08,0x62,0x66,0xD7,0x3B,0xAF};
char Remote_mac[6]= {0x15,0xCC,0x20,0xE2,0xEF,0xFE};

//IP Address
char Dest_IP[4] = {192,168,0,150};
char My_IP[4] = {192,168,0,30};

//Packet Save LOC
char packet_save_loc_high = 0x00;
char packet_save_loc_low = 0x00;

/******************** Functions **************************/

//Initialize the serial connection this part relies on
void ENC28J60_Init(){
	//Initialize the serial port
	SPI_Init();
	
	return; //Return to call point
}

//Write to the ENC28J60 once
uint8_t ENC28J60_Transfer(uint8_t data){
	SPI_Enable();
	//Open the SPI Line and push data over it, get the return
	data = SPI_Transfer(data);
	SPI_Disable();
	return data; //Return the data
}

//Write to the ENC28J60 once and wait for the first dummy byte (Required for the MAC and MII registers)
uint8_t ENC28J60_Transfer_Dummy(uint8_t data){
	SPI_Enable();
	SPI_Transfer(data); //Send the data
	data = SPI_Transfer(0xFF); //Send a don't care to retrieve the value
	SPI_Disable();
	return data; //Return the data
}

//Write twice to the device, no returned data
void ENC28J60_Double_Transfer(uint8_t da, uint8_t ta){
	SPI_Enable();
	//Send both bytes
	SPI_Transfer(da);
	SPI_Transfer(ta);
	SPI_Disable();
	return; //Return to call point
}

//Open the serial port for writing
void ENC28J60_Continous_Write(uint8_t data){
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return; //Return to call point
}

//Read from the serial port
uint8_t ENC28J60_Continous_Read(){
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));
	return SPDR; //Return to call point
}

uint16_t EN28J60_PHY_Read(uint8_t PHY_Addr){
	//Set bank 2
	SPI_Enable();
	SPI_Transfer(WCR|ECON1);
	SPI_Transfer(0x02);
	SPI_Disable();
	
	SPI_Enable()
	SPI_Transfer(WCR|MIREGADR);
	SPI_Transfer(PHY_Addr);
	SPI_Disable();
	
	SPI_Enable();
	SPI_Transfer(RCR|MICMD);
	uint8_t past = SPI_Transfer(0xFF);
	SPI_Disable();
	
	SPI_Enable();
	SPI_Transfer(WCR|MICMD);
	SPI_Transfer(past|0x01);
	SPI_Disable();
	//Delay for a brief moment
	_delay_us(11);
	//Set bank 3
	SPI_Enable();
	SPI_Transfer(WCR|ECON1);
	SPI_Transfer(past|0x03);
	SPI_Disable();
	
	//Check if the PHY is busy
	SPI_Enable();
	past = SPI_Transfer(RCR|MISTAT);
	SPI_Disable();
	past = past & 0x01;
	//If keep polling to see if busy until not
	while(past == 0x01){
		SPI_Enable();
		SPI_Transfer(RCR|MISTAT);
		past = SPI_Transfer(0xFF);
		SPI_Disable();
		past = past & 0x01;
	}
	//PHY is available
	//Set to bank 2
	SPI_Enable();
	SPI_Transfer(RCR|ECON1);
	SPI_Transfer(0x02);
	SPI_Disable();
	
	//Clear the MICMD.MIIRD
	SPI_Enable();
	SPI_Transfer(RCR|MICMD);
	past = SPI_Transfer(0xFF);
	SPI_Disable();
	
	SPI_Enable();
	SPI_Transfer(WCR|MICMD);
	SPI_Transfer(~(past & 0x01));
	SPI_Disable();
	
	SPI_Enable();
	SPI_Transfer(RCR|MIRDH);
	uint8_t datah = SPI_Transfer(0xFF);
	SPI_Transfer(RCR|MIRDL);
	uint8_t datal = SPI_Transfer(0xFF);
	SPI_Disable();
	uint16_t result = datal + (8<<datah);
	return result;
}


/******************** Interrupt Service Routines *********/
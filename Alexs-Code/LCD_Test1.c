
//**********************************************************
/* NOTE: before running make sure SPI code is laoded with 
 > gpio load spi						
					
 Module pin				Raspberry pin	wiringPI#	
 
 1 VDD                        1					
 2 VSS                        6					
 3 PS (low for serial)        6					
 4 DB7/SID                    19			12		
 5 DB6/SCLK                   23			14		
 6-11 DB5-DB0                 N/C					
 12 E_RD                      N/C			
 13 RW_W                      N/C					
 14 RS (0=ctrl mode, 1=data   5				9		
 15 RES reset input           3				8		
 16 CS                        6					
 17 Led+      				  requires external bias 				
 18 Led-                      6							  */
//**********************************************************

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "font5x7int.h"

//**********************************************************
/*	Function Descriptions								  
														  
	digitalwrite(pin,value)								  
	pinMode(pin,direction)								  
	wiringPiSPIDataRW (channel, data, int length)
	wiringPiSPISetup (channel,speed)
														  */
//**********************************************************

int main (void)
{
uint8_t spiData [10] ;

// set interface speed
if (wiringPiSPISetup (0,100000) < 0)
	{
	fprintf (stderr, "Unable to open SPI device 0: %s\n", strerror (errno)) ;
	exit (1) ;
	}

wiringPiSetupSys() ;
wiringPiSetup() ;

/* setup output ports */
pinMode(8, OUTPUT); /* reset */
pinMode(9, OUTPUT); /* rs */

/* reset LCD display */
digitalWrite(8,0);
delayMicroseconds (100) ;

digitalWrite(8,1);

void write_cmd(int i)
	{
	digitalWrite(9,0); 					// set rs bit for control mode
	spiData[0]=i;
	wiringPiSPIDataRW (0, spiData, 1) ;
	}
	
void gotoxy(int x,int y)
{
	digitalWrite(9,0); 					// set rs bit for control mode
	spiData[0]=x;
	wiringPiSPIDataRW (0, spiData, 1) ;
	spiData[0]=y;
	wiringPiSPIDataRW (0, spiData, 1) ;
}
	
void write_char(char Char)
	{
	int c;
	digitalWrite(9,1); 					// set rs bit for control mode
	for(c=0;c<=5;c++)					// font set is 5 bits wide
		{
		spiData[c]=(font5x7int[Char*5+c]);
		}	
	spiData[5]=0;
	wiringPiSPIDataRW (0, spiData, 6) ;
	}
	
void write_str(char *Str)
	{
	int c;
	for(c=0;c<strlen(Str);c++)
		{
		write_char(Str[c]);
		}
	while(c<23) {
		write_char(' '); 				// fill with white space
		c++;
		}
	}

write_cmd(175);							//display on
write_cmd(167);							// reverse
write_cmd(226);							// reset display
write_cmd(47); 							// power control
write_cmd(179); 						// set row (180-row)
write_cmd(163); 						// LCD bias select
delayMicroseconds (100) ;

//Write text/graphics to display

gotoxy(179,16);							//row 1, column 0
write_str("Green Pieces");

gotoxy(178,16);							//row 2, column 0
write_str(" ");

gotoxy(177,16);							//row 3, column 0
write_str("Mystery Machine");

gotoxy(176,16);							//row 4, column 0
write_str(" ");

return 0 ;
}

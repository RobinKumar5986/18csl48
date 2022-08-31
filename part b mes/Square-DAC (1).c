// program to generate square wave with DAC interface
/*********************************************************************
 * EXP3:External DAC interface (Square Wave)
 * Developed by
 * Advanced Electronics Systems, Bengaluru
 *--------------------------------------------------------------------
 * Controller	: LPC2148
 * Project		: ALS-SDA-ARM7-09
 * Description	: This example explains about how Sqaure Wave is generated.P0.0 to P0.15 are used to get the Digital values.
 
			
       	0xff  ________
             |				|					|
             |				|					|
             | 				|					|
						 |				|					|
				0x00 |				|_________|
 
 ***************************************************************************/

#include <lpc21xx.h>

void delay(void);

int main ()
{
	PINSEL0 = 0x00000000 ;						// Configure P0.0 to P0.15 as GPIO
	PINSEL1 = 0x00000000 ;						// Configure P0.16 to P0.31 as GPIO
	IO0DIR  = 0x00FF0000 ;
   
	while(1)
    {
    	  IO0PIN = 0x00000000;
        delay();
        IO0PIN = 0x00FF0000;
        delay();
    }
}   

void delay(void)
{
	  unsigned int i=0;
   	for(i=0;i<=3000;i++);
}
 

/********************************************************************************
 * EXP4 : SEVEN SEGMENT DISPLAY
 * Developed by
 * Advanced Electronics Systems. Bengaluru.
 *-------------------------------------------------------------------------------
 * Controller	: LPC2148
 * Project		: ALS-SDA-ARM7-09
 
 * Description	:\\\\\\\\\\\\\\\DISPLAY ARE CONNECTED IN COMMON CATHODE MODE\\\\\\\\\\\\\\\\\\\\\
	Port0 Connected to data lines of all 7 segement displays
	   a
	  ----
	f|  g |b
	 |----|
	e|    |c
	  ----  . dot
	   d
	a = P0.16					
	b = P0.17
	c = P0.18
	d = P0.19
	e = P0.20 
	f = P0.21
	g = P0.22
	dot = P0.23
	
	
	Select lines for two 7 Segments
	DIS1	P0.28
	DIS2	P0.29
	DIS3	P0.30
	DIS4	P0.31
	
	Values Correspoinding to Alphabets 1, 2, 3 and 4*/



#include <LPC21XX.h>
unsigned int delay,j;
unsigned int Switchcount=0; 
unsigned int Disp[16]={0x003F0000, 0x00060000, 0x005B0000, 0x004F0000, 0x00660000,0x006D0000,
					   0x007D0000, 0x00070000, 0x007F0000, 0x006F0000, 0x00770000,0x007C0000,
					   0x00390000, 0x005E0000, 0x00790000, 0x00710000 };

int main (void)
{
	PINSEL0 = 0x00000000;   
	PINSEL1 = 0x00000000;
	IO0DIR  = 0x00FF0000;
	IO1DIR  = 0x00000000;
	
	while(1)
	{
		IO0CLR = 0x00FF0000;		 	// clear the data lines to 7-segment displays
		IO0SET = Disp[Switchcount];	   	// get the 7-segment display value from the array
		
		 for(j=0;j<20;j++)
			for(delay=0;delay<30000;delay++);	 // 1s delay   		
	
				Switchcount++;
				if(Switchcount == 0x10)	// 0 to F has been displayed  go back to 0
			    {
				   Switchcount = 0;
				   IO0CLR  =	0x00FF0000;				
			    }
			
	}
}

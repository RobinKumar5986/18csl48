/********************************************************************************
 * EXP5.DCM Direction Control
 * Developed by
 * Advanced Electronics Systems. Bengaluru.
 *-------------------------------------------------------------------------------
 * Controller	: LPC2148
 * Project		: ALS-SDA-ARM7-09
 
 * Description	:Direction of the DCM is cotrolled in this software by alternatively inter-
 * changing the supply with the help of Relay.	Port lines: P1.16 and P1.17.  
 
 ----------------------------------------------------------------------------

*********************************************************************************/

#include<lpc214x.h>

void clock_wise(void);
void anti_clock_wise(void);
unsigned int j=0;

int main()
{
  PINSEL2 = 0XFFFFFFF0;
	//IO1CLR = 0X0000ff00;
	IO1DIR= 0X00030000;        //p1.16 and p1.17 are selected as outputs. 
	IO1SET= 0X00010000; 			//P1.16 should always high.
  				
  	while(1)
  	{
			
			clock_wise();
     	for(j=0;j<500000;j++); 		//delay
	
    	anti_clock_wise();
    	for(j=0;j<500000;j++); 		//delay
			
	} 								//End of while(1)
}									//End of Main

void clock_wise(void)
{ 
	IO1CLR = 0x00030000; 			//stop motor and also turn off relay
	for(j=0;j<500000;j++);//small delay to allow motor to turn off 
	IO1SET = 0X00030000;
		   		//Selecting the P1.17 line for clockwise and turn on motor
 }

void anti_clock_wise(void)    
{
	
	IO1CLR = 0X00030000;			//stop motor and also turn off relay
  for(j=0;j<1000000;j++); 			//small delay to allow motor to turn off 
  IO1SET = 0X00010000;			//not selecting the P1.17 line for Anti clockwise	
  	
}


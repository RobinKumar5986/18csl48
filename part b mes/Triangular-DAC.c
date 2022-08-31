// program to generate Triangular wave with DAC interface
/*********************************************************************
 * EXP3:External DAC interface (Triangle Wave)
 * Developed by
 * Advanced Electronics Systems, Bengaluru
 *--------------------------------------------------------------------
 * Controller	: LPC2148
 * Project		: ALS-SDA-ARM7-09
 * Description	: This example explains about how Triangular Wave is generated.P0.4 to P0.11 are used to get the Digital values.
			
        
        0xff     
                   /\          /\
                  /  \        /  \
                 /    \      /    \
                /      \    /      \
							 /        \  /        \
				0x00 	/		       \/          \
 
 ***************************************************************************/






#include <LPC21xx.h>

int main ()
{
	unsigned long int temp=0x00000000; 
  	unsigned int i=0;

  	IO0DIR=0x00FF0000;
   
    while(1)
    {
    	// output 0 to FE 
        for(i=0;i!=0xFF;i++)
        {
        	temp=i;
          	temp = temp << 16;
          	IO0PIN=temp;
        }
       	
		// output FF to 1   
        for(i=0xFF; i!=0;i--)
        {
        	temp=i;
          	temp = temp << 16;
          	IO0PIN=temp;
        }
	}//End of while(1)
}//End of main()


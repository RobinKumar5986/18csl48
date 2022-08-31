/*********************************************************************
 * EXP1:Internal ADC Demonstration - ADC0.4
 * Developed by
 * Advanced Electronics Systems, Bengaluru
 *--------------------------------------------------------------------
 * Controller	: LPC2148
 * Project		: ALS-SDA-ARM7-09
 * Description	: This example scans the channel ADC0.4.
 *  Voltage is varied by varying the pot R2. Since ref
 *	voltage is 3.3, ADC output range is 000 to 3FF (10 bit) 
 *	Short JP2 to enable the hardware.
***********************************************************************/


//10-bit internal ADC 
//AIN0 pin is selected 
//you can change the channel by changing PINSEL1 and ADCR value	   

#include <lpc214x.h>
#include <Stdio.h>


#define vol 3.3               	//Reference voltage
#define fullscale 0x3ff         //10 bit adc fullscale 


unsigned int data_lcd=0,i=0,n=0;
unsigned int adc_value=0,temp_adc=0,temp1,temp2,adc[8];
float temp,adc1[8];
unsigned char var[15],var1[15],fst_flag=0xff;
unsigned char *ptr,arr[]= "ADC O/P= ";
unsigned char *ptr1,dis[]="A I/P  = ";

void lcd_init(void);
void wr_cn(void);
void clr_disp(void);
void delay(unsigned int);
void lcd_com(void);						   
void wr_dn(void);
void lcd_data(void);





int main()
{					   
	  PINSEL1 = 0X04000000;   	//AD0.4 pin is selected
    IO0DIR = 0x000000FC;    	//configure o/p lines for lcd  
	
	delay(3200);
	lcd_init();	 				//LCD initialization  
  delay(3200);
	clr_disp();	 				//clear display
	delay(3200);				//delay

	ptr = dis;
	temp1 = 0x80;				//Display starting address of 1st line on LCD
	lcd_com();
	delay(800); 

    while(*ptr!='\0')
    {
   		temp1 = *ptr;
    	lcd_data();
		  ptr ++;
	} 

	ptr1 = arr;
	temp1 = 0xC0;				//Display starting address of 2nd line on LCD
	lcd_com();
	delay(800); 
        
	while(*ptr1!='\0')
    {
    	temp1 = *ptr1;
    	lcd_data();
		  ptr1 ++;
	}

    
    while(1)    //infinite loop	
    { 
     temp = 0;
     adc_value = 0;			
		 AD0CR = 0x01200004;       			////CONTROL register for ADC-AD0.4
	  
		while(((temp_adc = AD0GDR) &0x80000000)  == 0x00000000);	//to check the interrupt bit
		
		adc_value = AD0GDR;          		//reading the ADC value
		adc_value >>=6;
		adc_value &= 0x000003ff;
		temp = ((float)adc_value * (float)vol)/(float)fullscale;
			
		if(fst_flag)
		{
     fst_flag = 0x00;
			for(i=0;i<8;i++)
			{
				adc[i] = adc_value;
				adc1[i] = temp;
			}
		}			
		
		else
		{
			n=7;
			for(i=n;i>0;i--)
			{
			adc[i] = adc[i-1];
			adc1[n] = adc1[n-1];
			n = n-1;	
			}
		 adc[0] = adc_value;
		 adc1[0] = temp;
		}
		temp=0;
		adc_value=0;
		for(i=0;i<8;i++)
		{
			temp += adc1[i];
			adc_value += adc[i];
		}
		 temp = (temp/8);
		 adc_value = (adc_value/8);
		
		sprintf(var1,"%4.2fV",temp);
		sprintf(var,"%3x",adc_value); 		
		
	   	temp1 = 0x89;
	 	  lcd_com();
	 	  delay(1200); 
	 	  ptr1 = var1;
        
		while(*ptr1!='\0')
        {	        
  			temp1=*ptr1;
			  lcd_data();	
        ptr1++;
		} 
                 
        temp1 = 0xc9;
        lcd_com();
        delay(1200);
						
        ptr1 = var;
        while(*ptr1!='\0')
        {	 	
        	temp1=*ptr1;
			    lcd_data();
          ptr1++;
		}       
	}	 // end of while(1)		
} //end of main()
  
//**** LCD initialization ****//
void lcd_init()
{
	temp2=0x30;		   
	wr_cn();
	delay(800); 
	
	temp2=0x30;
	wr_cn();
	delay(800);	 
		
	temp2=0x30;
	wr_cn();
	delay(800);

	temp2=0x20;
	wr_cn();
	delay(800);

	temp1 = 0x28;
	lcd_com();
	delay(800);
		
	temp1 = 0x0c;		
	lcd_com();
	delay(800);
	
	temp1 = 0x06;
	lcd_com();
	delay(800);
	
	temp1 = 0x80;
	lcd_com();
	delay(800);
}

void lcd_com(void)
{
	temp2= temp1 & 0xf0;
	wr_cn();
	temp2 = temp1 & 0x0f;
	temp2 = temp2 << 4; 
	wr_cn();
    delay(500);
}

// command nibble o/p routine
void wr_cn(void)                // write command reg
{ 	 
	IO0CLR  = 0x000000FC;		     // clear the port lines.
	IO0SET 	= temp2;			      // Assign the value to the PORT lines    
	IO0CLR  = 0x00000004;		   // clear bit  RS = 0
	IO0SET 	= 0x00000008;   	// ENABLE=1
	delay(10);
	IO0CLR  = 0x00000008;
}

// data nibble o/p routine
void wr_dn(void)
{  	  
	IO0CLR  = 0x000000FC;		 // clear the port lines.
	IO0SET = temp2;				  // Assign the value to the PORT lines 
	IO0SET = 0x00000004;   // set bit  RS = 1 	
	IO0SET = 0x00000008;  // ENABLE=1
	delay(10);
	IO0CLR = 0x00000008;
}

// data o/p routine which also outputs high nibble first
// and lower nibble next
void lcd_data(void)
{  
	temp2 = temp1 & 0xf0;
    wr_dn();
    temp2= temp1 & 0x0f;	
    temp2= temp2 << 4;
    wr_dn();
    delay(100);					
} 

void delay(unsigned int r1)
{
  	unsigned int r;
  	for(r=0;r<r1;r++);
}
void clr_disp(void)
{
	temp1 = 0x01;
	lcd_com();
 	delay(500);
}
	  

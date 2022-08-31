/*********************************************************************
 * EXP2 :Key pad Interface
 * Developed by
 * Advanced Electronics Systems, Bengaluru
 *--------------------------------------------------------------------
 * Controller	: LPC2148
 * Project		: ALS-SDA-ARM7-09
 
 * Description	:4x4 matrix keyboard has total 16 keys. There are 4 rows and 4 cols
 * Identity of key pressed (0 to F) will be displayed on LCD. 
 * Port lines used : P0.8 to P0.11 row1 to row4,P0.12 to P0.15 - col1 to col4
**********************************************************************/


#include<lpc21xx.h>
#include<stdio.h>

void scan(void);
void get_key(void);
void display(void);
void delay(unsigned int);
void init_port(void);

void lcd_init(void);   
void clr_disp(void);
void lcd_com(void);		// LCD routines 
void lcd_data(void);
void wr_cn(void);
void wr_dn(void);

unsigned long int scan_code[16]= { 0x0000EE00,0x0000ED00,0x0000EB00,0x0000E700 ,
                                   0x0000DE00,0x0000DD00,0x0000DB00,0x0000D700 ,
                                   0x0000BE00,0x0000BD00,0x0000BB00,0x0000B700 ,
                                   0x00007E00,0x00007D00,0x00007B00,0x00007700 };



unsigned char ASCII_CODE[16]= {'0','4','8','C',
                               '1','5','9','D',
                               '2','6','A','E',
                               '3','7','B','F'};	 
unsigned char  row,col;										  									
unsigned char temp,flag,i,result,temp1;
unsigned int r,r1;
unsigned long int var,var1,var2,res1,temp2,temp3,temp4;
unsigned char *ptr;
unsigned char disp0[] = "KEYPAD TESTING";
unsigned char disp1[] = "KEY = ";
int main()
{	
	PINSEL0 = 0X00000000;		 // configure P0.0 TO P0.15 as GPIO
	init_port();            //port intialisation
 	delay(3200);			       //delay
	lcd_init();             //lcd intialisation
	delay(3200);			      //delay
  clr_disp();				      //clear display
	delay(500);             //delay
	clr_disp();
	
  ptr = disp0;
	temp1 = 0x80;			// Display starting address of 1st line on LCD
	lcd_com();
    
	while(*ptr!='\0')
    {
    	  temp1 = *ptr;
      	lcd_data();
	  	  ptr ++;
    } 

     ptr = disp1;
	   temp1 = 0xC0;			// Display starting address of 2nd line on LCD
	   lcd_com();
        
	while(*ptr!='\0')
    {
    	  temp1 = *ptr;
        lcd_data();
	  	  ptr ++;
    }
    

  	while(1)	
	{	         
    	  get_key();
        display();		
	} 
      
}  //end of main()	

void get_key(void)                //get the key from the keyboard
{
	  unsigned int k;	
	  flag = 0x00;
    IO0PIN=0x0000F000;
	        
	while(1)
	{		
    	for(row=0X00;row<0X04;row++)	//Writing one for col's 
        {					
        	if( row == 0X00)
            { 
            	temp3=0x00000E00; 
		         }
            else if(row == 0X01)
            { 
            	temp3=0x00000D00;
		         }  
		         else if(row == 0X02)
		         {
            	temp3=0x00000B00;
		          }
            else if(row == 0X03)
		         {
            	temp3=0x00000700;
		          }	
						 
	  	  	  var1 = temp3;
          	IO0PIN = var1;		// each time var1 value is put to port1
          	IO0CLR =~var1;		// Once again Confirming (clearing all other bits)

          	scan();
          	delay(100);			//delay

          	if(flag == 0xff) 
          		break;

       	} // end of for loop

		if(flag == 0xff)
			break;
	}  // end of while	
  
    for(k=0;k<16;k++)
    {
    	if(scan_code[k] == res1)      //equate the scan_code with res1
    	{
			result =  ASCII_CODE[k];    //same position value of ascii code
			break;                      //is assigned to result
      	}
    }
}// end of get_key(); 

void scan(void)
{	
    unsigned long int t;
    temp2 = IO0PIN;                             // status of port1
    temp2 = temp2 & 0x0000F000;                 // Verifying column key
    if(temp2 != 0x0000F000)                     // Check for Key Press or Not
    {
    	delay(3000);                              //delay(100)//give debounce delay check again
    	temp2 = IO0PIN; //IO0		
      	temp2 = temp2 & 0x0000F000;              //changed condition is same 

        if(temp2 != 0x0000F000)                // store the value in res1
        {
        	flag = 0xff;
          	res1 = temp2; 
          	t = (temp3 & 0x00000F00);           //Verfying Row Write
          	res1 = res1 | t;                    //final scan value is stored in res1
        }
        else
        {
        	flag = 0x00;
        }
    }
}  // end of scan()
			 	 	 	    	 
void display(void)
{	  
  
    temp1 = 0xC6;			//display  address for key value
	  lcd_com();
    temp1 = result;    
    lcd_data();	
}  

void lcd_init (void)
{
	temp = 0x30;		   
	wr_cn();
	delay(3200);			
		
	temp = 0x30;
	wr_cn();
	delay(3200);							 
		
	temp = 0x30;
	wr_cn();
	delay(3200);				

	temp = 0x20;
	wr_cn();
	delay(3200);				

	temp = 0x28;	// load command for lcd function setting with lcd in 4 bit mode,
	lcd_com();	 	// 2 line and 5x7 matrix display
	delay(3200);					
		
	temp1 = 0x0C;	// load a command for display on, cursor on and blinking off		
	lcd_com();
	delay(800);  				
	
	temp1 = 0x06; 	// command for cursor increment after data dump	
	lcd_com();
	delay(800);  				
	
	temp1 = 0x80;
	lcd_com();
	delay(800);  		
}

void lcd_data(void)
{   	         
    temp = temp1 & 0xf0;
    wr_dn();
    temp= temp1 & 0x0f;	
    temp= temp << 4;
    wr_dn();
    delay(100);					
} 

void wr_dn(void)			////write data reg
{  	  
	IO0CLR  = 0x000000FC;	  // clear the port lines.
	IO0SET = temp;			    // Assign the value to the PORT lines 
	IO0SET = 0x00000004;   	// set bit  RS = 1 	
	IO0SET = 0x00000008;   	// Enable=1
	delay(10);
	IO0CLR = 0x00000008;
}

void lcd_com(void)
{
    temp = temp1 & 0xf0;
    wr_cn();
    temp = temp1 & 0x0f;
    temp = temp << 4; 
    wr_cn();
    delay(500);
}

void wr_cn(void)                //write command reg
{ 
	IO0CLR  = 0x000000FC;		       // clear the port lines.
	IO0SET 	= temp;				        // Assign the value to the PORT lines    
	IO0CLR  = 0x00000004;		     // clear bit  RS = 0
  	IO0SET 	= 0x00000008;   	// Enable=1
	delay(10);
	IO0CLR  = 0x00000008;
}
	
void clr_disp(void)
{
    temp1 = 0x01;  		// command to clear lcd display
    lcd_com();
    delay(500);					
}  

void delay(unsigned int r1)
{
	for(r=0;r<r1;r++);
} 
      										 
void init_port()
{    
   
    IO0DIR = 0x00000FFC;	  //Configured LCD Lines and Rows as O/P(P0.8-P0.11) and Columns as I/P(P0.12-P0.15)
   
	  IO0SET = 0x0000FF00;  //Set the Rows high.
}   

#include "stdint.h" 
#include "C:/Keil/header/tm4c123gh6pm.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void SystemInit(){
}

//Delays in milli & micro
void dmilli(int n){
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<3180;j++)
	{}
}

void dmicro(int n){
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<3;j++)
	{}
}


//Ports Initiallization
void ports_initiallization(void){
volatile unsigned long delay;

//PORTA
	SYSCTL_RCGCGPIO_R |= 0x01;
	while ((SYSCTL_PRGPIO_R & 0x01) == 0){}
	GPIO_PORTA_CR_R = 0xE0;
	GPIO_PORTA_DIR_R |=0xE0;
	GPIO_PORTA_DEN_R|=0xE0;
	GPIO_PORTA_AMSEL_R &= ~0xE0;	
	GPIO_PORTA_AFSEL_R &= ~ 0xE0;	
	GPIO_PORTA_PCTL_R &= ~ 0xFFF00000;


//PORTB	
	SYSCTL_RCGCGPIO_R |= 0x02; 
	while ((SYSCTL_PRGPIO_R & 0x02) == 0){}
	GPIO_PORTB_CR_R = 0xFF;
	GPIO_PORTB_DIR_R |=0xFF; 
	GPIO_PORTB_DEN_R |=0xFF;
	GPIO_PORTB_AMSEL_R &= ~0xFF;
	GPIO_PORTB_AFSEL_R &= ~0xFF;
	GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;

//PORTF		
	SYSCTL_RCGCGPIO_R |= 0x20;
	while( (SYSCTL_PRGPIO_R & 0x20) == 0){}
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x04 ;
	GPIO_PORTF_AFSEL_R &= ~ 0x04;
	GPIO_PORTF_PCTL_R &= ~ 0xFFFFFFFF;
	GPIO_PORTF_DEN_R |= 0x04;
	GPIO_PORTF_AMSEL_R &= ~ 0x04;
	GPIO_PORTF_DIR_R |= 0X04 ;

	//UART initialization
	SYSCTL_RCGCGPIO_R |= 0x10;	//enable port E
	while( (SYSCTL_PRGPIO_R & 0x10) == 0){}
	SYSCTL_RCGCUART_R  |= 0x20;  //enable UART5 clock
	UART5_CTL_R |=	0x00000000;
	GPIO_PORTE_DEN_R |= 0x30;	//E4,E5 digital
	GPIO_PORTE_AMSEL_R &= ~ 0x30;	// disable analog
	GPIO_PORTE_AFSEL_R |=  0x30;	
	GPIO_PORTE_PCTL_R |=  0x00110000;	
	UART5_IBRD_R  = 104;
	UART5_FBRD_R  = 11;	
	UART5_LCRH_R  = 0x70;
  UART5_CTL_R  = 0x201;	//reciever only	
	}


//LED_FUNCTOINS
	const double PI = 3.1415926;


//Function to receive the data from the GPS
 void GpsInterface(char* firstchar){
	int i,j,final ;
	int done = 1;

	while( (UART5_FR_R &0x10)!= 0){}


	do{
		while (UART5_DR_R != 0x24){}
			for ( i=0 ; i<5 ; i++){
				firstchar[i]= UART5_DR_R & 0xFF;
			}
			if (firstchar[4] == 'G'){
				for ( i=5 ; i<50 ; i++){
					firstchar[i] = UART5_DR_R & 0xFF;
					done =1;
				}
			}
			else done =0;
		}
	while(!done);	

	}

//Function to extract the Lat & Long
static void extract(double* x1,double* y1,char* pointer){	
	  char *ptrx1, *ptrx2;
    int index;
    double retx, retX1, retX2;
    char *ptry1, *ptry2;
    double rety, retY1, retY2;
    int i;
    int j=17;
	  char fixedX1[2], fixedX2[10];
	  char fixedY1[3], fixedY2[11];
    char finalx[20];
    char finaly[20];
//    char str[] ="$GPGGA,181908.00,3404.7041778,N,07044.3966270,W,4,13,1.00,495.144,M,29.200,M,0.10,0000*40";   
	  for(i=0; i<20;i++){
        if (pointer[j]==','){
            index = j+3;
            break;
        }
        else{
            finalx[i] = pointer[j];
            j++;
        }
    }

    for(i=0; i<20;i++){
        if (pointer[index]==','){

            break;
        }
        else{
            finaly[i] = pointer[index];
            index++;
        }
		}
		//fixing latitude
		for(i=0;i<2;i++){
		fixedX1[i]=finalx[i];
		}
		for(i=2;i<20;i++){
		fixedX2[i]=finalx[i];
		}
		retX1 = strtod(fixedX1, &ptrx1);
		retX2 = strtod(fixedX2, &ptrx2);
    retx = retX1 + (retX2/60);
		//fixing longitude
		for(i=0;i<3;i++){
		fixedY1[i]=finaly[i];
		}
		for(i=3;i<20;i++){
		fixedY2[i]=finaly[i];
		}
		retY1 = strtod(fixedY1, &ptry1);
		retY2 = strtod(fixedY2, &ptry2);
    rety = retY1 + (retY2/60);
//Trying the c code on a compilor
//   printf(finalx);
//   printf("\n");
//   printf(finaly);
//   printf("\n");
     
		*x1 =retx;
//   printf("%lf",retx);
//   printf("\n");
		 *y1 = rety;
//   printf("%lf",rety);

	}


//Calculating the distance
static double calcDist( double x1, double y1)
{
	char secArray[50];
	double f;
	double x2,y2,x,y;
	double radius = 6371;	
  double d = 0;
	double x_ = x1, y_ = y1;
	while(d<=3){
		dmilli(1000);
		GpsInterface(secArray);
		extract(&x2,&y2,secArray);

	x = (x2 - x_)* PI /180;
  y = (y2 - y_)* PI /180;
	x1 =  x1 * PI /180;
	x2 = x2 * PI /180;
	f = pow(sin(x/2),2) + cos(x1)*cos(x2)*pow(sin(y/2),2);
	d += 2*radius* asin(sqrt(f));
  x_ = x2;
  y_ = y2;		
	}
 	// x2=500,y2=500;

	return (d);
}

//LED function
static void LedOn(double d){
       if (d>=100) {

           GPIO_PORTF_DATA_R |= 0x04;
        }
}


//LCD_FUNCTIONS

//LCD commands and data
void LCD_Cmd( char command)
{
	GPIO_PORTB_DATA_R = command;
	GPIO_PORTA_DATA_R &= ~ 0x20; //RS =0,RW=0,E=0
	GPIO_PORTA_DATA_R &= ~ 0x40; //RS =0,RW=0,E=0
	dmilli(1);
	GPIO_PORTA_DATA_R |=0x80; //E=1
	dmicro(1);
	GPIO_PORTA_DATA_R &= ~0x80;
	dmicro(5);
}

void LCD_Data( char data) 
{ 
	GPIO_PORTB_DATA_R = data;
	GPIO_PORTA_DATA_R |= 0x20; 		//RS=1,RW=0,E=0
	GPIO_PORTA_DATA_R &= ~ 0x40; 	//RS=1,RW=0,E=0
	GPIO_PORTA_DATA_R |= 0x80; 		//RS=1,RW=0,E=1
	dmicro(1);
	GPIO_PORTA_DATA_R &= ~0x80;
	dmicro(1);
}


//LCD restart
void LCD_init(void)
	{

	 dmilli(20);
   LCD_Cmd(0x38); // Select 8-bit Mode of LCD
	 dmicro(50);
   LCD_Cmd(0x0F); // display on , cursor blinking
	 dmicro(50);
	 LCD_Cmd(0x06); //auto increment cursor
	 dmicro(50);
	 LCD_Cmd(0x01); //clear display
	 dmilli(5);
}

//Converting to a character
char convert (int a ){
	switch (a){
	case 0 :
		return '0';
		break ;

	case 1 :
			return '1';
			break ;

	case 2 :
			return '2';
			break ;

	case 3 :
			return '3';
			break ;


	case 4 :
			return '4';
			break ;

	case 5 :
			return '5';
			break ;

	case 6 :
			return '6';
			break ;

	case 7 :
			return '7';
			break ;

	case 8 :
			return '8';
			break ;

	case 9 :
			return '9';
			break ;
	}
}


char A[3];

void convert_to_char(int y )
{
	A[0]= convert((y/100)%10) ;
	A[1]=	convert( (y/10)%10 ) ;
	A[2]=convert(y%10);
}


//Displaying on the LCD
void LCD_Test (void)
{
	int i;
if ((GPIO_PORTF_DATA_R & 0X04) != 0)
	{
	dmilli(20);
	LCD_Data('T'); 
	dmilli(20);
	LCD_Data('H'); 
	dmilli(20);
	LCD_Data('E');
	dmilli(20);	
	LCD_Data(' '); 
	dmilli(20);
	LCD_Data('D'); 
	dmilli(20);
	LCD_Data('I'); 
	dmilli(20);
	LCD_Data('S');
	dmilli(20);
	LCD_Data('T');
	dmilli(20);
	LCD_Data('A');
	dmilli(20);
	LCD_Data('N');
	dmilli(20);
	LCD_Data('C');
	dmilli(20);
	LCD_Data('E');
	dmilli(20);
	LCD_Data(' ');
	dmilli(20);
	LCD_Data('I');
	dmilli(20);
	LCD_Data('S');
	dmilli(20);
	LCD_Data(' ');
	dmilli(20);
	LCD_Cmd(0xC0);
	dmicro(50);

    for ( i= 0 ; i <3 ; i ++)
	{
		LCD_Data(A[i]);
		dmilli(1);
	}	
}
}

//Main
int main ()
{	
	int distance;
	char dataArray[50];
	double xInitial;
	double yInitial;


	ports_initiallization();
	dmilli(50);

	GpsInterface(dataArray);
	extract(&xInitial,&yInitial,dataArray);
	distance	= calcDist( xInitial, yInitial);

	LedOn(distance);

	convert_to_char(distance);

	LCD_init();

	LCD_Test();


	while (1)
    {

    }
		return 0;
	}

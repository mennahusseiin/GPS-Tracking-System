//////////////UART initialization//////////
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

const double PI = 3.1415926;
static double calcDist( double x1, double y1, double x2, double y2)
{
	double f;
  double d; 	
	double radius = 6371;
	double x = (x2 - x1)* PI /180;
	double y = (y2-y1)* PI /180;
	x1 =  x1 * PI /180;
	x2 = x2 * PI /180;
	f = pow(sin(x/2),2) + cos(x1)*cos(x2)*pow(sin(y/2),2);
	d = 2*radius* asin(sqrt(f));
	return d;
}

int main () 
{ 
	double distance; 
	double x1=0;
	double y1=0;
	double x2=200; 
	double y2=200;
	
	
  distance	= calcDist( x1, y1,x2, y2);
}

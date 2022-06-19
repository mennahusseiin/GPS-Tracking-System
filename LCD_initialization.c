void ports_initiallization(void){

//PORTA_Initiallization
//We used PORTA for control : PD0=Rs , PD1=R/W , PD2=E
	SYSCTL_RCGCGPIO_R |= 0x01;
	while ((SYSCTL_PRGPIO_R & 0x01) == 0){}
	GPIO_PORTA_CR_R = 0xE0;
	GPIO_PORTA_DIR_R |=0xE0;
	GPIO_PORTA_DEN_R|=0xE0;
	GPIO_PORTA_AMSEL_R &= ~0xE0;	
	GPIO_PORTA_AFSEL_R &= ~ 0xE0;	
	GPIO_PORTA_PCTL_R &= ~ 0xFFF00000;
		
//PORTB_Initiallization
//We used PORTB for data from PB0 to PB7
	SYSCTL_RCGCGPIO_R |= 0x02; 
	while ((SYSCTL_PRGPIO_R & 0x02) == 0){}
	GPIO_PORTB_CR_R = 0xFF;
	GPIO_PORTB_DIR_R |=0xFF; 
	GPIO_PORTB_DEN_R |=0xFF;
	GPIO_PORTB_AMSEL_R &= ~ 0xFF;
	GPIO_PORTB_AFSEL_R &= ~ 0xFF;
	GPIO_PORTB_PCTL_R &= ~ 0xFFFFFFFF;
} 

void LCD_init(void){
//Will be called in main to operate the LCD
//Calling 3 other functions: LCD_Cmd,dmilli & dmicro
	dmilli(20);
   	LCD_Cmd(0x38); 
	dmicro(50);
   	LCD_Cmd(0x0F); 
	dmicro(50);
	LCD_Cmd(0x06); 
	dmicro(50);
	LCD_Cmd(0x01); 
	dmilli(5);
}

//Converting the distance into a chararcter
char x[3];
void convert_to_char(int a )
{
	x[0]= convert((a/100)%10) ;
	x[1]=	convert( (a/10)%10 ) ;
	x[2]=convert(a%10);
}

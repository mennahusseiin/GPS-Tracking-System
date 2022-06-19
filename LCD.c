//delay function in milli 
void dmilli(int n){
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<3180;j++)
	{}
}

//delay function in micro
void dmicro(int n){
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<3;j++)
	{}
}
	
void LCD_Cmd( char command)
{
	GPIO_PORTB_DATA_R = command;
	GPIO_PORTA_DATA_R &= ~ 0x20; 
	GPIO_PORTA_DATA_R &= ~ 0x40; 
	dmilli(1);
	GPIO_PORTA_DATA_R |=0x80; 
	dmicro(1);
	GPIO_PORTA_DATA_R &= ~0x80;
	dmicro(5);
}

void LCD_Data( char data) 
{ 
	GPIO_PORTB_DATA_R = data;
	GPIO_PORTA_DATA_R |= 0x20; 		
	GPIO_PORTA_DATA_R &= ~ 0x40; 	
	GPIO_PORTA_DATA_R |= 0x80; 		
	dmicro(1);
	GPIO_PORTA_DATA_R &= ~0x80;
	dmicro(1);
}

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
		LCD_Data(x[i]);
		dmilli(1);
	}	
}
}

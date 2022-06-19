void intiallizing ()
{
	
	SYSCTL_RCGCGPIO_R |= 0x20;
	while( (SYSCTL_PRGPIO_R & 0x20) == 0){}
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x04 ;
	GPIO_PORTF_AFSEL_R &= ~ 0x04;
	GPIO_PORTF_PCTL_R &= ~ 0xFFFFFFFF;
	GPIO_PORTF_DEN_R |= 0x04;
	GPIO_PORTF_AMSEL_R &= ~ 0x04;
	GPIO_PORTF_DIR_R |= 0X04 ;
	
}
				
static void ledOn(double d)
{
	
if( d >= 100)
{ 
	GPIO_PORTF_DATA_R |=0X04 ;    //blue led is on 
	
}

int main ()
{	
	
	ports_initiallization();
	dmilli(50);
	
  //distance = 120;
	distance	= calcDist( x1, y1);
  ledOn(distance);
	
	convert_to_char(distance);
	LCD_init();
	LCD_Test();

	while (1)
    {

    }
		return 0;
	}

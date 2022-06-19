#include <math.h>
const double PI = 3.1415926;
// function to get coordinates:
void getCoordinates(double *lat,double *longi){
  *lat = 100; //later on will be get from gps module
  *longi = 100;	
}
static double calcDist( double x1, double y1)
{
	double f;
	double x2,y2,x,y;
	double radius = 6371;	
  double d = 0;
	double x_ = x1, y_ = y1;
	while(d<100){
    getCoordinates(&x2,&y2);
    x = (x2 - x_)* PI /180;
    y = (y2 - y_)* PI /180;
    x1 =  x1 * PI /180;
    x2 = x2 * PI /180;
    f = pow(sin(x/2),2) + cos(x1)*cos(x2)*pow(sin(y/2),2);
    d = d + 2*radius* asin(sqrt(f));
    x_ = x2;
    y_ = y2;		
	}
  
	return (d);
}

/* function to get initial points:
initial_points(){
}*/

int main () 
{
	double dist; 
	double x1=0;//later will be get from initial_points()
	double y1=0;

  dist	= calcDist( x1, y1);

}

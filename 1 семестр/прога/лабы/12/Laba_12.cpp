#include <iostream> 
#include <math.h>
#include <graphics.h> 
#include <ctime>
using namespace std; 

void Draw (int x, int y, int color)
{
	setcolor (color);
	moveto (x,y+20);
	lineto (x+20,y+20);
	lineto (x+25,y+17);
	lineto (x,y+17);
	lineto (x,y+20);	
} 

int main() 
{
	initwindow (1280, 1024); 
	int x[100],y[100], c[100];
	for (int i=0; i<100; i++)
	{
        delay (20);
		x[i] = rand()%500+50;
		y[i] = rand()%500+50;
		Draw (x[i],y[i],5);
	}
	while ( 1 ) // бесконечный цикл
	{
	  for( int i=0; i<100; i++)
	  {
        delay (20);
	  	Draw(x[i],y[i],0);
	  	//x[i]+=3-rand()%7;
	  	//y[i]+=3-rand()%7;
	  	x[i] = rand()%500+50;
		y[i] = rand()%500+50;
		c[i] = rand()%5+2;
	  	Draw(x[i],y[i],c[i]);
	  }
	}

	
	
	getch();
	closegraph();
	return 0;
	
}

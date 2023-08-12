#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h>
#include "graphics.h"
#include "tFigures.h"

using namespace std;

int main() 
{
	srand(time(NULL));
	tSegment segment1;
	tCircle circle1;
	tRectangle rectangle1;
	tTriangle triangle1;
	tEllipse ellipse1;	
	tRhombus rhombus1;
	initwindow(640, 480);
	while(1)
	{		
		segment1.drawSegment();
		circle1.drawCircle();
		rectangle1.drawRectangle();
		triangle1.drawTriangle();
		ellipse1.drawEllipse();
		rhombus1.drawRhombus();
		//clearviewport();
	}
	getch();
  	closegraph();
    return 0;
}

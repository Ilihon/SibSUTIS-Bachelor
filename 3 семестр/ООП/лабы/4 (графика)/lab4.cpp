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
	int page = 0;
	int n = 5;
	tSegment segmentArray[n];
	tCircle circleArray[n];
	tRectangle rectangleArray[n];
	tTriangle triangleArray[n];
	tEllipse ellipseArray[n];	
	tRhombus rhombusArray[n];
	initwindow(640, 480);
	int x;
	cout << "Chose type of move:" << endl;
	cout << "1. Line move" << endl;
	cout << "2. Rotation" << endl;
	cin >> x;
	while(1)
	{	
		setactivepage(page);
		setvisualpage(1-page);
		cleardevice();
			
		/// DRAWING ///
		for (int i = 0; i < n; i++)
		{
			segmentArray[i].draw();
			circleArray[i].draw();
			rectangleArray[i].draw();
			triangleArray[i].draw();
			ellipseArray[i].draw();
			rhombusArray[i].draw();
		}
		
		
		/// MOVING ///
		if(x == 1)
		{
			for (int i = 0; i < n; i++)
			{
				segmentArray[i].lineMove();
				circleArray[i].lineMove();
				rectangleArray[i].lineMove();
				triangleArray[i].lineMove();
				ellipseArray[i].lineMove();
				rhombusArray[i].lineMove();
			}
		}
		
		/// MOVE AROUND ///
		else if (x == 2)
		{
			for (int i = 0; i < n; i++)
			{
				segmentArray[i].moveAround();
				rectangleArray[i].moveAround();
				triangleArray[i].moveAround();
				ellipseArray[i].moveAround();
				rhombusArray[i].moveAround();
			}
		}
					
		page = 1 -page;
		delay(10);
	}
	getch();
  	closegraph();
    return 0;
}

#include <iostream> 
#include <math.h>
#include <graphics.h> 
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
using namespace std; 

const int r=500, b=400;
int x=5,y=5;
int radius = 20;

void Draw (int x, int y, int color)
{
	setcolor(color);
	circle(x+radius,y+radius,radius);
	moveto(x+radius - (radius*sqrt(2))/2, y+radius - (radius*sqrt(2))/2);
	lineto(x+radius + (radius*sqrt(2))/2, y+radius + (radius*sqrt(2))/2);
	moveto(x+radius + (radius*sqrt(2))/2, y+radius - (radius*sqrt(2))/2);
	lineto(x+radius - (radius*sqrt(2))/2, y+radius + (radius*sqrt(2))/2);
} 

int random (int N){
	return rand()%N;
}

int main(){
	setlocale(LC_ALL, "RUS"); 
	srand(time(0));
	while(true){
		system("cls");
		printf("\n--------------------------------------\n1. Свободное движение \n2. Движение с помощью клавиатуры\n3. Выход\n");
		int flag;
		cin>>flag;
		switch(flag){
			case 1: 
			{
			    x=5,y=5, radius = 20;
			    initwindow (r,b); 
			    int sw=1,swlock,ran;
				Draw (x,y,15);
				while(1){
			    	delay (20);
					if ( kbhit() ){ 
			            if ( getch() == 27 ){
							closegraph();
							break;
						}
					}
			        swlock = 0;
			        Draw(x,y,0);
			        if (x<=5 && sw==2 && swlock==0)
						{radius -= radius/2; sw=5; swlock++;}
			        if (x<=5 && sw==3 && swlock==0)
			            {radius -= radius/2; sw=5; swlock++;} 
			        if (x+radius*2 >= r-15 && sw==1 && swlock==0)
			            {radius += radius/2; sw=6; swlock++;} 
			    	if (x+radius*2 >= r-15 && sw==4 && swlock==0)
			        	{radius += radius/2; sw=6; swlock++;}
			        if (y+radius*2 >= b-15 && sw==2 && swlock==0)
			            {radius -= radius/2; sw=8; swlock++;}
			    	if (y+radius*2 >= b-15 && sw==1 && swlock==0)
			        	{radius -= radius/2; sw=8; swlock++;}   
			        if (y <= 5  && sw==3 && swlock==0)
			            {radius += radius/2; sw=7; swlock++;};
			        if (y <= 5 && sw==4 && swlock==0)
			            {radius += radius/2; sw=7; swlock++;};
			                
			        ran = random(2)+1;
			                
			        if (x==5 && sw==6 && swlock==0) 
			        {
			        	radius -= radius/2;
			            if (ran==1){sw=4; swlock++;}
			            if (ran==2){sw=1; swlock++;} 
			        }
			        if (x+radius*2 >= r-15 && sw==5 && swlock==0)
			        {
			        	radius += radius/2;
			        	if (ran==1){sw=2; swlock++;} 
			        	if (ran==2){sw=3; swlock++;}
			        }
			        if (y+radius*2 >= b-15 && sw==7 && swlock==0)
			        {
			        	radius -= radius/2;
			            if (ran==1){sw=3; swlock++;}
			            if (ran==2){sw=4; swlock++;}   
			        }
			        if (y == 5 && sw==8 && swlock==0)
			        {
			        	radius += radius/2;
			            if (ran==1){sw=2; swlock++;};
			            if (ran==2){sw=1; swlock++;};
			        }
			                
			        switch(sw)
			        {
			            case 1: x++; y++; break;
			            case 2: x--; y++; break;
			            case 3: x--; y--; break;
			            case 4: x++; y--; break;
			            case 5: x++; break;
			            case 6: x--; break;
			            case 7: y++; break;
			        	case 8: y--; break;
			        }
			        Draw(x,y,15);
			    }
			    break;
			}
			case 2: 
			{
			    initwindow (r,b); 
			    x=5,y=5, radius = 20;
				int tplock;
				Draw (x,y,0);
				Draw (x,y,15);
				while(1)
				{
			    	tplock=0;
			        delay (0);
			        int key = getch();
			        if ( key == 27 ){
						closegraph();
						break;
					}
				 	switch(key) 
			        {
			            case 's': Draw(x,y,0); x=x-10; Draw(x,y,15); break;	//влево
			            case 'x':  Draw(x,y,0); y=y+10; Draw(x,y,15); break;	//вниз
			            case 'd': Draw(x,y,0); x=x+10; Draw(x,y,15); break;		//вправо
			            case 'e': Draw(x,y,0); y=y-10; Draw(x,y,15); break;	//вверх
			        }      
			        if ((x <=  -radius*2) && (tplock==0)){
						Draw(x,y,0);
						x=r+radius*2;
						Draw(x,y,15);
						tplock++;
					}
			        if ((x >= r+radius*2) && (tplock==0)){
						Draw(x,y,0);
						x=-radius*2;
						Draw(x,y,15);
						tplock++;
						}  
			        if ((y <= -radius*2) && (tplock==0)){
						y=b+radius*2;
						Draw(x,y,15);
						tplock++;
						}
			        if ((y >= b+radius*2) && (tplock==0)){
						Draw(x,y,0);
						y=-radius*2;
						Draw(x,y,15);
						tplock++;
					}     
			    }
			    break;     
			}
			case 3: 
				return 0;
		}
	}
}

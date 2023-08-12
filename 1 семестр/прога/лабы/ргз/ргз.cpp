#include <iostream> 
#include <math.h>
#include <graphics.h> 
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
using namespace std; 

int x=5,y=5;
int radius = 20;

void Draw (int x, int y, int color)
{
	setcolor(color);
	moveto (x,y+40);
	lineto (x+40,y+40);
	lineto (x+50,y+34);
	lineto (x,y+34);
	lineto (x,y+40);	
	moveto (x+20,y+34);
	lineto(x+20,y);
	moveto (x+20,y+6);
	lineto(x+8,y+6);
	lineto(x+8,y+26);
	lineto(x+32,y+26);
	lineto(x+32,y+6);
	lineto(x+20,y+6);
	moveto(x+32,y+6);
	lineto(x+42,y+6);
} 

int random (int N) { return rand()%N; }
const int r=500, b=400;

int main(){
	setlocale(LC_ALL, "RUS"); 
	srand(time(0));
	while(true){
		system("cls");
		int flag;
		printf("\n--------------------------------------\n1. Свободное движение \n2. Движение с помощью клавиатуры\n3. Выход\n");
		cin>>flag;
		switch(flag){
			case 1: 
			{
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
			        if ((x<=5) and (sw==2) and (swlock==0))
			        	{sw=5; swlock++;}
			        if ((x<=5) and (sw==3) and (swlock==0))
			            {sw=5; swlock++;} 
			        if ((x+50>=r-5) and (sw==1) and (swlock==0))
			            {sw=6; swlock++;} 
			    	if ((x+50>=r-5) and (sw==4) and (swlock==0))
			        	{sw=6; swlock++;}
			        if ((y+40 >= b-5)  and (sw==2) and (swlock==0))
			            {sw=8; swlock++;}
			    	if ((y+40 >= b-5)  and (sw==1) and (swlock==0))
			        	{sw=8; swlock++;}   
			        if ((y <= 5) and (sw==3) and (swlock==0))
			            {sw=7; swlock++;};
			        if ((y <= 5) and (sw==4) and (swlock==0))
			            {sw=7; swlock++;};
			                
			        ran = random(2)+1;
			                
			        if ((x==5) and (sw==6) and (swlock==0)) 
			        {
			            if (ran==1){sw=4; swlock++;}
			            if (ran==2){sw=1; swlock++;} 
			        }
			        if ((x+50 == r-5) and (sw==5) and (swlock==0))
			        {
			        	if (ran==1){sw=2; swlock++;} 
			        	if (ran==2){sw=3; swlock++;}
			        }
			        if ((y+40 == b-5)  and (sw==7) and (swlock==0))
			        {
			            if (ran==1){sw=3; swlock++;}
			            if (ran==2){sw=4; swlock++;}   
			        }
			        if ((y == 5) and (sw==8) and (swlock==0))
			        {
			            if (ran==1){sw=2; swlock++;};
			            if (ran==2){sw=1; swlock++;};
			        }
			                
			        switch(sw)
			        {
			            case 1: x++; y++; break;
			            case 2: x--; y++; break;
			            case 3: x    --; y--; break;
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
			    x=5,y=5;
				int tplock;
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
			            case '4' : Draw(x,y,0); x=x-10; Draw(x,y,15); break;
			            case '2':  Draw(x,y,0); y=y+10; Draw(x,y,15); break;
			            case '6': Draw(x,y,0); x=x+10; Draw(x,y,15); break;
			            case '8': Draw(x,y,0); y=y-10; Draw(x,y,15); break;
			        }      
			        if ((x <= -55) and (tplock==0)) {x=r+5; Draw(x,y,15); tplock++;}
			        if ((x >= r+55) and (tplock==0)) {x=-55; Draw(x,y,15); tplock++;}  
			        if ((y <= -45) and (tplock==0)) {y=b+5; Draw(x,y,15); tplock++;}
			        if ((y >= b+5) and (tplock==0)) {y=-45; Draw(x,y,15); tplock++;}     
			    }
			    break;     
			}
			case 3: 
				return 0;
		}
	}
}

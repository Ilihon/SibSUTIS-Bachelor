#include <iostream> 
#include <math.h>
#include <graphics.h> 
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
using namespace std; 


void Draw (int x, int y, int color)
{
	setcolor(color);
	moveto (x-5,y+60);
	lineto (x+20,y+50);
	moveto (x-5,y+60);
	lineto (x,y+50);
	lineto (x+40,y+50);
	lineto (x+50,y+45);
	lineto (x+40,y+40);
	lineto (x,y+40);
	lineto (x,y+50);
	moveto (x,y+40);	
	lineto (x-5,y+30);
	lineto (x+20,y+40);
	circle (x+35, y+45, 3);
} 

int random (int N) { return rand()%N; }
const int r=500, b=400;

int main(){
	setlocale(LC_ALL, "RUS"); 
	srand(time(0));
	int flag;
		printf("\n--------------------------------------\n1. Свободное движение \n2. Движение с помощью клавиатуры\n3. Выход\n");
		cin>>flag;
switch(flag){
case 1: 
{
     initwindow (r,b); 
     int sw=1,swlock,x=5,y=5,ran;
	 int tick=0;
     int tick_limit=random(300)+1;
	 Draw (x,y,15);
	 while(1)
	{
        delay (20);
	    if ( kbhit() ) 
            if ( getch() == 27 )  
	           {closegraph(); break;}
            swlock = 0;
            Draw(x,y,0);
            if ((x<=5) and (sw==2) and (swlock==0))
                {sw=5; swlock++;}
            if ((x<=5) and (sw==3) and (swlock==0))
                {sw=5; swlock++;} 
            if ((x+50>=r-8) and (sw==1) and (swlock==0))
                {sw=6; swlock++;} 
            if ((x+50>=r-8) and (sw==4) and (swlock==0))
                {sw=6; swlock++;}
            if ((y+60 >= b-12)  and (sw==2) and (swlock==0))
                {sw=8; swlock++;}
            if ((y+60 >= b-12)  and (sw==1) and (swlock==0))
                {sw=8; swlock++;}   
            if ((y <= 0) and (sw==3) and (swlock==0))
                {sw=7; swlock++;};
            if ((y <= 0) and (sw==4) and (swlock==0) )
                {sw=7; swlock++;};
               
            ran = random(2)+1;
                
            if ((x<=5) and (sw==6) and (swlock==0)) 
            {
	            if (ran==1){sw=4; swlock++;}
    	        if (ran==2){sw=1; swlock++;} 
            }
            if ((x+50 >= r-5) and (sw==5) and (swlock==0))
            {
             	if (ran==1){sw=2; swlock++;} 
        	    if (ran==2){sw=3; swlock++;}
            }
            if ((y+60 >= b-12)  and (sw==7) and (swlock==0))
            {
                if (ran==1){sw=3; swlock++;}
                if (ran==2){sw=4; swlock++;}   
            }
            if ((y <= 0) and (sw==8) and (swlock==0))
            {
                if (ran==1){sw=2; swlock++;};
                if (ran==2){sw=1; swlock++;};
            }
            
			if(tick==tick_limit){
				tick_limit=random(300)+1;
				tick=0;
				sw = random(8)+1;
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
            tick++;
    }
 	 main();
 }
case 2: 
{
              
    initwindow (r,b); 
    int x=5,y=5,tplock;
	Draw (x,y,15);
	int i;
	while(1)
	{
            tplock=0;
            delay (0); 
	 switch(getch()) 
            {
            i=getch();
            cout <<i;
                      case '4' : Draw(x,y,0); x=x-10; Draw(x,y,15); break;
                      case '2':  Draw(x,y,0); y=y+10; Draw(x,y,15); break;
                      case '6': Draw(x,y,0); x=x+10; Draw(x,y,15); break;
                      case '8': Draw(x,y,0); y=y-10; Draw(x,y,15); break;
                      case '27': closegraph(); break;
            }      
            if ((x <= -55) and (tplock==0)) {x=r+5; Draw(x,y,15); tplock++;}
            if ((x >= r+55) and (tplock==0)) {x=-55; Draw(x,y,15); tplock++;}  
            if ((y <= -75) and (tplock==0)) {y=b+5; Draw(x,y,15); tplock++;}
            if ((y >= b+5) and (tplock==0)) {y=-45; Draw(x,y,15); tplock++;}     
    }        
    main();
}
case 3:  return 0; break;
default: return 0;
}
return 0;
}

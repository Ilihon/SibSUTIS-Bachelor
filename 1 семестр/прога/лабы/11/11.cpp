#include <stdlib.h>
#include <math.h>
#include <graphics.h>
int main()
{
 initwindow(640,480); // открыть графическое окно 
 //само тело рисунка
 moveto(320,0);
 setcolor(BLUE);
 lineto(320,480);
 moveto(0,240);
 setcolor(BLUE);
 lineto(640,240);
 
int X=321, Y=240;  
moveto(X,Y); 
setcolor(RED);
for(int X1=1;X1<320 ;X1++) 
{
int K1=(X1-1)*(X1-1); 
X=X+X1;
Y=Y-K1;                 
lineto(X,Y);
} 


X=321, Y=240;  
moveto(X,Y); 
for(int X1=1;X1<320 ;X1++) 
{
int K1=(X1-1)*(X1-1); 
X=X-X1;
Y=Y-K1;                 
lineto(X,Y);
} 


X=0, Y=159; 
moveto(X,Y);
lineto(640,159);

outtextxy ( 370, 135, " f(x)=81" ); 
outtextxy ( 370, 70, " f(x)=sqr(X1-1)" ); 
setfillstyle ( 1, 2 ); 
floodfill (320, 220, 4);

getch();            
 closegraph();        // закрываем графическое окно
 return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
const int N = 100;
void Draw ( int x, int y, int color )// ������� ��������� �����                                                         
{
setcolor(color);
moveto(x,y);
lineto(x+30,y);
moveto(x,y);
lineto(x-30,y);
moveto(x,y);
lineto(x,y-30);
moveto(x,y);
lineto(x,y+30);

moveto(x-30,y+30);
lineto(x+30,y-30);
moveto(x-30,y-30);
lineto(x+30,y+30);
}

int random (int N) { return rand()%N; }
main()
{ system("CLS"); 
  int i, y[N], a = -100, b = 100;
   int x[N],C[N];
  for ( i = 0; i < N; i ++ )
     y[i] = random(b-a+1) + a;
  for ( i = 0; i < N; i ++ )
     x[i] = random(b-a+1) + a; 
     for ( i = 0; i < N; i ++ )
     C[i] = random(b-a+1) + a;
      initwindow (640,480); // ������� ���� ��� ������� �������� 400�400
   setfillstyle(1, 0); // �������� �������, ������ ���� (��� ������)
   bar (0, 0, 399, 399); // �������� ��� ������

   while(1)
   {
   
    for ( i = 0; i < N; i ++ )
  {
    if ( kbhit() ) // ���� ������ ��������
       if ( getch() == 27 )  // ���� ������ Esc
            break; // ����� �� �����
      x[i] = rand()%570+50;
		y[i] = rand()%400+50; 
      C[i]=rand() %16;    
    Draw ( x[i], y[i], C[i]); 
    delay ( 150 ); // �������� 20 ��
    Draw (x[i], y[i], 0); // �������, ������������� �� ������ ����
      // ����������
  }
  }
  closegraph(); // ��������� ����������� ����
}

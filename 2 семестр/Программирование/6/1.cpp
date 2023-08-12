#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <math.h>


int triangle(int x, int y, int z, double &s, int &p) {
	double pol = 0;
	if (((x+y)>z) && ((y+z)>x) && ((x+z)>y)) {
		p=x+y+z;
		pol=p/2;
		s=sqrt(pol*(pol-x)*(pol-y)*(pol-z));	
		return 1;
	} 
	return 0;
}

int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	int p = 0;
	double s = 0.0;
printf ( "Storona 1: ");
scanf ( "%d", &a );
printf ( "Storona 2: ");
scanf ( "%d", &b );
printf ( "Storona 3: ");
scanf ( "%d", &c );
printf ( "Function return %d\n", triangle(a,b,c,s,p));
printf("Perimeter: %d \n",p);
printf("Space: %lf \n",s);


//printf ( " Наименьшее из них %d, наибольшее - %d\n", min, max );
system("pause");
getch();
}


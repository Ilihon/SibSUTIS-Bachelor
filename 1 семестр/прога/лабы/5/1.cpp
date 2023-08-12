#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


int main()
{
		float i = 1, pi = 0, s = 0, e;
		int x = 0;

		do
		{
			e = 1 / i;
			s += (e)*pow(-1, x);
			x++;
			i += 2;
			pi = 4 * s;
		} 
		while (e > 0.00001);

		printf("Pi = %.4f \n", pi);
		system("PAUSE");
}

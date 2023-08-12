#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <conio.h>

using namespace std;
void FillInc(int *a, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		a[i] = i;
		cout << a[i] << " ";
	}
	cout << endl;
}
int main()
{
	int n, i, p, q, j, temp;
	cin >> n;
	int *A = new int[n];
	FillInc(A, n);

	for (p = 2; p < n; p++)
	{
		for (i = 2; i < n; i++)
		{
			A[p * i] = 0;
		}
	}
	cout << endl;
    for(p = 2; p < n; p++)
    {
        if(A[p] > 0)
        cout << A[p] << " ";
    }
    getch();
	return 0;
}


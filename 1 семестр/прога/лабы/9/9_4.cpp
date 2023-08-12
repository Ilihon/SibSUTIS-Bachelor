#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
main()
{
	int m[3][3],flag=1,n=0;
	srand(time(NULL));
	while(flag)
	{for (int i=0;i<3;i++)
	for (int j=0;j<3;j++)
	m[i][j]=rand()%10;
	if(((m[0][0]+m[0][1]+m[0][2])==(m[1][0]+m[1][1]+m[1][2]))&&((m[1][0]+m[1][1]+m[1][2])==(m[2][0]+m[2][1]+m[2][2]))&&((m[0][0]+m[0][1]+m[0][2])==(m[0][0]+m[1][0]+m[2][0]))&&((m[0][0]+m[1][0]+m[2][0])==(m[0][1]+m[1][1]+m[2][1]))&&((m[0][1]+m[1][1]+m[2][1])==(m[0][2]+m[1][2]+m[2][2])))
		{
			flag=0;
		}
		n++;
	}
	for (int i=0;i<3;i++)
	{
			for (int j=0;j<3;j++)
			cout<<m[i][j]<<" ";
			cout<<endl;
	}
	cout<<n;
	return 0;
}

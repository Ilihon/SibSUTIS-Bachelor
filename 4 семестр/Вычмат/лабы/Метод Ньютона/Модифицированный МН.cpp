#include<iostream>
#include<stdlib.h>
#include<math.h>

#define urav1 (x*y)-2.3
#define urav2 (x/y)-1.9
using namespace std;

	const int n=2;
	const int m =3;
	const int shag_count =3;
	int shag=0;
	double mass[n][m] = {1,2,-0.3,1,-2,0.1};
	double x_shag[n]={2,1};
	double arr[n];
	
		 
void Gauss(){
	double ugol;
	for(int j = 0; j<m-2;j++)
	{
		ugol=mass[j][j];
		for(int i = j+1;i<n;i++)
		{
			mass[i][j]=mass[i][j]/ugol;
		}
		for(int i =j+1;i<n;i++)
		{
			for(int curj = j+1;curj<m;curj++)
			{
				mass[i][curj]-=mass[i][j]*mass[j][curj];
			}
			mass[i][j] = 0;
		}
	}
	cout<<endl<<"Gaus:"<<endl;
	for(int i =0;i<n;i++)
	{
		for(int j= 0;j<m;j++)
		{
			cout<<mass[i][j];
			if(j == m-2)
			{
				cout<<"|";
			}
			cout<<"\t";
		}
		cout<<endl;
	}
	
	cout <<endl<< "=========" <<endl << "Y"<<shag<<":  x1    x2"<<endl;
	for(int i =0 ;i<n;i++)
	{
		arr[i] = 0;
	}
	arr[n-1] = mass[n-1][m-1]/mass[n-1][m-2];
	for(int i=n-2;i>=0;i--)
	{
		arr[i]=mass[i][m-1];
		for(int j=m-2; j>i;j--){
			arr[i]=arr[i]-mass[i][j]*arr[j];
		}
		arr[i]/=mass[i][i];
	}
	for(int i=0;i<n;i++){
		cout << arr[i] << "    ";
	}
	cout <<endl << "=========" <<endl;
	
}

int main()
{
	setlocale(LC_ALL, "rus");
	int i;
	int j;
	
	for(shag=0;shag<shag_count;shag++){
		cout<<endl << "==========Step "<<shag+1 <<"=========="<<endl<<"";
		for(i =0;i<n;i++)
		{
			for(j= 0;j<m;j++)
			{
				cout << mass[i][j];
				if(j == m-2)
				{
					cout << "\t|";
				}
				cout << "\t";
			}
			cout << endl;
		}
		Gauss();
		for(i=0;i<n;i++){
			x_shag[i]-=arr[i];
		}
		double x=x_shag[0];
		double y=x_shag[1];
		cout <<"X"<<shag+1<<":  x     y";
		printf("\n%3.15f\t%3.15f\n=========", x,y);
		
		
		mass[0][0]=y;
		mass[0][1]=x;
		mass[1][0]=1/y;
		mass[1][1]=-(x/(pow(y,2)));
		
		mass[0][2]=urav1;
		mass[1][2]=urav2;
		
		system("PAUSE");
		
	}
	system("PAUSE");
	return 0;
	
}

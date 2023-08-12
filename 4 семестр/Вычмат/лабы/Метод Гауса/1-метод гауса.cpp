#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	int n=3,m;
//	cout <<"¬ведите размер матрицы"<<endl;
//	cin >> n;
	m = n+1; 
	double ugol;


	double mass[3][4]={8,12,8.28,-28,
					  12,28,18.02,-72,
					  8.28,18.02,12,-44.42};
//	cout<<"¬вод элементов матрицы"<<endl;
//	for(int i=0;i<n;i++)
//	{
//		cout << "¬ведите "<<i+1<<" строку: "<<endl; 
//		for(int j=0;j<m;j++)
//		{
//			cin >> mass[i][j];
//		}
//	}
	for(int i =0;i<n;i++)
	{
		for(int j= 0;j<m;j++)
		{
			cout << mass[i][j];
			if(j == m-2)
			{
				cout << "\t|";
			}
			cout << " ";
		}
		cout << endl;
	}
	for(int j = 0; j<m-2;j++)
	{
		ugol=mass[j][j];
		for(int i = j+1;i<n;i++)
		{
			mass[i][j]/=ugol;
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
	cout<<"\n¬аша нова€ матрица:"<<endl;
	for(int i =0;i<n;i++)
	{
		for(int j= 0;j<m;j++)
		{
			cout<<mass[i][j];
			if(j == m-2)
			{
				cout<<"|";
			}
			cout<<" ";
		}
		cout<<endl;
	}
	
	float arr[n];
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
	cout << endl;
	for(int i=0;i<n;i++){
		cout << arr[i] << " ";
	}
	system("PAUSE");
	return 0;
	
}

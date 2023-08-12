#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	int n,m;
	cout <<"¬ведите размер матрицы"<<endl;
	cin >> n;
	m = n+1; 
	float ugol;

	float mass[n][m];
	cout<<"¬вод элементов матрицы"<<endl;
	for(int i=0;i<n;i++)
	{
		cout << "¬ведите "<<i+1<<" строку: "<<endl; 
		for(int j=0;j<m;j++)
		{
			cin >> mass[i][j];
		}
	}
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
		//находим большую по модулю строку
		ugol=mass[j][j];
		int max = ugol;
		int i_memory=j;
		for(int i =j+1; i<n;i++){
			if(abs(mass[i][j])>abs(max)){
				i_memory=i;
				max=mass[i][j];
			}
		}
		//мен€ем если нашли
		if(i_memory!=j){
			for(int i=j;i<m;i++){
				float buffer=mass[i_memory][i];
				mass[i_memory][i]=mass[j][i];
				mass[j][i]=buffer;
			}
		}
		for(int k =0;k<n;k++)
		{
			for(int l= 0;l<m;l++)
			{
				cout<<mass[k][l];
				if(l == m-2)
				{
					cout<<"|";
				}
				cout<<" ";
			}
			cout<<endl;
		}
		
		
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
	cout<<"¬аша нова€ матрица:"<<endl;
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
	for(int i=n-2;i>0;i--)
	{
		arr[i]=mass[i][m-1];
		for(int j=m-2; j>i;j--){
			arr[i]=arr[i]-mass[i][j]*arr[j];
		}
		arr[i]/=mass[i][i];
	}
	for(int i=0;i<n;i++){
		cout << arr[i] << " ";
	}
	system("PAUSE");
	return 0;
	
}

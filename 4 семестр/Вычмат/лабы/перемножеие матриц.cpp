#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	int n1,m1;
	cout <<"1ая матрица"<<endl;
	cout <<"Введите количество строк"<<endl;
	cin >> n1;
	cout <<"Введите количество столбцов"<<endl;
	cin >> m1;
	int mass1[n1][m1];	
	cout<<"Ввод элементов матрицы"<<endl;
	for(int i=0;i<n1;i++)
	{
		cout << "Введите "<<i+1<<" строку: "<<endl; 
		for(int j=0;j<m1;j++)
		{
			cin >> mass1[i][j];
		}
	}
	
	int n2,m2;
	cout << endl <<"2ая матрица"<<endl;
	cout <<"Введите количество строк"<<endl;
	cin >> n2;
	cout <<"Введите количество столбцов"<<endl;
	cin >> m2;
	int mass2[n2][m2];	
	cout<<"Ввод элементов матрицы"<<endl;
	for(int i=0;i<n2;i++)
	{
		cout << "Введите "<<i+1<<" строку: "<<endl; 
		for(int j=0;j<m2;j++)
		{
			cin >> mass2[i][j];
		}
	}
	
	cout << endl << "Ваши матрицы"<<endl;
	for(int i =0;i<n1;i++)
	{
		for(int j= 0;j<m1;j++)
		{
			cout << mass1[i][j] << " ";
		}
		cout << endl;
	}
	cout  << endl << " X"<<endl <<endl;
	
	for(int i =0;i<n2;i++)
	{
		for(int j= 0;j<m2;j++)
		{
			cout << mass2[i][j] << " ";
		}
		cout << endl;
 	}
 	
 	if(m1!=n2){
 		cout << "Невозможно перемножить матрицы(количество столбцов в 1ой не совпадает с количеством строк во 2ой)";
	}
	else{
		int mass3[n1][m2];
		for(int i=0; i<n1;i++){
			for(int j=0;j<m2;j++){
				mass3[i][j]=0;
			}
		}
		for(int i=0; i<n1;i++){
			for(int j=0;j<m2;j++){
				
				for(int v=0;v<m1;v++){
					mass3[i][j]+=mass1[i][v]*mass2[v][j];
				}
			}
		}
		cout << endl <<"Ваша полученная матрица"<<endl;
		for(int i =0;i<n1;i++)
		{
			for(int j= 0;j<m2;j++)
			{
				cout << mass3[i][j] << " ";
			}
			cout << endl;
	 	}
	}
 	
	system("PAUSE");
	return 0;
	
}

#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	int n1,m1;
	cout <<"1�� �������"<<endl;
	cout <<"������� ���������� �����"<<endl;
	cin >> n1;
	cout <<"������� ���������� ��������"<<endl;
	cin >> m1;
	int mass1[n1][m1];	
	cout<<"���� ��������� �������"<<endl;
	for(int i=0;i<n1;i++)
	{
		cout << "������� "<<i+1<<" ������: "<<endl; 
		for(int j=0;j<m1;j++)
		{
			cin >> mass1[i][j];
		}
	}
	
	int n2,m2;
	cout << endl <<"2�� �������"<<endl;
	cout <<"������� ���������� �����"<<endl;
	cin >> n2;
	cout <<"������� ���������� ��������"<<endl;
	cin >> m2;
	int mass2[n2][m2];	
	cout<<"���� ��������� �������"<<endl;
	for(int i=0;i<n2;i++)
	{
		cout << "������� "<<i+1<<" ������: "<<endl; 
		for(int j=0;j<m2;j++)
		{
			cin >> mass2[i][j];
		}
	}
	
	cout << endl << "���� �������"<<endl;
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
 		cout << "���������� ����������� �������(���������� �������� � 1�� �� ��������� � ����������� ����� �� 2��)";
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
		cout << endl <<"���� ���������� �������"<<endl;
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

#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;


	int n=3,m=4;
	int x_count=3;
	int E=10000;
	float **c_mass;

float* mass_multiplication(int n, float *b_mass)
{
	float mass3[n];
	for(int i=0; i<n;i++){
		mass3[i]=0;
	} 
	for(int i=0; i<n;i++){
		for(int v=0;v<n;v++){
			mass3[i]+=c_mass[i][v]*b_mass[v];
		}
	}/*
	cout << endl <<"Ваша полученная матрица"<<endl;
	for(int i =0;i<n;i++)
	{
		cout << mass3[i];
		cout << endl;
	}*/
	return mass3;
	
}

int main()
{
	setlocale(LC_ALL, "rus");
	float ugol;
	int i=0,j=0;
/*
	float mass[3][4]={5,-1,2,3,
					  3,-10,1,-17,
		 			  2,1,5,4};
*/

	float mass[3][4]={5,-1,2,3,
					  -2,-10,3,-4,
		 			  1,2,5,12};
	cout<<endl<<"Ваша матрица:"<<endl;
	for(i =0;i<n;i++)
	{
		for(int j= 0;j<m;j++)
		{
			printf("%3.f", mass[i][j]);
			if(j == m-2)
			{
				cout << " |";
			}
			cout << " ";
		}
		cout << endl;
	}
	
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(i!=j){
				mass[i][j]=mass[i][j]/mass[i][i];
			}
		}
		mass[i][i]/=mass[i][i];
	}
	
	cout<<endl<<"Ваша новая матрица:"<<endl;
	for(i =0;i<n;i++)
	{
		for(int j= 0;j<m;j++)
		{
			printf("%5.2f", mass[i][j]);
			if(j == m-2)
			{
				cout << " |";
			}
			cout << " ";
		}
		cout << endl;
	}
	
	float b_mass[n];
	for(i=0;i<n;i++){
		b_mass[i]=mass[i][m-1];
	}
	c_mass = new float*[n];
	for(i=0;i<n;i++){
		c_mass[i] = new float[n];
		for(j=0;j<n;j++){
			if(i==j){
				c_mass[i][j]=0;
			}
			else
				c_mass[i][j]=mass[i][j];
		}
	}
	
	cout << endl <<"\tB"<<endl;
	for(i=0;i<n;i++){
		cout << b_mass[i] << " ";
	}
	cout <<endl<<endl<<"\tC"<<endl;
	for(i =0;i<n;i++)
	{
		for(int j= 0;j<n;j++)
		{
			printf("%5.2f ", c_mass[i][j]);
		}
		cout << endl;
	}
	
	float C=0;
	for(i=0;i<n;i++){
		float buffer=0;
		for(j=0;j<n;j++){
			buffer=buffer+fabs(c_mass[i][j]);
		}
		if(buffer>C){
			C=buffer;
		}
	}
	cout <<endl<< "\t||C|| = "<< C<< endl; 
	
	float B=0;
	for(i=0;i<n;i++){
		if(fabs(b_mass[i]) > B)
			B = fabs(b_mass[i]);
	}
	cout << "\t||B|| = "<< B<< endl; 
	
	float x_mass[n];
	for(i=0;i<n;i++){
		x_mass[i]=0;
	}
	float *buffer;
	for(int v=0;v<3;v++){
		cout <<endl<< "\tX"<<v<<endl;
		for(i=0;i<n;i++)
		{
			printf("%5.2f ", x_mass[i]);
		}
		buffer = mass_multiplication(n,x_mass);
		for(i=0;i<n;i++){
			x_mass[i]=b_mass[i]-buffer[i];
		}
		
	}
	float N;
	N = (log((1-C)/(B*E)) / log(C));
	cout<< endl<<endl << "N = "<<(int)N+1<<endl;
	system("PAUSE");
	return 0;
}





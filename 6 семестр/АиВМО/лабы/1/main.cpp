#include <bits/stdc++.h>
#include <sstream>
#include "fractions.h"

using namespace std;


void print(Fraction **arr,int n,int m)
{
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n-1;j++)
		{
			cout<<arr[i][j]<<" ";
		}

		cout<<"| "<<arr[i][n-1]<<endl;
  	}

	cout<<endl;
}

void swap(Fraction **arr,int n,int from,int to)
{
	Fraction c;
	for (int i=0;i<n;i++)
	{
		c=arr[from][i];
		arr[from][i]=arr[to][i];
		arr[to][i]=c;
	}
}

void JordanGauss(Fraction **arr,int n,int m)
{
	int i,j,y=0,mx_ind=0,zz=0;
	bool check;		
	Fraction mx; 
	int mass[100][2]={};

	for (i=0;i<n;i++)
	{
	    if (y>m-1 || i==n-1)
			break;
	    
		check=false;
		mx_ind=y;
		mx=Fraction(0,1);
		
		for (j=y;j<m;j++)
		{
			if (Fraction::Abs(arr[j][i])>mx)
			{	
				mx=Fraction::Abs(arr[j][i]);
				mx_ind=j;
				check=true;
			}
		}

		swap(arr,n,y,mx_ind);

		if (!check)
			continue;
			
        print(arr,n,m);

		for (j=i+1;j<n;j++)
		{
			for (int l=0;l<m;l++)
			{
				if (l!=y)
				{
					arr[l][j]=arr[l][j]-(arr[y][j]*arr[l][i])/arr[y][i];
				}
			}			
		}


		for (j=i+1;j<n;j++)
		{
			arr[y][j]=arr[y][j]/arr[y][i];
		}

		arr[y][i]=arr[y][i]/arr[y][i];

		for (j=0;j<m;j++)
		{
			if (j!=y)
				arr[j][i]=Fraction(0,1);
		}

		print(arr,n,m);
		
		mass[zz][0]=y;
		mass[zz][1]=i;

		zz++;
		
		y++;
	}

	Fraction result;

	int ce=0, co=0, c0;
	for (i=0; i<m; i++) {
		ce=0;c0=0;
		for (j=0; j<n-1; j++) {
			if (arr[i][j]==Fraction(1,1)) ce++;
			if (arr[i][j]==Fraction(0,1)) c0++;
		}
		if (ce==1) co++;
		if (c0==n-1 && !(arr[i][n-1]==Fraction(0,1))) {
			cout << endl << "There are not resolves!" << endl;
			return;
		}
	}
	
	if (co==m && co==n-1) {
		for (i=0; i<m; i++) {
			cout << "x" << i+1 << " = "<<arr[i][n-1] << endl;
		}
	}
	
	else {
		for (i=0;i<zz;i++){
			int zero_sw = 0;
			cout<< "x" << mass[i][1]+1 << " = ";

			for (j=0;j<n-1;j++)
			{
				if (j!=mass[i][1])
				{
					zero_sw =1;
					result=Fraction(-1,1)*arr[mass[i][0]][j];
					

					if (result>Fraction(0,1))
						cout<<"+";
					else if (result==Fraction(0,1))
						continue;
						
					cout<<result<<"[x"<<j+1<<"] ";
				}
			}
			       
			if (arr[i][n-1]>Fraction(0,1))
				cout<<"+";
							     
			if (!(arr[i][n-1]==Fraction(0,1)))			
			//if(zero_sw)
				cout<<arr[i][n-1]<<endl;
		}
		
	}	
}
 

int main()
{   
	int n,m;
	string filename;
	cout << "Enter file name:" << endl;
	cin >> filename;
	ifstream input(filename);
	if(!input){
		cout << "Invalid file name" << endl;
		return 0;
	}
	input >> n;
	input >> m;
	
	Fraction **arr=new Fraction*[m];

	for (int i=0;i<m;i++)
	{
		arr[i]=new Fraction[n];		
    }
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			input>>arr[i][j];
		}
	}

	print(arr,n,m);
    JordanGauss(arr,n,m);

	return 0;
}

#include <bits/stdc++.h>
#include <sstream>
#include "fractions.h"
#include "fractions.cpp"

using namespace std;


long long fact(long long n)
{
	if (n<=1)
		return 1;

	return n*fact(n-1); 
}

long long combinationNum(long long a,long long b)
{
	if (a==b)
		return 1;
	
	return fact(b)/(fact(b-a)*fact(a));	
}



bool NextSet(int *a, int n, int m)
{
  int k = m;
  for (int i = k - 1; i >= 0; --i)
    if (a[i] < n - k + i + 1) 
    {
      ++a[i];
      for (int j = i + 1; j < k; ++j)
        a[j] = a[j - 1] + 1;
      return true;
    }
  return false;
}

void print(Fraction **arr,int n,int m)
{
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n-1;j++)
		{
			cout<< setw(5) << arr[i][j]<<" ";
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

void copy(Fraction **from,Fraction **to,int n,int m)
{
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
			to[i][j]=from[i][j];
	}		
}


void JordanGauss(Fraction **arr,int n,int m)
{
	int i,j,y=0,mx_ind=0,zz=0;
	bool check;		
	Fraction mx; 
	

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

		
		y++;
	}
	
	int rang=0;
	int cnt=0;

	for (i=0; i<m; i++) 
	{
		int count = 0;
		for(j=0;j<m;j++){
			if(arr[i][j]!=Fraction(0,1)){
				break;
			}
			count++;
		}
		if (count!=m) 
			rang++;
	}

	m=rang;
	
	print(arr,n,m);
	
	int combNum=combinationNum(rang,n-1);
	int comb_ind=rang;	
	int *tmp_comb=new int[rang];
	int *comb=new int[rang*combNum];
		
	for (i=0;i<rang;i++)
	{		
		tmp_comb[i]=i+1;
		comb[i]=i+1;
	}


	while(NextSet(tmp_comb,n-1,rang))
	{                      

		for (i=0;i<rang;i++)
		{
			comb[comb_ind]=tmp_comb[i];
			comb_ind++;
		}
	}

	
	              /*
    for (i=0;i<rang*combNum;i++)
    	cout<<comb[i]<<" ";
    
    cout<<endl; */

		           
	cout<<"Rang :"<<rang<<endl<<"N: "<<n-1<<endl<<"Number of combinations: "<<combNum<<endl;


	Fraction **temp=new Fraction*[m];
	int ed[rang][n]={};
	int ch0[rang]={};
	Fraction result;
	bool flag1,flag2;
	
//	int *ch0 = new int[rang];
	
	for (i=0;i<m;i++)
		temp[i]=new Fraction[n];
	

	copy(arr,temp,n,m);

	print(temp,n,m);
	
	cout << endl;
	for (i=0; i<rang*combNum; i++) cout << comb[i] << " ";
	cout << endl;
	
	for(i=0; i<rang;i++) ch0[i]=0;

	for (int k=0;k<rang*combNum;k++)
	{
		int index = comb[k];
		flag1=0;
		flag2=0;

		for (i=0;i<rang;i++)
		{
			//cout << temp[i][index-1] <<"+++"<<  ch0[i] << endl;
			if (!(temp[i][index-1]==Fraction(0,1)) && ch0[i]==0)
			{
			//	cout << "__" << i << "-" << index-1 << " " << endl;
				ch0[i]=1;
				flag1=1;	
				for (j=0;j<rang;j++)
				{
					for (int l=0;l<n;l++)
					{
						if (i==j || index-1==l)
							continue;
						temp[j][l]=temp[j][l]-(temp[j][index-1]*temp[i][l])/temp[i][index-1];
					}											
				}	
				for (j=0;j<rang;j++)
				{
					if (j!=i)
						temp[j][index-1]=Fraction(0,1);					
				}
				for (j=0;j<n;j++)
				{
					if (j!=index-1)
						temp[i][j]=temp[i][j]/temp[i][index-1];
				}
				temp[i][index-1]=Fraction(1,1);
				ed[i][index-1]=1;		
			}
			if (flag1) break;	
		}
			
		
		if ((k+1)%rang==0)
		{	
				
			for(i=0; i<rang;i++) 
				ch0[i]=0;
			
			cout << "Bazovoe " << ((k-1)/rang)+1 <<
				"[" << comb[k-2] <<" "<< comb[k-1]<<" "<<  comb[k] << "]" << endl;	
			
			print(temp,n,m);

			
//			for(j=0; j<n-1; j++) {
//				result=Fraction(0,1);
//				for (i=0; i<rang; i++)  {
//					if (temp[i][j]==Fraction(1,1)) result=temp[i][n-1];
//				}
//					if (!(result==Fraction(0,1))) cout << result << " ";
//					else cout << 0 << " ";
//			}
//			cout << endl;
//			
			
			for(j=0; j<n-1; j++) {
				result=Fraction(0,1);
				for (i=0; i<rang; i++) {
				  if (ed[i][j]==1) result=temp[i][n-1];
				}
				if (!(result==Fraction(1,1))) cout << result << " "; 
				else cout << 0 << " ";
			}
			cout << endl << endl;
					
			for (i=0; i<rang; i++) {
				for (j=0; j<n; j++) {
					cout << ed[i][j] << " ";
				}
				cout << endl;
			}		
				
			for (i=0; i<rang; i++) {
				for (j=0; j<n; j++) {
					ed[i][j] = 0;
				}
			}	
				
									
			copy(arr,temp,n,m);
					
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

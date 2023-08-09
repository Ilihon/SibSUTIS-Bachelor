#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct fraction
{
	long long numenator;
	long long denominator;
};

long long NOD(long long a, long long b)
{
	if(b == 0) return a;
	else return NOD(b, a % b);
}

fraction check(fraction A)
{
	if(A.numenator == 0)
	{
		A.denominator = 1;
		A.numenator = 0;
	}
	if(A.denominator < 0)
	{
		A.numenator=-A.numenator;
		A.denominator=-A.denominator;
	}
	return A;
}

fraction **dubl(int m, int n, fraction **A)
{
	fraction **xx = new fraction*[m];
	for(int i = 0; i < m; i++)
	{
		xx[i] = new fraction[n+1];
		for(int j = 0; j < n+1; ++j)
		{
			xx[i][j].numenator = A[i][j].numenator;
			xx[i][j].denominator = A[i][j].denominator;
		}
	}
	return xx;
}

fraction cut(fraction A)
{
	long long d = NOD(A.denominator,A.numenator);
	A.numenator /= d;
	A.denominator /= d;
	if(A.numenator > 0 && A.denominator < 0)
	{
		A.numenator=-A.numenator;
		A.denominator=-A.denominator;
	}
	return A;
}

fraction divide(fraction A, fraction B)
{
	fraction A1 = cut(A);
	fraction B1 = cut(B);
	fraction temp;
	temp.numenator = A1.numenator*B1.denominator;
	temp.denominator = B1.numenator*A1.denominator;
	return temp;
}

fraction multiply(fraction A, fraction B)
{
	fraction A1 = cut(A);
	fraction B1 = cut(B);
	fraction temp;
	temp.numenator = A1.numenator*B1.numenator;
	temp.denominator = B1.denominator*A1.denominator;
	
	return temp;
}

fraction minuss(fraction A, fraction B)
{	
	fraction A1 = cut(A);
	fraction B1 = cut(B);
	fraction C;
	
	long long temp,temp_a,temp_b;
	temp_a = A1.numenator*B1.denominator;
	temp_b = B1.numenator*A1.denominator;
	C.numenator = temp_a-temp_b;
	temp = A1.denominator*B1.denominator;
	C.denominator = temp;	
	
	return C;
}

void output(int m, int n, fraction **x)
{
	cout<<endl<<endl;
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n+1; ++j)
		{
			if(j != n)
			{
				if(x[i][j].denominator == 0) cout<<"0";
				else
				{
					cout<<x[i][j].numenator;
					if(x[i][j].denominator != 1) cout<<"/"<<x[i][j].denominator;
				}
				cout<<"\t";
			}
			else
			{
				cout<<"|";
				if(x[i][j].denominator == 0) cout<<"0";
				else
				{
					cout<<x[i][j].numenator;
					if(x[i][j].denominator != 1) cout<<"/"<<x[i][j].denominator;
				}
				cout<<endl;
			}
		}
	}
}
int main()
{
	ifstream in("ms.in");
	int m = 0, n = 0;
	
	//cout<<"Please, enter number of rows: ";
	in>>m;
	
	//cout<<"Please, enter number of X: ";
	in>>n;
	
	fraction **x = new fraction*[m];
	for(int i = 0; i < m; i++)
	{
		x[i] = new fraction[n+1];
		for(int j = 0; j < n+1; ++j)
		{
			long long p = 0;
			if(j != n)
			{
				//cout<<"a["<<i+1<<"]["<<j+1<<"] : ";
				in >> p;
				x[i][j].numenator = p;
				x[i][j].denominator = 1;
			}
			else
			{
				//cout<<"b["<<i+1<<"] : ";
				in >> p;
				
				x[i][j].numenator = p;
				x[i][j].denominator = 1;
			}
		}
	}
	
	cout<<endl<<"\tMatrix: ";
	output(m,n,x);
	
	int s = 0, k = 0, st = 0;
	
	while(1)
	{
		if(x[s][k].numenator != 0)
		{
			/*cout<<endl;
			cout<<"s = "<<s<<endl;
			cout<<"k = "<<k<<endl<<endl;*/
			
			fraction **xx = new fraction*[m];
			for(int i = 0; i < m; i++)
			{
				xx[i] = new fraction[n+1];
			}
			xx = dubl(m, n, x);
			if(x[s][s].numenator == 0) s++;
			for(int i = 0; i < n+1; ++i)
			{
				x[s][i] = divide(xx[s][i],xx[s][s]);
				x[s][i] = check(x[s][i]);
				x[s][i] = cut(x[s][i]);
			}
			
			for(int i = 0; i < m; ++i)
			{
				if(i != s)
				{
					x[i][s].numenator = 0;
					x[i][s].denominator = 1;
					
					for(int j = 0; j < n+1; ++j)
					{
						//cout<<endl;
						fraction mul = multiply(xx[i][s],xx[s][j]);
						mul = check(mul);
						mul = cut(mul);
						/*cout<<"1) "<<xx[i][s].numenator;
						if(xx[i][s].denominator != 1) cout<<"/"<<xx[i][s].denominator;
						cout<<" * "<<xx[s][j].numenator;
						if(xx[s][j].denominator != 1) cout<<"/"<<xx[s][j].denominator;
						cout<<" = "<<mul.numenator;
						if(mul.denominator != 1) cout<<"/"<<mul.denominator;
						cout<<endl;*/
						fraction div = divide(mul,xx[s][s]);
						div = check(div);
						div = cut(div);
						/*cout<<"2) "<<mul.numenator;
						if(mul.denominator != 1)cout<<"/"<<mul.denominator;
						cout<<" : "<<xx[s][s].numenator;
						if(xx[s][s].denominator != 1)cout<<"/"<<xx[s][s].denominator;
						cout<<" = "<<div.numenator;
						if(div.denominator != 1)cout<<"/"<<div.denominator;
						cout<<endl;*/
						fraction min = minuss(xx[i][j],div);
						min = check(min);
						min = cut(min);
						/*cout<<"3) "<<xx[i][j].numenator;
						if(xx[i][j].denominator != 1)cout<<"/"<<xx[i][j].denominator;
						cout<<" - "<<div.numenator;
						if(div.denominator != 1)cout<<"/"<<div.denominator;
						cout<<" = "<<min.numenator;
						if(min.denominator != 1)cout<<"/"<<min.denominator;
						cout<<endl<<endl;*/
						x[i][j] = min;
						x[i][j] = check(x[i][j]);
						x[i][j] = cut(x[i][j]);
					}
					xx = dubl(m,n,x);
					
				}
			}
			int cou = 0;
			for(int i = 0; i < m; ++i)
			{
				cou = 0;
				for(int j = 0; j < n; ++j)
				{
					if(x[i][j].numenator == 0)
					{
						cou++;
					}
					else cou = 0;
					
					if(cou == n) break;
				}	
			}	
			
			output(m,n,x);
			if(k < m-1 && cou != n)
			{
				k++;
				s++;
			}
			else break;
		}
		else if(s+1 != m) s++;
		else 
		{
			s = k;
			k++;
		}
	}
	
	int r = m;
	vector <int> tempi;
	for(int i = 0; i < m; ++i)
	{
		int count = 0;
		for(int j = 0; j < n+1; ++j)
		{
			if(x[i][j].numenator == 0)
			{
				count++;
			}
			else
			{
				if(count == n)
				{
					cout<<endl<<"\tCase 1: no solution"<<endl<<endl;
					return 0;
					break;
				}
				else
				{
					count = 0;
				}
			}
		}
		if(count == n+1)
		{
			tempi.push_back(i);
			r--;
		}
	}
	
	if(r == m && r == n && m == n)
	{
		cout<<endl<<"\tCase 2: one solution"<<endl<<endl;
		for(int i = 0; i < m; ++i)
		{
			cout<<"\tx"<<i+1<<" = "<<x[i][n].numenator;
			if(x[i][n].denominator != 1)
			{
				cout<<"/"<<x[i][n].denominator;
			}
			cout<<endl;
		}
	}
	else if(r <= m && m < n)
	{
		cout<<endl<<"\tCase 3: multiple solutions"<<endl<<endl;
		for(int i = 0; i < m; ++i)
		{
			if(find(tempi.begin(), tempi.end(), i) == tempi.end())
			{
				int c = 0;
				cout<<"\tx"<<i+1<<" = "<<x[i][n].numenator;
				if(x[i][n].denominator != 1)
				{
					cout<<"/"<<x[i][n].denominator;
				}
				for(int j = i+1; j < n; ++j)
				{
					int flag = 0;
					if(x[i][j].numenator != 0)
					{
						if(c == 0)
						{
							cout<<" - ";
							c = 1;
						} 
						if(x[i][j].numenator < 0) flag = 1;
						if(flag == 1) cout<<"(";
						cout<<x[i][j].numenator;
						if(x[i][j].denominator != 1)
						{
							cout<<"/"<<x[i][j].denominator;
						}
						cout<<"*x"<<j+1;
						if(flag == 1) cout<<")";
						if(j+1 != n && x[i][j+1].numenator != 0) cout<<" - ";
					}
				}
				cout<<endl;
			}
		}
	}
	return 0;
}

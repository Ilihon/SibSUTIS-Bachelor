#include <fstream>
#include <conio.h>
#include <iomanip>
#include <cstdio> 
#include <cstring> 
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

struct Fraction
{
	long long numerator;
	long long denominator = 1;
};


void print(Fraction **arr,int n,int m)
{
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n-1;j++)
		{
			if(arr[i][j].denominator==1 || arr[i][j].numerator==0){
				cout << arr[i][j].numerator << " ";
			}
			else
				cout<<arr[i][j].numerator << "/" << arr[i][j].denominator<<" ";
		}

		cout<<"| ";
		if(arr[i][n-1].denominator==1 || arr[i][n-1].numerator==0){
			cout<<arr[i][n-1].numerator<<endl;
		}
		else
			cout<<arr[i][n-1].numerator << "/" << arr[i][n-1].denominator<<endl;
  	}

	cout<<endl;
}

//����������� ���������� ����
long long NOD(long long a, long long b)
{
	if(b == 0) return a;
	else return NOD(b, a % b);
}

//���������� ������� ������
long long divide(Fraction **arr,int n,int m){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(arr[i][j].denominator != 0)
				if(arr[i][j].numerator % arr[i][j].denominator == 0){
					arr[i][j].numerator /= arr[i][j].denominator;
					arr[i][j].denominator = 1;
				}
				else{
					long long d = NOD(arr[i][j].denominator,arr[i][j].numerator);
					if(d!=0){
						arr[i][j].denominator /= d;
						arr[i][j].numerator /= d;
					}
				}
		}
	}
}

//�������� �������� ���� X 
void PrintXAnswer(Fraction **arr, int n, int m){
	for(int i = 0; i < m; i++){
		if(arr[i][i].numerator==0){
			continue;
		}
		cout << "x" << i+1 << " = ";
		if(arr[i][n-1].numerator==0){
			cout << "0 ";
		}
		else{
			cout << arr[i][n-1].numerator;
			if (arr[i][n-1].denominator != 1){
				cout << "/" << arr[i][n-1].denominator;
			}
		}
		for(int j = i+1; j < n-1; j++){
			if (arr[i][j].numerator == 0){
				continue;
			}
			if (arr[i][j].numerator < 0){
				if (arr[i][j].denominator != 1){
					cout << " + " << arr[i][j].numerator * -1 << "/" << arr[i][j].denominator;
				}
				else{
					cout << " + " << arr[i][j].numerator * -1;
				}
			}
			else{
				if (arr[i][j].denominator < 0){
					cout << " + " << arr[i][j].numerator << "/" << arr[i][j].denominator*-1;
				}
				else{
					if (arr[i][j].denominator != 1){
						cout << " - " << arr[i][j].numerator << "/" << arr[i][j].denominator;
					}
					else{
						cout << " - " << arr[i][j].numerator;
					}
				}
			}
			cout << " * x" <<j+1;
		}
		cout << endl;
	}
}

//������� ������ ����� � ��� �������
void MoveZeroLinesBot(Fraction **arr, int n, int m){
	for(int i = 0; i < m; i++){
		int count = 0;
		for(int j = 0; j < n; j++){
			if(arr[i][j].numerator != 0){
				break;
			}
			count++;
		}
		if(count == n){
			for(int v = i+1; v < m; v++){
				int count_2 = 0;
				for(int j = 0; j < n; j++){
					if(arr[v][j].numerator != 0){
						break;
					}
					count_2++;
				}
				if(count_2 != n){
					for(int j = 0; j < n; j++){
						arr[i][j].numerator = arr[v][j].numerator;
						arr[i][j].denominator = arr[v][j].denominator;
						arr[v][j].numerator = 0;
					}
					break;
				}
			}
		}
	}
}

//������ ����� �������
int CountRang(Fraction **arr, int n, int m){
	int rang = 0;
	for (int i = 0; i < m; i++) 
	{
		int count = 0;
		for(int j = 0; j < n-1; j++){
			if(arr[i][j].numerator != 0){
				break;
			}
			count++;
		}
		if (count != n-1) 
			rang++;
	}
	return rang;
}

//������ ����������
long long fact(long long n)
{
	if (n<=1)
		return 1;

	return n*fact(n-1); 
}

//������ ���������� ����������
long long CombinNum(int rang, int X_count)
{
	if (rang == X_count)
		return 1;
	
	return fact(X_count) / (fact(X_count - rang) * fact(rang));	
}


bool NextSequence(int *a, int X_count, int rang)
{
  for (int i = rang - 1; i >= 0; --i)
    if (a[i] < X_count - rang + i + 1) 
    {
      ++a[i];
      for (int j = i + 1; j < rang; ++j)
        a[j] = a[j - 1] + 1;
      return true;
    }
  return false;
}

void Jordan_Gauss(Fraction **arr,int n,int m){
	MoveZeroLinesBot(arr,n,m);
	for(int i = 0; i < m; i++){
		//���� ������� ������� ��������� == 0, �� �������
		if(arr[i][i].numerator == 0){
			continue;
		}
		//���� ������� ������� ��������� - ������������� �����
		if(arr[i][i].numerator/arr[i][i].denominator < 0){
			for(int j = i; j < n; j++){
				arr[i][j].numerator *= -1;
			}
		}
		//���� ������� ������� ��������� �� = 1
		if(arr[i][i].numerator/arr[i][i].denominator != 1 || arr[i][i].numerator % arr[i][i].denominator != 0){
			long long num = arr[i][i].numerator;
			long long den = arr[i][i].denominator;
			for(int j = i; j < n; j++){
				arr[i][j].numerator *= den;
				arr[i][j].denominator *= num;
			}
		}
		
		//cout << endl;
		divide(arr,n,m);
		print(arr,n,m);
		
		//�������� ������� ���� � ���� ������� ���������
		for(int v = 0; v < m; v++){
			//���� ������� �� ������� ��������� - �������
			if(v == i){
				continue;
			}
			//����� ��������
			for(int j = i+1; j < n; j++){
				//�������� ��������� �� ������� ������� ������
				long long num = arr[v][i].numerator * arr[i][j].numerator;
				long long den = arr[v][i].denominator * arr[i][j].denominator;
				//cout << num<< "/" << den<< " - " << arr[v][j].numerator << "/" << arr[v][j].denominator << " - ";
				
				//���� � ������������ � ����������� ������ ����������� - ��������� �� ����������� ���� �����
				if (den != arr[v][j].denominator){
					long long buf = den;
					num *= arr[v][j].denominator;
					den *= arr[v][j].denominator;
					
					arr[v][j].numerator *= buf;
					arr[v][j].denominator *= buf;
				}
				//cout << num<< "/" << den<<endl;
				
				arr[v][j].numerator -= num;
			}
			//�������� ��������
			arr[v][i].numerator = 0;
			arr[v][i].denominator = 0;
			
			//�������� �� ���������� ���� (��� �==0, ����� ��������� !=0)
			if(arr[v][n-1].numerator != 0){
				int zero_counter = 0;
				for (int j = 0; j <n-1;j++){
					if (arr[v][j].numerator!=0){
						break;
					}
					zero_counter++;
				}
				if(zero_counter==n-1){
					divide(arr,n,m);
					cout << endl;
					print(arr,n,m);
					cout << "There are no resolves here!"<<endl;
					return;
				}
			}
		}
		divide(arr,n,m);
		cout << endl;
		print(arr,n,m);
	}
	MoveZeroLinesBot(arr,n,m);
	
	print(arr,n,m);
	
	//������� ���� �������
	int rang = CountRang(arr,n,m);
	int combination_num = CombinNum(rang,n-1);
	cout << "Matrix rang:\t" << rang << endl << "X count:\t" << n-1 << endl << "Combination num:\t" << combination_num << endl;
	
	//���������� ���������
	int *buf_comb = new int[rang];
	int *comb = new int[rang * combination_num];
	int combin_index = rang;
	//���������� ������� ������������������
	for(int i = 0; i < rang; i++)
	{		
		buf_comb[i]=i+1;
		comb[i]=i+1;
	}
	//���������� ��������� ������������������
	while(NextSequence(buf_comb, n-1, rang))
	{                      
		for(int i = 0; i < rang; i++)
		{
			comb[combin_index] = buf_comb[i];
			combin_index++;
		}
	}
	cout << endl << "Combin sequence:" << endl; 
	for(int i = 0; i < rang * combination_num; i++){
		cout << comb[i] << " ";
	}
	cout << endl << endl;
	cout << "--------------------" << endl << endl; 
	
	//���� ��� �������� �������
	for(int i = 0; i < combination_num; i++){
		int break_flag = 0;
		cout << "#" << i+1 << " [";
		for(int j = 0; j < rang; j++){
			cout << " " << comb[i*rang + j];
		}
		cout << " ]" << endl << endl;
		
		//��������� �������
		Fraction **buf = new Fraction*[m];
		for (int v=0; v<m; v++)
		{
			buf[v]=new Fraction[n];		
	    }
		for (int v = 0; v < m; v++)
		{
			for (int j = 0; j < n; j++)
			{
				buf[v][j].numerator = arr[v][j].numerator;
				buf[v][j].denominator = arr[v][j].denominator;
			}
		}
		print(buf, n, m);
		
		int v_memmory = -1;
		//������������ ������ ����������
		for(int v = 0; v < rang; v++){
			//���� ������� ���������� ����� 0, �� ��������� ����� �� ���� ����� ������ ������������
			if(buf[v][comb[i*rang + v]-1].numerator == 0){
				int count = 0;
				//���� �������� � ������ �������, ���������������� ���������� ����� 0, �� ������ ��� 
				for(int j = 0; j < rang; j++){
					if(buf[v][comb[i*rang + j]-1].numerator == 0){
						count++;
					}
				}
				if(count == rang){
					cout << "This option can't exist" << endl;
					break_flag = 1;
					break;
				}
				//����� ������� � ���� ������ �����
				else{
					//�� ���������� ������, ���� ���� ��������� ��� ���� ������
					if(v_memmory != -1)
						continue;
					//����� ���������� ������, � ������� ����� �������
					v_memmory = v;
					//cout << endl << "v_memmory: " << v_memmory+1 << endl;
					continue;
				}
			}
			//cout << endl << v+1 << " - " << comb[i*rang + v] << endl;
			//print(buf,n,m);
			//���� ������� - ������������� �����
			if(buf[v][comb[i*rang + v]-1].numerator / buf[v][comb[i*rang + v]-1].denominator < 0){
				for(int k = 0; k < n; k++){
					buf[v][k].numerator *= -1;
				}
			//	print(buf,n,m);
			}
			//���� ������� ������� �� = 1
			if(buf[v][comb[i*rang + v]-1].numerator / buf[v][comb[i*rang + v]-1].denominator != 1 || buf[v][comb[i*rang + v]-1].numerator % buf[v][comb[i*rang + v]-1].denominator != 0){
				long long num = buf[v][comb[i*rang + v]-1].numerator;
				long long den = buf[v][comb[i*rang + v]-1].denominator;
				for(int k = 0; k < n; k++){
					buf[v][k].numerator *= den;
					buf[v][k].denominator *= num;
				}
				divide(buf,n,m);
				print(buf,n,m);
			}
			//�������� �������� ���� � ���� �������� ��������
			for(int j = 0; j < m; j++){
				if (v == j){
					continue;
				}
				//���� ����� ������ � �� ������� ��������� � ������� �������
				if(buf[j][comb[i*rang + v]-1].numerator != 0){
					
					
					
					//��������
					for(int k = 0; k < n; k++){
						if(k == comb[i*rang + v]-1){
							continue;
						}
						//�������� ��������� �� ������� �������
						long long num = buf[j][comb[i*rang + v]-1].numerator * buf[v][k].numerator;
						long long den = buf[j][comb[i*rang + v]-1].denominator * buf[v][k].denominator;
						
						//cout << num << " / " << den << endl;
						//���� � ������������ � ����������� ������ ����������� - ��������� �� ����������� ���� �����
						if (den != buf[j][k].denominator && buf[j][k].denominator != 0 && buf[j][k].numerator != 0 && den != 0){
							long long buffer = den;
							num *= buf[j][k].denominator;
							den *= buf[j][k].denominator;
							
							buf[j][k].numerator *= buffer;
							buf[j][k].denominator *= buffer;
						}
						//cout << num<< "/" << den<<endl;
						
						//cout << num << " / " << den << endl<< endl ;
						buf[j][k].numerator -= num;
						if (buf[j][k].denominator==0)
							buf[j][k].denominator = den;
					}
					//�������� ��������
					buf[j][comb[i*rang + v]-1].numerator = 0;
					buf[j][comb[i*rang + v]-1].denominator = 0;			
					divide(buf,n,m);
					print(buf,n,m);
				}
			}
			//���� �� ���������� ������, � ������� ����� �������
			if(v_memmory != -1){
				//���� ������� ���������, �� ������������, ����� ���������� ������ �������������, � ������ ������� �����
				if(buf[v][comb[i*rang + v_memmory]-1].numerator != 0){
					v = v_memmory-1;
					v_memmory = -1;
				}
			}
			//��������� �� �� ���������������
			if(v+1 == rang){
				int schet =0;
				for(int j = 0; j < rang; j++){
					//���� ������� ������ ����� 1, �� +1 � ��������
					if(buf[j][comb[i*rang + j]-1].numerator == 1){
						schet++;
					}
				}
				//���� �� ��� �������� ���������������, �� ��������� �����
				if(schet != rang){
					v = -1;
				}
			}
		}
		divide(buf,n,m);
		//���� ����� ����� �� ��������
		if(break_flag){
			cout << "--------------------" << endl << endl; 
			continue;
		}
		//������� �������� �������
		cout << "X" << i+1 << " = (";
		int index = 0;
		for(int j = 0; j < n-1; j++){
			cout << " ";
			if (j == comb[i*rang + index]-1){
				if(buf[index][n-1].numerator == 0){
					cout << "0";
				}
				else{
					cout << buf[index][n-1].numerator;
					if(buf[index][n-1].denominator != 1){
						cout << "/" << buf[index][n-1].denominator;
					}
				}
				index++;
			}
			else{
				cout << "0";
			}
			cout << ";";
		}
		cout << ")" << endl;
		
		cout << "--------------------" << endl << endl; 
		
	}
	
	return;
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
			input>>arr[i][j].numerator;
		}
	}
	print(arr,n,m);
    Jordan_Gauss(arr,n,m);

	return 0;
}

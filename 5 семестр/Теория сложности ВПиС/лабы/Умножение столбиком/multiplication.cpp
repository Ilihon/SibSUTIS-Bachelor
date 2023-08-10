#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

string ToString(int i) {
	stringstream ss;
	ss << i;
	return ss.str();
}

int StrToInt(char b)
{
	return b - '0';
}

int Multiplication(string, string);

int oper_sum = 0;
int oper_umnoj =0;

void swap(string &aStr, string &bStr){
	int k=0;
	int l=0;
	int n = aStr.length();
	int m = bStr.length();
	for (int i = n-1; i >= 0; i--) {
		if (StrToInt(aStr[i])==0){
			k++;
		}
		else{
			break;
		}
	}
	for (int i = m-1; i >= 0; i--) {
		if (StrToInt(bStr[i])==0){
			l++;
		}
		else{
			break;
		}
	}
	if(n-k<m-l){
		string tmp = bStr;
		bStr = aStr;
		aStr = tmp;
	}
}

int main()
{
	setlocale(0, "");
	string aStr, bStr;
	cout << "¬ведите два числа: " << endl;
	getline(cin, aStr);
	getline(cin, bStr);
	cout << endl <<endl <<"*\t" << aStr << "\n \t" << bStr << "\n     --------\n+";
	swap(aStr, bStr);
	//cout << endl << aStr << " - " << bStr << endl;
	int answer = Multiplication(aStr, bStr);
	cout << "     --------\n";
	cout << "\t" << answer <<endl<<endl;
	cout << "oper sum: " << oper_sum-1 << endl;
	cout << "oper umnoj: " << oper_umnoj << endl;
	system("pause");
	return 0;
}

int Multiplication(string aStr, string bStr) {
	int t;
	int n = aStr.length();
	int m = bStr.length();
	t = n + m;
	int *C = new int[t];
	for (int i = 0; i < t; i++)
		C[i] = 0;
	int tmp = 0;
	int tmp_str = 0;
	int k = 0;
	double mnoj_j = 0.1;
	double mnoj_i = 1;
	for (int j = m-1; j >=0; j--) {
		mnoj_j *= 10;
		if(StrToInt(bStr[j])!=0){
			tmp_str = 0;
			mnoj_i = 0.1;
			for (int i = n-1; i >= 0; i--) {
				mnoj_i *= 10;
				if (StrToInt(aStr[i])!=0){
					tmp_str += StrToInt(aStr[i]) * StrToInt(bStr[j])*mnoj_i;
					//cout << j << " - " << i << " : " << StrToInt(aStr[i]) * StrToInt(bStr[j]) << endl;
					oper_umnoj++;
				}
			}
			cout << "\t"<< tmp_str << endl;	
			tmp += tmp_str*mnoj_j;
			oper_sum++;
		}
		//cout << "tmp: " << tmp << endl;
	}
	return tmp;
}


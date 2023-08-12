#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

string BinNumber(int);
string FixVar(int);
void g_code(int);
void w_code(int);
const int N = 10;

int main()
{
	setlocale(0, "rus");
	string vp, a, w;
	cout << "+-----+--------------------------------------------------+" << endl;
	cout << "|     |                    Кодовое слово                 |" << endl;
	cout << "|Число|----------------+----------------+----------------+" << endl;
	cout << "|     | Fixed+Variable |гамма-код Элиаса|омега-код Элиаса|" << endl;///Variable + Variable = ?-код Элиаса && ?-код Элиаса
	cout << "+-----+----------------+----------------+----------------+" << endl;
	for (int i = 0; i <= N; i++) {
		vp = FixVar (i);
		cout << "|";
		cout << setw(5) << i << "|";
		cout << setw(7) << vp.substr(0, 4) << " " << vp.substr(4, vp.length()) << setw(13 - (int) vp.length()) << "|";
		g_code(i);
		cout << "|";
		w_code(i);
		cout << setw(7) <<"|";
		cout << endl;
		cout << "+-----+----------------+----------------+----------------+" << endl;
	}
	system("PAUSE");
	return 0;
}


string BinNumber(int M) {
	char tmp; 
	string binM;
	while (M) {
		tmp = '0' + M % 2;
		binM = tmp + binM;
		M /= 2;
	}
	return binM;
}

string FixVar(int M) {
	string order = "", mantissa = "";
	if (M == 0) {
		mantissa = "";
		order = "0000";
		return (order + mantissa);
	}
	else {
		mantissa = BinNumber(M);
		mantissa = mantissa.erase(0, 1); // удаляет из строки символ с индексом i;
		order = BinNumber(mantissa.length() + 1);
		while (order.length() != 4)
			order = "0" + order;
		return (order + mantissa);
	}
}

void g_code(int M) {
	if (M == 0) {
		cout << setw(8) << "-" << setw(9);
		return;
	}
	string p = "", m = "";
	m = BinNumber(M);
	for (int i = 1; i < (m.length()); i++) {
		p = "0" + p;
	}
	cout << setw(7) << p << " " << m << setw(9-m.length());
}

void w_code(int M) {
	if (M == 0) {
		cout << setw(8) << "-" << setw(9);
		return;
	}
	else 
		if (M == 1) {
			cout << setw(8) << "0" << setw(9);
			return;
		}
	string *l = new string[10];
	int n;
	l[0] = "0";
	int i = 0;
	n = M;
	while (n >= 2) {
		i++;
		l[i] = BinNumber(n);
		n = l[i].length()-1;
	} 
	for (int j = i+1; j >= 0; j--) {
		cout << " " << l[j];
	}
}

#include <cmath>
#include <conio.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
const int expSize = 6;

string intToBinary(unsigned int value, bool useConst = false) { // �������������� � �������� �������������
	string binary;
	if (useConst) {
		for (int i = 0; i < expSize; i++) {
			if(value != 0){
				binary = to_string(value % 2) + binary;
				value = value / 2;
			} else {
				binary.insert(0, "0");
			}
		}
	} else {
		while (value != 0) {
			binary = to_string(value % 2) + binary;
			value = value / 2;
		}
	}
	return binary;
}

string fixedVariableEncode(unsigned int value) {
	string binary = intToBinary(intToBinary(value).length(), true) + intToBinary(value).erase(0,1); // �������� ������������� ����� ��������� ������������� value 
	return binary;																					// + �������� ������������� value ��� ������� �����
}

string gammaEncode(unsigned int value) { //����� ���������
	string gamma;
	if (!value) {
		gamma = 1;
	} else {
		gamma = intToBinary(value); //������������ �������� � �������� �������
		for (int i = 1, len = gamma.length(); i < len; i++) { 
			gamma.insert(0, "0");	//��������� � ��������� ������������� ������� �����, ������� ����� ���� ����������� �������������
		}
	}
	return gamma;
}

string omegaEncode(unsigned int value) { //����� ���������
	string omega;
	if (!value) {
		omega = 1;
	} else {
		omega = "0";
		while (value != 1) {
			string binary = intToBinary(value); //������������ �������� � �������� �������
			omega = binary + omega;				//���������� ����� ����
			value = binary.length() - 1; 		//������������ �������� � ����� ��� ��������� �������������
		}
	}
	return omega;
}

int main() {
	setlocale(LC_ALL, "Russian");

	unsigned int value;
	string fixed, gamma, omega;
	cout << "number " << setw(10) << "Fixed + Variable\t" << setw(10) << "gamma-code\t" << setw(10) <<  "omega-code" << endl;
	for (int i = 1; i < 21; i++)
	{
		fixed = fixedVariableEncode(i); //����������� �������� ���� fixed+variable
		gamma = gammaEncode(i);			//����������� �������� ����� �����
		omega = omegaEncode(i);			//����������� �������� ����� �����
		cout << i << setw(20) << fixed << setw(15) << gamma << setw(15) << omega << endl;
	}
}

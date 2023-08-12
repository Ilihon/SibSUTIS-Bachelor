#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <iostream>

using namespace std;

int main () {
	setlocale(LC_ALL,"Russian");
	int i, j, l, m, a, n = 3;
	double t;
	double mas[n][n+1];
	double B[n];
	double mod;
	int index;
//	mas[0][0] = 2;
//	mas[0][1] = 1;
//	mas[0][2] = -3;
//	mas[0][3] = -5;
//	mas[1][0] = -3;
//	mas[1][1] = 4;
//	mas[1][2] = 1;
//	mas[1][3] = 6;
//	mas[2][0] = -1;
//	mas[2][1] = 2;
//	mas[2][2] = -3;
//	mas[2][3] = -4;

	for (i = 0; i < n; i++) {
		for (j = 0; j <= n; j++) {
			cin >> a;
			mas[i][j] = a;
		}
	}

	cout<<"�������:"<<endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf (" %6.2f ", mas[i][j]);
		printf ("| %6.2f \n", mas[i][j]);
	}
	cout << endl << endl;
	for (j = 0; j < n - 1; j++) {
		mod = mas[j][j];
		index = j;
		for (int i = j + 1; i < n; i++) {
			if (fabs(mas[i][j]) > fabs(mod)) {//���������� 1 �� 2 � 1 � 3 ���� ������� �� ������ �� ������� ���� ������ �� ������ j �� i
				mod = mas[i][j];
				index = i;
			}
		}
		if (index != j) {//������� �� �������� �����,��� �� ���������� ������ �� ������ � ������� ������ � ����� ���������� ��������� � ������ �� ��������
			for (int i = 0; i < n + 1; i++) {
				swap(mas[j][i], mas[index][i]);
			}
			cout << "������ ������� " << j + 1 << " � " << index + 1 << " ������" << endl;
			cout << endl;
			for (m = 0; m < n; m++) {//����� �������
				for (int  g = 0; g < n; g++)
					printf (" %6.2f ", mas[m][g]);
				printf ("| %6.2f \n", mas[m][n]);
			}
			cout << endl;
			for (i = j + 1; i < n; i++) {
				t = mas[i][j] / mas[j][j] * (-1);

				for (l = 0; l <= n; l++) {
					mas[i][l] = mas[i][l] + t * mas[j][l];
				}
				cout << "���������� " << i + 1 << "-� � " << j + 1 << "-� ������, ���������� �� " << t << endl;
				cout << endl;
				for (m = 0; m < n; m++) {
					for (int  g = 0; g < n; g++)
						printf (" %6.2f ", mas[m][g]);
					printf ("| %6.2f \n", mas[m][n]);
				}
				cout << endl;
			}
			cout << "�������� " << j + 1 << "-�� �������" << endl << endl;
		} else {
			cout << endl;
			for (i = j + 1; i < n; i++) {
				if(mas[j][j]==0){
					t = 0;
				}
				else{
					t = mas[i][j] / mas[j][j] * (-1);
				}

				for (l = 0; l <= n; l++) {
					mas[i][l] = mas[i][l] + t * mas[j][l];
				}
				cout << "���������� " << i + 1 << "-� � " << j + 1 << "-� ������, ���������� �� " << t << endl;
				cout << endl;
				for (m = 0; m < n; m++) {
					for (int  g = 0; g < n; g++)
						printf (" %6.2f ", mas[m][g]);
					printf ("| %6.2f \n", mas[m][n]);
				}
				cout << endl;
			}
			cout << "�������� " << j + 1 << "-�� �������" << endl << endl;
		}
	}
	int counter = 0;
	for(int i = 0; i < n; i++) {
		int zeros = 0;
		for(int j = 0; j < n+1; j++) {
			if(mas[i][j] == 0) {
				zeros++;
			}
		}
		if(zeros != n+1) {
			counter++;
		}
	}
	cout << "���� ������� : " << counter << endl;




	for (i = n - 1; i >= 0; i--) {   //�������� � ����� (2-�� �������)
		t = mas[i][n]; //���������� ����� �� b-�������

		for (j = i + 1; j < n; j++) { //�������� ��� ��������� ���,����� �������� ���� ����������
			t = t - (B[j] * mas[i][j]);
		}
		if(mas[i][i]==0){
			t = 0;
		}
		else{
			t = t / mas[i][i];
		}
		B[i] = t; //���������� ����� (x1,x2,x3)
	}

	for (i = 0; i < n; i++) {
		printf ("X%d =%6.2f\n", i + 1, B[i]);
	}
	return 0;
}


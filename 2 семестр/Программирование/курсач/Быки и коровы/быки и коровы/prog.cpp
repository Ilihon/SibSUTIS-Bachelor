#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

void Random(char* num, int n)
{
char digits[10] = "123456789";
srand((unsigned)time(0));
for (unsigned i = 0, rmax = 9;  i < n; i++)
{
unsigned r = rand() % rmax--;
num[i] = digits[r];
digits[r] = digits[rmax];
}
}

template <int row, int col>
int BullsandCows(char(&arr)[row][col], unsigned& bull, unsigned& cow)
{
cow = 0;
bull = 0;
unsigned i1, i2;
for (i1 = 0; i1 < col - 1; i1++)
{
for (i2 = 0; i2 < col - 1; i2++)
{
if (arr[0][i1] == arr[1][i2])
{
if (i1 == i2)
cow++;
else
bull++;
}
}
}
return cow ;
}

int main()
{
setlocale(LC_ALL, "RUS");
srand((unsigned)time(NULL));
int choice;
while (true)
{
std::cout << "1.����� ����" << std::endl;
std::cout << "2.������� ����" << std::endl;
std::cout << "3.�����" << std::endl;
std::cin >> choice;
system("CLS");

if (choice == 1)
{
int choise1;
std::cout << "�������� ������� ���������" << std::endl;
std::cout << "1:˸����(4 �����)" << std::endl;
std::cout << "2:�������(6 ����)" << std::endl;
std::cout << "3:������(8 ����)" << std::endl;
std::cout << "4:�����" << std::endl;
std::cin >> choise1;
system("CLS");

if (choise1 == 1)
{
unsigned bulls(0), cows(0);
char numbers[2][5];
numbers[0][4] = '\0';
int c1;
Random(numbers[0], 4);
std::cout << "����� ����������" << std::endl << std::endl;
std::cout << "� ��� ���� 10 �������" << std::endl << std::endl;
for (int i=9; i >= 0 ; i--)
{
std::cout << "���������� ������������������" << std::endl;
std::cout << "****" << std::endl;
std::cout << "������� ���� ������������������(4 �����)" << std::endl;
std::cout << std::endl;
std::cin >> numbers[1];
BullsandCows(numbers, bulls, cows);
std::cout << "����� " << bulls << " �" << " ����� " << cows << std::endl;
std::cout << std::endl;
std::cout << "�������� ������� " << i << std::endl;

if(i == 0)
{
std::cout << "�� ���������" << std::endl << std::endl;
std::cout << "�� 10 �������, �� �� ������� ������������������ " << std::endl;
system("PAUSE");
system("CLS");
break;
}

if (bulls == 4)
{
std::cout << "�� ��������" << std::endl;
std::cout << "���������� ������������������" << std::endl;
std::cout << "" << numbers[1] <<std::endl;
system("PAUSE");
system("CLS");
break;
}
}
}

if (choise1 == 2)
{
unsigned bulls(0), cows(0);
char numbers[2][7];
numbers[0][6] = '\0';
int c1;
Random(numbers[0],6);
std::cout << "����� ����������" << std::endl << std::endl;
std::cout << "� ��� ���� 10 �������" << std::endl << std::endl;
for (int i=9; i >= 0 ; i--)
{
std::cout << "���������� ������������������" << std::endl;
std::cout << "******" << std::endl;
std::cout << "������� ���� ������������������(4 �����)" << std::endl;
std::cin >> numbers[1];
BullsandCows(numbers, bulls, cows);
std::cout << "����� " << bulls << " �" << " ����� " << cows << std::endl;
std::cout << std::endl;
std::cout << "�������� ������� " << i << std::endl;

if(i == 0)
{
std::cout << "�� ���������" << std::endl;
std::cout << "�� 10 �������, �� �� ������� ������������������ " << std::endl;
system("PAUSE");
system("CLS");
break;
}

if (bulls == 6)
{
std::cout << "�� ��������" << std::endl;
std::cout << "���������� ������������������" << std::endl;
std::cout << "" << numbers[1] <<std::endl;
system("PAUSE");
system("CLS");
break;
}
}
}

if (choise1 == 3)
{
unsigned bulls(0), cows(0);
char numbers[2][9];
numbers[0][8] = '\0';
int c1;
Random(numbers[0],8);
std::cout << "����� ����������" << std::endl << std::endl;
std::cout << "� ��� ���� 10 �������" << std::endl << std::endl;
for (int i=9; i >= 0 ; i--)
{
std::cout << "���������� ������������������" << std::endl;
std::cout << "********" << std::endl;
std::cout << "������� ���� ������������������(4 �����)" << std::endl;
std::cin >> numbers[1];
BullsandCows(numbers, bulls, cows);
std::cout << "����� " << bulls << " �" << " ����� " << cows << std::endl;
std::cout << std::endl;
std::cout << "�������� ������� " << i << std::endl;

if(i == 0)
{
std::cout << "�� ���������" << std::endl;
std::cout << "�� 10 �������, �� �� ������� ������������������ " << std::endl;
system("PAUSE");
system("CLS");
break;
}

if (bulls == 8)
{
std::cout << "�� ��������" << std::endl;
std::cout << "���������� ������������������" << std::endl;
std::cout << "" << numbers[1] <<std::endl;
system("PAUSE");
system("CLS");
break;
}
}
}

if(choise1 == 4)
{
system("CLS");
}
}

if (choice == 2)
{
std::cout << "������� ���������� ���� ���� � ������" << std::endl;
std::cout << std::endl;
std::cout << "��������� ���������� ������������������ ����� (������������������ ������� �� ��������� ������������� ������ ���������) " << std::endl;
std::cout << std::endl;
std::cout << "����� �������� ������������� ������������������, ��������� ����� ��������� � ���� '�����' � '�����'" << std::endl;
std::cout << std::endl;
std::cout << "��� '����' ��� ����� ��������� � ��������� �� �������, � '������' ����� ��������� �� ����� �� �� ���� �����" << std::endl;
std::cout << std::endl;
system("PAUSE");
system("CLS");
}

if (choice == 3)
{
std::cout << "�� ��������" << std::endl;
break;
}
}return 0;}


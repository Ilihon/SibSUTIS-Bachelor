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
std::cout << "1.Новая игра" << std::endl;
std::cout << "2.Правила игры" << std::endl;
std::cout << "3.Выход" << std::endl;
std::cin >> choice;
system("CLS");

if (choice == 1)
{
int choise1;
std::cout << "Выберите уровень сложности" << std::endl;
std::cout << "1:Лёгкий(4 цифры)" << std::endl;
std::cout << "2:Средний(6 цифр)" << std::endl;
std::cout << "3:Тяжёлый(8 цифр)" << std::endl;
std::cout << "4:Назад" << std::endl;
std::cin >> choise1;
system("CLS");

if (choise1 == 1)
{
unsigned bulls(0), cows(0);
char numbers[2][5];
numbers[0][4] = '\0';
int c1;
Random(numbers[0], 4);
std::cout << "Добро пожаловать" << std::endl << std::endl;
std::cout << "У вас есть 10 попыток" << std::endl << std::endl;
for (int i=9; i >= 0 ; i--)
{
std::cout << "Загаданная последовательность" << std::endl;
std::cout << "****" << std::endl;
std::cout << "Введите свою последовательность(4 цифры)" << std::endl;
std::cout << std::endl;
std::cin >> numbers[1];
BullsandCows(numbers, bulls, cows);
std::cout << "Быков " << bulls << " и" << " Коров " << cows << std::endl;
std::cout << std::endl;
std::cout << "Осталось попыток " << i << std::endl;

if(i == 0)
{
std::cout << "Вы проиграли" << std::endl << std::endl;
std::cout << "За 10 попыток, вы не угадали последовательность " << std::endl;
system("PAUSE");
system("CLS");
break;
}

if (bulls == 4)
{
std::cout << "Вы выиграли" << std::endl;
std::cout << "Загаданная последовательность" << std::endl;
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
std::cout << "Добро пожаловать" << std::endl << std::endl;
std::cout << "У вас есть 10 попыток" << std::endl << std::endl;
for (int i=9; i >= 0 ; i--)
{
std::cout << "Загаданная последовательность" << std::endl;
std::cout << "******" << std::endl;
std::cout << "Введите свою последовательность(4 цифры)" << std::endl;
std::cin >> numbers[1];
BullsandCows(numbers, bulls, cows);
std::cout << "Быков " << bulls << " и" << " Коров " << cows << std::endl;
std::cout << std::endl;
std::cout << "Осталось попыток " << i << std::endl;

if(i == 0)
{
std::cout << "Вы проиграли" << std::endl;
std::cout << "За 10 попыток, вы не угадали последовательность " << std::endl;
system("PAUSE");
system("CLS");
break;
}

if (bulls == 6)
{
std::cout << "Вы выиграли" << std::endl;
std::cout << "Загаданная последовательность" << std::endl;
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
std::cout << "Добро пожаловать" << std::endl << std::endl;
std::cout << "У вас есть 10 попыток" << std::endl << std::endl;
for (int i=9; i >= 0 ; i--)
{
std::cout << "Загаданная последовательность" << std::endl;
std::cout << "********" << std::endl;
std::cout << "Введите свою последовательность(4 цифры)" << std::endl;
std::cin >> numbers[1];
BullsandCows(numbers, bulls, cows);
std::cout << "Быков " << bulls << " и" << " Коров " << cows << std::endl;
std::cout << std::endl;
std::cout << "Осталось попыток " << i << std::endl;

if(i == 0)
{
std::cout << "Вы проиграли" << std::endl;
std::cout << "За 10 попыток, вы не угадали последовательность " << std::endl;
system("PAUSE");
system("CLS");
break;
}

if (bulls == 8)
{
std::cout << "Вы выиграли" << std::endl;
std::cout << "Загаданная последовательность" << std::endl;
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
std::cout << "Правила логической игры быки и коровы" << std::endl;
std::cout << std::endl;
std::cout << "Компьютер загадывает последовательность чисел (последовательность зависит от выбраного пользователем уровня сложности) " << std::endl;
std::cout << std::endl;
std::cout << "После введеной пользователем последовательности, программа выдаёт подсказки в виде 'Быков' и 'Коров'" << std::endl;
std::cout << std::endl;
std::cout << "Где 'Быки' это число угаданное с точностью до позиции, а 'Коровы' число угаданное но стоит не на своём месте" << std::endl;
std::cout << std::endl;
system("PAUSE");
system("CLS");
}

if (choice == 3)
{
std::cout << "До свидания" << std::endl;
break;
}
}return 0;}


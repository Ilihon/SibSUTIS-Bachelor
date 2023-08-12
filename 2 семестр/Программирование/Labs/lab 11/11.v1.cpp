#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
using namespace std;

struct pas 
{
	char fio[100];	//ФИО ПАССАЖИРА
	int km;			//КОЛИЧЕСТВО МЕСТ БАГАЖА	
	int kg;			//ВЕС БАГАЖА
} lonepas;

void input(FILE *);
void output(FILE *);
void app(FILE *);
void findDelete(FILE *);

main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char ch;
	FILE *lone;
	while (1) {
		system("CLS");
		puts(" 1 - Новый файл :)");
		puts(" 2 - Просмотр файла :D");
		puts(" 3 - Добавление в файл :()");
		puts(" 4 - Поиск и Удаление :/");
		puts(" 0 - Выход :(");
		ch=getch();
		switch (ch) {
			case '1': input(lone); break;
			case '2': output(lone); break;
			case '3': app(lone); break;
			case '4': findDelete(lone); break;
			case '0': return 0;
			default : puts("Ошибка ввода! D:");
		}
	}
}

void input(FILE *lone)
{
	char ch;
	lone=fopen("file1.dat", "wb");
	system("CLS");
	printf("\nВвод Пассажира\n");
	do {
		printf("\n ФИО: "); cin.ignore(); gets(lonepas.fio);
		printf("Места: "); cin >> lonepas.km;
		printf("Вес: "); cin >> lonepas.kg;
		fwrite(&lonepas, sizeof(lonepas), 1, lone);
		printf("\nЗакончить?(y/n): "); ch=getch();
	} while (ch!='y');
	fclose(lone);
}

void output(FILE *lone)
{
	int i;
	system("CLS");
	lone=fopen("file1.dat", "rb");
	i=0;
	fread(&lonepas, sizeof(lonepas), 1, lone);
	printf("+-------+-----------+------+-----+\n");
	printf("| Номер |    ФИО    | Мест | Вес |\n");
	while (!feof(lone)) {
		printf("+-------+-----------+------+-----+\n");
		printf("|%7d|%11s|%6d|%5d|\n", i++, lonepas.fio, lonepas.km, lonepas.kg);
		fread(&lonepas, sizeof(lonepas), 1, lone);
	}
	printf("+-------+-----------+------+-----+\n");
	getch();
}

void app(FILE *lone)
{
	char ch;
	lone=fopen("file1.dat", "ab");
	system("CLS");
	printf("\nВвод Пассажира\n");
	do {
		printf("\n ФИО: "); cin.ignore(); gets(lonepas.fio);
		printf("Места: "); cin >> lonepas.km;
		printf("Вес: "); cin >> lonepas.kg;
		fwrite(&lonepas, sizeof(lonepas), 1, lone);
		printf("\nЗакончить?(y/n): "); ch=getch();
	} while (ch!='y');
	fclose(lone);
}

void findDelete(FILE *lone)
{
	char ch;
	int kgk;
	int i=0, n=0, k;
	pas *str;
	
	lone=fopen("file1.dat", "rb+");
	system("CLS");
	
	puts("Вес меньший 10кг");
	kgk=10;
	
	fread(&lonepas, sizeof(lonepas), 1, lone);
	printf("+-------+-----------+------+-----+\n");
	printf("| Номер |    ФИО    | Мест | Вес |\n");
	while (!feof(lone)) {
		if (lonepas.kg<kgk) {
			printf("+-------+-----------+------+-----+\n");
			printf("|%7d|%11s|%6d|%5d|\n", i, lonepas.fio, lonepas.km, lonepas.kg);
			n++;	
		}
		i++;
		fread(&lonepas, sizeof(lonepas), 1, lone);
	}
	printf("+-------+-----------+------+-----+\n");
	
	k=i-n;
	str=new pas[k];
	
	fseek(lone, 0, 0);
	fread(&lonepas, sizeof(lonepas), 1, lone);
	i=0;
	while (!feof(lone)) {
		if (lonepas.kg>=kgk) str[i++]=lonepas;
		fread(&lonepas, sizeof(lonepas), 1, lone);
	}
	fclose(lone);
	lone=fopen("file1.dat", "wb");
	
	for (i=0; i<k; i++) 
		fwrite(&str[i], sizeof(lonepas), 1, lone);
	
	delete str;
	str=NULL;
	
	getch();
	fclose(lone);
}





#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
void rand_word(char *ss) 
{
	long ml = rand() % 10 + 5;
	ss[ml] = '\n';
	ss[ml + 1] = 0;
	long i;
	ss[0] = 'A' + rand() % (('Z' - 'A') + 1);
	for (i = 1; i < ml; i++) {
		ss[i] = 'a' + rand() % (('z' - 'a') + 1);
	}
}
int main()
{
	setlocale(LC_ALL, "RUS");
	int n;
	FILE *f = fopen("words_vse1.txt", "w");

	char buf[4096];
	cout << "������� ���������� ����: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	 {
		rand_word(buf); //������ ��������� �����
		fputs(buf, f); //���������� ��� � �����
	}
	fclose(f);
	f = fopen("words_vse1.txt", "r");
	while (!feof(f)) //���� ������ �� ������
	if (fgets(buf, 4096, f) > 0 && 0 != strcmp(buf, "")) puts(buf);//������� ����������
		
   	  fclose(f);
    printf("-------------\n");

	f = fopen("words_vse1.txt", "r");
	FILE *fr = fopen("words_r.txt", "w");
	while (!feof(f)) //���� ������ �� ������
	{
		if (fgets(buf, 4096, f) > 0 && 0 != strcmp(buf, "")) 	//�������� ������ � ���������� � ������ ����
		{
			buf[strlen(buf)-1] = 0;
			_strrev(buf); //��������� ������ � ���������� ��� ������� � �������� �������
			buf[strlen(buf)] = 0x0a;
			fputs(buf, fr);
			puts(buf);
		}
	}
	fclose(fr);
	fclose(f);
	_getch();
}
	
	
	

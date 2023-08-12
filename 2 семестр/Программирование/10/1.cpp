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
	FILE *f = fopen("words_vse.txt", "w");

	char buf[4096];
	cout << "Введите количество слов: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	 {
		rand_word(buf); //делаем случайное слово
		fputs(buf, f); //дописываем его в файл
	}


	fclose(f);

	FILE *fa = fopen("words_g.txt", "w");
	FILE *fb = fopen("words_s.txt", "w");
	f = fopen("words_vse.txt", "r");
	while (!feof(f)) //если строка не пустая
	{
		if (fgets(buf, 4096, f) > 0 && 0 != strcmp(buf, "")) //если первая буква гласная, то в первый, иначе во второй
		 {	
			if (buf[0] == 'A' || buf[0] == 'E' || buf[0] == 'I' || buf[0] == 'O' || buf[0] == 'U' || buf[0] == 'Y') {
				fputs(buf, fa);
				puts(buf);
			}
			else {
				fputs(buf, fb);
				puts(buf);
			}

		}
	}               
    
   	fclose(f);
	fclose(fb);
	fclose(fa);
    


	fclose(f);
	_getch();
}
	
	
	
	

#pragma warning(disable : 4996)
#include <fstream> ///Для работы с файлом
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <math.h>

const int n = 27;
int c[n][n], lenght[n], sum = 0;
float p[n];
char a[n];	
int lgm = 0;

int up(int m, float q)
{
	int j = 1;
	for (int i = m - 1; i > 1; i--)
	{
		if (p[i - 1] <= q)
			p[i] = p[i - 1];
		else
		{
			j = i;
			break;
		}
	}
	p[j] = q;
	return j;
}

void down(int m, int j)
{
	int s[n];
	for (int i = 1; i < n; i++)
		s[i] = c[j][i];
	int L = lenght[j];
	for (int i = j; i < m - 1; i++)
	{
		for (int k = 1; k < n; k++)
			c[i][k] = c[i + 1][k];
		lenght[i] = lenght[i + 1];
	}
	for (int i = 1; i < n; i++)
	{
		c[m - 1][i] = s[i];
		c[m][i] = s[i];
	}
	c[m - 1][L + 1] = 0;
	c[m][L + 1] = 1;
	lenght[m - 1] = lenght[m] = L + 1;
}

void huffman(int m)
{
	if (m == 2)
	{
		c[1][1] = 0;
		c[2][1] = 1;
		lenght[1] = lenght[2] = 1;
	}
	else
	{
		float q = p[m - 1] + p[m];
		int j = up(m, q);
		huffman(m - 1);
		down(m, j);
	}
}

void shanon()
{
	float q[n];
	p[0] = 0; q[0] = 0;
	for (int i = 1; i < n; i++)
	{
		q[i] = q[i - 1] + p[i];
		lenght[i] = ceil(-log(p[i]) / log(2));
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j <= lenght[i]; j++)
		{
			q[i - 1] *= 2;
			c[i][j] = floor(q[i - 1]);
			while (q[i - 1] >= 1)
				q[i - 1] -= 1;
		}
	}
}

int med(int L, int R)
{
	float sl = 0, sr;
	for (int i = L; i < R; i++)
		sl += p[i];
	sr = p[R];
	int m = R;
	while (sl >= sr)
	{
		m--;
		sl -= p[m];
		sr += p[m];
	}
	return m;
}

void fano(int L, int R, int k)
{
	if (L < R)
	{
		k++;
		int m = med(L, R);
		for (int i = L; i <= R; i++)
		{
			if (i <= m)
				c[i][k] = 0;
			else
				c[i][k] = 1;
			lenght[i]++;
		}
		fano(L, m, k);
		fano(m + 1, R, k);
	}
}

void gilbert_moor()
{
	bool b = true;
	while (b)
	{ // сортировка по алфавиту (а не по вероятностям, как это было ранее)
		b = false; // не было обмена
		for (int i = 2; i < n; i++)
		{
			if (a[i - 1] > a[i])
			{ // если обмен нужен
				float temp = p[i - 1];
				p[i - 1] = p[i];
				p[i] = temp;
				char c = a[i - 1];
				a[i - 1] = a[i];
				a[i] = c;
				b = true; // помечаем что был обмен
			}
		}
	}  
	float q[n];
	p[0] = 0; q[0] = 0;
	for (int i = 1; i < n; i++)
	{
		q[i] = q[i - 1] + p[i] / 2;
		lenght[i] = ceil(-log(p[i]) / log(2)) + 1;
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j <= lenght[i]; j++)
		{
			q[i] *= float(2);
			c[i][j] = floor(q[i]);
			while (q[i] >= 1)
				q[i] -= 1;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE *f;
	float entropy = 0, lhuffman = 0, lshanon = 0, lfano = 0;
	f = fopen("SAO.txt", "r");
	for (int i = 1; i < n; i++)
		p[i] = 0;
	for (char i = 'а'; i <= 'я'; a[i - 'а' + 1] = i++);

	while (!feof(f))
	{
		char c;
		fscanf(f, "%c", &c);
		if (feof(f))
			break;
		printf("%c",c); 
		p[c - 'а' + 1] += 1;
		sum++;
	}
	printf("\n");
	
	bool b = true;
	while (b)
	{
		b = false;
		for (int i = 1; i < n; i++)
		{
			if (p[i - 1] < p[i])
			{
				float temp = p[i - 1];
				p[i - 1] = p[i];
				p[i] = temp;
				char c = a[i - 1];
				a[i - 1] = a[i];
				a[i] = c;
				b = true;
			}
		}
	}

	float P[n];
	for (int i = 1; i < n; i++)
	{
		p[i] /= float(sum);
		entropy += p[i] * abs(log(p[i]) / log(2));
		P[i] = p[i];
	}
	fclose(f);

	huffman(n - 1);
	printf("\n\nКод Хаффмана: \n");
	printf("---------------------------------------------------------------\n");
	printf("| Символ | Вероятность | Кодовое слово | Длина кодового слова |\n");
	printf("---------------------------------------------------------------\n");
	for (int i = 1; i < n; i++)
	{
		p[i] = P[i];
		printf("|    %c   |  %2.6f   | ", a[i], p[i]);
		for (int j = 1; j <= lenght[i]; j++)
			printf("%d", c[i][j]);
		for (int j = lenght[i] + 1; j < 11; j++)
			printf(" ");
		printf("    |  %14d      |\n", lenght[i]);
		printf("--------------------------------------------------------------\n");
		lhuffman += lenght[i] * p[i];
	}

	for (int i = 1; i < n; i++)
		lenght[i] = 0;

	shanon();
	printf("\n\nКод Шеннона: \n");
	printf("---------------------------------------------------------------\n");
	printf("| Символ | Вероятность | Кодовое слово | Длина кодового слова |\n");
	printf("---------------------------------------------------------------\n");
	for (int i = 1; i < n; i++)
	{
		printf("|    %c   |  %2.6f   | ", a[i], p[i]);
		for (int j = 1; j <= lenght[i]; j++)
			printf("%d", c[i][j]);
		for (int j = lenght[i] + 1; j < 11; j++)
			printf(" ");
		printf("    |  %14d      |\n", lenght[i]);
		printf("--------------------------------------------------------------\n");
		lshanon += lenght[i] * p[i];
	}

	for (int i = 1; i < n; i++)
		lenght[i] = 0;

	fano(1, n - 1, 0);
	printf("\n\nКод Фано: \n");
	printf("---------------------------------------------------------------\n");
	printf("| Символ | Вероятность | Кодовое слово | Длина кодового слова |\n");
	printf("---------------------------------------------------------------\n");
	for (int i = 1; i < n; i++)
	{
		printf("|    %c   |  %2.6f   | ", a[i], p[i]);
		for (int j = 1; j <= lenght[i]; j++)
			printf("%d", c[i][j]);
		for (int j = lenght[i] + 1; j < 11; j++)
			printf(" ");
		printf("    |  %14d      |\n", lenght[i]);
		printf("--------------------------------------------------------------\n");
		lfano += lenght[i] * p[i];
	}

	for (int i = 1; i < n; i++)
		lenght[i] = 0;

	gilbert_moor();
	printf("\n\nКод Гилберта-Мура: \n");
	printf("---------------------------------------------------------------\n");
	printf("| Символ | Вероятность | Кодовое слово | Длина кодового слова |\n");
	printf("---------------------------------------------------------------\n");
	for (int i = 1; i < n; i++)
	{
		printf("|    %c   |  %2.6f   | ", a[i], p[i]);
		for (int j = 1; j <= lenght[i]; j++)
			printf("%d", c[i][j]);
		for (int j = lenght[i] + 1; j < 11; j++)
			printf(" ");
		printf("    |  %14d      |\n", lenght[i]);
		printf("--------------------------------------------------------------\n");
		lgm += lenght[i] * p[i];
	}

	printf("\n\n    Сравнение средних длин кодового слова с энтропией исходного файла");
	printf("\n     ________________________________________________________________\n");
	printf("    |      Энтропия     |      Средняя длина кодового слова         |\n");
	printf("    |                   |___________________________________________|\n");
	printf("    | исходного текста  | Хаффман | Шеннон  |   Фано  | Гилберт Мур |\n");
	printf("    |___________________|_________|_________|_________|_____________|\n");
	printf("    | %12f      | %7.5f | %7.5f | %7.5f |    %7.5f  |\n", entropy, lhuffman, lshanon, lfano, lgm);
	printf("    |___________________|_________|_________|_________|_____________|\n");
	system("pause");
}

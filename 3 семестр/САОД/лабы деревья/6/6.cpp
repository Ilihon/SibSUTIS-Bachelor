#include "fuc.h"
#define YES true
#define NO false

int vr = 1,
	hr = 1;
bool up = NO;
vertex	*root = NULL,
		*root2 = NULL;

int main()
{
	setlocale(0, "rus");
	int *m;
	int NUM = 256;

	m = new int[NUM];
	for (int i = 0; i < NUM; i++) {
		m[i] = rand() % 100 +1;
	}
	
	for (int i = 0; i < NUM; i++) {
		addAVL(m[i], root);
	}
	for (int i = 0; i < NUM; i++) {
		binSert(m[i], root2);
	}

	cout << "\t\t\t\t\tAVL: " << endl;
	LR(root);
	cout << endl << "---" << endl;
	cout << "\t\t\t\t\tDBT: " << endl;
	LR(root2);
	cout << endl << "---" << endl;
	printf("+------+----------+----------------+----------+----------------+\n");
	printf("|%6d|  Размер  |  Контр. сумма  |  Высота  |  Сред. высота  |\n", NUM);
	printf("+------+----------+----------------+----------+----------------+\n");
	printf("|  АВЛ |%10d|%16d|%10d|%16.2f|\n", size(root), summ(root), height(root), (double)sdp(root, 1) / size(root));
	printf("|  БДП |%10d|%16d|%10d|%16.2f|\n", size(root2), summ(root2), height(root2), (double)sdp(root2, 1) / size(root2));
	printf("+------+----------+----------------+----------+----------------+\n");

	system("pause");
    return 0;
}


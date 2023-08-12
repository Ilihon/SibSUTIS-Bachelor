

#include "fuc.h"


const int N = 100;
bool up = NO;

vertex *root = NULL, *root2 = NULL, *root3 = NULL;

int main()
{	
	setlocale(0, "rus");

	int *m;

	m = new int[N];
	
	cout << "\t\t\t\t\tORIG: " << endl;
	for (int i = 0; i < N; i++) {
		m[i] = rand() % 100;
		cout << m[i] << " ";
	}
	cout  << endl << endl;

	for (int i = 0; i < N; i++) {
		addAVL(m[i], root);
	}

	for (int i = 0; i < N; i++) {
		SDP(m[i], root2);
	}
	
	
	for (int i = 0; i < N; i++) {
		m[i] = i;
	}
	root3 = ISDP(0, N - 1, m);

	cout << "\t\t\t\t\tAVL: " << endl;
	LR(root);
	cout << endl << "---" << endl;
	cout << "\t\t\t\t\tSDP: " << endl;
	LR(root2);
	cout << endl << "---" << endl;
	cout << "\t\t\t\t\tISDP: " << endl;
	LR(root3);
	cout << endl << "---" << endl;
	printf("\t+------+----------+----------------+----------+----------------+\n");
	printf("\t|%6d|  Размер  |  Контр. сумма  |  Высота  |  Сред. высота  |\n", N);
	printf("\t+------+----------+----------------+----------+----------------+\n");
	printf("\t|  АВЛ |%10d|%16d|%10d|%16.2f|\n", TreeSize(root), Sum(root), TreeHeight(root), (double) SumDlinPutey(root, 1) / TreeSize(root));
	printf("\t|  СДП |%10d|%16d|%10d|%16.2f|\n", TreeSize(root2), Sum(root2), TreeHeight(root2), (double) SumDlinPutey(root2, 1) / TreeSize(root2));
	printf("\t| ИСДП |%10d|%16d|%10d|%16.2f|\n", TreeSize(root3), Sum(root3), TreeHeight(root3), (double) SumDlinPutey(root3, 1) / TreeSize(root3));
	printf("\t+------+----------+----------------+----------+----------------+\n");

	system("PAUSE");
	return 0;
}



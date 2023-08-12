
#include "fuc.cpp"

vertex *root;

int c = 0;
int *mas, *W;
int *h;
int AW[N + 1][N + 1];
int AP[N + 1][N + 1], AR[N + 1][N + 1];

int main()
{
	setlocale(0, "rus");
	srand(time_t(NULL));
	mas = new int[N];
	for (int i = 0; i < N; i++) {
		mas[i] = i + 1;
		cout << setw(3) << mas[i] << " ";
	}
	cout << " // Начальные ключи" << endl;

	W = new int[N];
	for (int i = 0; i < N; i++) {
		W[i] = rand() % 99 + 1;
		cout << setw(3) << W[i] << " ";
	}
	cout << " // Начальные весы" << endl<<endl;

	AW_count();
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			cout << setw(4) << AW[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	AP_AR_count();

	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			cout << setw(4) << AR[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			cout << setw(4) << AP[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	create_tree(0, N);
	
	int WW = AW[0][N];

	cout << endl;

	root->h = 1;
	seth(root);
	midh(root);
	LRprint(root);


	cout << endl << (double)AP[0][N] / AW[0][N] << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "| n=100 |  Размер  | Контр. сумма | Средневзвеш. высота |" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "|  ДОП  |" << setw(10) << size(root) << "|" << setw(14) << summ(root) << "|" << setw(21) << c / (double)WW << "|" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	system("PAUSE");
	return 0;
}

int height(vertex *x, int data) {
	if (x == NULL) {
		return 0;
	}
	else {
		if (x->data < data) {
			return 1 + height(x->left, data);
		}
		else if (x->data > data) {
			return 1 + height(x->right, data);
		}
		else if (x->data == data) {
			return 1;
		}
	}
}


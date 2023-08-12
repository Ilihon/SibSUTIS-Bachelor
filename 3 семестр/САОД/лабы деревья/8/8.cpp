#include "fuc.cpp"

vertex *root1;
vertex *root2;
vertex *root3;

int c = 0;
int *mas, *W;
int *h;
int AW[N + 1][N + 1];
int AP[N + 1][N + 1], AR[N + 1][N + 1];


int main()
{
	setlocale(0, "rus");
	srand(time(NULL));
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

	root1->h = 1;
	seth(root1);
	midh(root1);

	A2(0, N - 1);
	root3->h = 1;
	seth(root3);
	
	
	BubbleSort();
	for (int i = 0; i < N; i++) {
		cout << setw(3) << mas[i] << " ";
	}
	cout << " // Отсортированные ключи" << endl;
	for (int i = 0; i < N; i++) {
		cout << setw(3) << W[i] << " ";
	}
	cout << " // Отсортированные весы" << endl<<endl;
	
	
	for(int i=0; i<N;i++){
		add(root2, mas[i], W[i]);
	}
	root2->h = 1;
	seth(root2);
	
	
	
	cout <<endl << " Точный алгоритм" <<endl;
	LRprint(root1);
	cout <<endl << " Почти ДОП по А1" <<endl;
	LRprint(root2);
	cout <<endl<<" "<< root3->data<< " - центр тяжести корня A2"<<endl;
	cout << " Почти ДОП по А2" <<endl;
	LRprint(root3);
	
	
	
	int WW = AW[0][N];
	cout << endl << (double)AP[0][N] / AW[0][N] << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "| n=100 |  Размер  | Контр. сумма | Средневзвеш. высота |" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "|  ДОП  |" << setw(10) << size(root1) << "|" << setw(14) << summ(root1) << "|" << setw(21) << (double)c / WW << "|" << endl;
	c=0;
	midh(root2);
	
	cout << "|   А1  |" << setw(10) << size(root2) << "|" << setw(14) << summ(root2) << "|" << setw(21) << (double)c / WW << "|" << endl;
	c=0;
	midh(root3);
	cout << "|   А2  |" << setw(10) << size(root3) << "|" << setw(14) << summ(root3) << "|" << setw(21) << (double)c / WW << "|" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	
	system("PAUSE");
	return 0;
}

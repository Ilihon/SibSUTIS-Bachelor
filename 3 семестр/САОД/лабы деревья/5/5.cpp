
#include "fuc.h"
#include <conio.h>

vertex *root = NULL;
vertex *root1 = NULL;
vertex *root2 = NULL;
int N;

const int add = 100;
const int dell = 50;
int turn = 0;//поворот

int main()
{
	setlocale(0, "rus");
	srand(time_t(NULL));
	int val;
	//5+//
	/*turn = 0;*/
	int add_turns = 0, del_turns = 0;
	/*for (int i = 0; i < add; i++) {
		mas[i] = rand() % 10000;
		addAVL(mas[i], root1);
	}
	add_turns = turn;
	for (int i = 0; i < dell; i++) {
		addAVL(i, root1);
	}
	turn = 0;
	for (int i = 0; i < dell; i++) {
		DeleteAVL(i, root1);
	}
	del_turns = turn;*/
	turn = 0;
	//////
	int y = 0;
	int enter = 0;
	while (true) {
		system("CLS");
		cout << endl << endl;
		cout << "\t----------Menu---------" << endl;
		cout << "\t1. Создать дерево из массива" << endl;
		cout << "\t2. Добавить вершину" << endl;
		cout << "\t3. Удалить вершину" << endl;
		cout << "\t4. Просмотреть дерево" << endl;
		cout << "\t5. Посмотреть статистику" << endl;
		cout << "\t6. Выйти" << endl;
		cout << "\t-----------------------" << endl;
		cout << "\nВыберите пункт: "; cin >> enter;

		if(enter==1){
			turn = 0;
			int *m;
			root=NULL;
			cout << "N = "; 
			cin >> N;
			m = new int[N];
			for (int i = 0; i < N; i++) {
				m[i] = rand() % 100;
			}
			for (int i = 0; i < N; i++) {
				cout << i << "-" << m[i] <<endl;
				addAVL(m[i], root);
			}
			add_turns = turn;
		}
		if(enter==2){
			int data;
			LRprint(root);
			cout << "\nВведите данные вершины: "; cin >> data;
			addAVL(data, root);
			LRprint(root);
			_getch();
		}
		if(enter==3){
			int del;
			turn = 0;
			y = 1;
			while (y != 0) {
				LRprint(root);
				cout << "\nВведите удаляемое число: "; cin >> del;
				DeleteAVL(del, root);
				cout << "\nУдалить еще? (1/0)  "; cin >> y;
			}
			del_turns = turn;
		}
		if(enter==4){
			LRprint(root);
			_getch();
		}
		if(enter==5){
			printf("\t+------+----------+----------------+----------+----------------+----------------+----------------+\n");
			printf("\t|%6d|  Размер  |  Контр. сумма  |  Высота  |  Сред. высота  |  Поворотов del |  Поворотов add |\n", N);
			printf("\t+------+----------+----------------+----------+----------------+----------------+----------------+\n");
			printf("\t|  АВЛ |%10d|%16d|%10d|%16.2f|%16d|%16d|\n", TreeSize(root), Sum(root), TreeHeight(root), (double) SumDlinPutey(root, 1) / TreeSize(root), del_turns, add_turns);
			printf("\t+------+----------+----------------+----------+----------------+----------------+----------------+\n");
			_getch();
		}
		if(enter==6){
			return 0;
		}
	}
	system("PAUSE");
	return 0;
}



#include <iostream>
#include <iomanip>
//#include "AllInOne.h"

using namespace std;

struct Vertex {
    int Data{}, Balance = 0;
    Vertex *Left = nullptr;
    Vertex *Right = nullptr;
};

struct WeightArray {
    int Data{}, Weight{};
};

void LeftRight(Vertex *p) {
    if (p != nullptr) {
        LeftRight(p->Left);
        cout << p->Data << " ";
        LeftRight(p->Right);
    }
}

void BubbleSort(WeightArray *A, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].Data > A[j + 1].Data)
                swap(A[j], A[j + 1]);
        }
}

//Сортировочка пузыриком
void BubbleSortW(WeightArray *A, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j].Weight < A[j + 1].Weight)
                swap(A[j], A[j + 1]);
        }
}

//Двойная косвенность случайного дерева поиска
void RandomSearchTree(int D, Vertex *&Root) {
    auto **p = &Root;
    while (*p != nullptr) {
        if (D < (*p)->Data) p = &((*p)->Left);
        else if (D > (*p)->Data) p = &((*p)->Right);
        else return;
    }
    if ((*p) == nullptr) {
        (*p) = new Vertex;
        (*p)->Data = D;
        (*p)->Right = nullptr;
        (*p)->Left = nullptr;
    }
}

void CreateMatrix(int **&AW, int **&AP, int **&AR, int Size) {
    AW = new int *[Size];
    AP = new int *[Size];
    AR = new int *[Size];
    for (int i = 0; i < Size; ++i) {
        AW[i] = new int[Size];
        AP[i] = new int[Size];
        AR[i] = new int[Size];
    }
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            AW[i][j] = 0;
            AP[i][j] = 0;
            AR[i][j] = 0;
        }
    }
}

//Заполнение матрицы AW данными из массива
void FillAW(int N, WeightArray *W, int **&AW) {
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            AW[i][j] = AW[i][j - 1] + W[j - 1].Weight;
        }
    }
}

//Заполнение матрицы AW данными из массива
void FillAPaAR(int N, int **&AW, int **&AP, int **&AR) {
    for (int i = 0; i < N; ++i) {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }
    for (int h = 2; h <= N; ++h) {
        for (int i = 0; i < N - h; ++i) {
            int j = i + h;
            int m = AR[i][j - 1];
            int min = AP[i][m - 1] + AP[m][j];
            for (int k = m + 1; k <= AR[i + 1][j]; ++k) {
                int x = AP[i][k - 1] + AP[k][j];
                if (x < min) {
                    m = k;
                    min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}

void CreateTree(int L, int R, int **AR, Vertex *&Root, WeightArray A[]) {
    if (L < R) {
        int k = AR[L][R];
        RandomSearchTree(A[k - 1].Data, Root);
        CreateTree(L, k - 1, AR, Root, A);
        CreateTree(k, R, AR, Root, A);
    }
}

void A1(WeightArray *W, Vertex *&Root, int Size) {
    BubbleSortW(W, Size);
    for (int i = 0; i < Size; ++i) {
        RandomSearchTree(W[i].Data, Root);
    }
}

void A2(int L, int R, WeightArray *W, Vertex *&Root) {
    int Wes = 0, Sum = 0, i;
    if (L <= R) {
        for (i = L; i <= R; ++i) {
            Wes += W[i].Weight;
        }
        for (i = L; i < R; ++i) {
            if (Sum <= (Wes / 2) and (Sum + W[i].Weight) >= (Wes / 2)) break;
            Sum += W[i].Weight;

        }
        RandomSearchTree(W[i].Data, Root);
        A2(L, i - 1, W, Root);
        A2(i + 1, R, W, Root);
    }
}

//Высота
int HeightLevel(Vertex *p, int D) {
    if (D < p->Data) return 1 + HeightLevel(p->Left, D);
    if (D > p->Data) return 1 + HeightLevel(p->Right, D);
    return 1;
}

//Уровень вершины
int Level(int X, Vertex *&p) {
    if (X < p->Data)
        return 1 + Level(X, p->Left);
    else if (X > p->Data)
        return 1 + Level(X, p->Right);
    else
        return 1;
}

//Средне взвешанная высота
void MidleTree(WeightArray *Matrix, int N, Vertex *&p) {
    int W = 0, S = 0;
    for (int i = 0; i < N - 1; i++)
        W += Matrix[i].Weight;
    //cout << W << " ";
    for (int i = 0; i < N - 1; i++)
        S += Matrix[i].Weight * Level(Matrix[i].Data, p);
    //cout << S << " ";
    cout << fixed << setprecision(3) << (float) S / (float) W << " ";
}

void PrintMatrix(int **&T, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(3) << T[i][j] << "   ";
        }
        cout << endl;
    }
    cout << endl;
}

void PrintTable(int Size, WeightArray *Matrix, Vertex *&Tree) {
    cout << "| Num |  Data | Weight | Level |"
            "\n|-----|-------|--------|-------|" << endl;
    for (int i = 0; i < Size - 1; ++i) {
        cout << "|" << setw(4) << i + 1 << " | " << setw(5) << Matrix[i].Data
             << " | " << setw(5) << Matrix[i].Weight
             << "  |  " << setw(3) << Level(Matrix[i].Data, Tree) << "  |" << endl;
    }
}

int main() {
    srand(time(nullptr));
    Vertex *Tree = nullptr, *Root = nullptr, *Roots = nullptr;
    int Size = 10;
    WeightArray Matrix[Size], Matrix1[Size], Matrix2[Size];
    //Матрица весов поддеревьев
    int **AW = nullptr,
    //Матрица взвешанных весов поддеревьев
    **AP = nullptr,
    //Матрица корней поддеревьев
    **AR = nullptr;

    for (int i = 0; i < Size - 1; ++i) {
        Matrix[i].Data = rand() % (Size * 100) + 1;
        Matrix[i].Weight = rand() % (Size * 2) + 1;
        for (int j = 0; j < i; ++j) {
            if (Matrix[i].Data == Matrix[j].Data or Matrix[i].Weight == Matrix[j].Weight) i--;
        }
    }

/*
    Matrix[0].Data = 12;
    Matrix[0].Weight = 1;
    Matrix[1].Data = 16;
    Matrix[1].Weight = 2;
    Matrix[2].Data = 18;
    Matrix[2].Weight = 1;
    Matrix[3].Data = 13;
    Matrix[3].Weight = 3;
    Matrix[4].Data = 6;
    Matrix[4].Weight = 1;
    Matrix[5].Data = 3;
    Matrix[5].Weight = 2;
    Matrix[6].Data = 1;
    Matrix[6].Weight = 3;
    Matrix[7].Data = 10;
    Matrix[7].Weight = 3;
    Matrix[8].Data = 5;
    Matrix[8].Weight = 1;
    Matrix[9].Data = 33;
    Matrix[9].Weight = 1;
    Matrix[10].Data = 14;
    Matrix[10].Weight = 1;
    Matrix[11].Data = 23;
    Matrix[11].Weight = 1;
*/

    for (int i = 0; i < Size - 1; ++i) {
        Matrix1[i] = Matrix2[i] = Matrix[i];
    }

    BubbleSort(Matrix, Size - 1);
    BubbleSort(Matrix2, Size - 1);

    CreateMatrix(AW, AP, AR, Size);
    FillAW(Size, Matrix, AW);
    FillAPaAR(Size, AW, AP, AR);
    cout << "AW" << endl << "---------------------" << endl;
    PrintMatrix(AW, Size);
    cout << "AP" << endl << "---------------------" << endl;
    PrintMatrix(AP, Size);
    cout << "AR" << endl << "---------------------" << endl;
    PrintMatrix(AR, Size);

    CreateTree(0, Size - 1, AR, Tree, Matrix);
    cout << "Left Right DOP: ";
    LeftRight(Tree);
    cout << endl;
    A1(Matrix1, Root, Size - 1);
    cout << "Left Right A1: ";
    LeftRight(Root);
    cout << endl;
    A2(0, Size - 1, Matrix2, Roots);
    cout << "Left Right A2: ";
    LeftRight(Roots);

    cout << endl << endl << "Table DOP" << endl;
    PrintTable(Size, Matrix, Tree);
    cout << endl << "Table A1" << endl;
    PrintTable(Size, Matrix1, Root);
    cout << endl << "Table A2" << endl;
    PrintTable(Size, Matrix2, Roots);

    cout << "Middle Tree DOP: ";
    MidleTree(Matrix, Size, Tree);
    cout << endl << "Middle Tree A1: ";
    MidleTree(Matrix1, Size, Root);
    cout << endl << "Middle Tree A2: ";
    MidleTree(Matrix2, Size, Roots);

    cout << endl << setprecision(3) << (float) AP[0][Size - 1] / (float) AW[0][Size - 1] << " ";
}

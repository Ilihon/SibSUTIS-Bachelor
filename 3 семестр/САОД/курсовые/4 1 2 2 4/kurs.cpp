//      C = 1 - ?? ??? ? ???????? ?????, ? = ??p??? ?p? ????? ???????;+++++++++++++++++
//      S = 2   ????? ???p?
//    ????    ????   ??????   ???p???????   ?   ????????????   ?????? ? ++++++++++++++
//    ??p??p??????? ?????????? ??????? ??? ??????? ??????????.
//      D = 2   ???????? ?-?????? ++++++++++++++++++
//      E = 4   ??? ????????-????

#include <fstream>
#include <iostream> 
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdio> 
#include <cstring> 
#include <cstdlib>
#include <cmath>
#include <iomanip>

#define n 4000

const int M = 256;

using namespace std;

struct record3 {
    char fio[32];
    char street[18];
    short int dom;
    short int kv;
    char date[10];
} Temp;

struct vertex {
    record3 Data;
    int bal;
    vertex* Left;
    vertex* Right;
};

struct GM_code {
	char a;
	float p;
	float q;
	int l;
};

GM_code A[M];
GM_code B[166];

vertex* Tree = NULL;
bool rost;
bool vr = 1;
bool hr = 1;
int i, code[M][M], fcompression = 0, cfcompression = 0, sum = 0, v=0;
float entropy = 0, lgm = 0;



//////////// ?????????? ???????? ////////////////////////////
void QuickSortFIO(record3* A, int l, int r) // ?????????? ???
{
    int i = l, j = r;
    char* x = A[r].fio;

    while (i <= j) {

        while (strcmp(A[i].fio, x) < 0)
            i++;
        while (strcmp(A[j].fio, x) > 0)
            j--;
        if (i <= j) {
            Temp = A[i];
            A[i] = A[j];
            A[j] = Temp;

            i++;
            j--;
        }
    }
    if (l < j)
        QuickSortFIO(A, l, j);
    if (i < r)
        QuickSortFIO(A, i, r);
}

void QuickSortStreet(record3* A, int l, int r) // ?????????? ????
{
    int i = l, j = r;
    char* x = A[r].street;

    while (i <= j) {
        while (strcmp(A[i].street, x) < 0)
            i++;
        while (strcmp(A[j].street, x) > 0)
            j--;

        if (i <= j) {
            Temp = A[i];
            A[i] = A[j];
            A[j] = Temp;

            i++;
            j--;
        }
    }
    if (l < j)
        QuickSortStreet(A, l, j);
    if (i < r)
        QuickSortStreet(A, i, r);
}

void QuickSortAll(record3* mas) // ?????????? ????? ?????? ? ??, ??? ?????
{
    int k = 0, l = 0;
    char* temp;
    QuickSortStreet(mas, 0, 3999);
    while (l < n) {

        temp = mas[l].street;

        while (strcmp(temp, mas[l].street) == 0)
            l++;

        QuickSortFIO(mas, k, l - 1);
        k = l;
    }
}
/////////////////////////////////////////////////////////

//////////////////// ????? ?????? ///////////////////////
void Read20(FILE* f, record3* mas) // ????? 20 ???????
{
    int i = 0, button = 0;

    while (i < n) {
        cout << setw(4) << i + 1 << ") " << mas[i].fio << " " << setw(5)
             << mas[i].street << " " << mas[i].dom << " " << mas[i].kv << setw(5)
             << "        " << mas[i].date << endl
             << endl;
        i++;
        if (i % 20 == 0) {
            cout << "\nNu chto, vihodim??? Press ESC for exit or press druguyu "
                    "button for continue\n"
                 << endl;
            button = getch();
            if ((button == 27)) {
                system("cls");
                break;
            }
        }
    }
}

void ReadAll(FILE* f, record3* mas) // ????? ???? ???????
{
    int i = 0, button = 0;

    while (i < n) {
       cout << setw(4) << i + 1 << ") " << mas[i].fio << " " << setw(5)
             << mas[i].street << " " << mas[i].dom << " " << mas[i].kv << setw(5)
             << "        " << mas[i].date << endl
             << endl;
        i++;
        if (_kbhit()) {
            button = getch();
            if (button == 27) {
                break;
            } else if (button == 8) { // BACKSPACE
                while (1) {
                    if (_kbhit()) {
                        button = getch();
                        if (button == 8) { // BACKSPACE
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Sort(record3* mas) // ????????? ???????????? ??? ???? ??????? ???????
{
    cout << "Key Sortirovki:" << endl
         << "1) FIO " << endl
         << "2) Street" << endl
         << "3) FIO and Street " << endl
         << "4) Exit " << endl
         << "\n* Any button to go back *\n";
    char num = getch();

    if (num == '1') {
        system("cls");
        QuickSortFIO(mas, 0, 3999);
    } else if (num == '2') {
        system("cls");
        QuickSortStreet(mas, 0, 3999);
    } else if (num == '3') {
        system("cls");
        QuickSortAll(mas);
    } else if (num == '4') {
        exit(0);
    } else {
        system("cls");
        cout << "";
    }
}
//////////////////////////////////////////////////////////////

////////////////// ??? ??? ?????? ??? ////////////////////////
void insertDT(record3 D, vertex*& p)
{
    vertex* q;
    if (p == NULL) {
        p = new vertex;
        p->Data = D;
        p->Left = p->Right = NULL;
        p->bal = 0;
        vr = 1;
    } else if (strcmp(p->Data.fio, D.fio) > 0)  {
        insertDT(D, p->Left);
        if (vr == 1) {
            if (p->bal == 0) {
                q = p->Left;
                p->Left = q->Right;
                q->Right = p;
                p = q;
                q->bal = 1;
                vr = 0;
                hr = 1;
            } else {
                p->bal = 0;
                hr = 1;
            }
        } else
            hr = 0;
    } else if (strcmp(p->Data.fio, D.fio) <= 0) {
        insertDT(D, p->Right);
        if (vr == 1) {
            p->bal = 1;
            vr = 0;
            hr = 1;
        } else if (hr == 1) {
            if (p->bal == 1) {
                q = p->Right;
                p->Right = q->Left;
                p->bal = 0;
                q->bal = 0;
                q->Left = p;
                p = q;
                vr = 1;
                hr = 0;
            } else
                hr = 0;
        }
    }
}

void obhod(vertex* p)
{
    if (p != NULL) {
        obhod(p->Left);
         cout << setw(4) << i++ << ") " << p->Data.fio << " " << setw(5)
                     << p->Data.street << " " << p->Data.dom << " " << p->Data.kv << setw(5)
                     << "        " << p->Data.date << endl
                     << endl;
        obhod(p->Right);
    }
}
////////////////////////////////////////////////////

void BinSearch(record3* mas, char* key) // ???????? ????? (??????? ???????????? ????????)
{
    int mid, L = 0, R = n - 1, i = 0, k = 0;
    bool find = 0;
    while (L < R) {
        mid = (L + R) / 2;

        if (strncmp((mas[mid].fio), key, 3) == 0) {
            find = 1;
            break;
        }

        if (strncmp((mas[mid].fio), key, 3) < 0)
            L = mid;
        else
            R = mid - 1;
    }

    if (!find) {
        cout << endl
             << "Net takoy FIO\n"
             << endl;
    } else {
        for (i = 0; i < n; i++) {
            if (strncmp((mas[i].fio), key, 3) == 0) {
            	insertDT(mas[i], Tree);
            //	k++; // ???????? ???????????? ?????? ??????
                ////////////////////////////////////////////////////////////////////////////
                  // cout << setw(4) << i + 1 << ") " << mas[i].fio << " " << setw(5)
                    // << mas[i].street << " " << mas[i].dom << " " << mas[i].kv << setw(5)
                    // << "        " << mas[i].date << endl
                    // << endl;
            }
        }
         obhod(Tree);
        //cout << k;
    }
}

void CodeBase()
{
    FILE *fp, *fcoded;
    fp = fopen("testBase4.dat", "rb");
    fcoded = fopen("BaseCoded.dat", "wb");
    char buffer;
    while (!feof(fp)) {
        fscanf(fp, "%c", &buffer);
        fcompression++;
        for (i = 0; i < v; i++) {
            if (buffer == B[i].a) {
                for (int j = 0; j < B[i].l; j++) {
                    putc(code[i][j], fcoded);
                    cfcompression++;
                }
            }
        }
    }
    fclose(fp);
    fclose(fcoded);
}

void CodePrint()
{
    printf("\n\nKodirovka Gilberta - Mura: \n");
    printf("-------------------------------------------------------------------------------\n");
    printf("|      ?        | Symbol | Veroyatnost |     Kodovoe slovo    | Dlina Kodovogo|\n");
    printf("|               |        |             |                      |     slova     |\n");
    printf("|-----------------------------------------------------------------------------|\n");
    for (int i = 0; i < v; i++) {
        printf("|  %12d |    %c   |  %2.6f   | ", i, B[i].a, B[i].q);
        for (int j = 1; j <= B[i].l; j++)
            printf("%d", code[i][j]);
        for (int j = B[i].l + 1; j < 18; j++)
            printf(" ");
        printf("    |  %7d      |\n", B[i].l);
        printf("|-----------------------------------------------------------------------------|\n");
        lgm += B[i].p * B[i].l;
    }

    printf("________________________________________________\n");
    printf("| Entropiya  |  Middle Length  | Kef schatiya  |\n");
    printf("|____________|_________________|_______________|\n");
    printf("| %10f |   %10.5f    |   %10.5f  |\n", entropy, lgm, (float)fcompression / cfcompression);
    printf("|____________|_________________|_______________|\n");

    cout << endl
         << endl
         << entropy + 2 << " > " << lgm << endl
         << endl;
}

void BaseCoding()
{

    int j;
    FILE* fp;
    fp = fopen("testBase4.dat", "rb");
    for (i = 0; i < M; i++) {
        A[i].p = 0;
        A[i].q = 0;
        A[i].l = 0;
        A[i].a = (char)(i-128);
    }
    while (!feof(fp)) {
        char c;
        fscanf(fp, "%c", &c);
        if (feof(fp))
            break;
        //printf("%c",c);
        //cout << c<<" - " << (int)c <<endl;
        A[c + 128].p += 1;
        sum++;
    }
    fclose(fp);
    system("PAUSE");
    for (i = 0; i < M; i++) {
        A[i].p /= sum;
    	cout << i << " - " << (char)(i-128) << " - " << A[i].p <<endl;
        if(A[i].p!=0){
        	v++;
        	entropy += A[i].p * abs(log(A[i].p) / log(2));
		}
    }
	j=0;
	for(i=0;i<M;i++){
		if(A[i].p!=0){
			B[j]=A[i];
    	cout << j << " - " << B[j].a << " - " << B[j].p <<endl;
			j++;
		}
		
	}
	

    for (i = 0; i < v; i++) {
        B[i].q = B[i - 1].q + B[i].p / 2;
        B[i].l = ceil(-log(B[i].p) / log(2)) + 1;
    }

    for (i = 0; i < v; i++) {
        for (j = 0; j <= B[i].l; j++) {
            B[i].q *= float(2);
            code[i][j] = floor(B[i].q);
            while (B[i].q >= 1)
                B[i].q -= 1;
        }
    }
}

int main()
{
	int size;
    FILE* fp;
    record3* mas;
    record3** ptrmas;
    ptrmas = new record3*[n];
    char* key = new char[3];
    fp = fopen("testBase4.dat", "rb");
    mas = new record3[n];
    size = fread((record3*)mas, sizeof(record3), 4000, fp);
    
     for (i = 0; i < n; i++) {
        ptrmas[i] = &mas[i];
      }
    
    while (1) {
        cout << "MENU\n"
             << endl
             << "1) Print 20" << endl
             << "2) Print all" << endl
             << "3) Sort spisok" << endl
             << "4) Binary Poisk and Binary Tree" << endl
             << "5) Kodirovka" << endl
             << "9) Exit" << endl;
        char button = getch();

        if (button == '9') {
            exit(0);
        } else if (button == '1') {
            system("cls");
            Read20(fp, *ptrmas);
        } else if (button == '2') {
            system("cls");
            ReadAll(fp, *ptrmas);
        } else if (button == '3') {
            system("cls");
            Sort(*ptrmas);
        } else if (button == '4') {
            system("cls");
            cout << "First 3 letters of FIO\n";
            for (i = 0; i < 3; i++) {
                scanf("%c", &key[i]);
            }
			BinSearch(*ptrmas, key);
        }  else if (button == '5') {
            system("cls");
            SetConsoleCP(866);
            BaseCoding();
			CodeBase();
			CodePrint();
        }  else
            cout << "\nError! Try again!\n"
                 << endl;
    }
    delete (mas);
    fclose(fp);
    system("PAUSE");
    return 0;
}


#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <iostream>


using namespace std;


struct airport {
    char surname[20];
    int seatnum, weight;
};
struct airport flyplain;




int main() {
	
setlocale(LC_ALL, "Russian");
FILE *f1, *f2;
int a, n = 0, i, j, k = 0;
while (a != 5)
{
      system("CLS");
      cout << "1) ������� ����" << endl;
      cout << "2) ����������� ����" << endl;
      cout << "3) �������� ������ � ����" << endl;
      cout << "4) ������� ����������, ��� ����� ������� ������ 10 ��" << endl;
      cout << "5) �����" << endl;
      cin >> a;
      if (a == 1) {
            cout << "������� ����� �������? n = ";
            cin >> n;
            f1 = fopen("structs.dat", "wb");
            for (i = 0; i < n; i++) {
              cout << "�������: ";
              cin >> flyplain.surname;
              cout << "���������� ����: ";
              cin >> flyplain.seatnum;
              cout << "��� ������: ";
              cin >> flyplain.weight;
              fwrite(&flyplain, sizeof(flyplain), 1, f1);
           }
          fclose(f1);
      }
      if (a == 2) {
	       f1 = fopen("structs.dat", "rb");
            for (i = 0; i < n; i++) {
                fread(&flyplain, sizeof(flyplain), 1, f1);
         	 	cout << flyplain.surname << " " << flyplain.seatnum << " " << flyplain.weight << endl;
            }
            fclose(f1);
            _getch();
        }
        if (a == 3)
        {
            f1 = fopen("structs.dat", "ab");
            n++;
            cout << "�������: ";
            cin >> flyplain.surname;
            cout << "���������� ����: ";
            cin >> flyplain.seatnum;
            cout << "��� ������: ";
            cin >> flyplain.weight;
            fwrite(&flyplain, sizeof(flyplain), 1, f1);
            fclose(f1);
        }
        if (a == 4)
        {
            i = 0;
            f1 = fopen("structs.dat", "rb");
            f2 = fopen("buffer.dat", "wb");
            while (i < n) {
                fread(&flyplain, sizeof(flyplain), 1, f1);
                if (flyplain.weight >= 10) {
                    fwrite(&flyplain, sizeof(flyplain), 1, f2);
                    k++;
                }
                i++;
            }
            n = k;
            k = 0;
            fclose(f1);
            remove("structs.dat");
            fclose(f2);
            rename("buffer.dat", "structs.dat");
        }
    }
    return 0;
}

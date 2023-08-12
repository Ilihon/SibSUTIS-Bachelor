#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>


int random (int N) { return rand()%N; }
int mp=0, cp=0;

void Spravochnik();
void Swap (int &x, int &y);
void SelectSort_Struct (int A[], int n, int z);

int Less (struct sprav x, struct sprav y, int z);

struct sprav {
	char sir[10];
	char name[10];
	char city[15];
	char phone[16];
};

struct sprav abonent[5];


main() {
	Spravochnik();
	system("PAUSE");
	return 0;
}


void Swap (int &x, int &y) {
	int t=x; x=y; y=t;
}

void zap () {
	strcpy (abonent[0].sir, "Stoyak");
	strcpy (abonent[1].sir, "Koloss");
	strcpy (abonent[2].sir, "Baukov");
	strcpy (abonent[3].sir, "Veding");
	strcpy (abonent[4].sir, "Cartman");
	strcpy (abonent[0].name, "Yri");
	strcpy (abonent[1].name, "Yana");
	strcpy (abonent[2].name, "Dmitry");
	strcpy (abonent[3].name, "Johnathan");
	strcpy (abonent[4].name, "Erick");
	strcpy (abonent[0].city, "Novosibirsk");
	strcpy (abonent[1].city, "Ufa");
	strcpy (abonent[2].city, "Bryansk");
	strcpy (abonent[3].city, "LA");
	strcpy (abonent[4].city, "South park");
	strcpy (abonent[0].phone, "8(913)980-32-01");
	strcpy (abonent[1].phone, "8(913)548-53-76");
	strcpy (abonent[2].phone, "8(997)177-90-61");
	strcpy (abonent[3].phone, "8(916)208-92-65");
	strcpy (abonent[4].phone, "8(917)918-19-20");
}

void Spravochnik() {
	zap ();
	int i, n=5;
	int a[n], b[n];
	for (i=0; i<n; i++) a[i]=b[i]=i;
	SelectSort_Struct (a, n, 0);
	SelectSort_Struct (b, n, 1);
	for (i=0; i<n; i++) {
		printf ("%s ", abonent[i].sir);
		printf ("%s ", abonent[i].name);
		printf ("%s ", abonent[i].city);
		printf ("%s ", abonent[i].phone);
		printf("\n");
	}
	printf("\nSurname\n\n");
	for (i=0; i<n; i++) {
		printf ("%s ", abonent[a[i]].sir);
		printf ("%s ", abonent[a[i]].name);
		printf ("%s ", abonent[a[i]].city);
		printf ("%s ", abonent[a[i]].phone);
		printf("\n");
	}
	printf("\nCity\n\n");
	for (i=0; i<n; i++) {
		printf ("%s ", abonent[b[i]].city);
		printf ("%s ", abonent[b[i]].sir);
		printf ("%s ", abonent[b[i]].name);
		printf ("%s ", abonent[b[i]].phone);
		printf("\n");
	}
}

void SelectSort_Struct (int A[], int n, int z) {
	int i, j ,k, t;
	for (i=0; i<(n-1); i++) {
		k=i;
		for (j=i+1; j<n; j++) {
			if (Less (abonent [A[j]], abonent [A[k]], z)) k=j;
		}
		if (k!=i) {
			Swap (A[i], A[k]);
		}
	}
}

int Less (struct sprav x, struct sprav y, int z) {
	int i;
	switch (z) {
		case 0: i=strcmp (x.sir, y.sir);
			if (i<0) return 1;
			else return 0;
			break;
		case 1: i=strcmp (x.city, y.city);
			if (i<0) return 1;
			else return 0;
			break;
	}
}

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <iostream>
#include <stdlib.h>


int main(){
	setlocale(LC_ALL,"RUS");
	int i, numberf = 3, t, j, k, s,n; 
	float pl;
	
	printf("Введите количество комнат: ");
	scanf("%d",&n); 
	
	char f[numberf][4] = {{"IVT"},{"MRM"},{"MTS"}};
		
	struct obshejitie {int number; int S; char fak[4]; int proj;};
	struct obshejitie A[n];	
	printf("номер комнаты | площадь комнаты | номер факультета | количество проживающих\n");
	for (i=0;i<n;i++)
	{
		scanf("%d%d%d%d",&A[i].number, &A[i].S, &t, &A[i].proj);
		strcpy(A[i].fak,f[t]);
	}
	for(i=0; i < numberf;i++) {
		t=0; k=0; s=0; pl=0;
		for(j=0;j < n;j++){
			if(strcmp(A[j].fak,f[i])==0){	
				t++;
				k+=A[j].proj;
				s+=A[j].S;
			}
		}
		if(k==0) {
		 pl=0;	
		} 
		else {
		pl=float(s)/k;
		}
		printf("Факультет %s. Кол-во комнат: %d, кол-во студентов: %d, площадь на человека: %.2f\n",f[i],t,k,pl);
	}
	return 0;
}

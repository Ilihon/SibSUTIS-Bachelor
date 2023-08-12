#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include<math.h>


//Вводим последовательность чисел через enter в конце ноль
int recyr(int *mass,int i){
	if(mass[i] <0){
		printf("%3d",mass[i]);
		
	}
	if(i!=6){
		recyr(mass,i+1);
	}
	if(mass[i] >0){
		printf("%3d",mass[i]);
		
	}
	return 0;
}

int main(){
	int mass[6] = {-1,1,2,-2,-8,6};
	int i=0;
recyr(mass,i);
printf("\n");
system("pause");
}
 


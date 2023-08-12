
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
const int n = 140;
const int symbol_index_start =32;
int all_sym_count = 0;

struct symbol_struc {
	char symbol;
	int count;
	float chance;
} symbols[n-symbol_index_start];

int read_file(char *filename){
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        cout << ("Ошибка открытия файла");
        return -1;
    }
    char* line;
    line = new char[4096];
    char buffer;
	while (!feof(f)){
		fscanf(f, "%c", &buffer);
		if(feof(f)){	
			break;
		}     
		if(buffer!='\n'){
			symbols[(char)(buffer)-symbol_index_start].count++;     
			all_sym_count++;      
		}  
    }
    fclose(f);
	return 0;
}

void struct_print(){
	printf("\n  -----------------------------------------------------\n");
	printf("  | Номер Символа | Символ | Количество | Вероятность |\n");
	printf("  |               |        | повторений |  символа    |\n");
	printf("  |---------------------------------------------------|\n");
	for(int i=0,j=0;i<n-symbol_index_start;i++){
		if(symbols[i].count!=0){
			printf("  |  %12d |    %c   |   %6d   |  %2.6f   |\n",j, symbols[i].symbol, symbols[i].count, symbols[i].chance);
			printf("  |---------------------------------------------------|\n");
			j++;
		}
	}
	cout << endl << "  Всего символов в файле: " << all_sym_count;
	return;
}

void InsertSort() 
{
	int i,j;
	struct symbol_struc *temp;
	for(i=1; i<n-symbol_index_start; i++) {
		*temp = symbols[i];
		j=i-1;
		while(j>=0 && temp->chance > symbols[j].chance) {
			symbols[j+1]=symbols[j];
			j=j-1;
		}
		symbols[j+1]= *temp;
	}
	return;
}

void calculate_chance(){
	for(int i=0;i<n-symbol_index_start;i++){
		symbols[i].chance = (float) symbols[i].count / all_sym_count;
	}
	return;
}

void symbols_init(){
	for(int i=0;i<n-symbol_index_start;i++){
		symbols[i].symbol = (char)(i+symbol_index_start);
		symbols[i].count = 0;
		symbols[i].chance = 0;
	}
	return;
}

int main(){
    setlocale(LC_ALL,"Russian");
	char filename[128];
	char answer[128];
	int end =0;
	while(!end){
		system("cls");
		cout << "\tВведите имя файла:\n\t";
		scanf("%s",filename);;
		symbols_init();
		if(read_file(filename)==0){
			calculate_chance();
			InsertSort();
			struct_print();
		}
		cout << "\n\n\tВыбрать новый файл? (y/n)\n\t";
		cin >> answer;
		if(strncmp(answer,"y",1)){
			end++;
		}
	}
	return 0;	
}

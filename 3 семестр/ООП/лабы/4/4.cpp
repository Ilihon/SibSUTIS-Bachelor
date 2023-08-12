#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Table{
	FILE *f;
	int i,j;
	void clean_mas(int n){
        try{
			for (int i = 0; i < n; i++) {
			  delete []mas[i];
			}
			delete *mas;
        }
        catch(const exception&exp)
        {
            cout << exp.what()<< endl;
            cout << "Массив не удалось очистить!"<<endl;
        }
		}
		
		void clear_f(){
			f = fopen("mas.txt", "w");
			fclose(f);
        }
	
	public:
	int **mas;
	
		
		
		Table()
		{
			cout << "Constructor"<< endl;
			i=j=0;
		}
		
		~Table(){
			cout << "Destructor";
			f = fopen("mas.txt", "w");
			fclose(f);
		}
		
		void mas_initialisation( int n){
			mas = new int *[n];
			for(i=0;i<n;i++){
			mas[i] = new int[n];
				for(j=0;j<n;j++){
					mas[i][j]= rand() % 9 + 1;
				}
			}
		}
		
		void mas_show(int n){
				cout<<endl <<"\t+--------------+"<< endl;
			for(i=0;i<n;i++){
				cout << "\t";
				for(j=0;j<n;j++){
					cout << "| " << mas[i][j];
				}
				cout<< "|"<<endl <<"\t+--------------+"<< endl;
			}	
		}
		
		void mas_show_txt(int n){
        try    
        {
		 	f = fopen("mas.txt", "r");
			char buf[n];
			if (fgets(buf, n*4, f)==0){
				cout << "Файл пустой";
			}
			else{
				fclose(f);
			 	f = fopen("mas.txt", "r");
				clean_mas(n);
				int k=0;
			 	while (!feof(f)){		 		
			 		if (fgets(buf, n*4, f) > 0 && 0 != strcmp(buf, "")){
			 			k++;
					}
				}
				cout << k;
				fclose(f);
				mas = new int *[k];			
			 	f = fopen("mas.txt", "r");	
				cout<<endl <<"\t+--------------+"<< endl;
				for(i=0;i<k;i++){
					if (fgets(buf, n*4, f) > 0 && 0 != strcmp(buf, "")){
						cout << "\t";
						mas[i] = new int[n];
			 			for(j=0;j<n;j++){
			 				mas[i][j]=	buf[j*2]-'0';
							cout << "| " << mas[i][j];
						}
						cout<< "|"<<endl <<"\t+--------------+"<< endl;
					}	
				}
			}	
			fclose(f);
        }
        catch(const exception&exp)
        {
            cout << exp.what()<< endl;
            cout << "Не удалось открыть файл!"<<endl;
        }
		}
		
		void mas_save(int n){
            try
            {
    			f = fopen("mas.txt", "a");
    			for(i=0;i<n;i++){
    				for(j=0;j<n;j++){
    					char buf[1];
    					itoa(mas[i][j],buf,10);
    					fputs(buf, f);
    					fputs(";", f);
    				}
    				fputs("\n", f);
    			}
    			fclose(f);
            }
            catch(const exception&exp)
            {
                cout << exp.what()<< endl;
                cout << "Не удалось открыть файл!"<<endl;
            }
		}
		
		void mas_new(int n){
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					mas[i][j]= rand() % 9 + 1;
				}
			}
		}
				
		void clean(int n){
			clean_mas(n);
			clear_f();
		}
};



int main(){
	Table terminal;
	srand(NULL);
	setlocale(LC_ALL, "RUS"); 
	FILE *f = fopen("mas.txt", "w");
	fclose(f);
	
	int n=5,i,yrst;
	
	terminal.mas_initialisation(n);
	while(1){
        cout<<"\t\t1.Показать таблицу" <<endl << "\t\t2.Добавить массив в текстовый файл" << endl << "\t\t3.Сгенерировать новый массив " << endl << "\t\t4.Показать весь файл "<< endl<< "\t\t5.Очистка" << endl << "\t\t6. ВЫХОД" << endl;
        cin >> yrst;
        if(yrst==1){
            terminal.mas_show(n);
        }
        if(yrst==2){
            terminal.mas_save(n);
        }
        if(yrst==3){
            terminal.mas_new(n);   
        }
        if(yrst==4){
            terminal.mas_show_txt(n);
        }
        if(yrst==5){
        	terminal.clean(n);
        }
        if(yrst==6){
            break;
        } 
        cout <<endl<<endl<<"Продолжить? 1/0: ";
        cin>>i;
        system("cls");
        if(i==0) break;
    }
}

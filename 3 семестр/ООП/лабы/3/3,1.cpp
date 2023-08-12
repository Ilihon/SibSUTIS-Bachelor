#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

class Menu {
	FILE *f,*fa;
	int n,i,j,len;
	char compare[4096];	
	char buf[4096];	
	public:
		void rand_word() 
		{	
			FILE *f = fopen("words_vse.txt", "w");
			cout << "������� ���������� ����: ";
			cin >> n;
			for (i = 0; i < n; i++)
		 	{	
			 	long ml = rand() % 10 + 5;
				buf[0] = 'A' + rand() % (('Z' - 'A') + 1);
				for (j = 1; j < ml; j++) {
					buf[j] = 'a' + rand() % (('z' - 'a') + 1);
				}
				fputs(buf, f);
				fputs("\n", f);
			}
	   		fclose(f);
		}
		
		void word_add()
		{
			cout << "word add: ";
			f = fopen("words_vse.txt", "a");
			cin >> buf;	
			len = strlen(buf);
			fputs(buf, f);
			fputs("\n", f);
			fclose(f);
		}
		
		void word_print()
	 	{
		 	f = fopen("words_vse.txt", "r");
		 	cout <<endl<<"------------------"<<endl;
			while (!feof(f)) //���� ������ �� ������
			{
				if (fgets(buf, 4096, f) > 0 && 0 != strcmp(buf, "")) //���� ������ ����� �������, �� � ������, ����� �� ������
				{	
						puts(buf);
				}
	
			}
	   		fclose(f);
		 	cout <<"------------------"<<endl;
		}  
		
		void word_search()
		{
			cout << "word search: ";
			cin >> compare;
			len = strlen(compare);	
			compare[len] ='\n';		
		 	f = fopen("words_vse.txt", "r");
			fa = fopen("words_found.txt", "a");
			i=0;
			
			while (!feof(f)) //���� ������ �� ������
			{
				if (fgets(buf, 4096, f) > 0 && 0 != strcmp(buf, ""))
		 		{
					if(!strcmp(compare,buf))
					{
						fputs(buf, fa);
						buf[len] =0;
						cout << buf << " ������� � ��������� �����"<<endl<<endl;
						i=1;
						break;
					}
				}
			}
			if(i==0)
			{
				compare[len] =0;	
				cout << compare << " �� ������� � ��������� �����" <<endl<<endl;
			}
			
			 
	   		fclose(f);
			fclose(fa);
		}
		
		void word_del(){
			cout << "word delete: ";
			cin >> compare;
			len = strlen(compare);	
			compare[len] ='\n';	
		 	f = fopen("words_vse.txt", "r");	
			fa = fopen("words_delete_buffer.txt", "w");
			i=0;
			
			while (!feof(f)) //���� ������ �� ������
			{
				if (fgets(buf, 4096, f) > 0 && 0 != strcmp(buf, ""))
		 		{
					j=0;
					if(!strcmp(compare,buf))
					{
						buf[len]=0;
						cout << endl << buf << " ������� � ��������� ����� � �������� � ���� word_found" <<endl;
						i=1;
						j=1;
					}
					if(j==0)
					{
						fputs(buf, fa);
					}
				}
			}
			fclose(f);
			fclose(fa);
			
			
			if(i==0) //�� �����
			{		
				f = fopen("words_delete_buffer.txt", "w");
				compare[len] =0;	
				cout << compare << " �� ������� � ��������� �����" << endl;
				fclose(f);
			}
			else // �����
			{
				f = fopen("words_vse.txt", "w");	
				fa = fopen("words_delete_buffer.txt", "r");
				while (!feof(fa)) //���� ������ �� ������
				{
					if (fgets(buf, 4096, fa) > 0 && 0 != strcmp(buf, "")) 
		 			{
						fputs(buf, f);
					}
				}		
			fclose(f);
			fclose(fa);
			}
		}
		
		
		void clear() 
		{  
			f = fopen("words_vse.txt", "w");
			fclose(f);
			f = fopen("words_found.txt", "w");
			fclose(f);
			f = fopen("words_delete_buffer.txt", "w");
			fclose(f);
		}  
};

int main()
{
	setlocale(LC_ALL, "RUS");
	FILE *f = fopen("words_vse.txt", "w");
	fclose(f); 
	f = fopen("words_found.txt", "w");
	fclose(f); 
	f = fopen("words_delete_buffer.txt", "w");
	fclose(f); 

	
	Menu terminal;
	int yrst,i;
	while(1){
        cout<<"1.�������� ��������� ���� � ������ � ����" <<endl << "2.����� ���� ���� �� ������" << endl << "3.���������� ����� � ����� ��������� �����" << endl << "4.����� ����� � ��������� �����" << endl << "5.�������� ���� ���������� ��������� �����" << endl << "6.������� ��������� ����������" << endl << "7. �����" << endl;
        cin >> yrst;
        if(yrst==1){
            terminal.rand_word();
        }
        if(yrst==2){
            terminal.word_print();   
        }
        if(yrst==3){
            terminal.word_add();   
        }
        if(yrst==4){
            terminal.word_search();
        }
        if(yrst==5){
            terminal.word_del();
        }
        if(yrst==6){
            terminal.clear();
        }
        if(yrst==7){
            break;
        } 
        cout <<endl<<endl<<"����������? 1/0: ";
        cin>>i;
        system("cls");
        if(i==0) break;
    }
	
	
	system("PAUSE");
	terminal.clear();
	return 0;
}

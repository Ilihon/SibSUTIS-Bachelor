#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
//#include <systdate.h>

using namespace std;

time_t t;
tm *tk;

const int n = 42;

struct calendar_struc {
	int January[n];
	int February[n];
	int March[n];
	int April[n];
	int May[n];
	int June[n];
	int July[n];
	int August[n];
	int September[n];
	int October[n];
	int November[n];
	int December[n];
} Calendar;

void calendar_init();
int MonthFill(int mass[n], int shift, int max_days);
void YearFill(int shift, int year);

void month_name_print(int mn);
void hole_year_print(int year);
int menu(int current_year, int current_shift, int *need_year, int *need_shift);

void new_shift(int *shift,int i);
int calculate_shift(int current_year, int need_year, int shift);

int calendar_save(char filename[256], int year);

void calendar_init(){
	for(int i=0;i<n;i++){
		Calendar.January[i]=0;
		Calendar.February[i]=0;
		Calendar.March[i]=0;
		Calendar.April[i]=0;
		Calendar.May[i]=0;
		Calendar.June[i]=0;
		Calendar.July[i]=0;
		Calendar.August[i]=0;
		Calendar.September[i]=0;
		Calendar.October[i]=0;
		Calendar.November[i]=0;
		Calendar.December[i]=0;
	}
	return;
}

int MonthFill(int mass[n], int shift, int max_days){
	int i=0,v=0;
	for(i=0,v=0;i<n;i++,v++){
		mass[i+shift]=i+1;
		if(v==max_days-1)
			break;
	}
	return i+shift;
}

void YearFill(int shift, int year){
	int i=0;
	i = MonthFill(Calendar.January,shift,31);
	new_shift(&shift,i);
	if(year % 4 !=0)
		i = MonthFill(Calendar.February,shift,28);
	else
		i = MonthFill(Calendar.February,shift,29);
	new_shift(&shift,i);
	i = MonthFill(Calendar.March,shift,31);
	new_shift(&shift,i);
	i = MonthFill(Calendar.April,shift,30);
	new_shift(&shift,i);
	i = MonthFill(Calendar.May,shift,31);
	new_shift(&shift,i);
	i = MonthFill(Calendar.June,shift,30);
	new_shift(&shift,i);
	i = MonthFill(Calendar.July,shift,31);
	new_shift(&shift,i);
	i = MonthFill(Calendar.August,shift,31);
	new_shift(&shift,i);
	i = MonthFill(Calendar.September,shift,30);
	new_shift(&shift,i);
	i = MonthFill(Calendar.October,shift,31);
	new_shift(&shift,i);
	i = MonthFill(Calendar.November,shift,30);
	new_shift(&shift,i);
	i = MonthFill(Calendar.December,shift,31);
	new_shift(&shift,i);
}

void month_name_print(int mn){
	switch(mn){
		case 1:
			cout << "ßíâàğü";
			break;
		case 2:
			cout << "Ôåâğàëü";
			break;
		case 3:
			cout << "Ìàğò";
			break;
		case 4:
			cout << "Àïğåëü";
			break;
		case 5:
			cout << "Ìàé";
			break;
		case 6:
			cout << "Èşíü";
			break;
		case 7:
			cout << "Èşëü";
			break;
		case 8:
			cout << "Àâãóñò";
			break;
		case 9:
			cout << "Ñåíòÿáğü";
			break;
		case 10:
			cout << "Îêòÿáğü";
			break;
		case 11:
			cout << "Íîÿáğü";
			break;
		case 12:
			cout << "Äåêàáğü";
			break;
	}
	return;	
}

void hole_year_print(int year){
	cout << "\t\t\t\t\t    " << year << " ãîä\n";
	cout << "\t";
	month_name_print(1);
	cout << "\t\t\t";
	month_name_print(2);
	cout << "\t\t\t ";
	month_name_print(3);
	cout << "\t\t\t ";
	month_name_print(4);
	cout << "\n ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ";
	cout << "\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ";
	cout << "\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ";
	cout << "\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\n";
	for(int i=0;i<6;i++){
		cout << " ";
		for (int v=0; v<7;v++){
			if(Calendar.January[i*7+v]!=0)
				printf("%02d",Calendar.January[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << "   ";
		for (int v=0; v<7;v++){
			if(Calendar.February[i*7+v]!=0)
				printf("%02d",Calendar.February[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << "   ";
		for (int v=0; v<7;v++){
			if(Calendar.March[i*7+v]!=0)
				printf("%02d",Calendar.March[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << "   ";
		for (int v=0; v<7;v++){
			if(Calendar.April[i*7+v]!=0)
				printf("%02d",Calendar.April[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	cout << "\t";
	month_name_print(5);
	cout << "\t\t\t  ";
	month_name_print(6);
	cout << "\t\t\t ";
	month_name_print(7);
	cout << "\t\t\t ";
	month_name_print(8);
	cout << "\n ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ";
	cout << "\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ";
	cout << "\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ";
	cout << "\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\n";
	for(int i=0;i<6;i++){
		cout << " ";
		for (int v=0; v<7;v++){
			if(Calendar.May[i*7+v]!=0)
				printf("%02d",Calendar.May[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << "   ";
		for (int v=0; v<7;v++){
			if(Calendar.June[i*7+v]!=0)
				printf("%02d",Calendar.June[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << "   ";
		for (int v=0; v<7;v++){
			if(Calendar.July[i*7+v]!=0)
				printf("%02d",Calendar.July[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << "   ";
		for (int v=0; v<7;v++){
			if(Calendar.August[i*7+v]!=0)
				printf("%02d",Calendar.August[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	cout << "\t";
	month_name_print(9);
	cout << "\t\t";
	month_name_print(10);
	cout << "\t\t\t ";
	month_name_print(11);
	cout << "\t\t\t ";
	month_name_print(12);
	cout << "\n ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ";
	cout << "\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ";
	cout << "\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ";
	cout << "\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\n";
	for(int i=0;i<6;i++){
		cout << " ";
		for (int v=0; v<7;v++){
			if(Calendar.September[i*7+v]!=0)
				printf("%02d",Calendar.September[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << "   ";
		for (int v=0; v<7;v++){
			if(Calendar.October[i*7+v]!=0)
				printf("%02d",Calendar.October[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << "   ";
		for (int v=0; v<7;v++){
			if(Calendar.November[i*7+v]!=0)
				printf("%02d",Calendar.November	[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << "   ";
		for (int v=0; v<7;v++){
			if(Calendar.December[i*7+v]!=0)
				printf("%02d",Calendar.December[i*7+v]);
			else
				cout << "  ";
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}

int menu(int current_year, int current_shift, int *need_year, int *need_shift){
	int shift;
	char enter;
	char input[256];
	char filename[256] = "CalendarSave.txt";
	cout << endl << " 1 - ïîêàçàòü òåêóùèé ãîä";
	cout << endl << " 2 - âûáğàòü ãîä";
	cout << endl << " 3 - ñîõğàíèòü òåêóùèé êàëåíäàğü";
	cout << endl << " 4 - âûéòè\n ";
	cin >> enter;
	switch(enter){
		case '1':
			*need_year = current_year;
			*need_shift = current_shift;
			system("CLS");
			calendar_init();
			YearFill(current_shift,current_year);
			break;
		case '2':
			cout << endl << " Ââåäèòå íóæíûé ãîä: ";
			cin >> input;
			*need_year = atoi(input);
			system("CLS");
			calendar_init();
			shift = calculate_shift(current_year, *need_year, current_shift);
			YearFill(shift,*need_year);
			break;
		case '3':
			return calendar_save(filename, *need_year);
			break;			
		case '4':
			return -1;
		default:
			cout << "\n Íåïğàâèëüíûé ââîä";
			return 0;
	}
	return 0;
}

void new_shift(int *shift,int i){
	if (i<34)
		*shift = 7-(34-i);
	else	
		*shift = 7-(41-i);
	return;
}

int calculate_shift(int current_year, int need_year, int shift){
	int counter;
	if(current_year>need_year){
		for(int i = current_year; i>need_year;i--){
			if((i % 4) == 1){
				shift = shift - 2;
			}
			else{
				shift-- ;
			}
			if(shift<0){
				shift = shift + 7;
			}
		}
	}
	else{
		for(int i = current_year; i<need_year;i++){
			if((i % 4) == 1){
				shift = shift+2;
			}
			else{
				shift++;
			}
			if(shift>6){
				shift = shift -6;
			}
		}
	}
	return shift;
}

int calendar_save(char filename[256], int year){
	FILE *f = fopen(filename, "wb");
	if(f==NULL)
  	{
  		perror("Error occured while opening file");
    	return -1;
  	}
	fprintf(f,"\t\t\t\t\t    %d ãîä\n",year);
	fprintf(f,"\tßíâàğü\t\t\tÔåâğàëü\t\t\t Ìàğò\t\t\t Àïğåëü\n");
	fprintf(f," ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\n");
	
	for(int i=0;i<6;i++){
		cout << " ";
		for (int v=0; v<7;v++){
			if(Calendar.January[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.January[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"   ");
		for (int v=0; v<7;v++){
			if(Calendar.February[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.February[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"   ");
		for (int v=0; v<7;v++){
			if(Calendar.March[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.March[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"   ");
		for (int v=0; v<7;v++){
			if(Calendar.April[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.April[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"\n");
	}
	fprintf(f,"\n");
	
	fprintf(f,"\tÌàé\t\t\t  Èşíü\t\t\t Èşëü\t\t\t Àâãóñò\n");
	fprintf(f," ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\n");
	for(int i=0;i<6;i++){
		cout << " ";
		for (int v=0; v<7;v++){
			if(Calendar.May[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.May[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"   ");
		for (int v=0; v<7;v++){
			if(Calendar.June[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.June[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"   ");
		for (int v=0; v<7;v++){
			if(Calendar.July[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.July[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"   ");
		for (int v=0; v<7;v++){
			if(Calendar.August[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.August[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"\n");
	}
	fprintf(f,"\n");
	
	fprintf(f,"\tÑåíòÿáğü\t\tÎêòÿáğü\t\t\t Íîÿáğü\t\t\t Äåêàáğü\n");
	fprintf(f," ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\t ÏÍ ÂÒ ÑĞ ×Ò ÏÒ ÑĞ ÂÑ\n");
	for(int i=0;i<6;i++){
		cout << " ";
		for (int v=0; v<7;v++){
			if(Calendar.September[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.September[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"   ");
		for (int v=0; v<7;v++){
			if(Calendar.October[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.October[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"   ");
		for (int v=0; v<7;v++){
			if(Calendar.November[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.November[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"   ");
		for (int v=0; v<7;v++){
			if(Calendar.December[i*7+v]!=0)
				fprintf(f,"%02d",Calendar.December[i*7+v]);
			else
				fprintf(f,"  ");
			fprintf(f," ");
		}
		fprintf(f,"\n");
	}
	fprintf(f,"\n");
	fclose(f);
	return 0;
}


int main(){
    setlocale(LC_ALL,"RUS");
	srand(time(NULL));
	time(&t);
	tk=localtime(&t);
	int current_year =1900+tk->tm_year;
	int current_shift = 2;
	int need_year = current_year;
	int need_shift = current_shift;
	calendar_init();
	YearFill(current_shift,current_year);
	while(true){
		system("CLS");
		hole_year_print(need_year);
		int r =	menu(current_year, current_shift, &need_year, &need_shift);
		if(r == -1)
			break;
	}
	system("pause");
	return 0;
	
}

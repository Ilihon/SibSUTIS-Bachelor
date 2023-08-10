#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct student 
{
    string surname;
    string name;
    string middle;
    string date;
    string number_group;
    float gpa;
    student *next;
} *head;

struct student2 
{
    string surname;
    string name;
    string middle;
    string date;
    string number_group;
    float gpa;
};
struct student2 save;

void AddStudent(student *&ph, student *&pt, string surname, string name, string middle, string date, string number_group, float gpa) 
{
    student *t = new student;
    t->surname = surname;
	t->name = name;
	t->middle = middle;
	t->date = date;
	t->number_group = number_group;
	t->gpa = gpa;
    t->next = NULL;
    if (ph == NULL) 
	    ph = pt = t; 
	else 
	    pt = pt->next = t;
}	

void PrintStudent(student *ph) 
{
	setlocale(0,"RUS");
    if (ph == NULL) 
        cout << "Queque clear";
    while (ph != NULL) 
	{
        cout << ph->surname <<" "<< ph->name <<" "<< ph->middle <<" "<< ph->date <<" "<< ph->number_group <<" "<< ph->gpa;
        cout << endl; 
		ph = ph->next;
    }
    cout << endl; 
}

void FindStudent (student *ph, string surname, string number_group) 
{
	int k = 1;
	while (ph != NULL) 
	{
        if (ph->surname == surname && ph->number_group == number_group)  
		{
			cout << "Information of Find: " << endl;
            cout << k <<": " << ph->surname <<" "<< ph->name <<" "<< ph->middle <<" "<< ph->date <<" "<< ph->number_group <<" "<< ph->gpa << endl;
	        return;
	    } 
	    ph = ph->next;	
		k++;
    }
    cout << "Find of error!" << endl;
    return;
}

void DeleteStudent(student *&ph, int n) 
{
	student *t1 = ph;
	if (n == 1) 
	{
	    ph = t1->next;
	    delete t1;
	    return;
	}
	for (int i = 1; i < n - 1; ++i) 
	{
	    t1 = t1->next;
	    if ((t1 == NULL) || (t1->next == NULL)) 
		{
	        cout << "Error";
            cout << endl;
	        return;
	    }
	}
	student *t2 = t1->next;
	t1->next = t2->next;
	delete t2;
	return;
}

int writef(student *ph)
{
	FILE *f1;	
	f1 = fopen("list.dat", "wb");
    if (ph == NULL) 
        cout << "Queque clear";
	while (ph != NULL) 
	{
		save.surname = ph->surname;
		save.name = ph->name;
		save.middle = ph->middle;
		save.date = ph->date;
		save.number_group = ph->number_group;
		save.gpa = ph->gpa;
        fwrite(&save, sizeof(save), 1, f1);
		ph = ph->next;
    }
    fclose(f1);
	cout <<"Список сохранён" << endl;
	return 0;
}
            
int main() 
{
    system("CLS");
    setlocale(0,"RUS");
    string surname, name, middle, date, number_group;
    float gpa; 
    student *t = new student;
    student *ph = NULL;
    student *pt = NULL; 
    int variant = 0;
    bool flag = true;
    while (1) 
	{	   
        cout << "Выберите вариант" << endl << endl;
        cout << "1. Добавить" << endl
        << "2. Посмотреть" << endl
        << "3. Поиск по фамилии имени и группе" << endl
        << "4. Удалить студента по номеру" << endl
        << "5. Сохранить список студентов" << endl
        << "6. Выйти" << endl << endl;
        cout << "Выберите действие" << endl << endl;
        
        cin >> variant;
        system("CLS");
        switch (variant) 
		{
            case 1: 
                while (flag) 
				{
                    cout << "Добавить студента:" << endl;
	                cout << "Фамилия, имя, отчество, дата рождения, номер группы, средний балл" << endl;
                    
					cin >> surname; 
					if (surname == "end") 
					{ 
					    break; 
					}
                    cin >> name >> middle >> date >> number_group >> gpa;
                    AddStudent(ph, pt, surname, name, middle, date, number_group, gpa);
	                
					cout << "Студент добавлен" << endl;
	                cout << endl;	
                }
                system("CLS");        	
	            break; 
            case 2:
	            cout << endl;	
                PrintStudent(ph);
                break;
            case 3:	
                cout <<"Поиск по фамилии и группе: " << endl;
                cin >> surname >> number_group; 
                FindStudent(ph, surname, number_group);
                break;                                         
            case 4:
                cout <<"Номер студента: ";
                int n;
	            cin >> n;
                cout << endl;
                DeleteStudent(ph, n);
                break;
	        case 5:
				writef(ph);
    			break;
	        case 6:
	            cout <<"Завершение работы" << endl;
    			return 0;
            default:
                cout << "Вы выбрали неверный вариант";
        }
    }
    
	system("PAUSE");
    return 0;
}

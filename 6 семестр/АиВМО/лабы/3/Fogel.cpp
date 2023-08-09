#include <fstream>
#include <conio.h>
#include <iomanip>
#include <cstdio> 
#include <cstring> 
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

int n,m; //n- columns, m  - lines

//��������� ��������� ��� ������� / ��������
struct minimum{
	int min_first = 9999999;
	int min_second = 9999999;
	int i = -1;
	int j = -1;
	int dif = 0;
};

//��������� ������� �������� ������ ��������� �� ����� ��������
void set_struct_to_default(minimum *mas, int size){
	for(int i = 0; i < size; i++){
		mas[i].min_first = 9999999;
		mas[i].min_second = 9999999;
		mas[i].i = -1;
		mas[i].j = -1;
		mas[i].dif = 0;
	}
	return;
}

void print(int **mas){
	cout << endl << " ����������";
	for(int i = 1; i < n; i++){
		cout << "\t  B" << i;
	}
	cout << "\t������" << endl;
	for (int i=0;i<m;i++)
	{
		if(i == m-1){
			cout << "�����������";
		}
		else{
			cout << "\tA" << i+1;
		}
		for (int j=0;j<n;j++)
		{
			if(mas[i][j] >= 0){
				printf("\t%3d",mas[i][j]);
			}
			else{
				if(mas[i][j] == -10){
					printf("\t  -");
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

void print_with_min(int **mas, minimum *min_lines, minimum *min_colls){
	cout << endl << " ����������";
	for(int i = 1; i < n; i++){
		cout << "\t B" << i;
	}
	cout << "\t������\t���" << endl;
	for (int i=0;i<m;i++)
	{
		if(i == m-1){
			cout << "�����������";
		}
		else{
			cout << "\tA" << i+1;
		}
		for (int j=0;j<n;j++)
		{
			if(mas[i][j] >= 0){
				printf("\t%3d",mas[i][j]);
			}
			else{
				if(mas[i][j] == -10){
					printf("\t  -");
				}
			}
		}
		if(i < m-1){
			if(min_lines[i].dif == -10){
				printf("\t  -\n");
			}
			else{
				printf("\t%3d\n",min_lines[i].dif);
			}
		}
	}
	cout << endl << "       ���";
	for(int i = 0; i < n-1; i++){
		if(min_colls[i].dif == -10){
			printf("\t  -");
		}
		else{
			printf("\t%3d",min_colls[i].dif);
		}
	}
}


int **update_Table(int **arr){
	int column_sum = 0;
	for(int i = 0; i < m-1; i++){
		column_sum += arr[i][n-1];
	}
	int line_sum = 0;
	for(int i = 0; i < n-1; i++){
		line_sum += arr[m-1][i];
	}
	cout << endl << "\t ������: " << column_sum << "\t\t\t �����������: " << line_sum << endl << endl;
	
	//��������� �������� �� ������ � �������������
	if(column_sum == line_sum){
		cout << "\t������ ������������� ������������, ������� �� ��������\n";
		return arr;
	}
	int **new_arr;
	//���� ������������ ������ - ��������� ��� ���� ������
	if(line_sum > column_sum){
		m = m+1;
		new_arr = new int*[m];			
		for (int i=0;i<m-2;i++)
		{
			new_arr[i]=new int[n];
			for (int j=0;j<n;j++)
			{
				new_arr[i][j] = arr[i][j];
			}
		}
		//��� ������
		new_arr[m-2] = new int[n];
		for (int i = 0; i < n-1; i++)
		{
			new_arr[m-2][i] = 0;
		}
		new_arr[m-2][n-1] = line_sum - column_sum;
		
		//��������� ������
		new_arr[m-1]=new int[n];
		for (int i = 0; i < n; i++)
		{
			new_arr[m-1][i] = arr[m-2][i];
		}
		cout << "\t������������ ������ ��� �������, �������� ����� ���������\n";
		return new_arr;
	}
	//���� ������� ������ - ��������� ��� ���� �������
	else{
		n = n+1;
		new_arr = new int*[m];			
		for (int i = 0; i < m; i++)
		{
			new_arr[i]=new int[n];
			for (int j = 0; j < n-2; j++)
			{
				new_arr[i][j] = arr[i][j];
			}
		}
		//��� �������
		for (int i = 0; i < m-1; i++)
		{
			new_arr[i][n-2] = 0;
		}
		new_arr[m-1][n-2] = column_sum - line_sum;
		
		//��������� �������
		for (int i = 0; i < m; i++)
		{
			new_arr[i][n-1] = arr[i][n-2];
		}
		cout << "\t������� ������ ��� ������������, �������� ����� �����������\n";
		return new_arr;
	}
}

//������� �������� ���� ��������� ��� �������
void count_lines_min(int **arr, minimum *mas){
	for(int i = 0; i < m-1; i++){
		//������� ������ ������� � ������
		for(int j = 0; j < n-1; j++){
			if((arr[i][j] > 0) && (arr[i][j] < mas[i].min_first)){
				mas[i].min_first = arr[i][j];
				mas[i].i = i;
				mas[i].j = j;
			}
		}
		//������� ������ ������� � ������
		for(int j = 0; j < n-1; j++){
			if((arr[i][j] > 0) && (arr[i][j] < mas[i].min_second) && (j != mas[i].j)){
				mas[i].min_second = arr[i][j];
			}
		}
		//������� ������� ����� ����� ���������
		mas[i].dif = mas[i].min_second - mas[i].min_first;
		//���� ������ ����������
		if(mas[i].min_first == 9999999){
			int counter = 0;
			for(int j = 0; j < n-1; j++){
				if(arr[i][j] == 0){
					mas[i].i = i;
					mas[i].j = j;
					break;
				}
				counter++;
			}
			//���� ����� ����������� � ��� ������ ��� ���������
			if(counter == n-1){
				mas[i].dif = -10;
			}
		}
		//���� ������� ������������ ������� � ������
		else{
			if(mas[i].min_second == 9999999){
				mas[i].dif = 0;
			}
		}
	}
	/*
	cout << endl;
	for(int i = 0; i < m-1; i++){
		cout << mas[i].dif << " ";
	}
	cout << endl;
	*/
	return;
}


//������� �������� ���� ��������� ��� ��������
void count_columns_min(int **arr, minimum *mas){
	for(int j = 0; j < n-1; j++){
		//������� ������ ������� � �������
		for(int i = 0; i < m-1; i++){
			if((arr[i][j] > 0) && (arr[i][j] < mas[j].min_first)){
				mas[j].min_first = arr[i][j];
				mas[j].i = i;
				mas[j].j = j;
			}
		}
		//������� ������ ������� � �������
		for(int i = 0; i < m-1; i++){
			if((arr[i][j] > 0) && (arr[i][j] < mas[j].min_second) && (i != mas[j].i)){
				mas[j].min_second = arr[i][j];
			}
		}
		//������� ������� ����� ����� ���������
		mas[j].dif = mas[j].min_second - mas[j].min_first;
		//���� ������� ����������
		if(mas[j].min_first == 9999999){
			int counter = 0;
			for(int i = 0; i < m-1; i++){
				if(arr[i][j] == 0){
					mas[j].i = i;
					mas[j].j = j;
					break;
				}
				counter++;
			}
			//���� �������� ��������� � ���� ������� ��������
			if(counter == m-1){
				mas[j].dif = -10;
			}
		}
		//���� ������� ������������ ������� � �������
		else{
			if(mas[j].min_second == 9999999){
				mas[j].dif = 0;
			}
		}
	}
	/*
	cout << endl;
	for(int i = 0; i < n-1; i++){
		//cout << mas[i].min_first << "-" << mas[i].min_second << "\n";
		cout << mas[i].dif << " ";
	}
	cout << endl;
	*/
	return;
}

minimum find_max(minimum *mas, int size){
	minimum max = mas[0];
	for(int i = 1; i < size; i++){
		if(mas[i].dif >= max.dif){
			max = mas[i];
		}
	}
	return max;
}

int check_end(int **arr){
	int counter = 0;
	for(int i = 0; i < m-1; i++){
		for(int j = 0; j < n-1; j++){
			if(arr[i][j] != -10){
				counter++;
			}
		}
	}
	if(counter == 0){
		return 1;
	}
	return 0;
}

int take_StockNeedMin(int a, int b){
	if (a >= b){
		return b;
	}
	else{
		return a;
	}
}

void zero_line(int **arr, int line){
	for(int i = 0; i < n-1; i++){
		arr[line][i] = -10;
	}
}

void zero_collumn(int **arr, int line){
	for(int i = 0; i < m-1; i++){
		arr[i][line] = -10;
	}
}

int main()
{   
	setlocale(LC_ALL, "Russian");
	int **arr, **pre_arr, **extra_arr;
	string filename;
	
	cout << "������� �������� �����:" << endl;
	cin >> filename;
	ifstream input(filename);
	if(!input){
		cout << "������ �������� �����" << endl;
		return 0;
	}
	
	input >> m;
	input >> n;
	
	pre_arr = new int*[m];
	
	for (int i=0;i<m;i++)
	{
		pre_arr[i]=new int[n];
		for (int j=0;j<n;j++)
		{
			if(i == m-1 && j == n-1){
				pre_arr[i][j] = -100;
			}
			else
				input >> pre_arr[i][j];
		}
	}
	cout << "\t�������� �������:";
	print(pre_arr);
	arr = update_Table(pre_arr);
	cout << "\n\t����� �������:";
	print(arr);
	
	extra_arr = new int*[m];
	for (int i=0;i<m;i++)
	{
		extra_arr[i]=new int[n];
		for (int j=0;j<n;j++)
		{	
			if(j < n-1 && i < m-1){
				extra_arr[i][j] = -10;
			}
			else{
				extra_arr[i][j] = arr[i][j];
			}
		}
	}
	minimum min_lines[m-1];
	minimum min_colls[n-1];
	minimum result;
	int Z = 0;
	while(true){
		//�������� ������� �������� ����������� ���������
		set_struct_to_default(min_lines,m-1);
		set_struct_to_default(min_colls,n-1);
		//������� ������� ����������� ��������� �� �������/�������� 
		count_lines_min(arr,min_lines);
		count_columns_min(arr,min_colls);
		
		print_with_min(arr,min_lines,min_colls);
		
		//������� ������������ ������� �� ���� ��������
		minimum line_result = find_max(min_lines,m-1);
		minimum coll_result = find_max(min_colls,n-1);
		//cout << endl << line_result.dif;  
		//cout << endl << coll_result.dif;  
		//���������� ����� ������/������� ������������� � �����-�� �� ������������ �������
		if(line_result.dif >= coll_result.dif){
			result = line_result;
		}
		else{
			result = coll_result;
		}
		cout << endl << endl << endl << "\t����������� �������: �" << result.i + 1 << "B" << result.j + 1; 
		
		//�������� ������ ��� �����������
		int Available_capacity = take_StockNeedMin(arr[result.i][n-1],arr[m-1][result.j]);
		
		Z += arr[result.i][result.j] * Available_capacity;
		
		//�������� ��������� ����� �� �������
		arr[result.i][n-1] -= Available_capacity;
		extra_arr[result.i][n-1] -= Available_capacity;
		//���� ������ ���������, �� ����������� ������
		if(arr[result.i][n-1] == 0){
			zero_line(arr, result.i);
		}
		
		//�������� ��������� ����� �� ������������
		arr[m-1][result.j] -= Available_capacity;
		extra_arr[m-1][result.j] -= Available_capacity;
		//���� ����������� ���������, �� ����������� �������
		if(arr[m-1][result.j] == 0){
			zero_collumn(arr, result.j);
		}
		
		arr[result.i][result.j] = -10;
		extra_arr[result.i][result.j] = Available_capacity;
		if(check_end(arr) == 1){
			break;
		}
		// ������ �������������� 0
		if((arr[result.i][n-1] == 0) && (arr[m-1][result.j] == 0)){
			if((result.i - 1 > 0) && (extra_arr[result.i-1][result.j] == -10)){
				extra_arr[result.i-1][result.j] = 0;
			}
			else{
				if((result.i + 1 > 0) && (extra_arr[result.i + 1][result.j] == -10)){
					extra_arr[result.i+1][result.j] = 0;
				}
				else{	
					if((result.j - 1 > 0) && (extra_arr[result.i][result.j-1] == -10)){
						extra_arr[result.i][result.j-1] = 0;
					}
					else{	
						if((result.j + 1 > 0) && (extra_arr[result.i][result.j+1] == -10)){
							extra_arr[result.i][result.j+1] = 0;
						}
					}
				}
			}
		}
		cout << endl;
		print(extra_arr);
	}
	extra_arr[result.i][result.j] = 0;
	cout << endl;
	print(extra_arr);
	print(arr);
	cout << "\t Z = " << Z;
	return 0;
}

#include "fuc.h"


	Set::Set(char *n){
			cout  << " �������������� "<< n<<"-������������ "<< endl;
			i=j=0;
		}	
			
	Set::Set(){
			cout << " ������������� ������������ ��� �������� ���������� � ����"<< endl;
			i=j=0;
		}
		
	Set::~Set(){
			cout <<" ����������� Set destroyed" <<endl <<endl;
		}
	
	template < class T >
	void Set::mas_init(T *A){
			cout <<endl << "������ ��� ������ "<< endl;
			for (i=0; i<N; i++) {
				A[i]=(rand()%26+0x61)+0.5;
				cout << " "<< A[i];
			}
			cout << endl;
		}

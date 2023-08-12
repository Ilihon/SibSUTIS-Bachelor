#include "fuc.h"


	Set::Set(char *n){
			cout  << " Иницивализация "<< n<<"-конструктора "<< endl;
			i=j=0;
		}	
			
	Set::Set(){
			cout << " Инициализация конструктора без передачи параметров в него"<< endl;
			i=j=0;
		}
		
	Set::~Set(){
			cout <<" Производный Set destroyed" <<endl <<endl;
		}
	
	template < class T >
	void Set::mas_init(T *A){
			cout <<endl << "Массив для списка "<< endl;
			for (i=0; i<N; i++) {
				A[i]=(rand()%26+0x61)+0.5;
				cout << " "<< A[i];
			}
			cout << endl;
		}

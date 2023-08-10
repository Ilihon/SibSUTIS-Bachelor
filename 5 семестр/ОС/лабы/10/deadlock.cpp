#include <windows.h>
#include <process.h>
#include <stdio.h>

HANDLE hMutex1, hMutex2;//это такой отдаленный аналог указателя на некий ресурс.
double sh1 = 0.0;
int sh2 = 0;

void Thread(void* pParams);

int main(void) 
{
	hMutex1 = CreateMutex(NULL, FALSE, NULL);
 	hMutex2 = CreateMutex(NULL, FALSE, NULL);	
	_beginthread(Thread, 0, NULL);//функция, размер стека или 0, список аргументов... создает поток, который начинает выполнение процедуры в start_address.

 	while (sh2 != 10)
 	{	
	 	///WaitForSingleObject(1,2) 1 - идентификатор объекта, 2 - время ожидания в милисекундах
		//останавливает выполнения программы до тех пор пока объект, идентификатор которого передан в функцию, не окажется в "сигнальном" состоянии
		//в нашем случае по завершению работы потока
		
		//не блокировка
		WaitForSingleObject(hMutex2, INFINITE);//захват
 		printf("m) %d\n", sh2);
 		WaitForSingleObject(hMutex1, INFINITE);//захват
 		printf("m) %g\n", sh1);
 		
		//блокировка
 		/*WaitForSingleObject(hMutex1, INFINITE);//захват
 		printf("m) %g\n", sh1);
 		WaitForSingleObject(hMutex2, INFINITE);//захват
 		printf("m) %d\n", sh2);		
 		*/
 		ReleaseMutex(hMutex2);//освобождение//Метод используется для освобождения мьютекса, когда он больше не нужен.
 		ReleaseMutex(hMutex1);//освобождение	 
	}
 	return 0;
}

void Thread(void* pParams)
{
 	while (sh2 != 10)
	{
 		WaitForSingleObject(hMutex2, INFINITE);//захват мьютекса
 		sh2 += 1;
 		//printf("t) %d\n", sh2);
 		WaitForSingleObject(hMutex1, INFINITE);//захват мьютекса
 		sh1 += 0.1;
 		//printf("t) %g\n", sh1);
 		ReleaseMutex(hMutex2);//освобождение
 		ReleaseMutex(hMutex1);//освобождение
 	}
}

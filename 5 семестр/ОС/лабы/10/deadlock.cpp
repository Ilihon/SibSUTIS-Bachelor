#include <windows.h>
#include <process.h>
#include <stdio.h>

HANDLE hMutex1, hMutex2;//��� ����� ���������� ������ ��������� �� ����� ������.
double sh1 = 0.0;
int sh2 = 0;

void Thread(void* pParams);

int main(void) 
{
	hMutex1 = CreateMutex(NULL, FALSE, NULL);
 	hMutex2 = CreateMutex(NULL, FALSE, NULL);	
	_beginthread(Thread, 0, NULL);//�������, ������ ����� ��� 0, ������ ����������... ������� �����, ������� �������� ���������� ��������� � start_address.

 	while (sh2 != 10)
 	{	
	 	///WaitForSingleObject(1,2) 1 - ������������� �������, 2 - ����� �������� � ������������
		//������������� ���������� ��������� �� ��� ��� ���� ������, ������������� �������� ������� � �������, �� �������� � "����������" ���������
		//� ����� ������ �� ���������� ������ ������
		
		//�� ����������
		WaitForSingleObject(hMutex2, INFINITE);//������
 		printf("m) %d\n", sh2);
 		WaitForSingleObject(hMutex1, INFINITE);//������
 		printf("m) %g\n", sh1);
 		
		//����������
 		/*WaitForSingleObject(hMutex1, INFINITE);//������
 		printf("m) %g\n", sh1);
 		WaitForSingleObject(hMutex2, INFINITE);//������
 		printf("m) %d\n", sh2);		
 		*/
 		ReleaseMutex(hMutex2);//������������//����� ������������ ��� ������������ ��������, ����� �� ������ �� �����.
 		ReleaseMutex(hMutex1);//������������	 
	}
 	return 0;
}

void Thread(void* pParams)
{
 	while (sh2 != 10)
	{
 		WaitForSingleObject(hMutex2, INFINITE);//������ ��������
 		sh2 += 1;
 		//printf("t) %d\n", sh2);
 		WaitForSingleObject(hMutex1, INFINITE);//������ ��������
 		sh1 += 0.1;
 		//printf("t) %g\n", sh1);
 		ReleaseMutex(hMutex2);//������������
 		ReleaseMutex(hMutex1);//������������
 	}
}

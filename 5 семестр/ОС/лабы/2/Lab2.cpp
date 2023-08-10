#include <windows.h>
#include <stdlib.h>
#include <iostream>

#define DIV 1024
#define WIDTH 7

using namespace std;

int GetArchitectureProc(int num) {
	switch (num)
	{
	case 6:
		return 64;
	case 9:
		return 64;
	case 0:
		return 32;
	default:
		return -1;
	}
}
int main() 
{
	
	setlocale(LC_ALL, "Russian");
	
	char path1[100];
	char path2[100];
	
	SYSTEM_INFO SysInfo;
	GetNativeSystemInfo(&SysInfo);
	GetSystemDirectory(path1, 100);
	GetTempPath(100, path2);
	
	MEMORYSTATUS stat;
	GlobalMemoryStatus(&stat);

	
  	//���� � ������ ��������
	cout << "���� � ���������� ��������: " << path1 << endl;
	printf ("----------------------------------------------------\n");
	//���� � �������� ������ ������
	cout << "���� � �������� ��������� ������: " << path2 << endl << endl;

	printf ("--------------------���������-----------------------\n");
	cout << "���������� ���� ����������:  " << SysInfo.dwNumberOfProcessors << endl;
	printf ("----------------------------------------------------\n");
	cout << "����������� ���������� - " << GetArchitectureProc(SysInfo.wProcessorArchitecture) << endl;
	printf ("----------------------------------------------------\n");
	cout << "��� ���������� - " << SysInfo.dwProcessorType << endl;
	printf ("----------------------------------------------------\n");
	cout << "lpMinimumApplicationAddress - " << SysInfo.lpMinimumApplicationAddress << endl;
	printf ("----------------------------------------------------\n");
	cout << "lpMaximumApplicationAddress - " << SysInfo.lpMaximumApplicationAddress << endl << endl;
    

  	printf ("-----------------------������-----------------------\n");
	cout << "����� ������ TMemoryStatus dwLenght: " << stat.dwLength << endl;
  	printf ("----------------------------------------------------\n");
	cout << "���������� �������������� ������ � % dwMemoryLoad: " << stat.dwMemoryLoad << endl;
	printf ("----------------------------------------------------\n");
	cout << "����� ���� ������������� �� ���������� ���������� ������ dwTotalPhys: " << stat.dwTotalPhys << endl;
	printf ("----------------------------------------------------\n");
	cout << "��������� ���������� ������ � ������ dwAvailPhys: " << stat.dwAvailPhys << endl;
  	printf ("----------------------------------------------------\n");
	cout <<"����� ����� �������� dwTotalPageFile: " << stat.dwTotalPageFile << endl;
  	printf ("----------------------------------------------------\n");
	cout << "�������� ����� �������� dwAvailPageFile: " <<stat.dwAvailPageFile << endl;
  	printf ("----------------------------------------------------\n");
	cout << "����� ����������� ������ dwTotalVirtual: " << stat.dwTotalVirtual << endl;
  	printf ("----------------------------------------------------\n");
	cout << "�������� ����������� ������ dwAvailVirtual:  "<< stat.dwAvailVirtual << endl<< endl;
	
	
	
	system("PAUSE");
	return 0;
}

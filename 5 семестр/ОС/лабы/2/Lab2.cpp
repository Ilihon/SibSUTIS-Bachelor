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

	
  	//путь к систем каталогу
	cout << "Путь к системному каталогу: " << path1 << endl;
	printf ("----------------------------------------------------\n");
	//путь к каталогу времен файлов
	cout << "Путь к каталогу временных файлов: " << path2 << endl << endl;

	printf ("--------------------Процессор-----------------------\n");
	cout << "Количество ядер процессора:  " << SysInfo.dwNumberOfProcessors << endl;
	printf ("----------------------------------------------------\n");
	cout << "Архитектура процессора - " << GetArchitectureProc(SysInfo.wProcessorArchitecture) << endl;
	printf ("----------------------------------------------------\n");
	cout << "Тип процессора - " << SysInfo.dwProcessorType << endl;
	printf ("----------------------------------------------------\n");
	cout << "lpMinimumApplicationAddress - " << SysInfo.lpMinimumApplicationAddress << endl;
	printf ("----------------------------------------------------\n");
	cout << "lpMaximumApplicationAddress - " << SysInfo.lpMaximumApplicationAddress << endl << endl;
    

  	printf ("-----------------------Память-----------------------\n");
	cout << "Длина записи TMemoryStatus dwLenght: " << stat.dwLength << endl;
  	printf ("----------------------------------------------------\n");
	cout << "Количество использованной памяти в % dwMemoryLoad: " << stat.dwMemoryLoad << endl;
	printf ("----------------------------------------------------\n");
	cout << "Число байт установленной на компьютере физической памяти dwTotalPhys: " << stat.dwTotalPhys << endl;
	printf ("----------------------------------------------------\n");
	cout << "Свободная физическая память в байтах dwAvailPhys: " << stat.dwAvailPhys << endl;
  	printf ("----------------------------------------------------\n");
	cout <<"Всего файла подкачки dwTotalPageFile: " << stat.dwTotalPageFile << endl;
  	printf ("----------------------------------------------------\n");
	cout << "Свободно файла подкачки dwAvailPageFile: " <<stat.dwAvailPageFile << endl;
  	printf ("----------------------------------------------------\n");
	cout << "Всего вирутальной памяти dwTotalVirtual: " << stat.dwTotalVirtual << endl;
  	printf ("----------------------------------------------------\n");
	cout << "Свободно виртуальной памяти dwAvailVirtual:  "<< stat.dwAvailVirtual << endl<< endl;
	
	
	
	system("PAUSE");
	return 0;
}

#include <windows.h>  
#include <stdio.h>  
#include <iostream>  
#include <fstream>
#include <imagehlp.h>
  
using namespace std;  
  
PIMAGE_SECTION_HEADER GetEnclosingSectionHeader(DWORD rva, PIMAGE_NT_HEADERS pNTHeader) 
{  
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(pNTHeader);  //перемещаемся на начало таблицы секций
	for (unsigned i = 0; i < pNTHeader->FileHeader.NumberOfSections; i++, section++)   
        if ((rva >= section->VirtualAddress) && (rva < (section->VirtualAddress + section->Misc.VirtualSize)))  
        	return section;    
    return 0;  
}  
   
void DumpFile(LPSTR filename) 
{  
	ofstream eout("import.txt", ofstream::out);
	int funk = 0;
	LOADED_IMAGE LoadedImage;
    HANDLE hFile;     
	HANDLE hFileMapping;    
	LPVOID lpFileBase;    
	ULONG ulSize;  
    PIMAGE_THUNK_DATA thunk;    
	PIMAGE_IMPORT_BY_NAME pOrdinalName;    
	PIMAGE_DOS_HEADER pDOSHeader;    
	PIMAGE_NT_HEADERS pNTHeader;  
    PIMAGE_IMPORT_DESCRIPTOR importDesc;    
	PIMAGE_SECTION_HEADER pSection;    
    
	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); //открываем файл  
    if (hFile == INVALID_HANDLE_VALUE) 
		return;    
	hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL); //отображаем файл в память  
    if (!hFileMapping) 
	{  
        CloseHandle(hFile);  
        return;  
    }  	     
	lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0); //преобразовать в указатель  
    if (!lpFileBase) 
	{  
        CloseHandle(hFileMapping);  
        CloseHandle(hFile);  
        return;  
    } 
   	cout << "DLL's and Function's of file in " << "import.txt" << endl;
    eout << "DLL's and Function's of file " << filename << ":" << endl;
	
	//Файл начинается с заголовка DOS, за которым следует небольшой EXE-файл формата DOS; 
	//При загрузке PE-файла мы обязаны сначала проверить сигнатуру DOS, затем найти смещение до заголовка PE, а затем проверить сигнатуру PE, расположенную в начале его заголовка.   
    pDOSHeader = (PIMAGE_DOS_HEADER)lpFileBase;  //указатель на DOS-заголовок 
    if (pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE) 
		return;     
    
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pDOSHeader + pDOSHeader->e_lfanew); //находим адрес NT заголовка (PE)
    if (pNTHeader->Signature != IMAGE_NT_SIGNATURE) 
		return;  
    
	int importsStartRVA = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress; //RVA-адрес таблицы импорта  
    if (!importsStartRVA) 
		return;    
    cout << "Address of import table: " << importsStartRVA << endl; 
    
	pSection = GetEnclosingSectionHeader(importsStartRVA, pNTHeader); //определяем адрес секции
	cout << "Address of section: " << pSection << endl; 
    if (!pSection) 
		return;  
    int delta = pSection->VirtualAddress - pSection->PointerToRawData;  //расстояние между секциями
    importDesc = (PIMAGE_IMPORT_DESCRIPTOR)(importsStartRVA - delta + (DWORD)lpFileBase);  //таблица импорта для каждой dll
    
	while (importDesc->Name) 
	{ 
        eout << (PBYTE)(importDesc->Name) - delta + (DWORD)lpFileBase << std::endl;  //название dll   
		thunk = (PIMAGE_THUNK_DATA)((PBYTE)importDesc->FirstThunk - delta + (DWORD)lpFileBase);  //указатель на dll 
        while (thunk->u1.AddressOfData)   
		{  
        	if (!(thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG)) //если ф-ия для импорта и ее не брали
			{    
                pOrdinalName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)thunk->u1.AddressOfData - delta + (DWORD)lpFileBase);  
	            eout << "     " << pOrdinalName->Name << std::endl;
	            funk++;
            }  
            thunk++;  
        }  
        importDesc++;  
    }  
    cout << "Numbers functions: " << funk << endl;
    
	UnmapViewOfFile(lpFileBase);  
    CloseHandle(hFileMapping);  
    CloseHandle(hFile);  
}  
  
int main(int argc, char *argv[])  
{     
	TCHAR Buffer2[] = TEXT("import.exe");
    DumpFile(Buffer2);  
}  

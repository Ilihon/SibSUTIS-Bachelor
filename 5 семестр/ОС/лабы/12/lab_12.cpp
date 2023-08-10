#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

ifstream::pos_type filesize(const char* filename);
int dll(char *a);
int exe(char *a);

int main(int argc, char*argv[]) {
	if (argc < 2) {
		cout << "Too few arguments!";
		return 0;
	}
	
	if (!exe(argv[1]) && !dll(argv[1])) {
		cout << "Wrong format!";
		return 0;
	}
	
	ifstream file(argv[1]);
	if (!file) {
		cout << "No such file in directory!";
		return 0;
	}
	file.close();
	
	HANDLE hSrcFile;
	HANDLE hMapSrcFile;
	PBYTE pSrcFile;
	hSrcFile = CreateFile (argv[1], GENERIC_READ, FILE_SHARE_READ,
                       NULL, OPEN_EXISTING, 0, NULL); //открываем файл
    if(hSrcFile == INVALID_HANDLE_VALUE){
    	printf("Could not open file\n");
    	return 0;
	}
	hMapSrcFile = CreateFileMapping (hSrcFile, NULL, PAGE_READONLY, 0, 0, NULL); //отображаем файл в память 
    if(hMapSrcFile == NULL){
    	printf("Could not create mapping file\n");
    	return 0;
	} 
	pSrcFile = (PBYTE) MapViewOfFile (hMapSrcFile, FILE_MAP_READ, 0, 0, 0); //преобразовываем в указатель  
    if(pSrcFile == NULL){
    	printf("Could not map file\n");
    	return 0;
	} 
	
	int fSize = filesize(argv[1]);
	int k = 0;
	for (int i = 0; i < fSize / 16; i++) {
		printf("%0.8X\t", i);
		for (int j = i * 16; j < (i + 1) * 16; j++) {
			printf("%-0.2x ", pSrcFile[j]);
		}
		printf("\t");
		for (int j = i * 16; j < (i + 1) * 16; j++) {
			printf("%c", pSrcFile[j]);
		}
		printf("\n");
	}
	return 0;
}

ifstream::pos_type filesize(const char* filename)
{
    ifstream in(filename, ifstream::ate | ifstream::binary);
    return in.tellg(); 
}

int dll(char *a)
{
	if(a[strlen(a)-4] != '.' || a[strlen(a)-3] != 'd' || a[strlen(a)-2] != 'l' || a[strlen(a)-1] != 'l') return 0;
    else return 1;
}

int exe(char *a)
{
    if(a[strlen(a)-4] != '.' || a[strlen(a)-3] != 'e' || a[strlen(a)-2] != 'x' || a[strlen(a)-1] != 'e') return 0;
    else return 1;
}

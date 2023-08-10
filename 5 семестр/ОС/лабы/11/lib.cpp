#include <windows.h>
#pragma data_seg(".M_SH")
extern __declspec(dllexport)
char sh[6] = { '\0' }; 
HANDLE hMutex;
#pragma data_seg()
#pragma comment(linker, "/SECTION:.M_SH,RWS" ) 

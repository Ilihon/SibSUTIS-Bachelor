#include <windows.h>

__declspec(dllexport)
int f(int b){
 return b*b;
}
__declspec(dllexport)
int g(int b){
 return b*b*b;
}


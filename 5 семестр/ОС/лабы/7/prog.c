#include <windows.h>
#include <stdio.h>
typedef int(*fun)(int);

int main(){
    DWORD pID;
    pID = GetCurrentProcessId();
    HINSTANCE hInst;
    fun pf, pg;
    hInst = LoadLibrary("lib.dll");

    pf = (fun)GetProcAddress(hInst,"f");
    pg = (fun)GetProcAddress(hInst,"g");

    int number = 3;
    printf("Proccess ID: %d\n", pID);
    printf("n = %d\nn^2 = %i\nn^3 = %i\n", number, pf(number), pg(number));
    printf("Library loaded.\n");
    int k;
    scanf("%d", &k);
    FreeLibrary(hInst);
    printf("Library unloaded.\n");
    scanf("%d", &k);
    return 0;
}

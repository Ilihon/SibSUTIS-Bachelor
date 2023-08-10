#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "lib" )

extern __declspec(dllimport) char sh[6];

int main(void) {
  HANDLE hMutex = CreateMutex(NULL, FALSE, "MyTestEvent");
  printf("Ready!\n");
  while (1) {
    WaitForSingleObject(hMutex, INFINITE);
    printf("sh: %s\n", sh);
    Sleep(100);
    ReleaseMutex(hMutex);
  }
  return 0;
}

#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "lib" )

extern __declspec(dllimport) char sh[6];

int main(void) {
  HANDLE hSemaphore = CreateSemaphore(NULL, 1, 2, "MyTestEvent");
  printf("Ready!\n");
  while (1) {
    WaitForSingleObject(hSemaphore, INFINITE);
    printf("sh: %s\n", sh);
    Sleep(100);
    ReleaseSemaphore(hSemaphore,1,NULL);
  }
  return 0;
}

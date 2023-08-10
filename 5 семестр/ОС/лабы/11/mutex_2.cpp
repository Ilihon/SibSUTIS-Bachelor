#include <windows.h>
#include <process.h>
#include <stdio.h> 

#pragma comment(lib, "lib" )

extern __declspec(dllimport) char sh[6];

int main() {
  int counter = 0;
  HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE,"MyTestEvent");
  if (hMutex == NULL) printf("Error!");
  while (1) {
    WaitForSingleObject(hMutex, INFINITE);
    if (counter % 2) {
        sh[0] = 'H'; sh[1] = 'e'; sh[2] = 'l'; sh[3] = 'l'; sh[4] = 'o'; sh[5] = '\0';
    } else {
        sh[0] = 'B'; sh[1] = 'y'; sh[2] = 'e'; sh[3] = '_'; sh[4] = 'u'; sh[5] = '\0';
    }
    counter++;
    Sleep(100);
    ReleaseMutex(hMutex);
  }
}

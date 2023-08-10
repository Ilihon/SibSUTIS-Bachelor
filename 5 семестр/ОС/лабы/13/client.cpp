#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	HANDLE hPipe;
	LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
	
	hPipe = CreateFile(lpPipeName, GENERIC_READ | GENERIC_WRITE, NULL,                           
        NULL, OPEN_EXISTING, NULL, NULL);
        
	while(1)
	{
        char buf[255] = {0};
        cout << "Client:";
        cin.getline(buf, 255);

        DWORD write = NULL;
        if (!WriteFile(hPipe, buf,strlen(buf), &write, NULL)) {
            printf("WriteFile failed: error code %d\n", (int)GetLastError());
            break;
        }
        
        DWORD read = NULL;
        if (!ReadFile(hPipe, buf, 255 - 1, &read, NULL)) {
            printf("ReadFile failed: error code %d\n", (int)GetLastError());
            break;
        }
        buf[read] = '\0';
        cout <<"Server: "<< buf << endl;
	}
	
	CloseHandle(hPipe);
	return 0;
}

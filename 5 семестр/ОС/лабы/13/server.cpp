#include <iostream>
#include <windows.h>

using namespace std;

DWORD WINAPI Thread(LPVOID param) {
    HANDLE hPipe = (HANDLE)param;
    while (1) {
        DWORD read = NULL;
        char buf[255] = {0};
        if (!ReadFile(hPipe, buf, 255 - 1, &read, NULL)) {
            printf("ReadFile failed: error code %d\n", (int)GetLastError());
            break;
        }
        buf[read] = '\0';
        cout <<"Client: "<< buf << endl;
        cout << "Server:";
        cin.getline(buf, 255);
        DWORD write = NULL;
        if (!WriteFile(hPipe, buf, strlen(buf), &write, NULL)) {
            printf("WriteFile failed: error code %d\n", (int)GetLastError());
            break;
        }
    }
    CloseHandle(hPipe);
 	exit(0);
    return 0;
}

int main() {
	HANDLE hPipe;
	LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
	HANDLE hThread;
	
	while (1) {
		hPipe = CreateNamedPipe(lpPipeName, PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE| PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES, 4096, 4096, PIPE_NOWAIT, NULL);
		
		if (hPipe == INVALID_HANDLE_VALUE) {
			printf("CreatePipe failed: error code %d\n",
				(int)GetLastError());
			return 0;
		}
		if ((ConnectNamedPipe(hPipe,NULL))==0) {
			printf("client could not connect\n");
			return 0;
		}
		
		hThread = CreateThread(NULL,NULL,Thread,hPipe,NULL,NULL); 
		
		if (!hThread) {
	        printf("CreateThread failed: error code %d\n", (int)GetLastError());
	        CloseHandle(hThread);
	        return 1;
	    }
	}
	
	CloseHandle(hThread);
	return 0;
}

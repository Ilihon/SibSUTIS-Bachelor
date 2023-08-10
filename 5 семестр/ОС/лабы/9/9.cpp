#include <iostream>
#include <thread>
#include <ctime>
#include <windows.h>

#define FALSE 0
#define TRUE 1
#define N 2

using namespace  std;

int turn; int readyFlags[N]; int sh = 0;

void EnterCriticalRegion(int threadid)
{
    readyFlags[threadid] = TRUE;
    turn = 1-threadid;
    while(turn == 1-threadid && readyFlags[1-threadid] == TRUE); 
}

void LeaveCriticalRegion(int process)
{
    readyFlags[process] = FALSE;
}

void th1()
{
    for(int i = 0; i < 100; ++i)
    {
    	EnterCriticalRegion(0);
    	sh++;
    	cout << sh << endl;
    	LeaveCriticalRegion(0);
    	Sleep(0);
	}
	readyFlags[0] = 0;
}
void th2()
{
    for(int i = 0; i < 100; ++i)
    {
    	EnterCriticalRegion(1);
    	sh += 2;
    	cout << sh << endl;
    	LeaveCriticalRegion(1);
    	Sleep(0);
	}
	readyFlags[1] = 0;
}

int main()
{
	clock_t start,finish;
	start = clock();
    thread th(th1);
    thread thh(th2);
    
    th.join();
    thh.join();
    finish = clock();
    
    cout << (double)(finish-start) / CLOCKS_PER_SEC << endl;
    
    return 0;
}


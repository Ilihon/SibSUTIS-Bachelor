#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <ctime>
#include <iostream>

CRITICAL_SECTION cs;
using namespace  std;
char sh[6];


void Thread( void* pParams ) {
	int counter = 0;

	while ( 1 ) {

		EnterCriticalSection( &cs );
		if(counter%2) {

			sh[0]='H';
			sh[1]='e';
			sh[2]='l';
			sh[3]='l';
			sh[4]='o';
			sh[5]='\0';

		}

		else {
			sh[0]='B';
			sh[1]='y';
			sh[2]='e';
			sh[3]='_';
			sh[4]='u';
			sh[5]='\0';

		}

		LeaveCriticalSection( &cs );
		counter++;

	}

}


int main( void ) {
	clock_t start,finish;
	InitializeCriticalSection( &cs );
	start = clock();
	_beginthread( Thread, 0, NULL );
	for(int i = 0; i < 100; ++i) {
		EnterCriticalSection( &cs );
		printf("%s\n",sh);
		LeaveCriticalSection( &cs );
		Sleep(0);
	}
    finish = clock();
    
    cout<<(double)(finish-start)/CLOCKS_PER_SEC<<endl;

	return 0;

}

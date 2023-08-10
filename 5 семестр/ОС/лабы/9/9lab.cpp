#include <windows.h>
#include <stdio.h>
#include <thread>
#include <time.h>
#include <iostream>

#define TEST_NUMBER 10000
#define THREAD_0_TERM 1
#define THREAD_1_TERM 2

using namespace std;

bool readyFlags[2];
int turn;
int sh;

CRITICAL_SECTION cs;

void EnterCriticalRegion(int threadId);
void LeaveCriticalRegion(int threadId);

void peterson_thread_0();
void peterson_thread_1();
void peterson();

void critical_section_thread_0();
void critical_section_thread_1();
void critical_section();

int main() {
    sh = 0;
    turn = 0;
    printf("*******************\n");
    printf("Expected value: %d\n", TEST_NUMBER * THREAD_0_TERM + TEST_NUMBER * THREAD_1_TERM);
    printf("*******************\n");
    peterson();
    printf("Real value: %d\n", sh);
    printf("-------------------\n");
    sh = 0;
    critical_section();
    printf("Real value: %d\n", sh);
    printf("-------------------\n");
    return 0;
}

void EnterCriticalRegion(int threadId) {
    readyFlags [threadId] = true; 
    turn = 1 - threadId; 
    while (turn == 1-threadId && readyFlags [1-threadId]);
}

void LeaveCriticalRegion(int threadId)
{
    readyFlags[threadId] = false; 
}

void peterson_thread_0() {
    for (int i = 0; i < TEST_NUMBER; i++)
    {
        EnterCriticalRegion(0);
        sh += THREAD_0_TERM;
        Sleep(0);
        LeaveCriticalRegion(0);
    }
}

void peterson_thread_1() {
    for(int i = 0; i < TEST_NUMBER; i++)
    {
        EnterCriticalRegion(1);
        sh += THREAD_1_TERM;
        Sleep(0);
        LeaveCriticalRegion(1);   
    }
}

void peterson()
{
    clock_t start = clock();
    thread t1(peterson_thread_0);
    thread t2(peterson_thread_1);
	if (!t1.joinable()) {
	   	cout << "Thread " << t1.get_id() << " is not joinable!" << endl;
	} else {
		t1.join();
	}
	if (!t2.joinable()) {
	   	cout << "Thread " << t2.get_id() << " is not joinable!" << endl;
	} else {
		t2.join();
	}

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Peterson time: %f seconds\n", seconds);
}

void critical_section_thread_0() {
    for (int i = 0; i <TEST_NUMBER; i++)
    {
        EnterCriticalSection(&cs);
        sh += THREAD_0_TERM; 
        //Sleep(0);
        LeaveCriticalSection(&cs);
    }
}

void critical_section_thread_1() {
    for(int i = 0; i < TEST_NUMBER; i++)
    {
        EnterCriticalSection(&cs);;
        sh += THREAD_1_TERM; 
        //Sleep(0);
        LeaveCriticalSection(&cs);    
    }
}

void critical_section()
{
    clock_t start = clock();
    InitializeCriticalSection(&cs);
    thread t1(critical_section_thread_0);
    thread t2(critical_section_thread_1);
	if (!t1.joinable()) {
	   	cout << "Thread " << t1.get_id() << " is not joinable!" << endl;
	} else {
		t1.join();
	}
	if (!t2.joinable()) {
	   	cout << "Thread " << t2.get_id() << " is not joinable!" << endl;
	} else {
		t2.join();
	}

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Critical Section time: %f seconds\n", seconds);
}

#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>

using namespace std;

//-----lec
int q = 1;
unsigned int wait_time_us = 500;

int lecture_example_end_func(const char *str, int *p) {
    *p = 0;
    cout << str << endl;
    return 0;
}

void lecture_example_thread(int (*call_function)(const char *, int *)) {
    int counter = 0;
    while (q) {
        cout << "child:  " << q << endl;
        Sleep(wait_time_us);
        if (counter++ > 10)
            break;
    }
    call_function("thread_is_over!", &q);
}

int lecture_example_main(int argc, char **argv) {
	thread thr(lecture_example_thread, lecture_example_end_func);
    thr.detach();

    while (q) {
        cout << "parent: " << q << std::endl;
        Sleep(wait_time_us);
    }

    return 0;
}
//-----lec


unsigned long int counter = 0;
const int threads_amount = 10;
const int for_iterations = 10000;
const int expected_value = threads_amount * for_iterations;

void fc_counter() {
    for (unsigned long int i = 0; i < for_iterations; ++i) {
        counter += 1;
    }
}

int main(int argc, char *argv[]) {
/*	lecture_example_main(argc, argv); // examples from lecture
	cout << endl << "******" << endl;
	cout << "Example from lecture end";
	cout << endl << "******" << e
	ndl;
	Sleep(1);
*/
    cout << "Expected value: " << expected_value << endl;
    vector<thread> threads; 
    for (unsigned long int i = 0; i < threads_amount; ++i) {
        thread new_thread(fc_counter);
        threads.push_back(move(new_thread));
    }

    for (auto & thread : threads) {
        if (!thread.joinable()) {
        	cout << "Thread " << thread.get_id() << " is not joinable!" << endl;
        } else {
            thread.join();
        }
    }

    cout << "Real value: " << counter << endl;

    return 0;
}

#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

void reset_signal_handler(int sigcode);
void signal_handler(int sigcode);


#endif

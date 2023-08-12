#ifndef _CU_H_
#define _CU_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

extern int last_command;

void CU();
int ALU(int command, int operand);


#endif

#ifndef _SETVAR_H_
#define _SETVAR_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

void set_mem(int address);
void set_accum();
void set_instructionCounter();


#endif

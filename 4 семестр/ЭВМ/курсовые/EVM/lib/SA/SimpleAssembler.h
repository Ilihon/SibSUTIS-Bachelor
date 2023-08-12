#ifndef _SIMPLEASSEMBLER_H_
#define _SIMPLEASSEMBLER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

int CommandAnalis(char *command);
int SimpleAssembler(int argc, char** argv);


#endif

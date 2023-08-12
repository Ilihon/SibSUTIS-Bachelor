#ifndef _SIMPLEBASIC_H_
#define _SIMPLEBASIC_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

char clearBackspace(char *str);
int getVarAddr(char varName, int offset);
int getGotoAddr(int gotoLine);
char getVarName(int varAddr, int offset);
int SimpleBasic(int argc, char** argv);


#endif

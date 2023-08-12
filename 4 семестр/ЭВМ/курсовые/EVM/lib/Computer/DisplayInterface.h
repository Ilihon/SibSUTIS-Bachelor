#ifndef _DISPLAYINTERFACE_H_
#define _DISPLAYINTERFACE_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int interface();
void print_interface(int address, enum keys key);
void print_mem(int address);
void print_term_boxes();
void PrintBigChars(int adress);
void memory_convert(int mem, int *conv);
void print_accum();
void print_instruction_Counter(int address);
void print_operation(int address);
void print_reg();
void print_last_command();

#endif

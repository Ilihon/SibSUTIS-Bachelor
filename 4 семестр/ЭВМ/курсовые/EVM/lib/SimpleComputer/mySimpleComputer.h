#ifndef _SIMPLECOMPUTER_H_
#define _SIMPLECOMPUTER_H_


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

using namespace std;

#define SIZE 100

#define REG_OPERATION_OVERFLOW 1
#define REG_DIVISION_ZERO 2
#define REG_MEMORY_OVERFLOW 3
#define REG_IMPULSE_IGNORE 4
#define REG_INVALID_COMMAND 5


extern short int memory[SIZE];
extern short int instructionCounter;
extern short int accum;
extern uint8_t flags;
extern const int REG_SIZE;


int sc_memoryInit();
int sc_memoryPrint();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int * value);
int sc_memorySave (char * filename);
int sc_memoryLoad (char * filename);
int sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);


#endif

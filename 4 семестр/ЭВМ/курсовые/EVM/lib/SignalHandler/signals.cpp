#include "../SimpleComputer/mySimpleComputer.h"
#include "../Terminal/myTerminal.h"
#include "../BigChars/myBigChars.h"
#include "../ReadKeys/myReadKeys.h"
#include "../CellChange/SetVariables.h"
#include "../CU/CU.h"
#include "../Computer/DisplayInterface.h"
#include "signals.h"

void reset_signal_handler(int sigcode) {
    alarm(0);
		sc_regInit();
		sc_regSet(REG_IMPULSE_IGNORE, 1);
    sc_memoryInit();
    instructionCounter=0;
		accum = 0;
    last_command = 0;
}

void signal_handler(int sigcode){
	CU();
	int reg_status = 0;
	if(sc_regGet(REG_MEMORY_OVERFLOW, &reg_status)==0 && reg_status==0){
		if(sc_regGet(REG_INVALID_COMMAND, &reg_status)==0 && reg_status==0){
  		if(sc_regGet(REG_OPERATION_OVERFLOW, &reg_status)==0 && reg_status==0){
    		if(sc_regGet(REG_DIVISION_ZERO, &reg_status)==0 && reg_status==0){
          instructionCounter++;
        }
      }
		}
	}
	enum keys key = KEY_r;
	int address = instructionCounter;
	print_interface(address, key);
	if(sc_regGet(REG_IMPULSE_IGNORE, &reg_status)==0 && reg_status==0){
		alarm(1);
	}
}

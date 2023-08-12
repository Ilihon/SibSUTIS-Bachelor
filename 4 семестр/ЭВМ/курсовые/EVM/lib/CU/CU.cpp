#include "../SimpleComputer/mySimpleComputer.h"
#include "../Terminal/myTerminal.h"
#include "../BigChars/myBigChars.h"
#include "../ReadKeys/myReadKeys.h"
#include "../CellChange/SetVariables.h"
#include "../SignalHandler/signals.h"
#include "../Computer/DisplayInterface.h"
#include "CU.h"

int last_command = 0;

void CU(){
  last_command = 0;
	int value;
	int command;
	int operand;
	sc_memoryGet(instructionCounter, &value);
	if(sc_commandDecode(value,&command, &operand) != 0){
		sc_regSet(REG_IMPULSE_IGNORE, 1);
		return;
	}
	if(operand < 0 | operand >=100){
		sc_regSet(REG_INVALID_COMMAND,1);
		sc_regSet(REG_IMPULSE_IGNORE, 1);
		return;
	}
	if(instructionCounter>=99){
		sc_regSet(REG_MEMORY_OVERFLOW, 1);
		sc_regSet(REG_IMPULSE_IGNORE, 1);
		instructionCounter = 0;
		return;
	}
  if((command>=0x30 && command <=0x33) || command == 0x54 || command == 0x67 || command == 0x68){
    if(ALU(command,operand) !=0){
		  sc_regSet(REG_IMPULSE_IGNORE, 1);
      return;
    }
  }
  value = 0;
  switch (command) {
    case 0x10:
      last_command = 10;
      set_mem(operand);
      break;
    case 0x11:
      last_command = 11;
      sc_memoryGet(operand, &value);
      mt_gotoXY(27,4);
      if (value < 0)
        printf("WRITE: -%04X\n", -value);
      else
        printf("WRITE: +%04X\n", value);
      break;
    case 0x20:
      last_command = 20;
      sc_memoryGet(operand, &value);
      accum = value;
      break;
    case 0x21:
      last_command = 21;
      sc_memorySet(operand, accum);
      break;
    case 0x40:
      last_command = 40;
      instructionCounter = operand-1;
      break;
    case 0x41:
      last_command = 41;
      if(accum < 0){
        instructionCounter = operand-1;
      }
      break;
    case 0x42:
      last_command = 42;
      if(accum == 0){
        instructionCounter = operand-1;
      }
      break;
    case 0x43:
      last_command = 43;
		  sc_regSet(REG_IMPULSE_IGNORE, 1);
      break;
    case 0x55:
      last_command = 55;
      if(accum > 0){
        instructionCounter = operand-1;
      }
      break;
  }
	return;
}

int ALU(int command, int operand){
  int value;
  sc_memoryGet(operand, &value);
  switch(command){
    case 0x30:
      last_command = 30;
      if((accum+value)>0x7FFF || (accum+value)<-0x7FFF){
  		  sc_regSet(REG_OPERATION_OVERFLOW, 1);
        return -1;
      }
      accum = accum + value;
      break;
    case 0x31:
      last_command = 31;
      if((accum-value)>0x7FFF || (accum-value)<-0x7FFF){
  		  sc_regSet(REG_OPERATION_OVERFLOW, 1);
        return -1;
      }
      accum = accum - value;
      break;
    case 0x32:
      last_command = 32;
      if(value == 0){
        sc_regSet(REG_DIVISION_ZERO, 1);
        return -1;
      }
      if((accum/value)>0x7FFF || (accum/value)<-0x7FFF){
  		  sc_regSet(REG_OPERATION_OVERFLOW, 1);
        return -1;
      }
      accum = accum / value;
      break;
    case 0x33:
      last_command = 33;
      if((accum*value)>0x7FFF || (accum*value)<-0x7FFF){
  		  sc_regSet(REG_OPERATION_OVERFLOW, 1);
        return -1;
      }
      accum = accum * value;
      break;
    case 0x54:
      last_command = 54;
      if((accum^value)>0x7FFF || (accum^value)<-0x7FFF){
  		  sc_regSet(REG_OPERATION_OVERFLOW, 1);
        return -1;
      }
      accum = accum ^ value;
      break;
      case 0x67:
        last_command = 67;
        if((value<<accum)>0x7FFF || (value<<accum)<-0x7FFF){
    		  sc_regSet(REG_OPERATION_OVERFLOW, 1);
          return -1;
        }
        accum = value<<accum;
        break;
    case 0x68:
      last_command = 68;
      if((value>>accum)>0x7FFF || (value>>accum)<-0x7FFF){
  		  sc_regSet(REG_OPERATION_OVERFLOW, 1);
        return -1;
      }
      accum = value>>accum;
      break;
  }
  return 0;
}

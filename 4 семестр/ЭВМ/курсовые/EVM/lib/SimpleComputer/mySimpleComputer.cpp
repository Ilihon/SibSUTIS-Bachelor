#include "mySimpleComputer.h"

using namespace std;

short int memory[SIZE];
short int instructionCounter =0;
short int accum =0;
uint8_t flags;
const int REG_SIZE = sizeof(flags) * 8;

int sc_memoryInit(){
	for(int i = 0; i < SIZE; i++){
		memory[i]=0;
	}
	return 0;
}

int sc_memoryPrint(){
	for(int i = 0; i < SIZE; i++){
		cout << " "<<memory[i];
	}
	return 0;
}

int sc_memorySet (int address, int value){
	if((address >= SIZE) || (address < 0)){
		sc_regSet(REG_MEMORY_OVERFLOW,1);
		return -1;
	}
	if((value > 0x7FFF)||(value < -0x7FFF)){
		return -1;
	}
	memory[address]=value;
	return 0;
}

int sc_memoryGet (int address, int * value){
	if((address >= SIZE) || (address < 0)){
		sc_regSet(REG_MEMORY_OVERFLOW,1);
		return -1;
	}
	*value=memory[address];
	return 0;
}

int sc_memorySave (char *filename){
	FILE *fp = fopen(filename, "wb");
	if(fp==NULL)
  {
  	perror("Error occured while opening file");
    return -1;
  }
  fwrite(memory, sizeof(int), sizeof(memory), fp);
	fclose(fp);
	return 0;
}

int sc_memoryLoad (char * filename){
	FILE *fp = fopen(filename, "rb");
	if(fp==NULL)
    {
        perror("Error occured while opening file");
        return -1;
    }
	fread(memory, sizeof(int), sizeof(memory), fp);
	fclose(fp);
	return 0;
}

int sc_regInit(){
	flags = 0;
	return 0;
}

int sc_regSet(int reg, int value){
	if(reg<0 || reg>REG_SIZE){
		return -1;
	}
	if(value!=0 && value!=1){
		return -1;
	}
	if(value==0){
		flags=flags&(~(1<<(reg-1)));
	}
	else{
		flags = flags | (1<<(reg-1));
	}
	return 0;
}

int sc_regGet(int reg, int *value){
	if(reg<0 || reg>REG_SIZE){
		return -1;
	}
	*value = (flags>>(reg-1)) & 1;
	return 0;
}

int sc_commandEncode(int command, int operand, int *value){
	if(command < 0x10 || (command > 0x11 && command <0x20) || (command > 0x21 && command < 0x30)
	|| (command > 0x33 && command < 0x40) || (command > 0x43 && command < 0x51) || command > 0x76){
		sc_regSet(REG_INVALID_COMMAND,1);
		return -1;
	}
	if(operand < 0 || operand > 127){
		sc_regSet(REG_INVALID_COMMAND,1);
		return -1;
	}
	*value = (command <<8) | operand;
	return 0;
}

int sc_commandDecode(int value, int *command, int *operand){
	if ((value >> 15) != 0) {
		sc_regSet(REG_INVALID_COMMAND,1);
		return -1;
	}
	int buffer=value >> 8;
	if((buffer < 0x10 || buffer > 0x11) && (buffer <0x20 || buffer > 0x21) && (buffer < 0x30 || buffer > 0x33) && (buffer < 0x40 || buffer > 0x43) && (buffer < 0x51 || buffer > 0x76)){
		sc_regSet(REG_INVALID_COMMAND,1);
		return -1;
	}
	*command = buffer;
	*operand = value & 0x7F;
	return 0;
}

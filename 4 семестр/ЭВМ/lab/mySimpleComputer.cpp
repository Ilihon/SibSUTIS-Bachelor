#include "mySimpleComputer.h"

using namespace std;


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
		cout<< "Going beyond memory limits" << endl;
		sc_regSet(REG_MEMORY_OVERFLOW,1);
		return 2;
	}
	memory[address]=value;
	return 0;
}

int sc_memoryGet (int address, int * value){
	if((address >= SIZE) || (address < 0)){
		cout<< "Going beyond memory limits" << endl;
		sc_regSet(REG_MEMORY_OVERFLOW,1);
		return 0;
	}
	*value=memory[address];
	return 0;
}

int sc_memorySave (char * filename){
	FILE *fp = fopen(filename, "wb");
	if(fp==NULL)
    {
        perror("Error occured while opening file");
        return 2;
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
        return 2;
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
		cout <<endl<< "Invalid register"<<endl;
		return 2;
	}
	if(value!=0 && value!=1){
		cout <<endl<< "Invalid value"<<endl;
		return 2;
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
		cout <<endl<< "Invalid register"<<endl;
		return 2;
	}
	*value = (flags>>(reg-1)) & 1;
	return 0;
}

int sc_commandEncode(int command, int operand, int *value){
	if(command < 0x10 || command > 0x11 && command <0x20 || command > 0x21 && command < 0x30 || command > 0x33 && command < 0x40 || command > 0x44 && command < 0x51 || command > 0x76){
		cout << endl <<"Invalid command"<<endl;
		return 2;
	}
	if(operand < 0 || operand > 127){
		cout << endl <<"Invalid operand"<<endl;
		return 2;
	}
	*value = (command << 0x7) | operand;
	return 0;
}

int sc_commandDecode(int value, int *command, int *operand){
	if ((value >> 14) != 0) {
		sc_regSet(REG_INVALID_COMMAND,1);
		return 2;
	}
	int buffer=value >> 7;
	if(buffer < 0x10 || buffer > 0x11 && buffer <0x20 || buffer > 0x21 && buffer < 0x30 || buffer > 0x33 && buffer < 0x40 || buffer > 0x44 && buffer < 0x51 || buffer > 0x76){
		cout << endl <<"Invalid command"<<endl;
		sc_regSet(REG_INVALID_COMMAND,1);
		return 2;
	}
	*command = buffer;
	*operand = value & 0x7F;
	return 0;
}

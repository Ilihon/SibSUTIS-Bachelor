 #include "../SimpleComputer/mySimpleComputer.h"
#include "../Terminal/myTerminal.h"
#include "../BigChars/myBigChars.h"
#include "../ReadKeys/myReadKeys.h"
#include "SetVariables.h"

void set_mem(int address){
	mt_gotoXY(27,5);
	printf("Set %02X memmory cell to: ",address);
	char buf[256];
	fgets(buf,256,stdin);
	int pos =0;
	int otriz = 0;
	if(buf[0] == '-'){
		pos = 1;
		otriz = 1;
	}
	if(buf[0] == '+'){
		pos = 1;
	}
	short	int result;
	mt_gotoXY(29,5);
	if(sscanf(buf+pos,"%X",&result)!=1){
		return;
	}
	if(otriz){
		sc_memorySet(address,(-result));
	}
	else{
			sc_memorySet(address,result);
	}
	return;
}

void set_accum(){
	mt_gotoXY(27,5);
	cout <<"Set accumulator to: ";
	char buf[256];
	fgets(buf,256,stdin);
	int pos =0;
	int otriz = 0;
	if(buf[0] == '-'){
		pos = 1;
		otriz = 1;
	}
	if(buf[0] == '+'){
		pos = 1;
	}
	int result;
	mt_gotoXY(29,5);
	if(sscanf(buf+pos,"%X",&result)!=1){
		return;
	}
	if(otriz){
		result = -result;
	}
	if((result > 0x7FFF)||(result < -0x8000)){
		return;
	}
	accum = result;
	return;
}

void set_instructionCounter(){
	mt_gotoXY(27,5);
	cout <<"Set Instruction Counter to: ";
	char buf[256];
	fgets(buf,256,stdin);
	int pos =0;
	if(buf[0] == '+'){
		pos = 1;
	}
	int result;
	mt_gotoXY(29,5);
	if(sscanf(buf+pos,"%d",&result)!=1){
		return;
	}
	if(result>=0 && result <100){
		instructionCounter = result;
	}
}

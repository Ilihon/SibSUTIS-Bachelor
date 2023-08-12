#include "../SimpleComputer/mySimpleComputer.h"
#include "../Terminal/myTerminal.h"
#include "../BigChars/myBigChars.h"
#include "../ReadKeys/myReadKeys.h"
#include "../CellChange/SetVariables.h"
#include "../CU/CU.h"
#include "../SignalHandler/signals.h"
#include "DisplayInterface.h"


int interface(){
	int impulse_status = 0;
	char buf[128];
  enum keys key = KEY_nothing;
	cout<<endl;
	signal(SIGUSR1, reset_signal_handler);
	signal(SIGALRM, signal_handler);
	int x=instructionCounter % 10;
	int y=instructionCounter / 10;
	int address=y*10 + x;
	mt_clrscr();
	while(key != KEY_q)	{
		print_interface(address, key);
		cout<<endl;
    stdin = freopen(nullptr, "r", stdin);
  	rk_readkey(&key);
		printf("\033(B");
		if(sc_regGet(REG_IMPULSE_IGNORE, &impulse_status)==0 && impulse_status==1){
			switch(key){
				case KEY_enter:
					set_mem(address);
					break;
				case KEY_l:
					mt_gotoXY(27,5);
			    printf("Input filename: ");
			    scanf("%s", buf);
					if(strcmp(buf,"abort")==0)
						break;
					sc_memoryLoad(buf);
					sc_regSet(REG_IMPULSE_IGNORE, 1);
					x = instructionCounter % 10;
					y = instructionCounter / 10;
					last_command = 0;
					break;
				case KEY_s:
					mt_gotoXY(27,5);
			    printf("Input filename: ");
			    scanf("%s", buf);
					if(strcmp(buf,"abort")==0)
						break;
					sc_memorySave(buf);
					break;
				case KEY_f5:
					set_accum();
					break;
				case KEY_f6:
					set_instructionCounter();
					x = instructionCounter % 10;
					y = instructionCounter / 10;
					break;
				case KEY_up:
					y--;
					if(y==-1)
						y = 9;
					break;
				case KEY_down:
					y++;
					if(y==10)
						y = 0;
					break;
				case KEY_left:
					x--;
					if(x==-1)
						x = 9;
					break;
				case KEY_right:
					x++;
					if(x==10)
						x = 0;
					break;
				case KEY_t:
					sc_regInit();
					sc_regSet(REG_IMPULSE_IGNORE, 1);
        	signal_handler(SIGALRM);
					x = instructionCounter % 10;
					y = instructionCounter / 10;
					break;
			}
		}
		switch (key) {
			case KEY_q:
				mt_gotoXY(27,5);
				printf("Poweroff SimpleComputer...\n");
				break;
			case KEY_esc:
				raise(SIGTERM);
				break;
			case KEY_i:
        raise(SIGUSR1);
				x = instructionCounter % 10;
				y = instructionCounter / 10;
				break;
			case KEY_r:
				int value;
				if(sc_regGet(REG_IMPULSE_IGNORE, &value)==0 && value == 1){
					sc_regInit();
					signal_handler(SIGALRM);
				}
				else {
					sc_regSet(REG_IMPULSE_IGNORE,1);
          alarm(0);
				}
				x = instructionCounter % 10;
				y = instructionCounter / 10;
				break;
		}
		address = x+(y*10);
	}
	mt_gotoXY(32,0);
	return 0;
}

void print_interface(int address, enum keys key){
	mt_clrscr();
	print_term_boxes();
	print_mem(address);
	PrintBigChars(instructionCounter);
	print_accum();
	print_instruction_Counter(instructionCounter);
	print_operation(instructionCounter);
	print_reg();
	mt_gotoXY(16,70);
	print_key(key);
	mt_gotoXY(29,5);
	print_last_command();
	mt_gotoXY(32,0);
	cout<<endl;
	return;
}

void print_last_command(){
	int value;
	int command;
	int operand;

  switch (last_command) {
		case 10:
			printf("READ\n");
			break;
  	case 11:
			sc_memoryGet(instructionCounter-1, &value);
			if(sc_commandDecode(value,&command, &operand) == 0){
				sc_memoryGet(operand, &value);
      	if (value < 0)
      		printf("WRITE: -%04X\n", -value);
        else
        	printf("WRITE: +%04X\n", value);
			}
			break;
		case 20:
			if (accum < 0)
				printf("LOAD: -%04X\n", -accum);
			 else
				printf("LOAD: +%04X\n", accum);
			break;
		case 21:
			sc_memoryGet(instructionCounter-1, &value);
			if(sc_commandDecode(value,&command, &operand) == 0){
	     	if (accum < 0)
	     		printf("STORE: -%04X to %02X memmory cell\n", -accum, operand);
	       else
	       	printf("STORE: +%04X to %02X memmory cell\n", accum, operand);
			}
			break;
		case 30:
			printf("ADD\n");
			break;
		case 31:
			printf("SUB\n");
			break;
		case 32:
			printf("DIVIDE\n");
			break;
		case 33:
			printf("MUL\n");
			break;
		case 40:
			printf("JUMP to %02X instructionCounter\n", instructionCounter);
			break;
		case 41:
			printf("JNEG\n");
			break;
		case 42:
			printf("JZ\n");
			break;
		case 43:
			printf("HALT\n");
			break;
		case 54:
			printf("XOR\n");
			break;
		case 55:
			printf("JNS\n");
			break;
		case 67:
			printf("LOGLC\n");
			break;
		case 68:
			printf("LOGRC\n");
			break;
  }
	return;
}

void print_accum(){
	mt_gotoXY(4,71);
	if(accum<0){
		printf("-");
		printf("%04X",~accum+1);
	}else{
		printf("+");
		printf("%04X",accum);
	}
	return;
}

void print_instruction_Counter(int address){
	mt_gotoXY(7,71);
	if(address<0 || address>99){
		sc_regSet(REG_MEMORY_OVERFLOW,1);
		return;
	}
	printf("+%04X",address);
	return;
}

void print_operation(int address){
	int value=0;
	int result[4];
	sc_memoryGet(address,&value);
	mt_gotoXY(10,70);
	if(value<0){
		printf("-");
		value = -value;
	}else{
		printf("+");
	}
	memory_convert(value, result);
	printf("%X%X : %X%X",result[0],result[1],result[2],result[3]);
	return;
}

void print_reg(){
	mt_gotoXY(13,71);
	int value=0;
	for(int i=1;i<6;i++){
		sc_regGet(i,&value);
		if(value==1){
			switch (i) {
				case REG_OPERATION_OVERFLOW:
					printf("P ");
					break;
			 	case REG_DIVISION_ZERO:
					printf("0 ");
					break;
				case REG_MEMORY_OVERFLOW:
					printf("M ");
					break;
				case REG_IMPULSE_IGNORE:
					printf("I ");
					break;
				case REG_INVALID_COMMAND:
					printf("E ");
					break;
			}
		}
		else{
			printf("  ");
		}
	}
	return;
}

void print_mem(int address){
	int value=0;
  for (int i=0;i<10;i++){
		mt_gotoXY(i+4,4);
		for(int j=0;j<10;j++){
			if(i*10 + j == address){
				mt_setbgcolor(GREEN);
			}
			if(i*10 + j == instructionCounter){
				mt_setfgcolor(RED);
			}
			sc_memoryGet (i*10 + j, &value);
			if(value<0){
				printf("-");
				value = -value;
			}else{
				printf("+");
			}
			printf("%04X",value);
			mt_setbgcolor(DEFAULT);
			mt_setfgcolor(DEFAULT);
			if(j!=9)
				printf(" ");
		}
	}
	return;
}

void print_term_boxes(){
	bc_box(3,3,10,59);
	mt_gotoXY(3,28);
	cout <<" Memory ";
	bc_box(3,64,1,20);
	mt_gotoXY(3,68);
	cout <<" accumulator ";
	bc_box(6,64,1,20);
	mt_gotoXY(6,65);
	cout <<" instructionCounter ";
	bc_box(9,64,1,20);
	mt_gotoXY(9,69);
	cout <<" Operation ";
	bc_box(12,64,1,20);
	mt_gotoXY(12,71);
	cout <<" Flags ";
	bc_box(15,3,8,40);
	bc_box(15,45,8,39);
	bc_box(15,62,1,22);
	mt_gotoXY(15,62);
	bc_printA("w");
	mt_gotoXY(17,85);
	bc_printA("u");
	mt_gotoXY(15,46);
	cout << " Keys ";
	mt_gotoXY(15,67);
	cout << " Pressed key ";
	mt_gotoXY(16,46);
	cout <<"l - load";
	mt_gotoXY(17,46);
	cout <<"s - save";
	mt_gotoXY(18,46);
	cout <<"r - run";
	mt_gotoXY(19,46);
	cout <<"t - step";
	mt_gotoXY(20,46);
	cout <<"i - reset";
	mt_gotoXY(21,46);
	cout <<"f5 - accumulator";
	mt_gotoXY(22,46);
	cout <<"f6 - instructionCounter";
	bc_box(25,3,5,81);
	mt_gotoXY(25,8);
	cout <<" Console ";
  return;
}

void PrintBigChars(int address){
	int result[4];
	int value=0;
	int otriz =0;
	sc_memoryGet (address, &value);
	if(value<0){
		value = -value;
		otriz =1;
	}
	memory_convert(value, result);
	int big[2];
	if(otriz == 1){
		ToBigChar(17,big);
	}else{
		ToBigChar(16,big);
	}
	int x=16,y=12;
	bc_printbigchar(big,x,y-8,DEFAULT,DEFAULT);
	for(int i =0;i<4;i++){
		ToBigChar(result[i],big);
		bc_printbigchar(big,x,y+8*i,DEFAULT,DEFAULT);
	}
	return;
}


void memory_convert(int mem, int *conv){
	int n=3;
	for(int i=n;i>=0;i--){
		conv[i]=mem % 16;
		mem = mem / 16;
	}
}

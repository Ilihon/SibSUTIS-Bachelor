#include "mySimpleComputer.h"
#include "SimpleComputerTest.h"

using namespace std;

char *filename = "MemmoryTest.txt";

void testMemory() {
	cout << endl << "======== START SIMPLE COMPUTER MEMORY TEST ========"<<endl;
	
	cout << "Setting 4 on 5th position"<<endl;
	sc_memorySet(5,4);
	cout << "Saving memory"<<endl;
 	sc_memorySave(filename);
	
	int n = 0;
	cout << "Setting 2 on 5th position"<<endl;
	sc_memorySet(5,2);
	cout << "Getting 3th position"<<endl;
	sc_memoryGet(3, &n);
	cout << "Expected: 0"<<endl;
	cout << "Result: "<< n << endl;
	cout << "Getting 5th position"<<endl;
	sc_memoryGet(5, &n);
	cout << "Expected: 2"<<endl;
	cout << "Result: "<< n << endl;

	cout << "Loading memory"<<endl;
	sc_memoryLoad(filename);
	
	
	cout << "Getting 5th position"<<endl;
	sc_memoryGet(5, &n);
	cout << "Expected: 4"<<endl;
	cout << "Result: "<< n << endl;
	
	cout << "======== END SIMPLE COMPUTER MEMORY TEST ========"<<endl;
	return;
}


void testRegister(){
	cout << endl << "======== START SIMPLE COMPUTER REGISTER TEST ========"<<endl;
	
	cout<< "Setting register flags 2 and 4 on"<<endl;
	sc_regSet(REG_DIVISION_ZERO,1);
	sc_regSet(REG_IMPULSE_IGNORE,1);
	cout << "Register flags: ";
	int value=0;
	for(int i=1;i<6;i++){
		sc_regGet(i,&value);
		cout << value << " ";
	}
	cout << endl << endl << "======== END SIMPLE COMPUTER REGISTER TEST ========"<<endl;
}

void testCommandCoding() {
	cout << endl << "======== START SIMPLE COMPUTER COMMAND CODING TEST ========"<<endl;
	
 	int value = 0;
    	int command = 0;
    	int operand = 0;
	
	cout << "Coding 11 command and 28 operand"<<endl;
    	sc_commandEncode(0x11, 0x28, &value);	
	cout << "Encoding value"<<endl;
    	sc_commandDecode(value, &command, &operand);
	

    cout << "Expected command: " << 11 << endl;
    printf("Result: %X\n", command);

    cout << "Expected operand: " << 28  << endl;
    printf("Result: %X\n", operand);
	
	cout << "======== END SIMPLE COMPUTER COMMAND CODING TEST ========"<<endl;
}
	
	
	
	
	
	

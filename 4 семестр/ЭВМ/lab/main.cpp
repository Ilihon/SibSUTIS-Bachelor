#include "mySimpleComputer.h"
#include "SimpleComputerTest.h"
#include "myTerminal.h"
#include "TerminalTest.h"

int main()
{
 	sc_memoryInit();
	sc_regInit();
	testMemory();
	testRegister();
	testCommandCoding();
	testTerminal();
    return 0;
}

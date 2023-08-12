#include "../../lib/SimpleComputer/mySimpleComputer.h"
//#include "SimpleComputerTest.h"
#include "../../lib/Terminal/myTerminal.h"
//#include "../lab3/TerminalTest.h"
#include "../../lib/BigChars/myBigChars.h"
#include "../../lib/ReadKeys/myReadKeys.h"
#include "../../lib/CellChange/SetVariables.h"
#include "../../lib/CU/CU.h"
#include "../../lib/SignalHandler/signals.h"
#include "../../lib/Computer/DisplayInterface.h"

int main()
{
 	sc_memoryInit();
	sc_regInit();
	//testMemory();
	//testRegister();
  //testCommandCoding();
	//testTerminal();
	/*mt_clrscr();
	bc_box(5,5,8,16);
	int big[2] = {bc_symbols[10][0], bc_symbols[10][1]};
	bc_printbigchar(big,6,6,DEFAULT,DEFAULT);
	bc_setbigcharpos(big,3,1,1);
	bc_setbigcharpos(big,2,1,0);
	bc_printbigchar(big,6,6,DEFAULT,DEFAULT);
	*/
  sc_regSet(REG_IMPULSE_IGNORE,1);
  interface();
  return 0;
}

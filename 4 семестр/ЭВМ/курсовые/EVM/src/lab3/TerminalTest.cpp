#include "myTerminal.h"
#include "mySimpleComputer.h"
#include "TerminalTest.h"


void testTerminal()
{
	mt_clrscr();
	cout << "======== START TERMINAL TEST ========" << endl;
	//cout << "Screen was cleared" << endl;
	//cout << "Setting cursor on 5 row and 6 column position" << endl;
	mt_gotoXY(2,8);
	cout <<"Memory";

	/*
	int rows,cols;
	mt_getscreensize(&rows,&cols);
	cout << "Terminal resolution: " <<rows << " rows and " << cols << " coloumns"<<endl;
	cout << endl << "Setting red foreground color";
	mt_setfgcolor(RED);
	cout << endl << "Setting green background color";
	mt_setbgcolor(GREEN);
	cout <<endl<< "Test";
	mt_setbgcolor(DEFAULT);
	mt_setfgcolor(DEFAULT);
	*/
	for (int i=0;i<10;i++){
		mt_gotoXY(i+3,3);
		for(int j=0;j<10;j++){
			printf("%04X ",memory[(i*10)+j]);
		}
	}


	cout << endl<<"======== END TERMINAL TEST ========"<<endl;
	return;
}

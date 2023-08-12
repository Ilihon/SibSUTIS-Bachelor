#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

using namespace std;

#define FGCOLOR "\033[3%dm"
#define LIGHT_FGCOLOR "\033[9%dm"

#define BGCOLOR "\033[4%dm"
#define LIGHT_BGCOLOR "\033[10%dm"

enum Colors {
	DEFAULT = 9,
	BLACK = 0,
	YELLOW = 3,
	VIOLET = 5,
	AQUAMARINE = 6,
	WHITE = 7,
	GREEN = 2,
	RED = 1,
	BLUE = 4
};

int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize (int * rows, int * cols);
int mt_setfgcolor(enum Colors color);
int mt_setLIGHTfgcolor (enum Colors color);
int mt_setbgcolor(enum Colors color);
int mt_setLIGHTbgcolor (enum Colors color);


#endif

#include "myTerminal.h"

int mt_clrscr (void)
{
	printf("\033[H\033[2J");
	return 0;
}

int mt_gotoXY (int x, int y)
{
	if(x>=0 && y>=0){
		printf("\033[%d;%dH",x,y);
		return 0;
	}
	else
		return -1;
}

int mt_getscreensize (int * rows, int * cols)
{
	struct winsize ws;
	if (!ioctl(1, TIOCGWINSZ, &ws)){
		*rows = ws.ws_row;
		*cols = ws.ws_col;
		return 0;
	} 
	else {
		return -1;
	}
}

int mt_setfgcolor(enum Colors color)
{
	printf(FGCOLOR,color);
	return 0;
}

int mt_setLIGHTfgcolor (enum Colors color)
{
	if(color==DEFAULT){
		printf(FGCOLOR,color);
		return 0;
	}
	printf(LIGHT_FGCOLOR,color);
	return 0;	
}

int mt_setbgcolor(enum Colors color)
{
	printf(BGCOLOR,color);
	return 0;
	
}

int mt_setLIGHTbgcolor (enum Colors color)
{
	if(color==DEFAULT){
		printf(BGCOLOR,color);
		return 0;
	}
	printf(LIGHT_BGCOLOR,color);
	return 0;	
}

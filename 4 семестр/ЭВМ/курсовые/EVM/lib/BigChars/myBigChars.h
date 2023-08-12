#ifndef _BIGCHARS_H_
#define _BIGCHARS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


using namespace std;

const int bc_symbols[18][2] = {{0x2424243C, 0x3C242424},	// 0
					  {0x18181818, 0x18181818}, // 1
					  {0x2020203C, 0x3C04043C}, // 2
					  {0x2020203C, 0x03C20203C}, // 3
					  {0x3C242424, 0x20202020}, // 4
					  {0x404043C, 0x03C20203C}, // 5
					  {0x404043C, 0x3C24243C}, // 6
					  {0x2020203C, 0x20202020}, // 7
				   	{0x3C24243C, 0x3C242424}, // 8
					  {0x3C24243C, 0x3C202020}, // 9
			 		  {0x24242418, 0x2424243C}, // A
					  {0x1C24241C, 0x1C24241C}, // B
					  {0x404043C, 0x3C040404}, // C
					  {0x2424241C, 0x1C242424}, // D
					  {0x3C04043C, 0x3C040404}, // E
					  {0x404043C, 0x404043C}, // F
					  {0x7E181800, 0x18187E}, // +
						{0x7E000000, 0x7E}};  // -

int bc_printA(char *str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int *symbol, int x, int y, enum Colors fg, enum Colors bg);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int *big,int count);
int bc_bigcharread(int fd, int *big, int need_count, int *count);
int ToBigChar(int num,int *big);

#endif

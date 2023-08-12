#include "../Terminal/myTerminal.h"
#include "myBigChars.h"
using namespace std;


int bc_printA(char *str){
    // "\E(0"
    // "\E(B"
    printf("\033(0%s\033(B",str);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2){
    if(x1<0 || y1<0 || x2<0 || y2<0){
        cout << "Invalid cols and rows";
        return 2;
    }
    mt_gotoXY(x1,y1);
    bc_printA("l");
    for(int i=y1;i<y1+y2;i++){
        bc_printA("q");
    }
    bc_printA("k");
    for(int i=x1;i<x1+x2;i++){
        mt_gotoXY(i+1,y1);
        bc_printA("x");
        mt_gotoXY(i+1,y1+y2+1);
        bc_printA("x");

    }
    mt_gotoXY(x1+x2+1,y1);
    bc_printA("m");
    for(int i=y1;i<y1+y2;i++){
        bc_printA("q");
    }
    bc_printA("j");
    return 0;
}

int bc_printbigchar(int *big, int x, int y, enum Colors fg, enum Colors bg){
	if ((x < 0) || (y < 0))
		return -1;
	mt_gotoXY(x, y);
	mt_setfgcolor(fg);
	mt_setbgcolor(bg);
	int position = 0;
	char row[8];
	row[8] = '\0';
	for (int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			int bit = (big[position] >> ((i % 4) * 8 + j)) & 1;
			if(bit == 0)
				row[j] = ' ';
			else
				row[j] = 'a';
		}
		mt_gotoXY(x+i, y);
		bc_printA(row);
		if(i==3){
			position = 1;
		}
	}
	mt_setbgcolor(DEFAULT);
	mt_setfgcolor(DEFAULT);
	return 0;
}

int bc_setbigcharpos (int *big, int x, int y, int value){
	if (x < 0 || x > 7 || y < 0 || y > 7 || value < 0 || value > 1)
        return -1;
	int position;
	if (y > 3)
		position = 1;
	else
		position = 0;
	y = y % 4;
	if (value == 0)
		big[position] &= ~(1 << (y*8 + x));
	else
		big[position] |= 1 << (y*8 + x);

	return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value){
	int position;
	if (x < 0 || x > 7 || y < 0 || y > 7)
        return -1;
	if (y > 3)
		position = 1;
	else
		position = 0;
	y = y % 4;
	*value = (big[position] >> (y*8 + x)) & 1;

	return 0;
}

int bc_bigcharwrite(int fd, int *big, int count){
	if (write(fd, big, count * (sizeof(int)) * 2) == -1)
		return -1;
	return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count){
	*count = read(fd, big, need_count * sizeof(int) * 2);
	if (*count == -1){
		*count = 0;
		return -1;
	}
	*count = *count / (sizeof(int) * 2);
	return 0;
}

int ToBigChar(int num,int *big){
	big[0]=bc_symbols[num][0];
	big[1]=bc_symbols[num][1];
  return 0;
}

#include <iostream> 
#include <math.h>
#include <graphics.h> 
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
using namespace std; 

//стартовые координаты для отрисовки поля
#define XSTARTCORD 60
#define YSTARTCORD 20
#define XINTERFACE 420
#define YINTERFACE 20

#define XTETROMINOSTARTCORD 20
#define YTETROMINOSTARTCORD 60


//количество колонок и строк в поле
#define ROWS 20
#define COLS 15

//сторона кубика
#define BLOCKSIZE 20

//Цвета
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED	4
#define PURPLE	5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTPURPLE 13
#define YELLOW 14
#define WHITE 15

//клавиши
#define ESC 27
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ENTER 13



void field_init();
int tetromino_blocks_init();
void generate_tetromino(int tetromino[][4], int *color);

void draw_field();
void draw_interface();
void enter_screen();
void draw_tetromino(int X_current, int Y_current, int Color);
void draw_tetromino_block(int X, int Y, int Color);

void Refresh_field();
void DeleteLines();

int move_tetromino(int direction);
int border_bump(int direction);
int tetromino_bump(int direction);

int pin_tetromino();
void take_new_tetromino();


//Виды тетромино
const int I_tetromino[4][4] = {
		 0,1,0,0,
		 0,1,0,0,
		 0,1,0,0,
		 0,1,0,0
	};
const int I_tetromino_turned[4][4] = {
		 0,0,0,0,
		 1,1,1,1,
		 0,0,0,0,
		 0,0,0,0
	};

const int O_tetromino[4][4] = {
		 1,1,0,0,
		 1,1,0,0,
		 0,0,0,0,
		 0,0,0,0
	};


const int T_tetromino[4][4] = {
		 0,1,0,0,
		 0,1,1,0,
		 0,1,0,0,
		 0,0,0,0
	};
const int T_tetromino_turned1[4][4] = {
		 0,1,0,0,
		 1,1,1,0,
		 0,0,0,0,
		 0,0,0,0
	};
const int T_tetromino_turned2[4][4] = {
		 0,1,0,0,
		 1,1,0,0,
		 0,1,0,0,
		 0,0,0,0
	};
const int T_tetromino_turned3[4][4] = {
		 0,0,0,0,
		 1,1,1,0,
		 0,1,0,0,
		 0,0,0,0
	};
	

const int L_tetromino[4][4] = {
		 0,1,0,0,
		 0,1,0,0,
		 0,1,1,0,
		 0,0,0,0
	};
const int L_tetromino_turned1[4][4] = {
		 0,0,1,0,
		 1,1,1,0,
		 0,0,0,0,
		 0,0,0,0
	};
const int L_tetromino_turned2[4][4] = {
		 1,1,0,0,
		 0,1,0,0,
		 0,1,0,0,
		 0,0,0,0
	};
const int L_tetromino_turned3[4][4] = {
		 0,0,0,0,
		 1,1,1,0,
		 1,0,0,0,
		 0,0,0,0
	};
	
	
const int L2_tetromino[4][4] = {
		 0,1,0,0,
		 0,1,0,0,
		 1,1,0,0,
		 0,0,0,0
	};
const int L2_tetromino_turned1[4][4] = {
		 0,0,0,0,
		 1,1,1,0,
		 0,0,1,0,
		 0,0,0,0
	};
const int L2_tetromino_turned2[4][4] = {
		 0,1,1,0,
		 0,1,0,0,
		 0,1,0,0,
		 0,0,0,0
	};
const int L2_tetromino_turned3[4][4] = {
		 1,0,0,0,
		 1,1,1,0,
		 0,0,0,0,
		 0,0,0,0
	};
	
	
const int Z_tetromino[4][4] = {
		 0,0,0,0,
		 0,1,1,0,
		 1,1,0,0,
		 0,0,0,0
	};	
const int Z_tetromino_turned[4][4] = {
		 1,0,0,0,
		 1,1,0,0,
		 0,1,0,0,
		 0,0,0,0
	};
	
	
const int Z2_tetromino[4][4] = {
		 0,0,0,0,
		 1,1,0,0,
		 0,1,1,0,
		 0,0,0,0
	};	
const int Z2_tetromino_turned[4][4] = {
		 0,1,0,0,
		 1,1,0,0,
		 1,0,0,0,
		 0,0,0,0
	};
	
//переменные, в которые запоминаются рисунок кубиков, void far - тип bitbap (для картинок)
void far *BlackBlockBuf;
void far *GreenBlockBuf;
void far *CyanBlockBuf;
void far *RedBlockBuf;
void far *PurpleBlockBuf;
void far *YellowBlockBuf;	

int tetris_field[ROWS][COLS];

int current_tetromino[4][4];
int current_tetromino_index = -1;
int current_color_index = BLACK;

int next_tetromino[4][4];
int next_tetromino_index = -1;
int next_color_index = BLACK;

int turn_index = 0;

int move_time_limit = 80;
int move_time_passed = 0;

//стартовые координаты тетромино
const int X_tetromino_start = 0;
const int Y_tetromino_start = 6;
 
int current_tetromino_X = X_tetromino_start;
int current_tetromino_Y = Y_tetromino_start;

int temp_tetromino[4][4];
int temp_turn_index = 0;

int score = 0;

void draw_field(){
	cleardevice(); // очистка окна
	setcolor(BLUE);
	moveto(XSTARTCORD-3, YSTARTCORD-3);
	lineto(XSTARTCORD+301,YSTARTCORD-3);
	lineto(XSTARTCORD+301,YSTARTCORD+401);
	lineto(XSTARTCORD-3,YSTARTCORD+401);
	lineto(XSTARTCORD-3,YSTARTCORD-3);
 	return;
}

void draw_interface(){
	setcolor(BROWN);
	moveto(XINTERFACE, YINTERFACE);
	lineto(XINTERFACE+200,YINTERFACE);
	lineto(XINTERFACE+200,YINTERFACE+230);
	lineto(XINTERFACE,YINTERFACE+230);
	lineto(XINTERFACE,YINTERFACE);
	
	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(XINTERFACE+60,YINTERFACE+10, "Управление:");
	outtextxy(XINTERFACE+15,YINTERFACE+45, "           ^");
	outtextxy(XINTERFACE+15,YINTERFACE+50, "Повернуть: |");
	outtextxy(XINTERFACE+15,YINTERFACE+80, "Влево:    <--");
	outtextxy(XINTERFACE+15,YINTERFACE+110, "Вправо:   -->");
	outtextxy(XINTERFACE+15,YINTERFACE+153, "           v");
	outtextxy(XINTERFACE+15,YINTERFACE+140, "Вниз:      |");
	outtextxy(XINTERFACE+15,YINTERFACE+180, "Пауза:   Enter");
	outtextxy(XINTERFACE+15,YINTERFACE+200, "Выйти:    ESC");
	
	setcolor(DARKGRAY);
	moveto(XINTERFACE, YINTERFACE+250);
	lineto(XINTERFACE+200,YINTERFACE+250);
	lineto(XINTERFACE+200,YINTERFACE+430);
	lineto(XINTERFACE,YINTERFACE+430);
	lineto(XINTERFACE,YINTERFACE+250);
	setcolor(WHITE);
	outtextxy(XINTERFACE+25,YINTERFACE+260, "Следующая фигура:");
	return;
}

void enter_screen(){
	moveto(XSTARTCORD+20, YSTARTCORD+150);
	setcolor(LIGHTRED);
	lineto(XSTARTCORD+280,YSTARTCORD+150);
	lineto(XSTARTCORD+280,YSTARTCORD+250);
	lineto(XSTARTCORD+20,YSTARTCORD+250);
	lineto(XSTARTCORD+20,YSTARTCORD+150);
	setcolor(WHITE);
	settextstyle(10,0,2);
	outtextxy(XSTARTCORD+110,YSTARTCORD+180, "Tetris");
	settextstyle(0,0,1);
	outtextxy(XSTARTCORD+30,YSTARTCORD+220, "Нажмите ENTER чтобы начать");
	char KEY;
	while(1){
		if(kbhit()){
			KEY = getch();
			if(KEY == ENTER){
				break;
			}
		}
	}
	setfillstyle ( 1, BLACK ); 
	bar(XSTARTCORD+20, YSTARTCORD+150, XSTARTCORD+290, YSTARTCORD+260);
	setcolor(WHITE);
	outtextxy(XSTARTCORD+15,YSTARTCORD+430, "Нажмите ENTER чтобы остановить");
	outtextxy(XSTARTCORD,YSTARTCORD+470, "Cчёт: 0");
	return;
}

void field_init(){
	for (int i =0;i<ROWS;i++){
		for (int j=0; j<COLS;j++){
			tetris_field[i][j]=0;
		} 
	}
	return;
}

int tetromino_blocks_init(){
	unsigned int size;
	//рисуем заготовки кубиков для тетромино
	setfillstyle ( 1, BLACK ); 
	bar(10, 10, 10+BLOCKSIZE, 10+BLOCKSIZE);
	
	setfillstyle ( 1, GREEN ); 
	bar(40, 10, 40+BLOCKSIZE, 10+BLOCKSIZE);	
	setfillstyle ( 1, LIGHTGREEN ); 
	bar(45, 15, 35+BLOCKSIZE, 5+BLOCKSIZE);
	
	setfillstyle ( 1, CYAN ); 
	bar(70, 10, 70+BLOCKSIZE, 10+BLOCKSIZE);
	setfillstyle ( 1, LIGHTCYAN ); 
	bar(75, 15, 65+BLOCKSIZE, 5+BLOCKSIZE);
	
	setfillstyle ( 1, RED ); 
	bar(100, 10, 100+BLOCKSIZE, 10+BLOCKSIZE);
	setfillstyle ( 1, LIGHTRED ); 
	bar(105, 15, 95+BLOCKSIZE, 5+BLOCKSIZE);
	
	setfillstyle ( 1, PURPLE ); 
	bar(130, 10, 130+BLOCKSIZE, 10+BLOCKSIZE);
	setfillstyle ( 1, LIGHTPURPLE ); 
	bar(135, 15, 125+BLOCKSIZE, 5+BLOCKSIZE);
	
	setfillstyle ( 1, BROWN ); 
	bar(160, 10, 160+BLOCKSIZE, 10+BLOCKSIZE);
	setfillstyle ( 1, YELLOW ); 
	bar(165, 15, 155+BLOCKSIZE, 5+BLOCKSIZE);
	
	// выделение памяти для изображений кубиков 
	//сохраняем в буферы, если удачно память выделилась
	size= imagesize(10, 10, 10+BLOCKSIZE, 10+BLOCKSIZE);
	if (size != 0xffff) {
		BlackBlockBuf = malloc(size);
		if(BlackBlockBuf) {
			getimage(10, 10, 10+BLOCKSIZE, 10+BLOCKSIZE, BlackBlockBuf);
		}
		else
			return 0;
	}
	size= imagesize(40, 10, 40+BLOCKSIZE, 10+BLOCKSIZE);
	if (size != 0xffff) {
		GreenBlockBuf= malloc(size);
		if(GreenBlockBuf) {
			getimage(40, 10, 40+BLOCKSIZE, 10+BLOCKSIZE, GreenBlockBuf);
		}
		else
			return 0;
	}
	size= imagesize(70, 10, 70+BLOCKSIZE, 10+BLOCKSIZE);
	if (size != 0xffff) {
		CyanBlockBuf= malloc(size);
		if(CyanBlockBuf) {
			getimage(70, 10, 70+BLOCKSIZE, 10+BLOCKSIZE, CyanBlockBuf);
		}
		else
			return 0;
	}
	size= imagesize(100, 10, 100+BLOCKSIZE, 10+BLOCKSIZE);
	if (size != 0xffff) {
		RedBlockBuf= malloc(size);
		if(RedBlockBuf) {
			getimage(100, 10, 100+BLOCKSIZE, 10+BLOCKSIZE, RedBlockBuf);
		}
		else
			return 0;
	}
	size= imagesize(130, 10, 130+BLOCKSIZE, 10+BLOCKSIZE);
	if (size != 0xffff) {
		PurpleBlockBuf= malloc(size);
		if(PurpleBlockBuf) {
			getimage(130, 10, 130+BLOCKSIZE, 10+BLOCKSIZE, PurpleBlockBuf);
		}
		else
			return 0;
	}
	size= imagesize(160, 10, 160+BLOCKSIZE, 10+BLOCKSIZE);
	if (size != 0xffff) {
		YellowBlockBuf= malloc(size);
		if(YellowBlockBuf) {
			getimage(160, 10, 160+BLOCKSIZE, 10+BLOCKSIZE, YellowBlockBuf);
		}
		else
			return 0;
	}
	return 1;
}

//генерируем новое тетромино
void generate_tetromino(int tetromino[][4], int *color, int *tetromino_index){
	int r = rand() % 7;
	switch(r) {
		case 0 :
			for (int i =0;i<4;i++){
				for (int j=0; j<4;j++){
					tetromino[i][j] = I_tetromino[i][j];
				} 
			}
			*tetromino_index = 0;	
			break;
		case 1 :
			for (int i =0;i<4;i++){
				for (int j=0; j<4;j++){
					tetromino[i][j] = O_tetromino[i][j];
				} 
			}
			*tetromino_index = 1;	
			break;
		case 2 :
			for (int i =0;i<4;i++){
				for (int j=0; j<4;j++){
					tetromino[i][j] = T_tetromino[i][j];
				} 
			}
			*tetromino_index = 2;	
			break;
		case 3 :
			for (int i =0;i<4;i++){
				for (int j=0; j<4;j++){
					tetromino[i][j] = L_tetromino[i][j];
				} 
			}
			*tetromino_index = 3;	
			break;
		case 4 :
			for (int i =0;i<4;i++){
				for (int j=0; j<4;j++){
					tetromino[i][j] = L2_tetromino[i][j];
				} 
			}
			*tetromino_index = 4;	
			break;
		case 5 :
			for (int i =0;i<4;i++){
				for (int j=0; j<4;j++){
					tetromino[i][j] = Z_tetromino[i][j];
				} 
			}
			*tetromino_index = 5;	
			break;
		case 6 :
			for (int i =0;i<4;i++){
				for (int j=0; j<4;j++){
					tetromino[i][j] = Z2_tetromino[i][j];
				} 
			}
			*tetromino_index = 6;	
			break;
	}
	r = rand() % 5;
	switch(r){
		case 0 :
		   *color = GREEN;
		   break;
		case 1:
		   *color = CYAN;
		   break;
		case 2:
		   *color = RED;
		   break;
		case 3:
		   *color = PURPLE;
		   break;
		case 4:
		   *color = YELLOW;
		   break;
	}
	return;
}

//отрисовка текущего тетромино
void draw_tetromino(int X_current, int Y_current, int Color){
	for (int i =0;i<4;i++){
		for (int j=0; j<4;j++){
			if(current_tetromino[i][j]==1){
				draw_tetromino_block(X_current+i*BLOCKSIZE,Y_current+j*BLOCKSIZE,Color);
			}
		} 
	}
	return;
}

//отрисовка одного кубика
void draw_tetromino_block(int X, int Y, int Color){
	switch(Color){
		case BLACK:
			putimage(Y, X, BlackBlockBuf, COPY_PUT);
			break;
		case GREEN:
			putimage(Y, X, GreenBlockBuf, COPY_PUT);
			break;
		case CYAN:
			putimage(Y, X, CyanBlockBuf, COPY_PUT);
			break;
		case RED:
			putimage(Y, X, RedBlockBuf, COPY_PUT);
			break;
		case PURPLE:
			putimage(Y, X, PurpleBlockBuf, COPY_PUT);
			break;
		case YELLOW:
			putimage(Y, X, YellowBlockBuf, COPY_PUT);
			break;
		default:
			cout << "Неизвестный цвет"<<endl;
			break;			
	}	
	return;
}

//крутим тетромино
void turn_tetromino(){
	switch(current_tetromino_index){
		case 0:
			if(turn_index == 0){
				for (int i =0;i<4;i++){
					for (int j=0; j<4;j++){
						current_tetromino[i][j] = I_tetromino_turned[i][j];
					} 
				}
				turn_index = 1;
			}
			else{
				for (int i =0;i<4;i++){
					for (int j=0; j<4;j++){
						current_tetromino[i][j] = I_tetromino[i][j];
					} 
				}
				turn_index = 0;
			}
			break;
		case 1:
			break;
		case 2:
			if(turn_index == 0){
				for (int i =0;i<4;i++){
					for (int j=0; j<4;j++){
						current_tetromino[i][j] = T_tetromino_turned1[i][j];
					} 
				}
				turn_index = 1;
			}
			else{
				if(turn_index == 1){
					for (int i =0;i<4;i++){
						for (int j=0; j<4;j++){
							current_tetromino[i][j] = T_tetromino_turned2[i][j];
						} 
					}
					turn_index = 2;
				}
				else{
					if(turn_index == 2){
						for (int i =0;i<4;i++){
							for (int j=0; j<4;j++){
								current_tetromino[i][j] = T_tetromino_turned3[i][j];
							} 
						}
						turn_index = 3;
					}
					else{
						for (int i =0;i<4;i++){
							for (int j=0; j<4;j++){
								current_tetromino[i][j] = T_tetromino[i][j];
							} 
						}
						turn_index = 0;
					}
				}
			}
			break;
		case 3:
			if(turn_index == 0){
				for (int i =0;i<4;i++){
					for (int j=0; j<4;j++){
						current_tetromino[i][j] = L_tetromino_turned1[i][j];
					} 
				}
				turn_index = 1;
			}
			else{
				if(turn_index == 1){
					for (int i =0;i<4;i++){
						for (int j=0; j<4;j++){
							current_tetromino[i][j] = L_tetromino_turned2[i][j];
						} 
					}
					turn_index = 2;
				}
				else{
					if(turn_index == 2){
						for (int i =0;i<4;i++){
							for (int j=0; j<4;j++){
								current_tetromino[i][j] = L_tetromino_turned3[i][j];
							} 
						}
						turn_index = 3;
					}
					else{
						for (int i =0;i<4;i++){
							for (int j=0; j<4;j++){
								current_tetromino[i][j] = L_tetromino[i][j];
							} 
						}
						turn_index = 0;
					}
				}
			}
			break;
		case 4:
			if(turn_index == 0){
				for (int i =0;i<4;i++){
					for (int j=0; j<4;j++){
						current_tetromino[i][j] = L2_tetromino_turned1[i][j];
					} 
				}
				turn_index = 1;
			}
			else{
				if(turn_index == 1){
					for (int i =0;i<4;i++){
						for (int j=0; j<4;j++){
							current_tetromino[i][j] = L2_tetromino_turned2[i][j];
						} 
					}
					turn_index = 2;
				}
				else{
					if(turn_index == 2){
						for (int i =0;i<4;i++){
							for (int j=0; j<4;j++){
								current_tetromino[i][j] = L2_tetromino_turned3[i][j];
							} 
						}
						turn_index = 3;
					}
					else{
						for (int i =0;i<4;i++){
							for (int j=0; j<4;j++){
								current_tetromino[i][j] = L2_tetromino[i][j];
							} 
						}
						turn_index = 0;
					}
				}
			}
			break;
		case 5:
			if(turn_index == 0){
				for (int i =0;i<4;i++){
					for (int j=0; j<4;j++){
						current_tetromino[i][j] = Z_tetromino_turned[i][j];
					} 
				}
				turn_index = 1;
			}
			else{
				for (int i =0;i<4;i++){
					for (int j=0; j<4;j++){
						current_tetromino[i][j] = Z_tetromino[i][j];
					} 
				}
				turn_index = 0;
			}
			break;
		case 6:
			if(turn_index == 0){
				for (int i =0;i<4;i++){
					for (int j=0; j<4;j++){
						current_tetromino[i][j] = Z2_tetromino_turned[i][j];
					} 
				}
				turn_index = 1;
			}
			else{
				for (int i =0;i<4;i++){
					for (int j=0; j<4;j++){
						current_tetromino[i][j] = Z2_tetromino[i][j];
					} 
				}
				turn_index = 0;
			}
			break;
	}
	return;
}

//обновления рисунка поля и следующей фигуры
void Refresh_field(){
	for (int i=0;i<ROWS;i++){
		for (int j=0; j<COLS;j++){
			draw_tetromino_block(XTETROMINOSTARTCORD+i*BLOCKSIZE, YTETROMINOSTARTCORD+j*BLOCKSIZE, BLACK);
		} 
	}
	for (int i=0;i<ROWS;i++){
		for (int j=0; j<COLS;j++){
			if(tetris_field[i][j]!=0){
				draw_tetromino_block(XTETROMINOSTARTCORD+i*BLOCKSIZE, YTETROMINOSTARTCORD+j*BLOCKSIZE, tetris_field[i][j]);
			}
		} 
	}
	
	for (int i=0;i<4;i++){
		for (int j=0; j<4;j++){
			draw_tetromino_block(YINTERFACE+320+i*BLOCKSIZE, XINTERFACE+72+j*BLOCKSIZE, BLACK);
		} 
	}
	for (int i=0;i<4;i++){
		for (int j=0; j<4;j++){
			if(next_tetromino[i][j]!=0){
				draw_tetromino_block(YINTERFACE+320+i*BLOCKSIZE, XINTERFACE+72+j*BLOCKSIZE, next_color_index);
			}
		} 
	}
	return;
}

void DeleteLines(){
	int line_counter=0;
	for (int i=1;i<ROWS;i++){
		line_counter=0;
		for (int j=0; j<COLS;j++){
			if(tetris_field[i][j]!=0){
				line_counter++;
			}
		}
		if(line_counter==15){
			for(int v=i; v>0;v--){
				for (int j=0; j<COLS;j++){
					tetris_field[v][j]=tetris_field[v-1][j];
				}
				score+=150;
			}
		}
	}
}

//двигаем тетромино
int move_tetromino(int direction){
	switch(direction){
		case DOWN:
			if(border_bump(DOWN)==1){
				if(tetromino_bump(DOWN)==1){
					draw_tetromino(XTETROMINOSTARTCORD+current_tetromino_X*BLOCKSIZE,YTETROMINOSTARTCORD+current_tetromino_Y*BLOCKSIZE,BLACK);
					current_tetromino_X++;
					return 0;
				}
			}
			return 1;
		case UP:
			if(border_bump(UP)==1){
				if(tetromino_bump(UP)==1){
					draw_tetromino(XTETROMINOSTARTCORD+current_tetromino_X*BLOCKSIZE,YTETROMINOSTARTCORD+current_tetromino_Y*BLOCKSIZE,BLACK);
					turn_tetromino();
					draw_tetromino(XTETROMINOSTARTCORD+current_tetromino_X*BLOCKSIZE,YTETROMINOSTARTCORD+current_tetromino_Y*BLOCKSIZE, current_color_index);
				}
			}
			return 0;
		case LEFT:
			if(border_bump(LEFT)==1){
				if(tetromino_bump(LEFT)==1){
					draw_tetromino(XTETROMINOSTARTCORD+current_tetromino_X*BLOCKSIZE,YTETROMINOSTARTCORD+current_tetromino_Y*BLOCKSIZE,BLACK);
					current_tetromino_Y--;
					draw_tetromino(XTETROMINOSTARTCORD+current_tetromino_X*BLOCKSIZE,YTETROMINOSTARTCORD+current_tetromino_Y*BLOCKSIZE, current_color_index);
				}
			}
			return 0;
		case RIGHT:
			if(border_bump(RIGHT)==1) {
				if(tetromino_bump(RIGHT)==1){
					draw_tetromino(XTETROMINOSTARTCORD+current_tetromino_X*BLOCKSIZE,YTETROMINOSTARTCORD+current_tetromino_Y*BLOCKSIZE,BLACK);
					current_tetromino_Y++;
					draw_tetromino(XTETROMINOSTARTCORD+current_tetromino_X*BLOCKSIZE,YTETROMINOSTARTCORD+current_tetromino_Y*BLOCKSIZE, current_color_index);
				}
			}
			return 0;
	}
}

//проверяем сталкивается ли тетромино с границами
int border_bump(int direction){
	switch(direction){
		case DOWN:
			if((current_tetromino_X>=16) && (current_tetromino[3][1]==1)){
				cout << "Фигура упёрлась в край"<<endl;
				return 0;
			}
			if((current_tetromino_X>=17) && ((current_tetromino[2][0]==1) || (current_tetromino[2][1]==1) || (current_tetromino[2][2]==1))){
				cout << "Фигура упёрлась в край"<<endl;
				return 0;
			}
			if((current_tetromino_X>=18) && (current_tetromino[1][1]==1)){
					cout << "Фигура упёрлась в край"<<endl;
					return 0;
			}
			return 1;
		case UP:
			switch(current_tetromino_index){
				case 0:
					if((current_tetromino_X>=17) && (current_tetromino[1][0]==1)){
						cout << "Невохможно повернуться"<<endl;
						return 0;
					}
					if((current_tetromino_Y<0) && (current_tetromino[0][1]==1)){
						cout << "Невохможно повернуться"<<endl;
						return 0;
						
					}
					if((current_tetromino_Y>11) && (current_tetromino[0][1]==1)){
						cout << "Невохможно повернуться"<<endl;
						return 0;
					}
					return 1;
				case 1:
					return 1;
				case 2:
					if(current_tetromino_X>=16){
						cout << "Фигура упёрлась в край"<<endl;
						return 0;
					}
					if(current_tetromino_Y<0){
						cout << "Невохможно повернуться"<<endl;
						return 0;
					}
					if((current_tetromino_Y>12) && (turn_index>=2)){
						cout << "Фигура упёрлась в край"<<endl;
						return 0;
					}
					return 1;
				case 3:
					if(current_tetromino_X>=16){
						cout << "Фигура упёрлась в край"<<endl;
						return 0;
					}
					if((current_tetromino_Y<0) && (turn_index==0)){
						cout << "Фигура упёрлась в край"<<endl;
						return 0;
					}	
					if((current_tetromino_Y>12) && (turn_index>=2)){
						cout << "Фигура упёрлась в край"<<endl;
						return 0;
					}
					return 1;
				case 4:
					if(current_tetromino_X>=16){
						cout << "Фигура упёрлась в край"<<endl;
						return 0;
					}
					if((current_tetromino_Y<0)){
						cout << "Фигура упёрлась в край"<<endl;
						return 0;
					}	
					if((current_tetromino_Y>12)){
						cout << "Фигура упёрлась в край"<<endl;
						return 0;
					}
					return 1;
				case 5:
					if((current_tetromino_Y>12)){
						cout << "Фигура упёрлась в край"<<endl;
						return 0;
					}
					return 1;
				case 6:
					if((current_tetromino_Y>12)){
						cout << "Фигура упёрлась в край"<<endl;
						return 0;
					}
					return 1;
			}
			return 0;
		case LEFT:
			if((current_tetromino_Y==0) && ((current_tetromino[0][0]==1) || (current_tetromino[1][0]==1) || (current_tetromino[2][0]==1) || (current_tetromino[3][0]==1))){
				cout << "Фигура упёрлась в край"<<endl;
				return 0;
			}
			if(current_tetromino_Y ==-1){
				cout << "Фигура упёрлась в край"<<endl;
				return 0;
			}
			return 1;
			
		case RIGHT:
			if((current_tetromino_Y==11) && (current_tetromino[1][3]==1)) {
				cout << "Фигура упёрлась в край"<<endl;
				return 0;				
			}
			if((current_tetromino_Y==12) && ((current_tetromino[0][2]==1) || (current_tetromino[1][2]==1) || (current_tetromino[2][2]==1) || (current_tetromino[3][2]==1))) {
				cout << "Фигура упёрлась в край"<<endl;
				return 0;				
			}
			if((current_tetromino_Y==13) && ((current_tetromino[0][1]==1) || (current_tetromino[1][1]==1) || (current_tetromino[2][1]==1) || (current_tetromino[3][1]==1))) {
				cout << "Фигура упёрлась в край"<<endl;
				return 0;				
			}
			return 1;
	}
	return 0;
}
 
//проверяем сталкивается ли тетромино с другими тетромино
int tetromino_bump(int direction){
	int d = 1;
	switch(direction){
		case DOWN:
			for (int i = 0;i<4;i++){
				for(int j = 0;j<4;j++){
					if(current_tetromino[i][j]==1){
						if(tetris_field[current_tetromino_X+1+i][current_tetromino_Y+j]!=0){
							return 0;
						}
					}
				}
			}
			return 1;
		case UP:
			for (int i =0;i<4;i++){
				for (int j=0; j<4;j++){
					temp_tetromino[i][j] = current_tetromino[i][j];
				} 
			}
			temp_turn_index = turn_index;
			turn_tetromino();
			for (int i = 0;i<4;i++){
				for(int j = 0;j<4;j++){
					if(current_tetromino[i][j]==1){
						if(tetris_field[current_tetromino_X+i][current_tetromino_Y+j]!=0){
							d = 0;
							break;
						}
					}
				}
				if(!d)
					break;
			}
			for (int v =0;v<4;v++){
				for (int g=0; g<4;g++){
					current_tetromino[v][g] = temp_tetromino[v][g];
				} 
			}
			turn_index = temp_turn_index;	
			return d;
		case LEFT:
			for (int i = 0;i<4;i++){
				for(int j = 0;j<4;j++){
					if(current_tetromino[i][j]==1){
						if(tetris_field[current_tetromino_X+i][current_tetromino_Y-1+j]!=0){
							return 0;
						}
					}
				}
			}		
			return 1;
		case RIGHT:
			for (int i = 0;i<4;i++){
				for(int j = 0;j<4;j++){
					if(current_tetromino[i][j]==1){
						if(tetris_field[current_tetromino_X+i][current_tetromino_Y+1+j]!=0){
							return 0;
						}
					}
				}
			}
			return 1;
	}
	return 0;
}

//закрепляем тетромино на поле
int pin_tetromino(){
	score+=10;
	if((current_tetromino_X==X_tetromino_start) && (current_tetromino_Y==Y_tetromino_start)){
		return 1;
	}
	
	for (int i = 0;i<4;i++){
		for(int j = 0;j<4;j++){
			if(current_tetromino[i][j]==1){
				tetris_field[current_tetromino_X+i][current_tetromino_Y+j] = current_color_index;
			}
		}
	}
	DeleteLines();
	take_new_tetromino();
	return 0;
}

//как закрепили текущее тетромино ставим новое и генерим следующее
void take_new_tetromino(){
	for (int i =0;i<4;i++){
		for (int j=0; j<4;j++){
			current_tetromino[i][j] = next_tetromino[i][j];
		} 
	}
	current_tetromino_index = next_tetromino_index;
	current_color_index = next_color_index;
	generate_tetromino(next_tetromino, &next_color_index, &next_tetromino_index); 
	turn_index = 0;
	current_tetromino_X = X_tetromino_start;
	current_tetromino_Y = Y_tetromino_start;
	return;
}

int main(){ 
	setlocale(LC_ALL, "RUS"); 
	srand(time(0));
	initwindow(680,550,"Тетрис");//открытие окна
	if(tetromino_blocks_init() == 0){
		cout << "Не удалось выделить память под кубики" <<endl;
		return 0;	
	}
	draw_field();
	
	field_init();
	generate_tetromino(current_tetromino, &current_color_index, &current_tetromino_index);  
	generate_tetromino(next_tetromino, &next_color_index, &next_tetromino_index);  
	for (int i=0;i<4;i++){
		for (int j=0; j<4;j++){
			if(next_tetromino[i][j]!=0){
				draw_tetromino_block(YINTERFACE+320+i*BLOCKSIZE, XINTERFACE+72+j*BLOCKSIZE, next_color_index);
			}
		} 
	}
	draw_interface();
	enter_screen();	
	
	int i=0;
	char KEY;
	int end = 0;
	while(end==0){
		if(move_time_passed >= move_time_limit){
			score++;
			char a[100] = "Счёт: ";
			char b[90];
			sprintf(b, "%d", score);
			strcat(a,b);
			outtextxy(XSTARTCORD,YSTARTCORD+470, a);
			int next = move_tetromino(DOWN);
			if(next){
				if(pin_tetromino()==1){
					end = 1;
					break;
				}
				Refresh_field();
			}
			move_time_passed=0;
		}
		if(move_time_passed == 0){
			draw_tetromino(XTETROMINOSTARTCORD+current_tetromino_X*BLOCKSIZE,YTETROMINOSTARTCORD+current_tetromino_Y*BLOCKSIZE, current_color_index);
		}
		if(kbhit()) {
			KEY = getch();
			switch(KEY){
				case ESC:
					return 0;
				case ENTER:
					outtextxy(XSTARTCORD+120,YINTERFACE+410, "Пауза");
					outtextxy(XSTARTCORD+15,YINTERFACE+430, "Нажмите ENTER чтобы продолжить");
					while(1){
						if(kbhit()){
							KEY = getch();
							if(KEY == ENTER){
								outtextxy(XSTARTCORD+120,YSTARTCORD+410, "      ");
								outtextxy(XSTARTCORD+15,YSTARTCORD+430, "Нажмите ENTER чтобы остановить");
								break;
							}
							if(KEY == ESC){
								return 0;
							}
						}
					}
				case  DOWN:
					move_time_passed +=100;
					break;
				case  UP:
					move_tetromino(UP);
					break;
				case LEFT:
					move_tetromino(LEFT);
					break;
				case RIGHT:
					move_tetromino(RIGHT);
					break;
			}
		}
    	delay (5);
    	move_time_passed++;
	}
	if(end){
		setfillstyle ( 1, BLACK ); 
		bar(XSTARTCORD+20, YSTARTCORD+150, XSTARTCORD+280, YSTARTCORD+250);
		moveto(XSTARTCORD+20, YSTARTCORD+150);
		setcolor(LIGHTRED);
		lineto(XSTARTCORD+280,YSTARTCORD+150);
		lineto(XSTARTCORD+280,YSTARTCORD+250);
		lineto(XSTARTCORD+20,YSTARTCORD+250);
		lineto(XSTARTCORD+20,YSTARTCORD+150);
		setcolor(WHITE);
		settextstyle(10,0,2);
		outtextxy(XSTARTCORD+40,YSTARTCORD+180, "ВЫ ПРОИГРАЛИ!");
		settextstyle(0,0,1);
		outtextxy(XSTARTCORD+30,YSTARTCORD+210, "Нажмите ESC чтобы закончить");
	}
	while(1){
		if(kbhit()){
			KEY = getch();
			if(KEY == ESC){
				break;
			}
		}
	}
	free(BlackBlockBuf);
	free(GreenBlockBuf);
	free(CyanBlockBuf);
	free(RedBlockBuf);
	free(PurpleBlockBuf);
	free(YellowBlockBuf);
	closegraph();        // закрываем графическое окно
	return 0;
}

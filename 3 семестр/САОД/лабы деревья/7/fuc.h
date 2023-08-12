#ifndef FUC_H
#define FUC_H


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <conio.h>

#define YES true
#define NO false
using namespace std;


struct vertex
{
	int data;
	int h;
	int w;
	vertex *left;
	vertex *right;
};

int const N = 10;

void AW_count();
void AP_AR_count();
void add(vertex *&, int, int);
void create_tree(int, int);
void LRprint(vertex *&x);
int size(vertex *);
long summ(vertex *);
int height(vertex *, int);
void seth(vertex*);
void midh(vertex*);

#endif //PCH_H



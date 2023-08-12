#ifndef FUC_H
#define FUC_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <conio.h>
#include <time.h>


using namespace std;

struct vertex
{
	int data;
	int w;
	int h;
	vertex *left;
	vertex *right;
};

int const N = 10;


void AW_count();
void AP_AR_count();
void add(vertex *&, int, int);
void create_tree(int, int);
void LRprint(vertex *&);
int size(vertex *);
long summ(vertex *);
int height(vertex *, int);
void seth(vertex*);
void midh(vertex*);

void BubbleSort();
void A1(int, int);
void A2(int, int);


#endif


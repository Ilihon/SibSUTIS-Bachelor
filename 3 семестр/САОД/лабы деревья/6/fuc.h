#ifndef FUC_H
#define FUC_H


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
// #include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>

#define YES true
#define NO false
using namespace std;

extern bool up;

struct vertex {
	int data;
	int bal;
	vertex *left;
	vertex *right;
};


void LR(vertex*);

void binSert(int, vertex*&);


void addAVL(int, vertex*&);
void ll(vertex*&);
void rr(vertex*&);
void lr(vertex*&);
void rl(vertex*&);

int size(vertex*);
int height(vertex*);
int max(int, int);
int sdp(vertex*, int);
int summ(vertex*);


 #include "fuc.cpp"
#endif 

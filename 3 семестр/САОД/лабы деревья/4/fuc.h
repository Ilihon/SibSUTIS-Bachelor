#ifndef FUC_H
#define FUC_H


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>

#define YES true
#define NO false
using namespace std;

extern bool up;

struct vertex
{
	int data;
	int bal;
	vertex *left;
	vertex *right;
};

//АВ
void addAVL(int, vertex*&);
void ll(vertex*&);
void rr(vertex*&);
void lr(vertex*&);
void rl(vertex*&);
void LR(vertex*);
//случайное рекусрсивно
int SDP(int, vertex*&);
//идеально-сбалансировванное
vertex* ISDP(int l, int r, int *m);
//Вычисление размера дерева
int TreeSize(vertex* p);
//Вычисление высоты дерева
int TreeHeight(vertex* p);
//Выбор максимальной
int Max(int l, int r);
//Вычисление средней высоты
int SumDlinPutey(vertex*, int L);
//Вычисление контрольной суммы
int Sum(vertex* p);


#include "fuc.cpp"
#endif //PCH_H


#ifndef FUC_H
#define FUC_H



#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


struct vertex
{
	int data;
	int bal;
	vertex *left;
	vertex *right;
};

extern int turn;//поворот
//АВЛ-дерево
void addAVL(int, vertex*&);
void ll(vertex*&);
void rr(vertex*&);
void lr(vertex*&);
void rl(vertex*&);
//Удаление из АВЛ
void DeleteAVL(int, vertex*&);
void del(vertex *&);
void BL(vertex *&);
void BR(vertex *&);
void LL1(vertex *&);
void RR1(vertex *&);
///////////////////

void LRprint(vertex*); //Обход
int TreeSize(vertex *p); // Вычисляет размер дерева
int Max(int l, int r); // Определяет максимальное число среди l и r
int TreeHeight(vertex *p); // Вычисляет высоту дерева
int SumDlinPutey(vertex*, int L); //Вычисление средней высоты


#include "fuc.cpp"
#endif 

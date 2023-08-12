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

//��
void addAVL(int, vertex*&);
void ll(vertex*&);
void rr(vertex*&);
void lr(vertex*&);
void rl(vertex*&);
void LR(vertex*);
//��������� �����������
int SDP(int, vertex*&);
//��������-�����������������
vertex* ISDP(int l, int r, int *m);
//���������� ������� ������
int TreeSize(vertex* p);
//���������� ������ ������
int TreeHeight(vertex* p);
//����� ������������
int Max(int l, int r);
//���������� ������� ������
int SumDlinPutey(vertex*, int L);
//���������� ����������� �����
int Sum(vertex* p);


#include "fuc.cpp"
#endif //PCH_H


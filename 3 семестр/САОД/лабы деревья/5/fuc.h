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

extern int turn;//�������
//���-������
void addAVL(int, vertex*&);
void ll(vertex*&);
void rr(vertex*&);
void lr(vertex*&);
void rl(vertex*&);
//�������� �� ���
void DeleteAVL(int, vertex*&);
void del(vertex *&);
void BL(vertex *&);
void BR(vertex *&);
void LL1(vertex *&);
void RR1(vertex *&);
///////////////////

void LRprint(vertex*); //�����
int TreeSize(vertex *p); // ��������� ������ ������
int Max(int l, int r); // ���������� ������������ ����� ����� l � r
int TreeHeight(vertex *p); // ��������� ������ ������
int SumDlinPutey(vertex*, int L); //���������� ������� ������


#include "fuc.cpp"
#endif 

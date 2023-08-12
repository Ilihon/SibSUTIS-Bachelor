#ifndef FUC_H
#define FUC_H



#define YES true
#define NO false
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


struct str
{
	struct str *next;
	struct str *prev;
	int data;
};

struct strchar
{
	struct strchar *next;
	struct strchar *prev;
	char data;
};

struct strdouble
{
	struct strdouble *next;
	struct strdouble *prev;
	double data;
};


int const N = 10;


class Set
{
	protected:
		int i,j;
	
	public:
		Set(char *n);
		Set();
		~Set();
		
		template < class T >
		void mas_init (T *A);	
			
		virtual	void PrintSpis(){ };		
};

#include "Set.cpp"


class Stack : public Set
{
	
	public:
		
		Stack(char *n);
		Stack();
		~Stack();
		void Stack_Init(str *&p);
		void PrintSpis(str *p);	
};

#include "Stack.cpp"

class Queue : public Set
{
	
	public:
		Queue(char *n);
		Queue();
		~Queue();
		
		template < class VG, class data_type >
		void Queue_Init(VG *&p, data_type);
		template < class VG >
		void PrintSpis(VG *p);
};

#include "Queue.cpp"

/*
class Vector : public Set
{
	
}*/

#endif 

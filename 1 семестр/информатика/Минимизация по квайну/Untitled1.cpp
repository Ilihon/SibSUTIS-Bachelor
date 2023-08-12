	/*
	QMCS - Quine McCluskey Simplifier. This program uses the Quine McCluskey
	method to mimize a boolean function. Inputs are decimal numbers, of which
	the binary representation of that number is used to determine the prime
	implicants (p_group) and then the essential prime implicants(final_gorup
	
	Copyright (C) 2005 Deian Stefan   stefan (at) cooper (dot) edu
	   
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA*/
	
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

int MIN_BITS = 4;		//minimum bits to print
vector<unsigned> input_values;	
bool show_mid = false;		//show middle process

struct B_number{
	unsigned number;
	unsigned dashes;
	bool used;
};

vector<vector<B_number> > table;	//original table
vector<vector<B_number> > p_group;	//mid process table
vector<vector<B_number> > final_group;	//final table
vector<B_number> printed_numbers; //avoid printing the same final numbers 

//----------------------------------------------------------
unsigned count_1s(unsigned number); //count the number of 1s in a number
void print_binary(unsigned number);//print the number in binary
void create_table();		//create original table sorted by the number of 1s
void print_table();		//print the table
B_number init_B_number(unsigned n,int d, bool u);//initialize a B_number
void create_p_group();		//create mid process table
void print_p_group();		//print it
void print_p_binary(unsigned n, unsigned d);//print the mid table (with -'s)
void create_final_group();		//create final table
void print_final_group();		//print final table with -'s and unused terms
bool is_printed(B_number n);		//dont print terms that were already printed
void init();				//start the table making and printing
void getinput();			//get input from user
unsigned count_bits(unsigned n);	//min bits to represent a number
//----------------------------------------------------------

int main(int argc, char *argv[]) {

	/* allow command line calling with arguments -m -b X
	   where X is a number. order or -m and -b X does not
	   matter*/
	cout<<"\nQMCS - Quine McCluskey Simplifier\n";
	if(argc >= 2)
	{
		string arg = argv[1];
		if(arg.find("-m") != -1) {
			show_mid = true;
			if(argc>=3) {
				arg = argv[2];
				if(arg.find("-b") != -1)
					MIN_BITS = atoi(argv[3]);
			}
		}
		else if(arg.find("-h") != -1) {
			cout<<"-b X\tminimum bits should be X.\n"
			    <<"-m  \tshow mid process computation.\n"
			    <<"-h  \tshow this.\n";
			return 0;
		
		}
		else {
			if(arg.find("-b") != -1  && argc >=3)
				MIN_BITS = atoi(argv[2]);

			if(argc >=4) {
			       	arg = argv[3];
				if(arg.find("-m") != -1) 
					show_mid = true;
			}
			else
			{
				cout<<"Invalid argument\n"
				    <<"-b X\tminimum bits should be X.\n"
				    <<"-m  \tshow mid process computation.\n"
				    <<"-h  \tshow this.\n";
				return 0;
			}
		}
	}

	getinput();
	init();
	
	return 0;
	
}

/* counts 1s by getting the LSB (%2) and then shifting until 0 */
unsigned count_1s(unsigned number) {
	short bit =0;
	int count = 0;
	while(number>0)	{
		bit = number%2;
		number>>=1;
		if(bit) {
			count++;
		}
	}
	return count;
}
/*get LSB, arrange it in array, the print array in reverse order so MSB is on
the left */
void print_binary(unsigned number) {
	unsigned bits[MIN_BITS];
	int count = 0;
	
	while(number>0||count<MIN_BITS)	{
		bits[count] = number%2;
		number>>= 1;
		count++;
	}
	for(int i=count-1;i>=0;i--)
		cout<<bits[i];
}
/*creating first table: append current number to the array located in
table[number of 1s f this number]*/
void create_table() {
	short tmp;
	B_number temp_num;
	for(int i=0;i<input_values.size();i++) {
		tmp = count_1s(input_values[i]);
		if(tmp+1>table.size())
			table.resize(tmp+1);
		
		temp_num = init_B_number(input_values[i],0,false);
		table[tmp].push_back(temp_num);
	}
}

void print_table() {
	
	cout<<endl<<"COMPUTING:"<<endl;
	for(int i=0;i<table.size();i++)	{
		cout<<i;
		for(int j=0;j<table[i].size();j++) {
			cout<<"\tm"<<table[i][j].number<<"\t";
			print_binary(table[i][j].number);
			cout<<endl;
		}
		cout<<"\n-------------------------------------"<<endl;
	}
}
/* initialize a B_number variable - like a constructor */
B_number init_B_number(unsigned	n,int d, bool u) {
	B_number num;
	num.number = n;
	num.dashes = d;
	num.used = u;
	return num;
}
/*like the original table, but the paring of numbers from the original table-
dashes are represented by a 1. for example original A=0011 B=1011, new number 
is -011 which is represented as C.number=A&B=0011,C.dashes=A^B=1000*/
void create_p_group() {
	short tmp;
	B_number temp_num;
	unsigned temp_number, temp_dashes;
	for(int i=0;i<table.size()-1;i++) {
		for(int j=0;j<table[i].size();j++) {
			for(int k=0;k<table[i+1].size();k++) {
				temp_number = table[i][j].number & table[i+1][k].number;
				temp_dashes = table[i][j].number ^ table[i+1][k].number;
				
				if(count_1s(temp_dashes)==1) {
					table[i][j].used = true;
					table[i+1][k].used = true;
					
					
					tmp = count_1s(temp_number);
					
					if(tmp+1>p_group.size())
						p_group.resize(tmp+1);
					
					temp_num = init_B_number(temp_number, temp_dashes, false);
					p_group[tmp].push_back(temp_num);
				}
			}
		}
	}
}

void print_p_group() {
	cout<<endl<<"MID PROCESS COMPUTATION:"<<endl;
	
	for(int i=0;i<p_group.size();i++) {
		cout<<i;
		for(int j=0;j<p_group[i].size();j++) {
			cout<<"\t\t";
			print_p_binary(p_group[i][j].number,p_group[i][j].dashes);
			cout<<endl;
		}
		cout<<"\n-------------------------------------"<<endl;
	}
	
}
/*print a number such as -001; this allocates bits in an array dash=2 then 
prints reverse array */
void print_p_binary(unsigned n, unsigned d) {
	unsigned bits[MIN_BITS];
	int count = 0;
	
	while(n>0||count<MIN_BITS) {
		if(!(d%2))
			bits[count] = n%2;
		else
			bits[count] = 2;
		
		n >>= 1;
		d >>= 1;
		count++;
	}
	for(int i=count-1;i>=0;i--) {
		if(bits[i]!=2)
			cout<<bits[i];
		else
			cout<<"-";
	}
}
/*creates final table. works like p_group(). example; in p_group you have: 
A=-001 B=-011 -> C= -0-1 which will be represented as 
C.number=A&B=0001&0011=0001, and C.dashes=A^B^A.dashes=0001^0011^1000=1010. 
Computation is done only when A.dashes = b.dashes*/
void create_final_group() {
	short tmp;
	B_number temp_num;
	unsigned temp_number, temp_dashes;
	for(int i=0;i<p_group.size()-1;i++) {
		for(int j=0;j<p_group[i].size();j++) {
			for(int k=0;k<p_group[i+1].size();k++) {
				if(p_group[i][j].dashes == p_group[i+1][k].dashes) {
					temp_number = p_group[i][j].number & p_group[i+1][k].number;
					temp_dashes = p_group[i][j].number ^ p_group[i+1][k].number;
					if(count_1s(temp_dashes)==1) {
						temp_dashes^= p_group[i][j].dashes;
						
						p_group[i][j].used = true;
						p_group[i+1][k].used = true;
						
						tmp = count_1s(temp_number);
						
						if(tmp+1>final_group.size())
							final_group.resize(tmp+1);
						
						temp_num = init_B_number(temp_number, temp_dashes, true);
						final_group[tmp].push_back(temp_num);
					}
				}
			}
		}
	}
}
/*print all the values from the final table, except for duplicates.
  print all the unused numbers from original table and mid process table*/
void print_final_group() {
	cout<<endl<<"FINAL:\n-------------------------------------"<<endl;
	int i,j;
	for(i=0;i<final_group.size();i++) {
		for(j=0;j<final_group[i].size();j++) {
			if(!is_printed(final_group[i][j])) {
				print_p_binary(final_group[i][j].number,final_group[i][j].dashes);
				cout<<endl;
				printed_numbers.push_back(final_group[i][j]);
			}
		}
	}
	for(i=0;i<p_group.size();i++) {
		for(j=0;j<p_group[i].size();j++) {
			if(!p_group[i][j].used) {
				print_p_binary(p_group[i][j].number,p_group[i][j].dashes);
				cout<<endl;
			}
		}
	}
	for(i=0;i<table.size();i++) {
		for(j=0;j<table[i].size();j++) {
			if(!table[i][j].used) {
				print_p_binary(table[i][j].number,table[i][j].dashes);
				cout<<endl;
			}
		}
	}
	cout<<"-------------------------------------"<<endl;
}
/*used to avoid printing duplicates that can exist in the final table*/
bool is_printed(B_number n) {
	for(int i=0;i<printed_numbers.size();i++)
		if(n.number==printed_numbers[i].number && n.dashes == printed_numbers[i].dashes)
			return true;
	
	return false;
}
/*initialize all table*/
void init() {
	table.resize(1);
	p_group.resize(1);
	final_group.resize(1);
	create_table();
	print_table();
	create_p_group();
	if(show_mid)
		print_p_group();
	create_final_group();
	print_final_group();
}

void getinput() {
	unsigned in;
	int num_bits=0;
	cout<<"\nInput value followed by ENTER[^D ends input]\n> ";
	while(cin>>in) {
		input_values.push_back(in);
		num_bits = count_bits(in);	
		if(num_bits>MIN_BITS)
			MIN_BITS = num_bits;
		cout<<"> ";
	}
}
/*return min number of bits a number is represented by. used for best output*/
unsigned count_bits(unsigned n) {
	short bit =0;
	int count = 0;
	while(n>0) {
		bit = n%2;
		n>>=1;
		count++;
	}
	return count;
}


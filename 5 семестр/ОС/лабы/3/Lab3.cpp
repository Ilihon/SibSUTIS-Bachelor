#include "sys/types.h"
#include "sys/stat.h"
#include <sys/wait.h>
#include "dirent.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void getFileName(string str)
{
	str = "/proc/" + str + "/stat";
	ifstream fstr(str);
	int n;
	fstr >> n >> str;
	cout << str << endl;
}

void l3t1()
{
	switch(fork())
	{
		case 0: 
		    printf("Noo\n"); //дочерний процесс
			break;
		case -1: 
		    perror("STROKA -\n");
		default: 
		    printf("i'm your father\n");  //родительский процесс
			break;
	}
}

void l3t2()
{
	switch(fork())
	{
		case 0: 
		    execl("/bin/ls", "ls", "-la", NULL); //передача аргументов процессу потомку 
			break;
		default: 
		    printf("i'm your father\n"); 
			break;
	}
}

void l3t3()
{
	int pid;

	switch(fork())
	{
		case 0: 
			if (fork())
			{
				printf("\tlson:%d BATYA:%d\n", getpid(), getppid());  //getpid возвращает ID процесса, getppid - ID родительского процесса
				getFileName(to_string(getpid()));
			} 
			else 
			{
				printf("\t\tlvnuk:%d lson:%d\n", getpid(), getppid());
				getFileName(to_string(getpid()));
			}
		    break;

		default:
			printf("BATYA:%d\n", getpid());
			getFileName(to_string(getpid()));
			switch(fork())
			{
				case 0: 
				{
					printf("\trson:%d BATYA:%d\n", getpid(), getppid());
					getFileName(to_string(getpid()));
					if (fork()) 
					{
						if (!fork()) 
						{
							printf("\t\trvunk2:%d rson:%d\n", getpid(), getppid());
							getFileName(to_string(getpid()));
						}
					} 
					else 
					{
						printf("\t\trvnuk1:%d rson:%d\n", getpid(), getppid());
						getFileName(to_string(getpid()));
					}
				}
				break;
			}
		break;
	}
}


int main()
{
	l3t1();
	l3t2();
	l3t3();
	
	while(fork()) 
	{
	    wait(getppid()); 
		cout << "kek";
	}

	return 0;
}

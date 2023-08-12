#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

void GetRandomNumber(char *num)
{
char digits[10] = "123456789";
srand((unsigned)time(0));
for (unsigned i = 0, rmax = 9; i < 4; i++)
{
unsigned r = rand() % rmax--;
num[i] = digits[r];
digits[r] = digits[rmax];
}
}

void GetRandomNumber2(char *num)
{
char digits[10] = "123456789";
srand((unsigned)time(0));
for (unsigned i = 0, rmax = 9; i < 6; i++) {
unsigned r = rand() % rmax--;
num[i] = digits[r];
digits[r] = digits[rmax];
}
}

void GetRandomNumber3(char *num)
{
char digits[10] = "123456789";
srand((unsigned)time(0));
for (unsigned i = 0, rmax = 9; i < 8; i++) {
unsigned r = rand() % rmax--;
num[i] = digits[r];
digits[r] = digits[rmax];
}
}

template <int row, int col>
bool CheckAnswer(char(&arr)[row][col], unsigned &bull, unsigned &cow)
{
	cow = 0; bull = 0;
	unsigned i1, i2;
	for (i1 = 0; i1 < col - 1; i1++)
	{
		for (i2 = 0; i2 < col - 1; i2++)
		{
			if (arr[0][i1] == arr[1][i2])
			{
				if (i1 == i2) cow++;
				else bull++;
			}
		}
	}
	return cow == col - 1;
}

int main()
{
	srand((unsigned)time(NULL));
    int choice;
	while (1)
	{
		printf("1:New game\n");
		printf("2:Game rules\n");
		printf("3:Exit\n");
        scanf("%d", &choice);

        if (choice == 1)
		{
			int choise1;
			printf("Select difficulty level\n");
			printf("1:Easy(4 numbers)\n");
			printf("2:Medium(6 numbers)\n");
			printf("3:Hard(8 numbers)\n");
			scanf("%d", &choise1);

            if (choise1 == 1)
			{
				unsigned bulls(0), cows(0);
				char numbers[2][5];
				int c1;
                GetRandomNumber(numbers[0]);
				while(true)
				{
				 printf("random number\n");
				 printf("Hidden number\n");
				 printf("****\n");
                 printf("vvodi 4 chisla");
                 printf("\n");
                 //scanf("%d", &numbers[1]);
				 std::cin>>numbers[1];
				 if(CheckAnswer(numbers, bulls, cows))
					{
						system("PAUSE");
						return 0;
					}
					printf(" %d bulls and %d cows\n", bulls, cows);
					if (bulls == 4)
					{
						printf("winner winner chiken dinner !!!");
						break;
					}
				 printf("Exit?\n");
					printf("1:Yes\n");
					printf("2:No\n");
					scanf("%d",&c1);

					if(c1 == 1)
					{
						printf("Bye\n");
						break;
					}
				}
				return 0;
			}

			if (choise1 ==2)
			{
				unsigned bulls(0), cows(0);
				char numbers[2][5];
				int c1;
                GetRandomNumber(numbers[0]);
				while(true)
				{
				 printf("random number\n");
				 printf("Hidden number\n");
				 printf("****\n");
                 printf("vvodi 6 chisla");
                 printf("\n");
                 //scanf("%d", &numbers[1]);
				 std::cin>>numbers[1];
				 if(CheckAnswer(numbers, bulls, cows))
					{
						system("PAUSE");
						return 0;
					}
					printf(" %d bulls and %d cows\n", bulls, cows);
					if (bulls == 6)
					{
						printf("winner winner chiken dinner !!!");
						break;
					}
				 printf("Exit?\n");
					printf("1:Yes\n");
					printf("2:No\n");
					scanf("%d",&c1);

					if(c1 == 1)
					{
						printf("Bye\n");
						break;
					}
				}
				return 0;
			}

			if (choise1 ==3)
			{
				unsigned bulls(0), cows(0);
				char numbers[2][5];
				int c1;
                GetRandomNumber(numbers[0]);
				while(true)
				{
				 printf("random number\n");
				 printf("Hidden number\n");
				 printf("****\n");
                 printf("vvodi 8 chisla");
                 printf("\n");
                 //scanf("%d", &numbers[1]);
				 std::cin>>numbers[1];
				 if(CheckAnswer(numbers, bulls, cows))
					{
						system("PAUSE");
						return 0;
					}
					printf(" %d bulls and %d cows\n", bulls, cows);
					if (bulls == 8)
					{
						printf("winner winner chiken dinner !!!");
						break;
					}
				 printf("Exit?\n");
					printf("1:Yes\n");
					printf("2:No\n");
					scanf("%d",&c1);

					if(c1 == 1)
					{
						printf("Bye\n");
						break;
					}
				}
				return 0;
			}
        }
      	else if (choice == 2)
		{
			printf("Game rules\n");
		}
		else if (choice == 3)
		{
			printf("Good bye\n");
		}
		if ((choice != 1) && (choice != 2))
			break;
    }
}

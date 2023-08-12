#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void swap(int& x, int& y);

void Random(int* A, int N)
{
    int i = 0;
    for (int j = 0; j < 10; j++) {
        A[j] = j;
    }
    for (i = 0; i < N * 10; i++) {
        swap(A[rand() % 10], A[rand() % 10]);
    }
}

void swap(int& x, int& y)
{
    int temp = 0;
    temp = x;
    x = y;
    y = temp;
}

void Search(int* A, int* B, int& bull, int& cow, int N)
{
    bull = 0;
    cow = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i] == B[j]) {
                if (i == j)
                    bull++;
                else
                    cow++;
            }
        }
    }
}

int Menu()
{
    srand(time(NULL));
    int P = 0, O = 0;
    std::cout << "1.New Game" << std::endl;
    std::cout << "2.Game Rules" << std::endl;
    std::cout << "3.Exit" << std::endl;
    std::cin >> P;
    switch (P) {
    case 1: {
        std::cout << "\tSelect difficulty level" << std::endl << std::endl;
        std::cout << "1.Easy" << std::endl;
        std::cout << "2.Medium" << std::endl;
        std::cout << "3.Hard" << std::endl;
        std::cout << "4.Back" << std::endl;
        std::cin >> O;
        switch (O) {
        case 1: {
            std::cout << "Hidden number" << std::endl;
            std::cout << "* * * *" << std::endl;
            int N = 4;
            int A[N];
            int B[N];
            Random(A, N);
            std::cout << std::endl;
            int bull = 0, cow = 0;
            do {
                std::cout << "Enter four numbers one by one" << std::endl;
                for (int i = 0; i < N; i++) {
                    std::cin >> B[i];
                }
                Search(A, B, bull, cow, N);
                std::cout << "bull: " << bull << "\tcow: " << cow << std::endl
                          << std::endl;
            } while (bull <= 3);
            std::cout << "You win!!!" << std::endl;
            break;
        }
        case 2: {
            std::cout << "Hidden number" << std::endl;
            std::cout << "* * * * * *" << std::endl;
            int N = 6;
            int A[N];
            int B[N];
            Random(A, N);
            std::cout << std::endl;
            int bull = 0, cow = 0;
            do {
                std::cout << "Enter four numbers one by one" << std::endl;
                for (int i = 0; i < N; i++) {
                    std::cin >> B[i];
                }
                Search(A, B, bull, cow, N);
                std::cout << "bull: " << bull << "\tcow: " << cow << std::endl
                          << std::endl;
            } while (bull <= 5);
            std::cout << "You win!!!" << std::endl;
            break;
        }
        case 3: {
            std::cout << "Hidden number" << std::endl;
            std::cout << "* * * * * * * *" << std::endl;
            int N = 8;
            int A[N];
            int B[N];
            Random(A, N);
            std::cout << std::endl;
            int bull = 0, cow = 0;
            do {
                std::cout << "Enter four numbers one by one" << std::endl;
                for (int i = 0; i < N; i++) {
                    std::cin >> B[i];
                }
                Search(A, B, bull, cow, N);
                std::cout << "bull: " << bull << "\tcow: " << cow << std::endl
                          << std::endl;
            } while (bull <= 7);
            std::cout << "You win!!!" << std::endl;
        }
        case 4: {
            Menu();
            break;
        }
        }
        break;
    }
    case 2: {
        break;
    }
    case 3: {
        break;
    }
    }
    return 0;
}

int main()
{
    srand(time(NULL));
    Menu();
    return 0;
}
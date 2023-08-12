#include "course.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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

int CountBullandCow(int* A, char* B, int& bull, int& cow, int N)
{
    bull = 0;
    cow = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i] == B[j] - '0') {
                if (i == j)
                    bull++;
                else
                    cow++;
            }
        }
    }
    return bull;
}

int Input(char* B, int N)
{
    for (int i = 0; i < N; i++) {
        std::string str;
        std::cin >> str;
        B[i] = str[0];
        if (((B[i] < '0' || B[i] > '9') && ((B[i] != 'Q') && (B[i] != 'q')))
            || (str.length() > 1)) {
            std::cout << std::endl;
            std::cout << "Invalid number entered" << std::endl;
            std::cout << "Error = '" << str << "' " << std::endl;
            std::cout << "Continue with the sequence of the error" << std::endl
                      << std::endl;
            i--;
            continue;
        }
        if ((B[i] == 'Q') || (B[i] == 'q')) {
            return 1;
        }
    }
    return 0;
}

int Menu()
{
    int P = 0, O = 0;
    std::cout << "1.New Game" << std::endl;
    std::cout << "2.Game Rules" << std::endl;
    std::cout << "3.Exit" << std::endl;
    std::cin >> P;
    switch (P) {
    case 1: {
        system("clear");
        std::cout << "\tSelect difficulty level" << std::endl << std::endl;
        std::cout << "1.Easy" << std::endl;
        std::cout << "2.Medium" << std::endl;
        std::cout << "3.Hard" << std::endl;
        std::cout << "4.Back" << std::endl;
        std::cin >> O;
        switch (O) {
        case 1: {
            system("clear");
            std::cout << "Hidden number" << std::endl;
            std::cout << "* * * *" << std::endl;
            int *A, N = 4;
            char* B;
            A = new int[100];
            B = new char[N];
            Random(A, N);
            std::cout << std::endl;
            int bull = 0, cow = 0;
            do {
                std::cout << "Enter four numbers one by one" << std::endl;
                std::cout << "To exit the game, type q or Q and press Enter"
                          << std::endl;
                if (Input(B, N)) {
                    system("clear");
                    Menu();
                    return 0;
                }
                std::cout << "The entered sequence = " << B << std::endl;
                CountBullandCow(A, B, bull, cow, N);
                std::cout << "bull: " << bull << "\tcow: " << cow << std::endl
                          << std::endl;
            } while (bull <= 3);
            std::cout << "You win!!!" << std::endl;
            std::cout << "Secret numder" << std::endl;
            for (int i = 0; i < N; i++) {
                std::cout << A[i] << " ";
            }
            std::cout << std::endl;
            delete A;
            A = NULL;
            delete B;
            B = NULL;
            break;
        }
        case 2: {
            system("clear");
            std::cout << "Hidden number" << std::endl;
            std::cout << "* * * * * *" << std::endl;
            int *A, N = 6;
            char* B;
            A = new int[100];
            B = new char[N];
            Random(A, N);
            std::cout << std::endl;
            int bull = 0, cow = 0;
            do {
                std::cout << "Enter six numbers one by one" << std::endl;
                std::cout << "To exit the game, type q or Q and press Enter "
                          << std::endl;
                if (Input(B, N)) {
                    system("clear");
                    Menu();
                    return 0;
                }
                std::cout << "The entered sequence = " << B << std::endl;
                CountBullandCow(A, B, bull, cow, N);
                std::cout << "bull: " << bull << "\tcow: " << cow << std::endl
                          << std::endl;
            } while (bull <= 5);
            std::cout << "You win!!!" << std::endl;
            std::cout << "Secret numder" << std::endl;
            for (int i = 0; i < N; i++) {
                std::cout << A[i] << " ";
            }
            std::cout << std::endl;
            delete A;
            A = NULL;
            delete B;
            B = NULL;
            break;
        }
        case 3: {
            system("clear");
            std::cout << "Hidden number" << std::endl;
            std::cout << "* * * * * * * *" << std::endl;
            int *A, N = 8;
            char* B;
            A = new int[100];
            B = new char[N];
            Random(A, N);
            std::cout << std::endl;
            int bull = 0, cow = 0;
            do {
                std::cout << "Enter eight numbers one by one" << std::endl;
                std::cout << "To exit the game, type q or Q and press Enter "
                          << std::endl;
                if (Input(B, N)) {
                    system("clear");
                    Menu();
                    return 0;
                }
                std::cout << "The entered sequence = " << B << std::endl;
                CountBullandCow(A, B, bull, cow, N);
                std::cout << "bull: " << bull << "\tcow: " << cow << std::endl
                          << std::endl;
            } while (bull <= 7);
            std::cout << "You win!!!" << std::endl;
            std::cout << "Secret numder" << std::endl;
            for (int i = 0; i < N; i++) {
                std::cout << A[i] << " ";
            }
            std::cout << std::endl;
            delete A;
            A = NULL;
            delete B;
            B = NULL;
            break;
        }
        case 4: {
            system("clear");
            Menu();
            break;
        }
        }
        break;
    }
    case 2: {
        system("clear");
        std::cout << "Правила логической игры быки и коровы" << std::endl;
        std::cout << std::endl;
        std::cout << "Коспьютер загадывает последовательность чисел "
                     "(последовательность зависит от выбранного пользователем "
                     "уровня сложности)"
                  << std::endl;
        std::cout << std::endl;
        std::cout << "После введенной пользователем последовательности, "
                     "программа выдает подсказки в виде 'Быков' и 'Коров'"
                  << std::endl;
        std::cout << std::endl;
        std::cout << "Где 'Быки' это число угаданное сточностью до позиции, а "
                     "'Коровы' угаданное число которое не стоит на своем месте"
                  << std::endl;
        std::cout << std::endl;
        int p;
        std::cout << "1.Back" << std::endl;
        std::cin >> p;
        system("clear");
        switch (p) {
        case 1: {
            Menu();
            break;
        }
        }
    }
    case 3: {
        break;
    }
    }
    return 0;
}
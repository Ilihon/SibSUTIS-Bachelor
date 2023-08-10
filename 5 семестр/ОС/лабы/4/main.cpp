#include <stdio.h>
#include <iostream>
#include <process.h>
#include <locale.h>
#include <stdlib.h>
#include <string>
#include <stdint.h>
#include <windows.h>
#include <vector>

using namespace std;


uint16_t GetMachineType(const char *path)
{
    uint16_t result = IMAGE_FILE_MACHINE_UNKNOWN;
    FILE *file = fopen(path, "rb");
    if (file != NULL)
    {
        fseek(file, 0x3c, SEEK_SET);
        uint32_t peOffset;
        if (fread(&peOffset, 1, sizeof(uint32_t), file) == sizeof(uint32_t))
        {
            fseek(file, peOffset, SEEK_SET);
            uint32_t peHead;
            if (fread(&peHead, 1, sizeof(uint32_t), file) == sizeof(uint32_t))
            {
                if (peHead == 0x00004550)
                {
                    uint16_t machineType;

                    if (fread(&machineType, 1, sizeof(uint16_t), file) == sizeof(uint16_t))
                    {
                        result = machineType;
                    }
                }
            }
        }
        fclose(file);
    }
    return result;
}

void split(vector<string> &a, string str)
{
    string s;
    bool f = 0;
    for (auto &i : str)
    {
        if (i == ' ')
        {
            if (s.size() != 0)
            {
                a.push_back(s);
                s.clear();
                f = 0;
            }
        }
        else
        {
            s.push_back(i);
            f = 1;
        }
    }
    if (f)
    {
        a.push_back(s);
    }
}

int ExecuteCommand(vector<string> str)
{
    if (str.size() == 1 && str[0] == "exit")
    {
        return 0;
    }
    if (str[0] == "ls" || str[0] == "dir")
    {
        if (str.size() > 1)
        {
            char *arg[] = {(char *)"cmd", (char *)"/c", (char *)"dir ", (char *)str[1].c_str(), NULL};
            _spawnvp(P_WAIT, arg[0], arg);
        }
        else
        {
            char *arg[] = {(char *)"cmd", (char *)"/c", (char *)"dir", NULL};
            _spawnvp(P_WAIT, arg[0], arg);
        }
    }
    else if ((str[0] == "clear" || str[0] == "reset") && str.size() == 1)
    {
        char *arg[] = {(char *)"cmd", (char *)"/c", (char *)"CLS", NULL};
        _spawnvp(P_WAIT, arg[0], arg);
    }
    else if (str[0] == "touch" && str.size() == 2)
    {
	    char *arg[] = {(char *)"cmd", (char *)"/c", (char *)"copy NUL ", (char *)str[1].c_str(), NULL};
	    _spawnvp(P_WAIT, arg[0], arg);
    }
    else if (str[0] == "cp" && str.size() == 3)
    {
	    char *arg[] = {(char *)"cmd", (char *)"/c", (char *)"copy ", (char *)str[1].c_str(),(char *)str[2].c_str(), NULL};
	    _spawnvp(P_WAIT, arg[0], arg);
	}
    else if (str[0] == "rm" && str.size() == 2)
    {
        char *arg[] = {(char *)"cmd", (char *)"/c", (char *)"del ", (char *)str[1].c_str(), NULL};
        _spawnvp(P_WAIT, arg[0], arg);
    }
    else if (str[0] == "mv" && str.size() == 3)
    {
        char *arg[] = {(char *)"cmd", (char *)"/c", (char *)"move ", (char *)str[1].c_str(), (char *)" ", (char *)str[2].c_str(), NULL};
        _spawnvp(P_WAIT, arg[0], arg);
    }
    else if (str[0] == "cat" && str.size() == 2)
    {
        char *arg[] = {(char *)"cmd", (char *)"/c", (char *)"type ", (char *)str[1].c_str(), NULL};
        _spawnvp(P_WAIT, arg[0], arg);
    }
    else if (str[0] == "vi" && str.size() == 2)
    {
	    cout << endl << "Редактирование файла '" << (char *)str[1].c_str() << "''" << endl;
	    cout << "Содержимое:" << endl << ">>>>" << endl;
		char *arg[] = {(char *)"cmd", (char *)"/c", (char *)"type ", (char *)str[1].c_str(), NULL};
        _spawnvp(P_WAIT, arg[0], arg);
        cout << endl << "<<<<" << endl;
        cout << "Чтобы закончить редактирование введите Ctrl+Z"<< endl << ">>>>" << endl;
	    char *arg2[] = {(char *)"cmd", (char *)"/c", (char *)"copy con ", (char *)str[1].c_str(), NULL};
	    _spawnvp(P_WAIT, arg2[0], arg2);
    }
    else
    {
        printf("Неизвестная команда!\n");
    }
    return 1;
}

int main()
{
    system("cls");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printf("**********************************************************************\n"
           "** Лабораторная работа №4 \"Командная строка\"\n"
           "** Copyright (c) 2020 Ilihon Corporation\n"
           "**********************************************************************\n");
    LPTSTR s = new TCHAR[MAX_PATH];
    GetModuleFileName(GetModuleHandle(NULL), s, MAX_PATH);
    int arch = GetMachineType(s);
    if (arch == IMAGE_FILE_MACHINE_AMD64)
        printf("Среда инициализирована для: 'x64'\n\n");
    else if (arch == IMAGE_FILE_MACHINE_I386)
    {
        printf("Среда инициализирована для: 'x86'\n\n");
    }
    else
        printf("Ошибка, неизвестная разрядность процесса\n\n");
    TCHAR curPath[MAX_PATH];
    if (!GetCurrentDirectory(MAX_PATH, curPath))
    {
        printf("Ошибка. Не удалось получить путь к текущей дериктории.\n");
        exit(0);
    }
    int code = 1;
    while (code)
    {
        string s;
        printf("%s>", curPath);
        getline(cin, s, '\n');
        vector<string> str;
        split(str, s);
        code = ExecuteCommand(str);
    }
    system("CLS");
    return 0;
}

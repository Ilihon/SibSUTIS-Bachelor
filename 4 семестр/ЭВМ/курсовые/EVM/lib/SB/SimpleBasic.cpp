#include "SimpleBasic.h"

char vars[100], asm_str[100][100], asm_str_out[100][100];
int numbers_mas[100];

// Удаляет символ пробела из строки
// Вход: str - строка символов
// Выход: строка символов без символа пробела
char clearBackspace(char *str)
{
    char * current = str;
    char * last = str;

    for (; *current != '\0' ; ++current)
    {
        if (*current != ' ')
        {
            *last = *current;
            last++;
        }
    }
    *last = '\0';
}

// Возращает адрес размещения переменной SimpleBasic.
// Вход: varName - имя переменной SimpleBasic;
//       offset - смещение области размещения переменных, относительно начала памяти SimpleComputer.
// Возвращает адрес размещения указанной переменной. Если переменная не
// имеет адреса, то ей выделяется адрес и возвращается адрес
// ее размещения.
int getVarAddr(char varName, int offset)
{
    int i;

    // Перебираем адреса переменных SimpleBasic
    for (i = 0; i < sizeof(vars); i++)
    {
        // Возвращаем адрес размещения переменной с учетом смещения, если переменная найдена
        if (vars[i] == varName) return offset + i;
        // Иначе, если переменная не найдена ...
        else if (strcmp((vars + i), "\0") == 0) break;
    }
    *(vars + i) = varName;       // Выделяем для переменной адрес
    return offset + i;           // и возвращаем его с учетом смещения области размещения переменных
}

// Возращает адрес перехода оператора SimpleBasic GOTO по номеру строки перехода.
// Вход: gotoLine - номер строки перехода оператора GOTO SimpleBasic.
// Возвращает адрес перехода, соответствующий номеру строки или -1 в случае,
// если соответствия не найдено.
int getGotoAddr(int gotoLine)
{
    int ln, num, addr;

    for (int k = 0; k < sizeof(asm_str)/sizeof(asm_str[0]); k++)
    {
        sscanf(asm_str[k], "%d %d %d", &ln, &num, &addr);
        if (num == gotoLine) return addr;
    }
    return -1;
}

// Возвращает имя переменной SimpleBasic по ее адресу.
// Вход: varAddr - адрес переменной SimpleBasic;
//       offset - смещение области размещения переменных, относительно начала памяти SimpleComputer.
// Возвращает имя переменной по указанному адресу. Если переменная не
// найдена, возвращает \0;
char getVarName(int varAddr, int offset)
{
    if ((varAddr - offset >= 0) && (strcmp((vars + varAddr - offset), "\0") != 0)) vars + varAddr - offset;
    else return '\0';
}



int SimpleBasic(int argc, char** argv){
    FILE *file_sb, *file_sa;
    if( argc != 3)
    {
      printf("Usage: sbt file.sb file.sa\n ");
      return -1;
    }
    if ((file_sb = fopen (argv[1], "rb" )) <= 0)
    {
      printf("Can`t open '%s' file.\n", argv[1]);
      return -1;
    }
    if ((file_sa = fopen (argv[2], "wb" )) <= 0)
    {
      printf("Can`t create '%s' file.\n", argv[2]);
      return -1;
    }

    // Инициализируем буфер строк промежуточного кода SimpleAssembler
    for (int i = 0; i < sizeof(asm_str)/sizeof(asm_str[0]); i++) sprintf(asm_str[i], "%s", "");

    // Инициализируем буфер строк выходного кода SimpleAssembler
    for (int i = 0; i < sizeof(asm_str_out)/sizeof(asm_str_out[0]); i++) sprintf(asm_str_out[i], "%s", "");

    // Инициализируем буфер адресов размещения переменных SimpleBasic
    for (int i = 0; i < sizeof(vars); i++) strcpy(&vars[i], "\0");

    int var_offset, strnum, asm_addr = 0, last_strnum = 0;
    int max_strnum, goto_addr, goto_line;
    char opr[6], str[100], ch;
    char line[100];
    int linenum = 1;

    do
    {
        fgets (line, sizeof(line), file_sb);
        if(feof(file_sb)){
          break;
        }
        // Если строка не пустая ...
        printf("%s",line);
        if (strcmp(line, "\n") != 0)
        {
            // Выделяем в строке номер строки и оператор SimpleBasic. У каждой строки должно
            // быть как минимум номер строки и оператор.
            if (sscanf(line, "%d %s", &strnum, opr) >= 2)
            {
                // Номер текущей строки должен быть больше номер предыдущей строки - это и прверяем
                if (strnum <= last_strnum) {
                  printf("Translation error 1\n");
                  return -1;
                }
                // Если оператор SimpleBasic REM, то только увеличиваем счетчик
                // текущеего номера строки файла
                if (strcmp(opr, "REM") == 0)
                {
                    linenum++;
                    continue;
                }
                // Иначе, если оператор SimpleBasic END ...
                else if (strcmp(opr, "END") == 0)
                {
                    // Проверяем синтаксис - после END никаких символов не должно быть
                    if (sscanf(line, "%d %s %s", &strnum, opr, str) != 2){
                      printf("Translation error 2\n");
                      return -1;
                    }
                    // Формируем строку кода SimpleAssembler
                    sprintf(asm_str[asm_addr], "%d %d %d %s", linenum, strnum, asm_addr, "HALT\n");
                }
                // Иначе, если оператор SimpleBasic INPUT ...
                else if (strcmp(opr, "INPUT") == 0)
                {
                    // Проверяем синтаксис - после INPUT должна идти только переменная SimpleBasic
                    if (sscanf(line, "%d %s %c %s", &strnum, opr, &ch, str) != 3){
                      printf("Translation error 3\n");
                      return -1;
                    }
                    sprintf(asm_str[asm_addr], "%d %d %d %s %c%s", linenum, strnum, asm_addr, "READ", ch, "\n");
                }
                // Иначе, если оператор SimpleBasic LET ...
                else if (strcmp(opr, "LET") == 0)
                {
                    // Выделяем правую часть строки после оператора LET
                    char *s = strstr(line, "LET") + 4;
                    clearBackspace(s); // Вырезаем символы пробела
                    // Проверяем синтаксис и разбивае строку на составляющие
                    char ch1, ch2, ch3, ch4;
                    //Если объявляем переменную с определённым числом, то формируем
                    //промежуточный код SimpleAssembler
                    int d;
                    if (sscanf(s, "%c=%d",&ch1,&d) == 2){
                      sprintf(asm_str[asm_addr], "%d %d %d %s %d%s", linenum, strnum, asm_addr, "LOAD", d, "\n");
                      asm_addr++;
                      sprintf(asm_str[asm_addr], "%d %d %d %s %c%s", -1, -1, asm_addr, "STORE", ch1, "\n");
                      asm_addr++;
                      last_strnum = strnum;
                      linenum++;
                      continue;
                    }
                    //Иначе проверяем на синтаксис операции
                    if (sscanf(s, "%c=%c%c%c%s", &ch1, &ch2, &ch3, &ch4, str) != 4){
                      printf("Translation error 4\n");
                      return -1;
                    }
                    // Формируем промежуточный код SimpleAssembler
                    sprintf(asm_str[asm_addr], "%d %d %d %s %c%s", linenum, strnum, asm_addr, "LOAD", ch2, "\n");
                    asm_addr++;
                    if (ch3 == '+') sprintf(asm_str[asm_addr], "%d %d %d %s %c%s", -1, -1, asm_addr, "ADD", ch4, "\n");
                    else if (ch3 == '-') sprintf(asm_str[asm_addr], "%d %d %d %s %c%s", -1, -1, asm_addr, "SUB", ch4, "\n");
                    else if (ch3 == '*') sprintf(asm_str[asm_addr], "%d %d %d %s %c%s", -1, -1, asm_addr, "MUL", ch4, "\n");
                    else if (ch3 == '/') sprintf(asm_str[asm_addr], "%d %d %d %s %c%s", -1, -1, asm_addr, "DIVIDE", ch4, "\n");
                    else{
                      printf("Translation error 5\n");
                      return -1;
                    }
                    asm_addr++;
                    sprintf(asm_str[asm_addr], "%d %d %d %s %c%s", -1, -1, asm_addr, "STORE", ch1, "\n");
                }
                // Иначе, если оператор SimpleBasic IF ...
                else if (strcmp(opr, "IF") == 0)
                {
                    // Выделяем правую часть строки после оператора IF
                    char *s = strstr(line, "IF") + 2;
                    clearBackspace(s); // Вырезаем символы пробела
                    // Проверяем синтаксис и разбивае строку на составляющие
                    char ch1, ch2, ch3;
                    if (sscanf(s, "%c%c%cGOTO%d%s", &ch1, &ch2, &ch3, &goto_line, str) != 4){
                      printf("Translation error 6\n");
                      return -1;
                    }
                    // Формируем промежуточный код SimpleAssembler
                    sprintf(asm_str[asm_addr], "%d %d %d %s %c%s", linenum, strnum, asm_addr, "LOAD", ch1, "\n");
                    asm_addr++;
                    if ((ch2 == '<') && (ch3 == '0')) sprintf(asm_str[asm_addr], "%d %d %d %s %d%s", -1, -1, asm_addr, "JNEG", goto_line, "\n");
                    else if ((ch2 == '>') && (ch3 == '0')) sprintf(asm_str[asm_addr], "%d %d %d %s %d%s", -1, -1, asm_addr, "JNS", goto_line, "\n");
                    else if ((ch2 == '=') && (ch3 == '0')) sprintf(asm_str[asm_addr], "%d %d %d %s %d%s", -1, -1, asm_addr, "JZ", goto_line, "\n");
                    else{
                      printf("Translation error 7\n");
                      return -1;
                    }
                }
                // Иначе, если оператор SimpleBasic GOTO ...
                else if (strcmp(opr, "GOTO") == 0)
                {
                    // Проверяем синтаксис - после GOTO должен идти только номер строки перехода SimpleBasic
                    if (sscanf(line, "%d %s %d %s", &strnum, opr, &goto_line, str) != 3){
                      printf("Translation error 8\n");
                      return -1;
                    }
                    sprintf(asm_str[asm_addr], "%d %d %d %s %d%s", linenum, strnum, asm_addr, "JUMP", goto_line, "\n");
                }
                // Иначе, если оператор SimpleBasic PRINT ...
                else if (strcmp(opr, "PRINT") == 0)
                {
                    // Проверяем синтаксис - после INPUT должна идти только переменная SimpleBasic
                    if (sscanf(line, "%d %s %c %s", &strnum, opr, &ch, str) != 3){
                      printf("Translation error 9\n");
                      return -1;
                    }
                    sprintf(asm_str[asm_addr], "%d %d %d %s %c%s", linenum, strnum, asm_addr, "WRITE", ch, "\n");
                }
                // Иначе, ошибка трансляции, если неизвестный оператор SimpleBasic
                else{
                  printf("Translation error 11\n");
                  return -1;
                }

                asm_addr++; // Увеличиваем счетчик адреса исходного кода SimpleAssembler
                last_strnum = strnum; // Сохраняем номер текущей строки исходного кода SimpleBasic
            }
            // Иначе ошибка трансляции
            else{
              printf("Translation error 12\n");
              return -1;
            }
        }
        linenum++;
    }
    while (!feof(file_sb));
    fclose (file_sb);

    // Сохраняем максимальный номер строки SimpleBasic
    max_strnum = strnum;

    // Определяем смещение области размещения переменных сразу после
    // исходного кода SimpleAssembler
    var_offset = asm_addr;

    // Второй проход. В этом проходе определяются адреса размещения переменных
    // и адреса переходов.
    for (int i = 0; i < sizeof(asm_str)/sizeof(asm_str[0]); i++)
    {
        // Если не пустая строка ...
        if (strcmp(asm_str[i], "") != 0)
        {
            sscanf(asm_str[i], "%d %d %d %s", &linenum, &strnum, &asm_addr, opr);

            // Если оператор SimpleAssembler READ или WRITE ...
            if ((strcmp(opr, "READ") == 0) || (strcmp(opr, "WRITE") == 0) ||
                    (strcmp(opr, "LOAD") == 0) || (strcmp(opr, "STORE") == 0) ||
                     (strcmp(opr, "ADD") == 0) || (strcmp(opr, "SUB") == 0) ||
                     (strcmp(opr, "DIVIDE") == 0) || (strcmp(opr, "MUL") == 0))
            {
                // Разбиваем промежуточный код SimpleAssembler на составляющие
                sscanf(asm_str[i], "%d %d %d %s %c", &linenum, &strnum, &asm_addr, opr, &ch);
                // Получаем адрес размещения переменной SimpleBasic
                int var_addr = getVarAddr(ch, var_offset);
                // Формируем строку выходного кода SimpleAssembler
                sprintf(asm_str_out[i], "%02d %s %02d%s", asm_addr, opr, var_addr, "\n");
                //Запоминаем будущее содержимое ячейки, введённую через LET
                int d;
                if(sscanf(asm_str[i], "%d %d %d %s %d", &linenum, &strnum, &asm_addr, opr, &d) == 5){
                  if(strcmp(opr,"LOAD")==0){
                    numbers_mas[var_addr] = d;
                  }
                }
            }
            // Если оператор SimpleAssembler JUMP ...
            else if ((strcmp(opr, "JUMP") == 0) || (strcmp(opr, "JNEG") == 0) ||
                     (strcmp(opr, "JNS") == 0) || (strcmp(opr, "JZ") == 0))
            {
                // Разбиваем промежуточный код SimpleAssembler на составляющие
                sscanf(asm_str[i], "%d %d %d %s %d", &linenum, &strnum, &asm_addr, opr, &goto_line);
                // Получаем адрес перехода
                int goto_addr = getGotoAddr(goto_line);
                // Ошибка трансляции, если переход по несуществующему номеру строки SimpleBasic
                if (goto_addr == -1){
                  printf("Translation error 13\n");
                  return -1;
                }
                // Формируем строку выходного кода SimpleAssembler
                sprintf(asm_str_out[i], "%02d %s %02d%s", asm_addr, opr, goto_addr, "\n");
            }
            // Если оператор SimpleAssembler HALT ...
            else if (strcmp(opr, "HALT") == 0)
            {
                // Разбиваем промежуточный код SimpleAssembler на составляющие
                sscanf(asm_str[i], "%d %d %d %s", &linenum, &strnum, &asm_addr, opr);
                // Формируем строку выходного кода SimpleAssembler
                sprintf(asm_str_out[i], "%02d %s%s", asm_addr, opr, " 00\n");
            }
        }
        else // Иначе ...
        {
            // Если область размещения переменных ...
            if (i >= var_offset) {
                //зануляем место для переменных INPUT
                if (getVarName(i, var_offset) != '\0')
                    sprintf(asm_str_out[i], "%02d %c %s", i, '=', "+0000\n");
                //подставляем числа для переменных через LET
                if(numbers_mas[i]!=0){
                    sprintf(asm_str_out[i], "%02d %c +%04X%s", i, '=',numbers_mas[i],"\n");
                }
            }
        }
    }

    // Записываем буфер строк SimpleAssembler в файл
    for (int i = 0; i < sizeof(asm_str)/sizeof(asm_str[0]); i++)
        fwrite (asm_str_out[i], 1 , strlen(asm_str_out[i]), file_sa);
    fclose (file_sa);

    printf("Translation status: OK.\n");

    return 0;

}

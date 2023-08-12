#include "SimpleAssembler.h"
#include "../SimpleComputer/mySimpleComputer.h"

int CommandAnalis(char *command){
  if(strcmp(command,"READ") == 0)return 0x10;
  if(strcmp(command,"WRITE") == 0)return 0x11;
  if(strcmp(command,"LOAD") == 0)return 0x20;
  if(strcmp(command,"STORE") == 0)return 0x21;
  if(strcmp(command,"ADD") == 0)return 0x30;
  if(strcmp(command,"SUB") == 0)return 0x31;
  if(strcmp(command,"DIVIDE") == 0)return 0x32;
  if(strcmp(command,"MUL") == 0)return 0x33;
  if(strcmp(command,"JUMP") == 0)return 0x40;
  if(strcmp(command,"JNEG") == 0)return 0x41;
  if(strcmp(command,"JZ") == 0)return 0x42;
  if(strcmp(command,"HALT") == 0)return 0x43;
  if(strcmp(command,"XOR") == 0)return 0x54;
  if(strcmp(command,"JNS") == 0)return 0x55;
  if(command[0] == '=')return 1;
  return -1;
}

int SimpleAssembler(int argc, char** argv){

  FILE *file_sa, *file_o;
  if( argc != 3)
  {
    printf("Usage: sat file.sa file.o\n ");
    return -1;
  }
  if ((file_sa = fopen (argv[1], "rb" )) <= 0)
  {
    printf("Can`t open '%s' file.\n", argv[1]);
    return -1;
  }
  sc_memoryInit();
  char line[100],ch;
  char strComm[10],operand_str[10], commentline[100] = "\0";
  int value,address,command,operand;
  do
  {
    fgets(line,sizeof(line),file_sa);
    if(feof(file_sa)){
      break;
    }
    if(sscanf(line,"%d %s %s ;%s",&address,strComm,operand_str,commentline)<3)
    {
      printf("Translation error 1\n");
      return -1;
    }
    command = CommandAnalis(strComm);
    printf("%d %d %s\n",address,command,operand_str);
    if(command != -1)
    {
      if(command != 1)
      {
        if(sscanf(operand_str, "%d", &operand) !=1 || sc_commandEncode(command,operand,&value)==-1 || sc_memorySet(address,value)==-1)
        {
          printf("Translation error 2\n");
          return -1;
        }
      }
      else {
        if(sscanf(operand_str, "%c%04X", &ch, &value)!=2){
          printf("Translation error 3\n");
      	  return -1;
      	}
        if(ch == '-'){
          value = -value;
        }
        if(sc_memorySet(address,value)==-1)
        {
          printf("Translation error 4\n");
          return -1;
        }
      }
    }
    else
    {
      printf("Translation error 5\n");
      return -1;
    }
  }
  while(!feof(file_sa));
  fclose
  (file_sa);
  if (sc_memorySave(argv[2]) == -1)
  {
      printf("Can`t create '%s' file.\n", argv[2]);
      return -1;
  }
  printf("Translation status: OK.\n");
  return 0;
}

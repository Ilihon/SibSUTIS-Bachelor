#ifndef OC_COMMAND_EXECUTOR_H
#define OC_COMMAND_EXECUTOR_H

#include "defines.h"

#define CMD_CD "chdir"
//#define CMD_CD "cd"
#define CMD_LS "dir"
//#define CMD_LS "ls"
#define CMD_MV "move"
//#define CMD_MV "mv"
#define CMD_RM "del"
//#define CMD_RM "rm"
#define CMD_EXIT "exit"

int cmd_execute(char *cmd_name, char args[MAX_ARGS][LARGE_BUFFER_SIZE]);

int cmd_cd(char *path);

int cmd_ls(char *path);

int cmd_mv(char *from, char *to);

int cmd_rm(char *path);

#endif //OC_COMMAND_EXECUTOR_H

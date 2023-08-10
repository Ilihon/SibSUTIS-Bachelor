#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "command_executor.h"

int cmd_execute(char *cmd_name, char args[MAX_ARGS][LARGE_BUFFER_SIZE]) {
    int code = 0;
    if (strcmp(CMD_CD, cmd_name) == 0) {
        code = cmd_cd(args[1]);
    } else if (strcmp(CMD_LS, cmd_name) == 0) {
        code = cmd_ls(args[1]);
    } else if (strcmp(CMD_MV, cmd_name) == 0) {
        code = cmd_mv(args[1], args[2]);
    } else if (strcmp(CMD_RM, cmd_name) == 0) {
        code = cmd_rm(args[1]);
    } else if (strcmp(CMD_EXIT, cmd_name) == 0) {
        code = 1;
    }

    return code;
}

int cmd_cd(char *path) {
    return chdir(path);
}

int cmd_ls(char *path) {
    DIR *d;
    struct dirent *dir;

    if (strlen(path) == 0) {
        strcpy(path, ".");
    }

    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            fprintf(stdout, "%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        return 1;
    }

    return 0;
}

int cmd_mv(char *from, char *to) {
    return rename(from, to);
}

int cmd_rm(char *path) {
    return remove(path);
}

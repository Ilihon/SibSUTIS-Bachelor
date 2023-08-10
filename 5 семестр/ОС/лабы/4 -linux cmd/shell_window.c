#include "shell_window.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void start_shell_window(void) {
    char username[SMALL_BUFFER_SIZE];
    char hostname[SMALL_BUFFER_SIZE];
    char cwd[LARGE_BUFFER_SIZE];
    getlogin_r(username, SMALL_BUFFER_SIZE);
    gethostname(hostname, SMALL_BUFFER_SIZE);

    char input[LARGE_BUFFER_SIZE];
    char cmd_name[SMALL_BUFFER_SIZE];
    char all_args[MAX_ARGS][LARGE_BUFFER_SIZE];
    uint args_amount = 0;
    while (1) {
        getcwd(cwd, LARGE_BUFFER_SIZE);
        input_prompt(username, hostname, cwd);
        fgets(input, sizeof(input), stdin);
        parse_input(input, all_args, &args_amount);

        if (args_amount > 0) {
            strcpy(cmd_name, all_args[0]);
            if (cmd_execute(cmd_name, all_args) != 0) {
                break;
            }
        } else {
            break;
        }
    }
}

void input_prompt(char *username, char *hostname, char *cwd) {
    fprintf(stdout, "%s@%s:%s$ ", username, hostname, cwd);
}

int parse_input(char *input_line, char args[MAX_ARGS][LARGE_BUFFER_SIZE], uint *args_amount) {
    *args_amount = 0;
    memset(args, 0, MAX_ARGS * sizeof(args[0]));
    char *arg = strtok(input_line, " \n");
    for (int i = 0; i < MAX_ARGS; ++i) {
        if (arg != NULL) {
            strcpy(args[i], arg);
            ++(*args_amount);
            arg = strtok(NULL, " \n");
        }
    }

    return 0;
}

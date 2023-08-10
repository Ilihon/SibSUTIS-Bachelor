#ifndef OC_SHELL_WINDOW_H
#define OC_SHELL_WINDOW_H

#include "defines.h"
#include "command_executor.h"

void start_shell_window(void);

void input_prompt(char *username, char *hostname, char *cwd);

int parse_input(char *input_line, char args[MAX_ARGS][LARGE_BUFFER_SIZE], uint *args_amount);

#endif //OC_SHELL_WINDOW_H

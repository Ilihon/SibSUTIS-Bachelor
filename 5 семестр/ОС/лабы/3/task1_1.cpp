#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void oldman()
{
    fprintf(stdout, "I`m not yet dead! My ID is %i\n", getpid());
}

void recreation()
{
    fprintf(stdout, "Who I am? My ID is  %i\n", getpid());
}

int main()
{
    pid_t child_pid, parent_pid;
    int i = 0;

    fprintf(stdout, "Before recreation %i\n", parent_pid = (int)getpid());

    child_pid = fork();

    while (i++ < 5) {
        if (child_pid != 0) {
            oldman();
        } else
            recreation();
    }
    return 0;
}
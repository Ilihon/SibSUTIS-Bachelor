#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// ps -ef | grep -P 'UID|a.out'

int main()
{
    pid_t pid;
    switch (pid = fork()) {
    case -1:
        perror("Eror!");
        exit(1);
        break;
    case 0:
        printf("  CHILD: PID - %d\n", getpid());
        printf("  CHILD: PID родителя - %d\n", getppid());
        break;
    default:
        printf("PARENT: PID - %d\n", getpid());
        printf("PARENT: PID потомка %d\n", pid);
        break;
    }
    while (1) {
    }
}

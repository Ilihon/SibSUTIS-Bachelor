#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t child_pid, parent_pid;
    int i = 0;

    FILE* fp;
    fp = fopen("test.dat", "a+");

    child_pid = fork();

    double s = 0;

    if (child_pid != 0) {
        s += 3.14;
        fprintf(stdout,
                "CHILD %i s = %g &s = %u fp = %u\n",
                (int)getpid(), s, &s, fp);
    } else {
        s += 2.72;
        fprintf(stdout,
                "PARENT %i s = %g &s = %u fp = %u\n",
                (int)getpid(), s, &s, fp);
    }
    fclose(fp);
    return 0;
}
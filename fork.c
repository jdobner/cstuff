#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>



char hello[] = "%c %d Hello World!\n";
char me = 'P';

int main(int argc, char const *argv[])
{
    printf("argc=%d arg0=%s\n", argc, argv[0]);

    if (argc > 1) me = 'E';
    printf("%c %d pre-fork\n", me, (int)getpid());
    int f_pid = (int)fork();
    if (f_pid == 0) me = 'C';
    int mp = (int)getpid();

    printf("%c %d post-fork forked=%d\n", me, (int)getpid(), f_pid);
    printf(hello, me, mp);
    printf("%c %d parent pid:%d\n", me, mp, (int)getppid());
    if (me == 'P')
    {
        printf("%c %d waiting for child to terminate\n", me, mp);
        pid_t deadpid = wait(NULL);
        printf("%c %d child %d terminated\n", me, mp, (int)deadpid);
        
    }

    if (me == 'P') 
    {
        execl(argv[0],argv[0], "exec", NULL);
        printf("%c %d exec failed errno: %d\n", me, mp, (int)errno);

    }
    printf("%c %d I will terminate\n", me, mp);

    return 0;
}

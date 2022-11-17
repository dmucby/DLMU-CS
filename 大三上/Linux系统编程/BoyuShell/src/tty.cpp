#include "stdio.h"
#include "unistd.h"
#define MY_STDIN 0
#define MY_STDOUT 1
#define MY_STDERR 2

/* 查看 当前终端 */
int main(int argc, char *argv[])
{
    if (isatty(MY_STDOUT))
    {
        puts(ttyname(MY_STDOUT)); // print absolute path of tty
    }
    else
    {
        puts("run error!");
        return -1;
    }
    return 0;
}

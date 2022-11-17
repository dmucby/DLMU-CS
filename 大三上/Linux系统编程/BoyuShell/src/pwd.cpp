#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

/* 很 easy!*/
int main()
{
    char *path = NULL;
    path = getcwd(NULL, 0);
    printf("%s", path);
    printf("\n");
    free(path);
    return 0;
}

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if(argc <= 1){
        printf("\n");
    } 

    for (size_t i = 1; i < argc; i++){
        printf("%s ",argv[i]);
    }

    printf("\n");

    return 0;
}

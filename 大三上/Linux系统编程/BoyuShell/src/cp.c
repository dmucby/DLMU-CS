#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
 
#define BUFFERSIZE 4096
#define COPYMOOE 0644
int main(int argc, char *argv[])
{
    int in_file, out_file, n_char;
    char buf[BUFFERSIZE];
 
    if(argc != 3){
        fprintf(stderr, "usage: %s source destination\n", *argv);
        exit(1);
    } 
    if((in_file = open(argv[1], O_RDONLY)) == -1){
        printf("Cannot creat file\n");
        exit(1);
    }
    if((out_file = creat(argv[2], COPYMOOE)) == -1){
        printf("Cannot copy file\n");
        exit(1);
    }
    while((n_char = read(in_file, buf, BUFFERSIZE)) > 0){
        if(write(out_file, buf, sizeof(buf)) != n_char){
           printf("Write error \n");
           exit(1);
        }
    }
    if(n_char == -1){
        printf("Read error \n");
        exit(1);
    }
    if(close(in_file) == -1||close(out_file) == -1){
        printf("Error closing files\n");
        exit(1);
    }
    return 0;
}
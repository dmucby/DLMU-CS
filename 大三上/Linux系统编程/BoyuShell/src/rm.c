#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
    int rt;
    if(argc < 2){
    	printf("use error!\n");
        exit(2);
    }
    else{
        for(int i = 1; i <= argc; i++){
            if((rt = unlink(argv[i])) != 0){
                printf("remoove error\n");
                exit(3);
            }
        }
    }
    return 0;
}

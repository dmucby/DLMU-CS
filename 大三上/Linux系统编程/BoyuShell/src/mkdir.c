#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<libgen.h>
#include<string.h>

#define MAXSIZE 100
void create(char *dir) {
    int i,len;
    char str[512];    
    strncpy(str, dir, 512);
    len=strlen(str);
    for( i=0; i<len; i++ ){
        if( str[i]=='/' ){
            str[i] = '\0';
            if( access(str,0)!=0 ){
               if(mkdir(str, 0777) == -1){
		printf("mkdir error 1\n");
		exit(1);
		}
            }
            str[i]='/';
        }
    	if( len>0 && access(str,0)!=0 ){
        	if(mkdir(str, 0777) == -1){
			printf("mkdir error 2\n");
			exit(1);
		}
    	}
    //return;
   }
}
int main(int argc, char *argv[]){
	if(argc <= 1){
		printf("error\n");
		exit(1);
	}
	while(--argc){
		argv++;
		create(*argv);
	}
	
}
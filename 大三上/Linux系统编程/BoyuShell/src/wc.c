#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <string.h>

/* 统计三个字符 */

int charCount(char *fname)
{
    FILE *fp;
    if((fp=fopen(fname,"r"))==NULL)
    {
        printf("open file error!\n");
        exit(0);
    }
    char ch;
    int cCount=0;
    while(!feof(fp))
    {
        ch=fgetc(fp);
        //printf("%c ",ch);
        if(ch!=EOF){
        	//printf("%c ",ch);
        	cCount++;
        }
    }
    fclose(fp);
    return cCount-1; // delete last '\n' char 
}
int wordCount(char *fname)
{
    FILE *fp;
    if((fp=fopen(fname,"r"))==NULL)
    {
        printf("open file error!\n");
        exit(0);
    }
    char ch;
    int wcount=0;
    while(!feof(fp))
    {
    	ch = fgetc(fp);
    	if(ch==' '||ch=='\n'||ch=='\r'||ch=='\t'){
    		wcount++;
    	}
    }
    fclose(fp);
    return wcount;
}
int lineCount(char *fname){
    FILE *fp;
    if((fp=fopen(fname,"r"))==NULL){
        printf("open file error!\n");
        exit(0);
    }
    char ch;
    int flag=1;
    int lcount=1;
    while(!feof(fp)){
    	ch = fgetc(fp);
    	if(flag){
    		if(ch==EOF) lcount = 0;
    		flag = 0;
    	}
    	if(ch == '\n'){
    		lcount++;
    	} 
    }
    fclose(fp);
    return lcount-1;// delete last '\n' 
}
int main(int argc,char *argv[]){
	if(argc<=1){
		printf("use error!\n");
		return -1;
	}
    printf("the file is:%s\n",argv[1]);
	printf("the number of chars:%d\n",charCount(argv[1]));
	printf("the number of words:%d\n",wordCount(argv[1]));
	printf("the number of lines:%d\n",lineCount(argv[1]));
		
}


#include <stdio.h>  

/* 打印当前文件 */

void copy(FILE * file1,FILE * file2);
int main(int argc,char *argv[])  
{  
    FILE * fp;  
    if(argc == 1)  
        copy(stdin,stdout);  
    else  
        while(--argc > 0)  
        {  
            if((fp = fopen(*++argv,"r")) == NULL)  
            {  
                printf("cat: %s: No such file or directory\n",*argv);  
                return 1;  
            }  
            else  
            {  
                copy(fp,stdout);  
                fclose(fp);  
            }  
        }  
    return 0;  
} 
void copy(FILE * file1,FILE * file2)  
{  
    int c;
    while((c = getc(file1)) != EOF)  
    {  
        putc(c,file2);  
    }  
}
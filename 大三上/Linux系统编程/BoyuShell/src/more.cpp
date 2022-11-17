#include<stdio.h>
#include<stdlib.h>
#define PAGELEN 20
#define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);

/**
 * @brief more操作
 * 三个基本操作：q 停止； 空格 翻页；d 返回一行内容
 * @param argc 
 * @param argv 
 * @return int 
 */
int main (int argc, char *argv[])
{    
    FILE *fp;
    
    if ( argc == 1)
        do_more(stdin); //如果没有第2个参数 从标准输入获取内容
    else 
    {
        while(--argc){
            if ( (fp = fopen(* ++argv, "r")) != NULL ){  //打开文件
                do_more(fp);
                fclose(fp);
            } else {
                exit(1);
            }
        }
    }
    return 0;
    
}

void do_more(FILE *fp)
{
    //定义变量
    char line[LINELEN];
    int num_of_lines = 0;
    int reply;
    FILE *fp_tty;
   
    fp_tty = fopen("/dev/tty","r"); // 打开/dev/tty设备文件 键盘与显示设备的描述文件），读取键
        
    while (fgets(line,LINELEN,fp)){
        
        if (num_of_lines == PAGELEN){ 
            reply = see_more(fp_tty);
            
            if (reply == 0)
                break;
            
            
            num_of_lines -= reply;
        }
        

        if (fputs(line,stdout) == EOF){
            exit(1);
        }
        num_of_lines++;
    }
}

/**
 * @brief 
 * 空格 再看一行
 * @param cmd 
 * @return int 
 */
int see_more(FILE *cmd)
{
    int c;

    printf("\033[7m more? \033[m");
    while( (c = getc(cmd)) != EOF)
    {
        if ( c == 'q')
            return 0;
        else if ( c == ' ')
            return PAGELEN; //空格返回PAGELEN行
        else if ( c == 'd' )  
            return 1;  //只返回一行
    }
    
    return 0;
 
            
}

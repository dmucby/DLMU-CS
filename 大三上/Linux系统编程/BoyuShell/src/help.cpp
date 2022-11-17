#include<stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
    if(argc==2)
    {
        if(strcmp(argv[1],"ls")==0)
        {
            printf("ls [-l] [路径]：用来显示目标目录列表\n");
            printf("\t[路径]：显示目标目录下文件名\n");
            printf("\t-l[路径]：显示目标目录下文件的详细信息\n");

        }
        else if(strcmp(argv[1],"cat")==0)
        {
            printf("cat [路径]：用来显示文件的内容\n");
            //printf("\t[路径]：显示指定文件的内容\n");
            //pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
        }
        else if(strcmp(argv[1],"mkdir")==0)
        {
            printf("mkdir [路径]：创建指定路径的文件夹，可创建多级目录\n");
            //printf("\t[路径]：创建指定路径的文件夹，可创建多级目录\n");
            //pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
        }
        else if(strcmp(argv[1],"rm")==0)
        {
            printf("rm：用来删除一个文件\n");
            printf("\trm[路径]：删除指定路径的文件\n");
            //pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
        }
        else if(strcmp(argv[1],"wc")==0)
        {
            printf("wc [路径]：用来统计一个文件的行数，字符数和单词\n");
            //pritnf("\t[路径]：显示目标目录下的非隐藏文件名\n");
            //pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
        }
        else if(strcmp(argv[1],"pwd")==0)
        {
            printf("pwd：用来显示当前工作路径\n");
            //pritnf("\t[路径]：显示目标目录下的非隐藏文件名\n");
            //pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
        }
        else if(strcmp(argv[1],"echo")==0)
        {
            printf("echo [字符串]：用来直接输出指定的字符串\n");
            printf("\t[字符串]：直接打印出指定的字符串\n");
           // pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
        }
        else if(strcmp(argv[1],"cd")==0)
        {
            printf("cd [路径]：用来切换工作目录\n");
            printf("\tcd[路径]：切换到指定路径\n");
            printf("\t~：切换到home目录\n");
        }
	 else if(strcmp(argv[1],"cp")==0)
        {
            printf("cp [路径1] [路径2]：用来对文件进行复制\n");
            printf("\t[路径1]：要复制的指定路径文件\n");
            printf("\t[路径2]：拷贝后的文件\n");
        }

        else if(strcmp(argv[1],"tty")==0)
        {
            printf("tty: 显示终端机连接标准输入设备的文件名称。\n");
            //pritnf("\t[路径]：显示目标目录下的非隐藏文件名\n");
            //pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
        }
        else if(strcmp(argv[1],"ps")==0)
        {
            printf("ps：显示当前进程的状态\n");
            //pritnf("\t[路径]：显示目标目录下的非隐藏文件名\n");
            //pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
        }
        else if(strcmp(argv[1],"exit")==0)
        {
            printf("exit:退出系统\n");
            //pritnf("\t[路径]：显示目标目录下的非隐藏文件名\n");
            //pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
        }

        else if(strcmp(argv[1],"more")==0)
        {
            printf("more[路径]：使目标文件逐页/逐行显示。按d键就往下显示20行，按回车键就往下显示1行，按 q 键就会退出。\n");
            //pritnf("\t[路径]：显示目标目录下的非隐藏文件名\n");
            //pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
            
        }
        else if(strcmp(argv[1],"rmdir")==0)
        {
            printf("rmdir[路径]：删除指定路径的文件夹\n");
            //pritnf("\t[路径]：显示目标目录下的非隐藏文件名\n");
            //pritnf("\t-l[路径]：显示目标目录下文件的详细信息\n");
            
        }
         else
       {
        printf("No such command!\n");   
       }
    }
    else
    {
        printf("No such command!\n");   
    }
    
    return 0;
    
}

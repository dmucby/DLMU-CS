#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"
#include "netdb.h"
#include "sys/types.h"
#include "pthread.h"
#include "unistd.h"
#include "dirent.h"

/* 打印进程树 */

//global variable
typedef struct file_info
{
    int pid;
    int ppid;
    char name[1024];
    int flag;
    int gen;
} info; //file struct of "/proc/pid/stat"

void show_info(info *file, int count, int ppid, int gen);
int is_digit(char p_name[]);
void pstree();

int main()
{
    pstree();
    return 0;
}

void pstree(){
    int i, total, count = 0, t;
    char str[1024], dir[1024];
    struct dirent **namelist;
    strcpy(dir, "/proc/");
    total = scandir(dir, &namelist, 0, alphasort);
    printf("path=%s,total=%d\n", dir, total);
    for (i = 0; i < total; i++)
    {
        strcpy(str, namelist[i]->d_name);
        if (is_digit(str) == 0)
            count++;
    }
    printf("process counts:%d\n", count);
    info file[1024];
    i = 0;
    t = 0;
    while (i < total)
    {
        FILE *fp;
        char path[1024];
		char state; //unused
        strcpy(str, namelist[i]->d_name);
        strcpy(path, "/proc/");
        if (is_digit(str) == 0)
        {
            strcat(path, str);
            strcat(path, "/stat");
            fp = fopen(path, "r");
            while (4 == fscanf(fp, "%d %s %c %d\n", &(file[t].pid), file[t].name, &state, &(file[t].ppid)))
	    {
		break;
	    }
            fclose(fp);
            t++;
        }
        i++;
    }
    memset(&file->flag, 0, count);
    memset(&file->gen, 0, count);
    show_info(file, count, 0, 0);
}

void show_info(info *file, int count, int ppid, int gen)
{
    int i, j, k;
    for (i = 0; i < count; i++)
    {
        if (file[i].flag == 0 && file[i].ppid == ppid)
        {
            file[i].gen = gen + 1;
            file[i].flag = 1;
            for (k = 0; k < gen; k++)
                printf("\t");
            printf("[%d]%s\n", file[i].pid, file[i].name);
            show_info(file, count, file[i].pid, file[i].gen);
        }
    }
}

int is_digit(char p_name[])
{
    int i, len;
    len = strlen(p_name);
    if (len == 0)
        return -1;
    for (i = 0; i < len; i++)
        if (p_name[i] < '0' || p_name[i] > '9')
            return -1;
    return 0;
}


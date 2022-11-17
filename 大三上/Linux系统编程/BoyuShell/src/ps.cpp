#include "stdio.h"
#include "unistd.h"
#include "sys/stat.h"
#include "string.h"
#include "stdlib.h"
#include "sys/types.h"
#include "dirent.h"
#include "pwd.h"
#include "assert.h"
#include "iostream"
#define MAX_LEN 20
using namespace std;
//options
/* 可以的玩法 玩法比较多*/
/* 代码有点小bug*/
enum OPTION
{
    OPT_a,
    OPT_A,
    OPT_f,
    OPT_u,
    OPT_NUM
};

int g_option[OPT_NUM]; //map of ps options
typedef struct ps_info
{
    char cmd[MAX_LEN];
    char user[MAX_LEN];
    int pid;
    int ppid;
    char state;
    struct ps_info *next;
} pi;

struct ps_info *trav_dir(char dir[]);
void ps(int pnum, char **param);
int read_info(char d_name[], struct ps_info *p1);
void print_detail(pi *list, char *tty);
void show_info(struct ps_info *head);
int is_digit(char *);
void resolve_uid(uid_t uid, struct ps_info *p1);
void get_tty(int pid, char *tty);
void get_option(const char *strOption);

int main(int argc, char **argv)
{
    ps(argc, argv);
    return 0;
}

void ps(int pnum, char **param)
{
    memset(g_option, 0, sizeof(int) * OPT_NUM);
    while (--pnum != 0)
    {
        if ('-' == param[pnum][0])
        {
            get_option(param[pnum]);
        }
        else
        {
            printf("ps: unreached option!\n");
            exit(0);
        }
    }
    pi *head, *link;
    head = trav_dir((char *)"/proc/");
    if (head == NULL)
        printf("traverse dir error\n");
    show_info(head);
    while (head != NULL)
    {
        link = head;
        head = head->next;
        free(link);
    }
}

pi *trav_dir(char dir[])
{
    DIR *dir_ptr;
    pi *head, *p1, *p2;
    struct dirent *direntp;
    struct stat infobuf;

    if ((dir_ptr = opendir(dir)) == NULL)
        fprintf(stderr, "cannot open directory %s\n.", dir);
    else
    {
        head = p1 = p2 = (struct ps_info *)malloc(sizeof(struct ps_info));
        while ((direntp = readdir(dir_ptr)) != NULL) //traverse all process under directory "/proc"
        {
            if ((is_digit(direntp->d_name)) == 0)
            {
                if (p1 == NULL)
                {
                    printf("malloc error!\n");
                    exit(0);
                }

                if (read_info(direntp->d_name, p1) != 0) //obtain the information of process
                {
                    printf("info read error\n");
                    exit(0);
                }
                p2->next = p1;
                p2 = p1;
                p1 = (struct ps_info *)malloc(sizeof(struct ps_info));
            }
        }
    }
    p2->next = NULL;
    return head;
}

int read_info(char d_name[], struct ps_info *p1)
{
    FILE *fd;
    char dir[20];
    struct stat infobuf;

    sprintf(dir, "%s/%s", "/proc/", d_name);
    chdir("/proc"); //switch to directory "/proc", or stat will return -1.
    if (stat(d_name, &infobuf) == -1) //get process USER
        fprintf(stderr, "stat error %s\n", d_name);
    else
        resolve_uid(infobuf.st_uid, p1);

    chdir(dir); //switch to directory "/proc/pid"
    if ((fd = fopen("stat", "r")) < 0)
    {
        printf("file open error!\n");
        exit(0);
    }
    while (4 == fscanf(fd, "%d %s %c %d\n", &(p1->pid), p1->cmd, &(p1->state), &(p1->ppid)))
    {
        break;
    }
    fclose(fd);
    return 0;
}

void resolve_uid(uid_t uid, struct ps_info *p1) //get username from uid
{
    struct passwd *getpwuid(uid_t uid), *pw_ptr;
    static char numstr[10];

    if ((pw_ptr = getpwuid(uid)) == NULL)
    {
        sprintf(numstr, "%d", uid);
        strcpy(p1->user, numstr);
    }
    else
        strcpy(p1->user, pw_ptr->pw_name);
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

void print_detail(pi *list, char *tty)
{
    if (g_option[OPT_u] && !g_option[OPT_f])
        cout << list->user << "\t\t";
    cout << list->pid << "\t";
    if (g_option[OPT_f])
        cout << list->ppid << "\t";
    cout << tty << "\t";
    if (g_option[OPT_u])
        cout << list->state << "\t";
    cout << list->cmd << endl;
}

void show_info(struct ps_info *head)
{
    pi *list;
    char headline[35];
    if (g_option[OPT_u] && !g_option[OPT_f])
        strcat(headline, "UID\t\t");
    strcat(headline, "PID\t");
    if (g_option[OPT_f])
        strcat(headline, "PPID\t");
    strcat(headline, "TTY\t");
    if (g_option[OPT_u])
        strcat(headline, "STAT\t");
    strcat(headline, "CMD\n");
    printf("%s", headline);
    for (list = head; list != NULL; list = list->next)
    {
        char ctty[32];
        get_tty(getpid(), ctty);
        char tty[32];
        get_tty(list->pid, tty);
        if (!g_option[OPT_a] && !g_option[OPT_A] && !g_option[OPT_u] && strcmp(tty, ctty) == 0)
        {
            print_detail(list, tty);
        }
        if (g_option[OPT_a] || g_option[OPT_u])
        {
            if (strcmp(tty, "?") != 0)
                print_detail(list, tty);
        }
        if (g_option[OPT_A])
        {
            print_detail(list, tty);
        }
    }
}

void get_option(const char *strOption)
{
    assert(strOption);
    while (*(++strOption) != '\0')
    {
        if (*strOption == 'a')
            g_option[OPT_a] = 1;
        else if (*strOption == 'A')
            g_option[OPT_A] = 1;
        else if (*strOption == 'f')
            g_option[OPT_f] = 1;
        else if (*strOption == 'u')
            g_option[OPT_u] = 1;
        else
        {
            printf("unreached option!\n");
            exit(0);
        }
    }
}

void get_tty(int pid, char *tty) //get tty of process by uid
{
    char file[32]{0}, buf[32] = {0};
    sprintf(file, "/proc/%d/fd/0", pid);
    if (-1 == readlink(file, buf, 32))
    {
        strcpy(tty, "?");
    }
    else if (0 != strncmp(buf, "/dev/", 5) || 0 == strncmp(buf, "/dev/null", 9))
    {
        strcpy(tty, "?");
    }
    else
    {
        strcpy(tty, buf + 5);
    }
}

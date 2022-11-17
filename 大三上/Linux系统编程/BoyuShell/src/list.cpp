#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
using namespace std;

//options
enum OPTION
{
    OPT_l,
    OPT_A,
    OPT_r,
    OPT_q,
    OPT_i,
    OPT_R,
    OPT_NUM
};

int g_option[OPT_NUM]; //map of ls options
vector<string> g_dirPath;
int dirFd; //the file descriptor  associated with the directory

void list(int pnum, char **param);
void get_option(const char *strOption);
void get_path(const char *strPath);
void exec_ls_task(const char *path);
void get_filestate(const string &filename, struct stat *p);
void show_info(const struct stat &filestat, const string &name);
void get_filemode(mode_t mode, char *str);
char *resolve_uid(uid_t uid);
char *resolve_gid(gid_t gid);

int main(int argc, char **argv)
{
    list(argc, argv);
    return 0;
}

void list(int pnum, char **param)
{
    memset(g_option, 0, sizeof(int) * OPT_NUM);
    //handle option
    while (--pnum != 0)
    {
        if ('-' == param[pnum][0])
        {
            get_option(param[pnum]);
        }
        else
        {
            get_path(param[pnum]);
        }
    }

    if (g_dirPath.empty())
    {
        exec_ls_task(".");
    }
    else
    {
        for (auto it = g_dirPath.begin(); it != g_dirPath.end();)
        {
            printf("%s:\n", it->c_str());
            exec_ls_task(it->c_str());
            if (++it != g_dirPath.end())
            {
                printf("\n");
            }
        }
    }
}

void get_option(const char *strOption)
{
    assert(strOption);
    while (*(++strOption) != '\0')
    {
        if (*strOption == 'a')
            g_option[OPT_A] = 1;
        else if (*strOption == 'A')
            g_option[OPT_A] = 1;
        else if (*strOption == 'l')
            g_option[OPT_l] = 1;
        else if (*strOption == 'i')
            g_option[OPT_i] = 1;
        else if (*strOption == 'r')
            g_option[OPT_r] = 1;
        else if (*strOption == 'q')
            g_option[OPT_q] = 1;
        else if (*strOption == 'R')
            g_option[OPT_R] = 1;
        else
        {
            fprintf(stderr, "ls: unreached option!\n");
            exit(0);
        }
    }
}

void get_path(const char *strPath)
{
    assert(strPath);
    g_dirPath.push_back(strPath);
}

void exec_ls_task(const char *path)
{
    assert(path);
    DIR *p_dir;
    struct dirent *p_next;
    vector<string> list;

    if ((p_dir = opendir(path)) == NULL)
    {
        perror("invalid directory.");
        exit(1);
    }

    if ((dirFd = dirfd(p_dir)) == -1)
    {
        perror("invalid parameter.");
        exit(0);
    }

    while ((p_next = readdir(p_dir)) != NULL)
    {
        //handle option -a, with "." and ".." and invisible files(".XXX")
        if (strcmp(p_next->d_name, ".") == 0 || strcmp(p_next->d_name, "..") == 0 || p_next->d_name[0] == '.')
        {
            if (g_option[OPT_A] == 0)
                continue;
        }
        list.push_back(p_next->d_name);
    }

    if (g_option[OPT_r])
    {
        sort(list.rbegin(), list.rend());
    }
    else if (g_option[OPT_q] == 0)
    {
        sort(list.begin(), list.end());
    }

    for (auto w : list)
    {
        struct stat fsTemp;
        get_filestate(w, &fsTemp);
        show_info(fsTemp, w);
    }
    if (!g_option[OPT_l])
        printf("\n");
    if (closedir(p_dir) != 0)
    {
        perror("cannot close directory.");
        exit(1);
    }
}

void get_filestate(const string &filename, struct stat *p)
{
    assert(p);
    if (fstatat(dirFd, filename.c_str(), p, AT_SYMLINK_NOFOLLOW) == -1)
    {
        perror("cannot fetch file state.");
        exit(0);
    }
}

void show_info(const struct stat &filestat, const string &name)
{
    if (g_option[OPT_i])
    {
        printf("%ld ", filestat.st_ino);
    }

    if (g_option[OPT_l])
    {
        char buf[11];
        get_filemode(filestat.st_mode, buf);
        printf("%s ", buf);
        printf("%4ld ", filestat.st_nlink);
        printf("%-8s ", resolve_uid(filestat.st_uid));
        printf("%-8s ", resolve_gid(filestat.st_gid));
        printf("%8ld ", filestat.st_size);
        printf("%.12s ", 4 + ctime(&filestat.st_mtime));
        printf("%s\n", name.c_str());
    }
    else
    {
        printf("%s\t", name.c_str());
    }
}

void get_filemode(mode_t mode, char *str)
{
    assert(str);
    strcpy(str, "----------");
    if (S_ISDIR(mode))
        str[0] = 'd';
    if (S_ISCHR(mode))
        str[0] = 'c';
    if (S_ISBLK(mode))
        str[0] = 'b';
    if (S_ISFIFO(mode))
        str[0] = 'p';
    if (S_ISLNK(mode))
        str[0] = 'l';
    if (S_ISSOCK(mode))
        str[0] = 's';

    if (S_IRUSR & mode)
        str[1] = 'r';
    if (S_IWUSR & mode)
        str[2] = 'w';
    if (S_IXUSR & mode)
        str[3] = 'x';

    if (S_IRGRP & mode)
        str[4] = 'r';
    if (S_IWGRP & mode)
        str[5] = 'w';
    if (S_IXGRP & mode)
        str[6] = 'x';

    if (S_IROTH & mode)
        str[7] = 'r';
    if (S_IWOTH & mode)
        str[8] = 'w';
    if (S_IXOTH & mode)
        str[9] = 'x';
}

char *resolve_uid(uid_t uid)
{
    struct passwd *pw_ptr;
    static char numstr[10];

    if ((pw_ptr = getpwuid(uid)) == NULL)
    {
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    else
    {
        return pw_ptr->pw_name;
    }
}

char *resolve_gid(gid_t gid)
{
    struct group *grp_ptr;
    static char numstr[10];

    if ((grp_ptr = getgrgid(gid)) == NULL)
    {
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else
    {
        return grp_ptr->gr_name;
    }
}

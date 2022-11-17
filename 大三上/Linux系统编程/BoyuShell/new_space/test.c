#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "sys/wait.h"
#include "stdlib.h"
#include "errno.h"
#include "signal.h"
#define BUF_SIZE 256

enum {
	RESULT_NORMAL,
	ERROR_FORK,
	ERROR_COMMAND,
	ERROR_WRONG_PARAMETER,
	ERROR_MISS_PARAMETER,
	ERROR_TOO_MANY_PARAMETER,
	ERROR_CD,

	ERROR_MANY_IN,
	ERROR_MANY_OUT,
	ERROR_FILE_NOT_EXIST,
	
	ERROR_PIPE,
	ERROR_PIPE_MISS_PARAMETER
};

char workingspace[BUF_SIZE] = "/root/OS/CSAPP/reference/refe2/sourcecode/obj/";
char command[BUF_SIZE];
char param[BUF_SIZE][BUF_SIZE];

int split(char command[BUF_SIZE]);
int syscall(int plen);
int syscall_with_pipe(int left, int right);
int syscall_with_redirect(int left, int right);

int cd(int plen);
int getkey(char* command, char* execute);
void print_status_info(int res);
void safe_flush(FILE *fp)
{
    int ch;
    while ((ch = fgetc(fp)) != EOF && ch != '\n')
        ;
}

int main()
{
    signal(SIGINT,SIG_IGN);
	chdir("./new_space");
    while (1)
    {
		int res;
        printf("\033[32mBoyuShell@Linux:\033[34m%s\033[0m$ ", getcwd(NULL, 0));
        scanf("%[^\n]", command);
		int len = strlen(command);
		if (len != BUF_SIZE) {
			command[len] = '\0';
		}
        int plen = split(command);
		if (strcmp(param[0], "cd") == 0)
        {
            res = cd(plen);
        }
        else if (strcmp(param[0], "exit") == 0 || strcmp(param[0], "quit") == 0)
        {
            printf("Boyu shell shut down\n");
            exit(0);
        }
        else if (strcmp(param[0], "clear") == 0)
        {
            system("clear");
        }
        else
        {
			char key[BUF_SIZE];
			if(res = getkey(param[0], key) == RESULT_NORMAL)
				res = syscall(plen);
			else {
				printf("Command '%s' not found!\n", command);
			}
        }
		print_status_info(res);
        safe_flush(stdin);
    }
    return 0;
}

/**
 * @brief 切分 
 * 按空格分开
 * @param command 
 * @return int 
 */
int split(char command[BUF_SIZE])
{
    int num = 0;
	int i, j;
	int len = strlen(command);
	for (i=0, j=0; i<len; ++i) {
		if (command[i] != ' ') {
			param[num][j++] = command[i];
		} else {
			if (j != 0) {
				param[num][j] = '\0';
				++num;
				j = 0;
			}
		}
	}
	if (j != 0) {
		param[num][j] = '\0';
		++num;
	}
	return num;
}

int syscall(int plen){
	int pid = fork();
	if(pid == -1) return ERROR_FORK;
	else if(pid == 0){
		// dup 复制文件描述符
		int fdin = dup(STDIN_FILENO);
		int fdout = dup(STDOUT_FILENO);
		int res = syscall_with_pipe(0, plen);
		// 打开文件描述符
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		exit(res);
	} else {
		int status;
		waitpid(pid, &status, 0);
		return WEXITSTATUS(status);
	}
}

// 0，命令个数
int syscall_with_pipe(int left, int right){
	if(left >= right) return RESULT_NORMAL;

	// 是否使用管道 记录管道位置
	int pipeIndex = -1;
	for(int i = left; i < right; ++i){
		if(strcmp(param[i], "|") == 0){
			pipeIndex = i;
			break;
		}
	}

	// 没有使用管道
	// 是否使用了重定向
	if(pipeIndex == -1) 
		return syscall_with_redirect(left, right);
	// 如果使用管道错误 类似 cat xx.txt |
	else if (pipeIndex + 1 == right)
		return ERROR_PIPE_MISS_PARAMETER;

	int fd[2];

	// 管道初始化错误
	if(pipe(fd) == -1) return ERROR_PIPE;

	int res = RESULT_NORMAL;
	int pid = vfork();
	if(pid == -1) res = ERROR_FORK;
	// 子进程管道写
	else if(pid == 0){
		// 关闭 读端 
		close(fd[0]);
		// 写端对应输出文件符
		dup2(fd[1], STDOUT_FILENO);
		// 关闭写端
		close(fd[1]);
		// 在命令和管道之间是否使用了重定向
		res = syscall_with_redirect(left, pipeIndex);
		exit(res);
	} else {
		int status;
		waitpid(pid, &status, 0);
		int exitcode = WEXITSTATUS(status);

		if(exitcode != RESULT_NORMAL){
			// todo
			res = exitcode;
		} else if (pipeIndex + 1 < right){
			// 父进程管道读
			close(fd[1]);
			// 读端 对应标准输入
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			// 递归多管道
			res = syscall_with_pipe(pipeIndex + 1, right);
		}
	}
	return res;// 返回码
}

// 重定向支持
int syscall_with_redirect(int left, int right){
	int inIndex = 0, outIndex = 0;
	// 重定向文件描述符
	char *inFilename = NULL, *outFilename = NULL;
	int endIndex = right;
	for(int i = left; i < right; i++){
		// 重定向输入文件
		if(strcmp(param[i], "<") == 0){
			inIndex++;
			// 如果命令还没截止
			if(i+1 < right) inFilename = param[i+1]; // 输入文件指向下一个文件参数
			else return ERROR_MISS_PARAMETER;
			if(endIndex == right) endIndex = i;
		} else if(strcmp(param[i], ">") == 0){
			// 如果是输出重定向
			outIndex++;
			if(i+1 < right) outFilename = param[i+1];
			else return ERROR_MISS_PARAMETER;
			if(endIndex == right) endIndex = i;
		}
	}
	if(inIndex > 1) return ERROR_MANY_IN; //目前只支持一个
	if(outIndex > 1) return ERROR_MANY_OUT; // 只支持一个

	int res = RESULT_NORMAL;
	int pid = vfork();
	if(pid == -1) res = ERROR_FORK;
	else if(pid == 0){
		// 子进程中进行读写
		if(inIndex == 1) freopen(inFilename, "r", stdin);
		if(outIndex == 1) freopen(outFilename, "w", stdout);
		
		char *commands[BUF_SIZE];
		// 遍历每个参数
		for (int i = left; i < endIndex; i++)
			commands[i] = param[i];
		// 这个NULL是重点
		commands[endIndex] = NULL;

		char key[BUF_SIZE];
		// 开始查找命令
		getkey(commands[left], key);
		//执行命令
		execvp(key, commands + left);
		exit(errno);
	} else {
		int status;
		waitpid(pid, &status, 0);
		int err = WEXITSTATUS(status);
		if(err) printf("\e[31;1mError: %s\n\e[0m", strerror(err));
	}
	return res;
}

int cd(int plen)
{
	int res = RESULT_NORMAL;
    if(plen > 2) res = ERROR_TOO_MANY_PARAMETER;
    else if(plen == 1) chdir("~");
    else {
		int ret = chdir(param[1]);
		if(ret) res = ERROR_CD;
	}
	return res;
}

int getkey(char* command, char* execute){
	char cmdlist[BUF_SIZE][BUF_SIZE] = {"ls","pwd","tty","ps","pstree", "more", "cp", "mkdir", "rm",
						"rmdir", "ipconfig", "ping", "cat", "touch","wc","help","echo","wc"};
	int cmdCnt = 19;
	for(int i = 0; i < cmdCnt; i++){
		if (strcmp(command, cmdlist[i]) == 0)
		{
		    strcpy(execute,workingspace);
			strcat(execute,cmdlist[i]);
			return RESULT_NORMAL;
		}
	}
	return ERROR_COMMAND;
}

void print_status_info(int res){
	switch(res){
		case ERROR_COMMAND:
			printf("No such command.\n");
			break;
		case ERROR_WRONG_PARAMETER:
			printf("No such arguement about this command.\n");
			break;
		case ERROR_MISS_PARAMETER:
			printf("Too few arguements you have given.\n");
			break;
		case ERROR_TOO_MANY_PARAMETER:
			printf("Too many arguements you have given.\n");
			break;
		case ERROR_CD:
			printf("No such directory or no root.\n");
			break;
		case ERROR_MANY_IN:
		case ERROR_MANY_OUT:
			printf("Only 1 input file or 1 output file are needed.Too many arguments you have given.\n");
			break;
		case ERROR_FILE_NOT_EXIST:
			printf("No such file.\n");
			break;
		case ERROR_PIPE:
			printf("Pipe open failed.\n");
			break;
		case ERROR_PIPE_MISS_PARAMETER:
			printf("Too few arguments to generate a pipe.\n");
			break;
	}
}
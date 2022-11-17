#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


/* 以open 形式生成文件 */
int main(int argc,char *argv[])
{

	int fd;
	fd=open(argv[1],O_CREAT|O_RDWR,0777);
	if(fd<0)
	{
		printf("cread %s file fail\n",argv[1]);
		return -1;

	}
	close(fd);
	return 0;	
}
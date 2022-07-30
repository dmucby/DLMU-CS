#include <stdio.h>
#include <ctype.h>
#include <string.h>

extern int TESTScan();

void main(int argc, char const *argv[])
{
	int es = 0;

	// 词法分析
	es = TESTScan();

	if (es > 0)
	{
		printf("词法分析出错！\n");
	}
	else{
		printf("词法分析成功！\n");
	}

	return;
}
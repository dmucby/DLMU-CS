#include <stdio.h>
#include <ctype.h>
#include <string.h>

// 以下定义独立为一个文件 .h
# define keywordSum 30

// 定义保留字 注意保留字对大小写不敏感
char *keyword[keywordSum] = {
	"if","else","for","while","do","int","read",
	"write","switch","case","break","default",
	"void","return","function","IF","ELSE","FOR","WHILE",
	"DO","INT","READ","WRITE","SWITCH","CASE","BREAK",
	"DEFAULT","VOID","RETURN","FUNCTION"
};

// 定义单分节符
char singleWord[50] = "+—*/^():;,><{}![]\'\"";

// 定义双分节符的首字符
char doubleWord[10] = "><=!&|\\";

// 错误数量
int errorNum;

// 程序行数
int line = 1;

// 接收文件路径
char scanIn[300],scanOut[300];

// 输入和输出文件
FILE *fin,*fout;

void printStart(){
	printf("=======================================================\n");
	printf("================Lexical analysis Start!================\n");
}

void printError(){
	printf("=======================Error Code======================\n");
	printf("Code 1:Can't find the input file!\n");
	printf("Code 2:Can't find the output file!\n");
	printf("Code 3:The Lexical Error!\nPlease read the output file!\n");
	printf("=======================================================\n");
}

/**
 * 判断是否为字符
 * @parm  ch 单个字符
 * return 1 or 0
 **/ 

int isAlpha(char ch){
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
		return 1;
	}
	return 0;
}

//int isNum();

/**
 * 判断是否为数字
 * @parm  ch 单个字符
 * return 1 or 0
 **/ 

int isDigit(char ch){
	if (ch >= '0' && ch <= '9')
	{
		return 1;
	}
	return 0;
}

/**
 * 对保留字进行排序，便于折半查找
 * void
 * @parm  无参数
 * return 排好序的keyword
 **/

void sort(){
	int i,j;
	char *temp;
	for (int i = 0; i < keywordSum; ++i){
		for (int j = 0; j < keywordSum-1; ++j){
			if(strcmp(keyword[i],keyword[j+1]) > 0){
				temp = keyword[i];
				keyword[i] = keyword[j+1];
				keyword[j+1] = temp;
			}
		}
	}
}


/**
 * 折半查找 
 * @parm key 查找关键字
 * @parm left 左边界
 * @parm rit  右边界
 * return index
 **/

int Search(char *key,int left,int rit){
	if (left > rit)
	{
		return 0;
	}
	int mid;
	mid = (rit + left) >> 1;
	if (strcmp(key,keyword[mid]) == 0){
		return 1;
	}else if (strcmp(key,keyword[mid]) < 0)
	{
		return Search(key,left,mid-1); 
	}else{
		return Search(key,mid+1,rit);
	}
}

/**
 * 是否为空 
 * @parm 单个字符
 * return 1 or 0
 **/ 

int isNone(char ch){
	if (ch == '\n')
	{
		line++;
		return 1;
	}
	//空格、回车、tab
	if(ch ==' ' || ch =='\t' ||ch =='\n')
        return 1 ;
    else
        return 0 ;
}

/**
 * 判断字符串是否还有字母 
 * @parm char token[]
 * return 1 or 0
 **/

int isHasAlpha(char *token){
	int i = 0;
	while(token[i]){
		if(isAlpha(token[i])){
			return 1;
		}
		i++;
	}
	return 0;
}


/**
 * 词法分析函数
 * @parm in File
 * @parm out File
 * return int code
 **/

int TESTScan(){
	// ch为每次读入的字符 
	//token用于保留识别的单词
	char ch,token[400]; 

	// 处理注释的情况
	char ch1;

	// cs为错误码 
	// 0 无错误
	// 1 找不到输入文件错误
	// 2 找不到输出文件错误
	// 3 其他错误
	int es = 0;	

	// j,n为临时变量 存储下标
	// j 识别字符
	// n 识别保留字
	int j,n;

	// 读入输入文件
	printf("Please enter the lexical analysis input file(absolute path):\n");
	scanf("%s",scanIn);

	// 读入输出文件位置 
	printf("Please enter the lexical analysis output file(absolute path):\n");
	scanf("%s",scanOut);        	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           

	// 判断输入文件名是否正确
	if ((fin=fopen(scanIn,"r")) == NULL)
	{
		//printf("\nCan't find the input file!\n");
		return (1);
	}

	if ((fout=fopen(scanOut,"w")) == NULL)
	{
		//printf("\nCan't find the output file!\n");
		return (2);
	}

	// 开始进行词法分析
	ch = getc(fin);

	while(ch!=EOF){

		// 跳过空的字符
		while(ch == ' ' || ch == '\n' || ch == '\t')
			ch = getc(fin);

		// 判定是否为字符
		if(isAlpha(ch)){
			token[0] = ch;
			j = 1;
			ch = getc(fin);

			// 如果是字符+数字 可能为一个变量名 
			// 持续读入数字 直到不是数字为止
			while(isAlpha(ch) || isDigit(ch)){
				token[j++] = ch;
				ch = getc(fin);
			}
			// 字符标识符结束
			token[j] = '\0';

			// 是否为保留字
			n = 0;
			// strcmp 需要库 <string.h>
			while( n<keywordSum && strcmp(token,keyword[n]))
				n++;

			// 输出字符和保留字结果
			if (n >= keywordSum)
			{
				fprintf(fout, "%s\t%s\n","ID",token);
			}else {
				fprintf(fout, "%s\t%s\n",token,token);
			}
		}

		// 如果读入的是数字
		else if(isDigit(ch)){
			token[0] = ch;
			j=1;
			ch = getc(fin);

			// 判断是否为组合数字
			while(isDigit(ch)|| isAlpha(ch)){
				token[j++] = ch;
				ch = getc(fin);
			}

			// 组合数字结束
			token[j] = '\0';

			if (isHasAlpha(token)){
				// 打印错误
				fprintf(fout,"%s\t%s\n","ID ERROR!",token);

				// 更改错误码
				es = 3;
			}else{
				// 输出组合数字
				fprintf(fout,"%s\t%s\n","NUM",token);
			}
		}

		// 处理注释
		else if(ch == '/'){
			ch = getc(fin);

			// 如果是注释
			if (ch == '*')
			{
				ch1 = getc(fin);
				do{
					// 保留ch1的前一个字符
					ch = ch1;
					ch1 = getc(fin);
					if (ch1 == EOF)
					{
						es = 3;
						// 注释错误
						fprintf(fout, "%s\t%s\n","Comment ERROR!","/*");
					}
				}while((ch != '*' || ch1 != '/') && ch1 != EOF);

				ch = getc(fin);
			}
			// 	如果不是注释 可能为单分节符
			else{
				token[0] = '/';
				token[1] = '\0';
				fprintf(fout, "%s\t%s\n",token,token);
			}
		}

		// 处理双分节符
		else if (strchr(doubleWord,ch) > 0){
			token[0] = ch;

			// 继续读入字符来判定
			ch = getc(fin);

			// 如果为判定符号
			if(ch == '='){
				token[1] = ch;
				token[2] = '\0';
				ch = getc(fin);
			}

			// 如果为逻辑判断符号 
			else if (ch == '&' || ch == '|'){
				token[1] = ch;
				token[2] = '\0';
				ch = getc(fin);
			}

			// 判定字符是否为 换行符
			else if (token[0] == '\\' && ch == 'n')
			{
				token[1] = ch;
				token[2] = '\0';
				ch = getc(fin);
			}

			// 不是单、双分界符
			else
				token[1] = '\0';

			// 打印结果
			fprintf(fout, "%s\t%s\n",token,token);
		}

		// 单分节符处理
		else if(strchr(singleWord,ch) > 0){
			token[0] = ch;
			token[1] = '\0';
			ch = getc(fin);
			// 输出单分节符
			fprintf(fout, "%s\t%s\n",token,token);
		}

		// 处理错误
		else{
			token[0] = ch;
			token[1] = '\0';
			ch = getc(fin);
			es = 3;
			fprintf(fout, "%s\t%s\n","Unrecognizable ERROR!",token);
		}
	}

	// 关闭文件
	fclose(fin);
	fclose(fout);

	// 返回错误码
	return es;
} 

// void main(int argc, char const *argv[])
// {
// 	printStart();

// 	int es = 0;

// 	// 词法分析
// 	es = TESTScan();

// 	if (es > 0)
// 	{
// 		printf("Lexical analysis Error!\n");
// 		printf("Code :%d\n",es);
// 		printError();
// 	}
// 	else{
// 		printf("Successfully completed Lexical analysis!\n");
// 	}

// 	return;
// }

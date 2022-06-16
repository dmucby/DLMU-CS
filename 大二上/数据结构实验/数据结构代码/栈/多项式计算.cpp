#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OPSETSIZE 8 //运算符集合数为8
char OPSET[OPSETSIZE] = { '+', '-', '*', '/', '(', ')', '#', '^' };
unsigned char Prior[8][8] =
{	 /**********运算符优先级表***********/
	     // '+'  '-'   '*' '/'  '('   ')' '#'  '^'
	/*'+'*/ '>', '>', '<', '<', '<', '>', '>', '<',
	/*'-'*/ '>', '>', '<', '<', '<', '>', '>', '<',
	/*'*'*/ '>', '>', '>', '>', '<', '>', '>', '<',
	/*'/'*/ '>', '>', '>', '>', '<', '>', '>', '<',
	/*'('*/ '<', '<', '<', '<', '<', '=', ' ', '<',
	/*')'*/ '>', '>', '>', '>', ' ', '>', '>', '>',
	/*'#'*/ '<', '<', '<', '<', '<', ' ', '=', '<',
	/*'^'*/ '>', '>', '>', '>', '<', '>', '>', '>'
};

typedef struct{
	char *base;
	char *top;
	int stacksize;
}SqStackC;//存放字符的栈

typedef struct{
	double *base;
	double *top;
	int stacksize;
}SqStackN;//存放数字的栈

void InitStack(SqStackN &S);//初始化数字栈
void InitStack(SqStackC &S);//初始化字符栈
void PushN(SqStackN &S,char e);//向数字栈中存放数字
void PopN(SqStackN &S,char &e);//从数字栈中取出数字
void PushC(SqStackC &S,char e);//向字符栈中存放字符
void PopC(SqStackC &S,char &e);//从字符栈中取出字符
char Precede(char optrtop,char c);//比较当前栈顶元素和字符c的优先关系
double Operate(double a, unsigned char theta, double b);//进行计算
int getIndex(char c);//将操作符转换成矩阵下标
void EvaluateExpression();//算数表达式求值的算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈

//初始化数字栈
void InitStackN(SqStackN &S){
	S.base=(double *)malloc(STACK_INIT_SIZE*sizeof(double));
	if(!S.base)
	exit(0);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
}

//初始化字符栈
void InitStackC(SqStackC &S){
	S.base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!S.base)
	exit(0);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
}

//向数字栈中存放数字
void PushN(SqStackN &S,double e){
	if(S.top - S.base>=S.stacksize){
		S.base=(double *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(double));
		if(!S.base) exit(0);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top=e;
	*S.top++;
}

//向字符栈中存放字符
void PushC(SqStackC &S,char e){
	if(S.top - S.base>=S.stacksize){
		S.base=(char *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(char));
		if(!S.base) exit(0);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top=e;
	*S.top++;
}

//从数字栈中取出数字
void PopN(SqStackN &S,double &e){
	if(S.top==S.base) exit(0);
	e=*--S.top;
}

//从字符栈中取出字符
void PopC(SqStackC &S,char &e){
	if(S.top==S.base) exit(0);
	e=*--S.top;
}

//比较当前栈顶元素和字符c的优先关系
char Precede(char optrtop,char c){
	int i,j;
	i=getIndex(optrtop);
	j=getIndex(c);
	if(i==-1||j==-1){
		printf("不支持的符号类型\n");
		exit(0);
	}
	else return Prior[i][j];
}

//进行计算
double Operate(double a, unsigned char theta, double b)
{
	switch (theta)
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a*b;
		case '/': return a / b;
		case '^': return pow(a, b);
		default: return 0;
	}
}

//将操作符转换成矩阵下标
int getIndex(char c)
{
	switch(c) {
		case '+': return 0;
		case '-': return 1;
		case '*': return 2;
		case '/': return 3;
		case '(': return 4;
		case ')': return 5;
		case '#': return 6;
		case '^': return 7;
	}
	return -1;
}

//算数表达式求值的算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈
void EvaluateExpression()
{
	SqStackN OPND;
	SqStackC OPTR;
	double a,b,sum,n;
	n=0;
	char c,e,theta;
	InitStackC(OPTR);
	PushC(OPTR,'#');
	InitStackN(OPND);
	printf("输入你想计算的表达式：（以“#”号结尾）\n");
	c=getchar();
	while(c!='#'||*(OPTR.top-1)!='#')
	{
		if(c>='0'&&c<='9')
		{
			n=n*10+c-'0';//保存数字，先不入栈
			c=getchar();
		}//不是运算符则进栈
		else
		{
			if(n!=0){//之前有数字
				PushN(OPND,n);//入栈
				n=0;
			}
			switch(Precede(*(OPTR.top-1),c))
			{
				case '<': //栈顶元素优先权低
					PushC(OPTR,c);
					c=getchar();
					break;
				case '=': //脱括号并接收下一字符
					PopC(OPTR,theta);
					c=getchar();
					break;
				case '>': //退栈并将运算结果入栈
					PopC(OPTR,theta);
					PopN(OPND,b);
					PopN(OPND,a);
					sum=Operate(a,theta,b);
					PushN(OPND,sum);
					break;
			}//switch
		}
	}//while
	printf("结果为：%lf\n",*(OPND.top-1));
}//EvaluateExpression

//主函数
int main()
{
	EvaluateExpression();
}

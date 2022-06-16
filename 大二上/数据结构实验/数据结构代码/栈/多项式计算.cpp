#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OPSETSIZE 8 //�����������Ϊ8
char OPSET[OPSETSIZE] = { '+', '-', '*', '/', '(', ')', '#', '^' };
unsigned char Prior[8][8] =
{	 /**********��������ȼ���***********/
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
}SqStackC;//����ַ���ջ

typedef struct{
	double *base;
	double *top;
	int stacksize;
}SqStackN;//������ֵ�ջ

void InitStack(SqStackN &S);//��ʼ������ջ
void InitStack(SqStackC &S);//��ʼ���ַ�ջ
void PushN(SqStackN &S,char e);//������ջ�д������
void PopN(SqStackN &S,char &e);//������ջ��ȡ������
void PushC(SqStackC &S,char e);//���ַ�ջ�д���ַ�
void PopC(SqStackC &S,char &e);//���ַ�ջ��ȡ���ַ�
char Precede(char optrtop,char c);//�Ƚϵ�ǰջ��Ԫ�غ��ַ�c�����ȹ�ϵ
double Operate(double a, unsigned char theta, double b);//���м���
int getIndex(char c);//��������ת���ɾ����±�
void EvaluateExpression();//�������ʽ��ֵ����������㷨����OPTR��OPND�ֱ�Ϊ�����ջ��������ջ

//��ʼ������ջ
void InitStackN(SqStackN &S){
	S.base=(double *)malloc(STACK_INIT_SIZE*sizeof(double));
	if(!S.base)
	exit(0);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
}

//��ʼ���ַ�ջ
void InitStackC(SqStackC &S){
	S.base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!S.base)
	exit(0);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
}

//������ջ�д������
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

//���ַ�ջ�д���ַ�
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

//������ջ��ȡ������
void PopN(SqStackN &S,double &e){
	if(S.top==S.base) exit(0);
	e=*--S.top;
}

//���ַ�ջ��ȡ���ַ�
void PopC(SqStackC &S,char &e){
	if(S.top==S.base) exit(0);
	e=*--S.top;
}

//�Ƚϵ�ǰջ��Ԫ�غ��ַ�c�����ȹ�ϵ
char Precede(char optrtop,char c){
	int i,j;
	i=getIndex(optrtop);
	j=getIndex(c);
	if(i==-1||j==-1){
		printf("��֧�ֵķ�������\n");
		exit(0);
	}
	else return Prior[i][j];
}

//���м���
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

//��������ת���ɾ����±�
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

//�������ʽ��ֵ����������㷨����OPTR��OPND�ֱ�Ϊ�����ջ��������ջ
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
	printf("�����������ı��ʽ�����ԡ�#���Ž�β��\n");
	c=getchar();
	while(c!='#'||*(OPTR.top-1)!='#')
	{
		if(c>='0'&&c<='9')
		{
			n=n*10+c-'0';//�������֣��Ȳ���ջ
			c=getchar();
		}//������������ջ
		else
		{
			if(n!=0){//֮ǰ������
				PushN(OPND,n);//��ջ
				n=0;
			}
			switch(Precede(*(OPTR.top-1),c))
			{
				case '<': //ջ��Ԫ������Ȩ��
					PushC(OPTR,c);
					c=getchar();
					break;
				case '=': //�����Ų�������һ�ַ�
					PopC(OPTR,theta);
					c=getchar();
					break;
				case '>': //��ջ������������ջ
					PopC(OPTR,theta);
					PopN(OPND,b);
					PopN(OPND,a);
					sum=Operate(a,theta,b);
					PushN(OPND,sum);
					break;
			}//switch
		}
	}//while
	printf("���Ϊ��%lf\n",*(OPND.top-1));
}//EvaluateExpression

//������
int main()
{
	EvaluateExpression();
}

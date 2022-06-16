#include<iostream>
using namespace std;
// #define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

#define OK 1
#define ERROR 0
#define MEMOVERFLOW -2
const char oper[7] = { '+', '-', '*', '/', '(', ')', '#' };
typedef char SElemType;
typedef int Status;
typedef struct SNode {
    int data;
    struct SNode *next;
} SNode, *LinkStack;

Status InitStack(LinkStack &S) {
    S = NULL;
    return OK;
}
bool StackEmpty(LinkStack S) {
    if (!S)
        return true;
    return false;
}
Status Push(LinkStack &S, SElemType e) {
    SNode *p = new SNode;
    if (!p) {
        return MEMOVERFLOW;
    }
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}
Status Pop(LinkStack &S, SElemType &e) {
    SNode *p;
    if (!S)
        return ERROR;
    e = S->data;
    p = S;
    S = S->next;
    delete p;
    return OK;
}
Status GetTop(LinkStack &S) {
    if (!S)
        return ERROR;

    return S->data;
}

//�ж�ch�Ƿ�Ϊ�����
bool In(char ch);

//�ж���������ȼ�
char Precede(char theta1, char theta2);

//��������������
char Operate(char first, char theta, char second);

//�㷨3.22�����ʽ��ֵ
char EvaluateExpression() {//�������ʽ��ֵ����������㷨����OPTR��OPND�ֱ�Ϊ�����ջ�Ͳ�����ջ
    LinkStack OPTR, OPND;
    char ch, theta, a, b, x,s;
    InitStack(OPND); //��ʼ��OPNDջ
    InitStack(OPTR); //��ʼ��OPTRջ
    Push(OPTR, '#'); //�����ʽ��ʼ����#��ѹ��OPTRջ
    cin >> ch;
    while (ch != '#' || (GetTop(OPTR) != '#')) //���ʽû��ɨ����ϻ�OPTR��ջ��Ԫ�ز�Ϊ��#��
    {
        if (!In(ch)) {
            Push(OPND, ch);
            cin >> ch;
        } //ch������������OPNDջ
        else
            switch (Precede(GetTop(OPTR), ch)) //�Ƚ�OPTR��ջ��Ԫ�غ�ch�����ȼ�
            {
            case '<':
                Push(OPTR, ch);
                cin >> ch; //��ǰ�ַ�chѹ��OPTRջ��������һ�ַ�ch
                break;
            case '>':
                Pop(OPTR, theta); //����OPTRջ���������
                Pop(OPND, b);
                Pop(OPND, a); //����OPNDջ��������������
                Push(OPND, Operate(a, theta, b)); //��������ѹ��OPNDջ
                break;
            case '=': //OPTR��ջ��Ԫ���ǡ�(����ch�ǡ�)��
                Pop(OPTR, x);
                cin >> ch; //����OPTRջ���ġ�(����������һ�ַ�ch
                break;
            } //switch
    } //while
    return GetTop(OPND); //OPNDջ��Ԫ�ؼ�Ϊ���ʽ��ֵ���
}

int main() {
    D(cout << "������Ҫ����ı��ʽ(�������ͽ������0-9�ķ�Χ�ڣ���#����): " << endl;)
    char res = EvaluateExpression(); //�㷨3.22�����ʽ��ֵ
    D(cout << "������Ϊ: ";)
    cout << res - 48 << endl;
    return 0;
}

bool In(char ch)
{//�ж�ch�Ƿ�Ϊ�����
	for (int i = 0; i < 7; i++) {
		if (ch == oper[i]) {
			return true;
		}
	}
	return false;
}



char Precede(char theta1, char theta2)
{//�ж���������ȼ�
	if ((theta1 == '(' && theta2 == ')') || (theta1 == '#' && theta2 == '#'))
	{
		return '=';
	}
	else if (theta1 == '(' || theta1 == '#' || theta2 == '(' || (theta1
			== '+' || theta1 == '-') && (theta2 == '*' || theta2 == '/'))
	{
		return '<';
	}
	else
		return '>';
}



char Operate(char first, char theta, char second)
{//��������������
	switch (theta)
	{
	case '+':
		return (first - '0') + (second - '0') + 48;
	case '-':
		return (first - '0') - (second - '0') + 48;
	case '*':
		return (first - '0') * (second - '0') + 48;
	case '/':
		return (first - '0') / (second - '0') + 48;
	}
	return 0;
}



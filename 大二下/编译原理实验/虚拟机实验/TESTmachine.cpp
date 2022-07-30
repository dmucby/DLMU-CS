#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<map>
using namespace std;

map<string, int> Map;

int TESTmachine();

typedef struct Code
{
    char opt[10];   //操作码
    int  operand;    //操作数
} Code;

Code codes[1000];    //中间代码
enum enum_Opt {LOAD, LOADI, STO, STI, ADD, SUB,
                    MULT, DIV,MOD, BR, BRF, EQ, NOTEQ, GT,
                    LES, GE, LE, AND, OR, NOT, IN, OUT, RETURN,ENTER,CAL};

void init() ///初始化
{
    Map["LOAD"] = LOAD;
    Map["LOADI"] = LOADI;
    Map["STO"] = STO;
    Map["STI"] = STI;
    Map["ADD"] = ADD;
    Map["SUB"] = SUB;
    Map["MULT"] = MULT;
    Map["DIV"] = DIV;
    Map["MOD"] = MOD;
    Map["BR"] = BR;
    Map["BRF"] = BRF;
    Map["EQ"] = EQ;
    Map["NOTEQ"] = NOTEQ;
    Map["GT"] = GT;
    Map["LES"] = LES;
    Map["GE"] = GE;
    Map["LE"] = LE;
    Map["AND"] = AND;
    Map["OR"] = OR;
    Map["NOT"] = NOT;
    Map["IN"] = IN;
    Map["OUT"] = OUT;
    Map["RETURN"] = RETURN;
    Map["ENTER"] = ENTER;
    Map["CAL"] = CAL;
}

int TESTmachine()
{

    int es = 0;

    int numCodes; //中间代码文件中指令的条数
    char Codein[30];
    FILE *fin; //用于指向中间代码文件的指针

    int stack[100], top = 0, base=0;
    //top：栈顶的下一个单元的下标

    int ip=0;//指令指针
    Code instruction;
    init();

    printf("请输入目标文件名（包括路径）：");
    scanf("%s", Codein);

    if((fin = fopen(Codein, "rb")) == NULL) {
        printf("\n打开%s错误!\n", Codein);
        es = 10;
        return(es);
    }

    numCodes = 0;
    //while(fread(codes + (numCodes++), sizeof(Code), 1, fin) == 1); 貌似有点错误

    while(!feof(fin)){
        fscanf(fin,"%s %d",&codes[numCodes].opt,&codes[numCodes].operand);
        numCodes++;
    }

    numCodes--; //最后一次读取会多加1
    fclose(fin);

    top=0;
    base=0;
    ip = 0;
    stack[0]=0;
    stack[1]=0;
    memset(stack,0,sizeof(stack));

    // for (int i = 0; i <=10 ; ++i)
    // {
    //     printf("%s\t%d\n",codes[i].opt,codes[i].operand);
    // }
    // 

    //printf("%d",ip);

    do{ //执行每条指令

        instruction=codes[ip]; // 记录当前操作
        ip++;

        switch(Map[instruction.opt]){

            case LOAD://LOAD D将D中的内容加载到操作数栈。
                stack[top] = stack[base+instruction.operand];
                top++;
                break;

            case LOADI://LOADI a将常量a压入操作数栈
                stack[top] =instruction.operand;
                top++;
                break;

            case STO: // 将操作数栈顶单元存入D中
                top--; // 栈顶元素-1
                stack[base+instruction.operand] = stack[top];
                break;

            case ADD://ADD将次栈顶单元与栈顶单元内容出栈并相加，和置于栈顶。
                top--;
                stack[top - 1] = stack[top - 1] + stack[top];
                break;

            case SUB://SUB    将次栈顶单元减去栈顶单元内容并出栈，差置于栈顶。
                top--;
                stack[top - 1] = stack[top - 1] - stack[top];
                break;

            case MULT://MULT   将次栈顶单元与栈顶单元内容出栈并相乘，积置于栈顶。
                top--;
                stack[top - 1] = stack[top - 1] * stack[top ];
                break;

            case DIV://DIV    将次栈顶单元与栈顶单元内容出栈并相除，商置于栈顶。
                top--;
                stack[top - 1] = stack[top - 1] / stack[top ];
                break;

            case MOD://MOD    将次栈顶单元与栈顶单元内容出栈并取模，值置于栈顶。
                top--;
                stack[top - 1] = stack[top - 1] % stack[top ];
                break;

            case BR://BR    lab  无条件转移到lab
                ip = instruction.operand;
                break;

            case BRF://BRF  lab  检查栈顶单元逻辑值，若为假（0）则转移到lab
                top--;
                if(stack[top] == 0)
                    ip =instruction.operand;
                break;

            case EQ://EQ  将栈顶两单元做等于比较，并将结果真或假（1或0）置于栈顶
                top--;
                stack[top - 1] =( stack[top - 1] == stack[top]);
                break;

            case NOTEQ://NOTEQ 将栈顶两单元做不等于比较，并将结果真或假（1或0）置于栈顶
                top--;
                stack[top - 1] =( stack[top - 1] != stack[top]);
                break;

            case GT://GT    次栈顶大于栈顶操作数，则栈顶置1，否则置0
                top--;
                stack[top - 1] = stack[top - 1] > stack[top ];
                break;

            case LES://LES  次栈顶小于栈顶操作数，则栈顶置1，否则置0
                top--;
                stack[top - 1] = stack[top - 1] < stack[top ];
                break;

            case GE://GE  次栈顶大于等于栈顶操作数，则栈顶置1，否则置0
                top--;
                stack[top - 1] = stack[top - 1] >= stack[top];
                break;

            case LE://LE  次栈顶小于等于栈顶操作数，则栈顶置1，否则置0
                top--;
                stack[top - 1] = stack[top - 1] <= stack[top ];
                break;

            case AND://AND 将栈顶两单元做逻辑与运算，并将结果真或假（1或0）置于栈顶
                top--;
                stack[top - 1] = stack[top - 1] && stack[top ];
                break;

            case OR://OR  将栈顶两单元做逻辑或运算，并将结果真或假（1或0）置于栈顶
                top--;
                stack[top -1] = stack[top - 1] || stack[top ];
                break;

            case NOT://NOT  将栈顶的逻辑值取反
                stack[top - 1] = !stack[top - 1];
                break;

            case IN://IN 从标准输入设备（键盘）读入一个整型数据，并入栈。
                printf("请输入数据：");
                scanf("%d", &stack[top]);
                top++;
                break;

            case OUT://OUT 将栈顶单元内容出栈，并输出到标准输出设备上（显示器）。
                top--;
                printf("程序输出:%d\n", stack[top]);
                break;

            case ENTER://进入函数
                top+=instruction.operand; //在栈中为被调函数开辟数据区
                break;

            case RETURN:
                top=base;//释放被调函数在栈中的空间
                ip=stack[top+1]; //取得主调函数中的返回地址
                base=stack[top]; //恢复主调函数的基地址
                break;

            case CAL:
                stack[top]=base; //主调过程的基地址入栈
                stack[top+1]=ip; //主调过程的返回地址入栈

                base=top; // 改变基地址为新进入过程的基地址
                ip=instruction.operand; //转入被调函数的函数体
                break;
            }

        }while(ip != 0);
    return(es);
}

int main(){
    int es=TESTmachine();
    return 0;
}






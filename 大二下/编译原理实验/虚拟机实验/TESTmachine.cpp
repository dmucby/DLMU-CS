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
    char opt[10];   //������
    int  operand;    //������
} Code;

Code codes[1000];    //�м����
enum enum_Opt {LOAD, LOADI, STO, STI, ADD, SUB,
                    MULT, DIV,MOD, BR, BRF, EQ, NOTEQ, GT,
                    LES, GE, LE, AND, OR, NOT, IN, OUT, RETURN,ENTER,CAL};

void init() ///��ʼ��
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

    int numCodes; //�м�����ļ���ָ�������
    char Codein[30];
    FILE *fin; //����ָ���м�����ļ���ָ��

    int stack[100], top = 0, base=0;
    //top��ջ������һ����Ԫ���±�

    int ip=0;//ָ��ָ��
    Code instruction;
    init();

    printf("������Ŀ���ļ���������·������");
    scanf("%s", Codein);

    if((fin = fopen(Codein, "rb")) == NULL) {
        printf("\n��%s����!\n", Codein);
        es = 10;
        return(es);
    }

    numCodes = 0;
    //while(fread(codes + (numCodes++), sizeof(Code), 1, fin) == 1); ò���е����

    while(!feof(fin)){
        fscanf(fin,"%s %d",&codes[numCodes].opt,&codes[numCodes].operand);
        numCodes++;
    }

    numCodes--; //���һ�ζ�ȡ����1
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

    do{ //ִ��ÿ��ָ��

        instruction=codes[ip]; // ��¼��ǰ����
        ip++;

        switch(Map[instruction.opt]){

            case LOAD://LOAD D��D�е����ݼ��ص�������ջ��
                stack[top] = stack[base+instruction.operand];
                top++;
                break;

            case LOADI://LOADI a������aѹ�������ջ
                stack[top] =instruction.operand;
                top++;
                break;

            case STO: // ��������ջ����Ԫ����D��
                top--; // ջ��Ԫ��-1
                stack[base+instruction.operand] = stack[top];
                break;

            case ADD://ADD����ջ����Ԫ��ջ����Ԫ���ݳ�ջ����ӣ�������ջ����
                top--;
                stack[top - 1] = stack[top - 1] + stack[top];
                break;

            case SUB://SUB    ����ջ����Ԫ��ȥջ����Ԫ���ݲ���ջ��������ջ����
                top--;
                stack[top - 1] = stack[top - 1] - stack[top];
                break;

            case MULT://MULT   ����ջ����Ԫ��ջ����Ԫ���ݳ�ջ����ˣ�������ջ����
                top--;
                stack[top - 1] = stack[top - 1] * stack[top ];
                break;

            case DIV://DIV    ����ջ����Ԫ��ջ����Ԫ���ݳ�ջ�������������ջ����
                top--;
                stack[top - 1] = stack[top - 1] / stack[top ];
                break;

            case MOD://MOD    ����ջ����Ԫ��ջ����Ԫ���ݳ�ջ��ȡģ��ֵ����ջ����
                top--;
                stack[top - 1] = stack[top - 1] % stack[top ];
                break;

            case BR://BR    lab  ������ת�Ƶ�lab
                ip = instruction.operand;
                break;

            case BRF://BRF  lab  ���ջ����Ԫ�߼�ֵ����Ϊ�٣�0����ת�Ƶ�lab
                top--;
                if(stack[top] == 0)
                    ip =instruction.operand;
                break;

            case EQ://EQ  ��ջ������Ԫ�����ڱȽϣ�����������٣�1��0������ջ��
                top--;
                stack[top - 1] =( stack[top - 1] == stack[top]);
                break;

            case NOTEQ://NOTEQ ��ջ������Ԫ�������ڱȽϣ�����������٣�1��0������ջ��
                top--;
                stack[top - 1] =( stack[top - 1] != stack[top]);
                break;

            case GT://GT    ��ջ������ջ������������ջ����1��������0
                top--;
                stack[top - 1] = stack[top - 1] > stack[top ];
                break;

            case LES://LES  ��ջ��С��ջ������������ջ����1��������0
                top--;
                stack[top - 1] = stack[top - 1] < stack[top ];
                break;

            case GE://GE  ��ջ�����ڵ���ջ������������ջ����1��������0
                top--;
                stack[top - 1] = stack[top - 1] >= stack[top];
                break;

            case LE://LE  ��ջ��С�ڵ���ջ������������ջ����1��������0
                top--;
                stack[top - 1] = stack[top - 1] <= stack[top ];
                break;

            case AND://AND ��ջ������Ԫ���߼������㣬����������٣�1��0������ջ��
                top--;
                stack[top - 1] = stack[top - 1] && stack[top ];
                break;

            case OR://OR  ��ջ������Ԫ���߼������㣬����������٣�1��0������ջ��
                top--;
                stack[top -1] = stack[top - 1] || stack[top ];
                break;

            case NOT://NOT  ��ջ�����߼�ֵȡ��
                stack[top - 1] = !stack[top - 1];
                break;

            case IN://IN �ӱ�׼�����豸�����̣�����һ���������ݣ�����ջ��
                printf("���������ݣ�");
                scanf("%d", &stack[top]);
                top++;
                break;

            case OUT://OUT ��ջ����Ԫ���ݳ�ջ�����������׼����豸�ϣ���ʾ������
                top--;
                printf("�������:%d\n", stack[top]);
                break;

            case ENTER://���뺯��
                top+=instruction.operand; //��ջ��Ϊ������������������
                break;

            case RETURN:
                top=base;//�ͷű���������ջ�еĿռ�
                ip=stack[top+1]; //ȡ�����������еķ��ص�ַ
                base=stack[top]; //�ָ����������Ļ���ַ
                break;

            case CAL:
                stack[top]=base; //�������̵Ļ���ַ��ջ
                stack[top+1]=ip; //�������̵ķ��ص�ַ��ջ

                base=top; // �ı����ַΪ�½�����̵Ļ���ַ
                ip=instruction.operand; //ת�뱻�������ĺ�����
                break;
            }

        }while(ip != 0);
    return(es);
}

int main(){
    int es=TESTmachine();
    return 0;
}






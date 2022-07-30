//TESTparse �﷨�������������������
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

#define maxsymbolIndex 100//������ű������
enum Category_symbol {variable,function};//��־��������

int TESTparse();
int program();
int fun_declaration();
int main_declaration();
int function_body();
int compound_stat();
int statement();
int expression_stat();
int expression();
int bool_expr();
int additive_expr();
int term();
int factor();
int if_stat();
int while_stat();
int for_stat();
int write_stat();
int read_stat();
int declaration_stat();
int declaration_list();
int statement_list();
int compound_stat();
int insert_Symbol(enum Category_symbol category, char *name);
int lookup(char *name, int *pPosition);

char token[20], token1[40]; //�������ֵ����������ֵ
char tokenfile[30];//�������ļ�������
char Codeout[30]; //����ļ���

FILE *fpTokenin;  //�������ļ�ָ��
FILE *fpCodeBinary;   //�м����������ļ�ָ��
FILE *fpCodeText; //�м�����ı��ļ�ָ��

struct //���ű�
{
    char name[20];
    enum Category_symbol kind;
    int address;
} symbol[maxsymbolIndex];

typedef struct Code
{
    char opt[10];    //������
    int operand;     //������
} Code;
Code codes[200];    //����м����Ľṹ������

int codesIndex;  //codes�����е�һ����Ԫ�ص��±꣬0����һ��Ҫ���ɵĴ�����codes�е�λ�ã�
int symbolIndex = 0; //symbol�����е�һ����Ԫ�ص��±꣬0����һ��Ҫ����ı�ʶ���ڷ��ű��е�λ�ã�
int offset;//�ֲ������������庯���ڲ�����Ե�ַ


//�﷨������������������ɳ���
int TESTparse()
{
    codesIndex = 0;
    int i;
    int es = 0;
    printf("�����뵥�����ļ���������·������");
    scanf("%s", tokenfile);
    if((fpTokenin = fopen(tokenfile, "r")) == NULL){
        printf("\n��%s����!\n",tokenfile );
        es = 10;
        return(es);
       }
    es = program();
    fclose(fpTokenin);

    printf("==�﷨������������������ɳ�����==\n");
    switch(es){
        case 0: printf("�﷨����������ɹ��������������ɴ���!\n"); break;
        case 10: printf("���ļ� %sʧ��!\n", tokenfile); break;
        case 1: printf("ȱ��{!\n"); break;
        case 2: printf("ȱ��}!\n"); break;
        case 3: printf("ȱ�ٱ�ʶ��!\n"); break;
        case 4: printf("�ٷֺ�!\n"); break;
        case 5: printf("ȱ��(!\n"); break;
        case 6: printf("ȱ��)!\n"); break;
        case 7: printf("ȱ�ٲ�����!\n"); break;
        case 11: printf("������ͷȱ��{!\n"); break;
        case 12: printf("��������ȱ��}!\n"); break;
        case 13:printf("���һ������������Ӧ����main}!\n"); break;
        case 21: printf("���ű����!\n"); break;
        case 22: printf("����%s�ظ�����!\n",token1); break;
        case 23: printf("����δ����!\n"); break;
        case 24:printf("������main���������󣬻������������ַ�\n");break;
        case 32: printf("�������ظ�����!\n"); break;
        case 34: printf("call������ı�ʶ��%s���Ǳ�����!\n",token1 ); break;
        case 35: printf("read������ı�ʶ�����Ǳ�����!\n"); break;
        case 36: printf("��ֵ������ֵ%s���Ǳ�����!\n",token1); break;
        case 37: printf("���Ӷ�Ӧ�ı�ʶ�����Ǳ�����!\n"); break;
        }

    printf("������Ҫ���ɵ��ı���ʽ���м�����ļ������֣�����·������");
    scanf("%s", Codeout);
    if((fpCodeText = fopen(Codeout, "w")) == NULL) {
        printf("\n����%s����!\n", Codeout);
        es = 10;
        return(es);
        }

    for(i=0;i<codesIndex;i++){
		if(strcmp(codes[i].opt,"LOAD")==0||strcmp(codes[i].opt,"LOADI")==0||strcmp(codes[i].opt,"STO")==0||
		strcmp(codes[i].opt,"BR")==0||strcmp(codes[i].opt,"BRF")==0||strcmp(codes[i].opt,"CAL")==0||strcmp(codes[i].opt,"ENTER")==0)
			fprintf(fpCodeText," %3d %-5s %d\n",i,codes[i].opt,codes[i].operand);
		else
			fprintf(fpCodeText," %3d %-5s\n",i,codes[i].opt);
        }
    fclose(fpCodeText);

    printf("������Ҫ���ɵĶ�������ʽ���м�����ļ������֣��ṹ��洢��:");
    scanf("%s",Codeout);
    if((fpCodeBinary = fopen(Codeout,"wb")) == NULL) {
        printf("\n����%s����!\n", Codeout);
        es = 10;
        return(es);
        }
    fwrite(codes,sizeof(Code),codesIndex,fpCodeBinary);
    fclose(fpCodeBinary);
    return(es);
}

//<program> ��{ fun_declaration }<main_declaration>
//<fun_declaration> �� function ID��(�� �� )��< function_body>
//<main_declaration>��  main��(�� �� )�� < function_body>

int program()
{
    int es = 0, i;
    strcpy(codes[codesIndex++].opt,"BR");//codes����ĵ�һ��ָ����������ת�Ƶ�main��������ڣ���ڵ�ַ��Ҫ����

    fscanf(fpTokenin, "%s %s\n", token, token1);
    while(!strcmp(token, "function")) {//�ж��Ƿ���ͨ�����Ķ��塱
       fscanf(fpTokenin, "%s %s\n", token, token1);

       es=fun_declaration();

       if(es !=0) return es;
       fscanf(fpTokenin, "%s %s\n", token, token1);
       }
    if(strcmp(token, "ID")){//��������������main�����Ķ��壬�����ֵΪ��ID��
        es=1;
        return es;
        }
    if(strcmp(token1, "main"))  {
        es=13;
        return es;
        }
    fscanf(fpTokenin, "%s %s\n", token, token1);

    es=main_declaration();

    if(es > 0) return(es);

    if(!feof(fpTokenin))    //���Դ�����У���������������������
	   return (es=24);

    //������ű������
    printf("     ���ű�\n");
    printf(" ����\t \t���� \t��ַ\n");
    for(i = 0; i < symbolIndex; i++)
        printf("  %-8s \t%d \t%d\n", symbol[i].name, symbol[i].kind,symbol[i].address);
    return(es);
}

//<fun_declaration> �� function ID��(�� �� )��< function_body>
int fun_declaration()
{
    int es=0;
    if (strcmp(token,"ID")){
            es=2;
            return es;
        }
    insert_Symbol(function,token1);//��������������ű�

    fscanf(fpTokenin, "%s %s\n", token, token1);
    if (strcmp(token,"(")) {
        es=5;
        return es;
        }
    fscanf(fpTokenin, "%s %s\n", token, token1);
    if (strcmp(token,")")){
       es=6;
       return es;
       }
    fscanf(fpTokenin, "%s %s\n", token, token1);
    es=function_body();
    return es;
}

//<main_declaration>�� main��(�� �� )�� < function_body>
int main_declaration()
{
    int es=0;
    insert_Symbol(function,"main");
    if (strcmp(token,"(")){
        es=5;
        return es;
        }
    fscanf(fpTokenin, "%s %s\n", token, token1);
    if (strcmp(token,")")) {
        es=6;
        return es;
        }

    codes[0].operand=codesIndex;//����codes����ĵ�0��ָ���ת��Ŀ��Ϊmain�����ĺ��������

    fscanf(fpTokenin, "%s %s\n", token, token1);

    es= function_body();
    return es;
}

//<function_body>��'{'<declaration_list><statement_list>'}'
int function_body()
{
    int es=0;

    if(strcmp(token,"{")){//�ж��Ƿ�'{'
        es=11;
        return(es);
        }
    symbol[symbolIndex-1].address=codesIndex;
    //�Ѻ��������ڵ�ַ���뺯�����ڷ��ű��еĵ�ַ�ֶ�
    offset=2;
    //����һ���µĺ�������������Ե�ַ��2��ʼ
    fscanf(fpTokenin,"%s %s\n",&token,&token1);

    es=declaration_list();

    if (es>0) return(es);
    strcpy(codes[codesIndex].opt, "ENTER");//������Ŀ�ʼ
    codes[codesIndex].operand=offset;
    codesIndex++;

    es=statement_list();

    if (es>0) return(es);
    if(strcmp(token,"}")){//�ж��Ƿ�'}'
        es=12;
        return(es);
        }
    strcpy(codes[codesIndex++].opt, "RETURN");//������Ľ���
    return es;
}

//<declaration_list>��{<declaration_stat>}
int declaration_list()
{
    int es = 0;

    while(strcmp(token, "int") == 0) {
        es = declaration_stat();
        if(es > 0) return(es);
        }
    return(es);
}

//<declaration_stat>��int ID;
int declaration_stat()
{
    int es = 0;

    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    if(strcmp(token, "ID"))	return(es = 3); //���Ǳ�ʶ��

    es = insert_Symbol(variable,token1); //������ű�

    if(es > 0) return(es);
    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    if(strcmp(token, ";"))	return(es = 4);
    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    return(es);
}

//<statement_list>��{<statement>}
int statement_list()
{
    int es = 0;

    while(strcmp(token, "}"))  {
        es = statement();
        if(es > 0) return(es);
        }
    return(es);
}

//<statement>�� <if_stat>|<while_stat>|<for_stat>
//               |<compound_stat> |<expression_stat>| <call _stat>
int statement()
{
    int es = 0;

    if(es == 0 && strcmp(token, "if") == 0) es = if_stat(); //<if���>
    if(es == 0 && strcmp(token, "while") == 0) es = while_stat(); //<while���>
    if(es == 0 && strcmp(token, "for") == 0) es = for_stat(); //<for���>
    //���ڴ˴����do������
    if(es == 0 && strcmp(token, "read") == 0) es = read_stat(); //<read���>
    if(es == 0 && strcmp(token, "write") == 0) es = write_stat(); //<write���>
    if(es == 0 && strcmp(token, "{") == 0) es = compound_stat(); //<�������>
    if(es == 0 && strcmp(token, "call") == 0) es = call_stat();//<�����������>
    if(es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0)) es = expression_stat(); //<���ʽ���>
    return(es);
}

//<if_stat>�� if '('<expr>')' <statement > [else < statement >]
int if_stat()
{
    int es = 0,cx1, cx2; //if
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
}

//<while_stat>�� while '('<expr >')' < statement >
int while_stat()
{
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//    return(es);
}

//<for_stat>�� for'('<expr>;<expr>;<expr>')'<statement>
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

//<write_stat>��write <expression>;
int write_stat()
{
    int es = 0;

    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    es = expression();
    if(es > 0)return(es);
    if(strcmp(token, ";"))  return(es = 4); //�ٷֺ�
    strcpy(codes[codesIndex++].opt, "OUT");
    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    return(es);
}

//<read_stat>��read ID;
int read_stat()
{
//
//
//
//
//
//
//
//
//
//
//
//
//
    return(es);
}

//<compound_stat>��'{'<statement_list>'}'
int compound_stat()    //������亯��
{
    int es = 0;

    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    es = statement_list();
    fscanf(fpTokenin,"%s %s\n",&token,&token1);
    return(es);
}

//< call _stat>��call ID( )
int call_stat()
{
    int es = 0, symbolPos;
//
//
//
//
//
//
//
//
//
//
//
//
//
//

//
}

//<expression_stat>��<expression>;|;
int expression_stat()
{
    int es = 0;

    if(strcmp(token, ";") == 0){
        fscanf(fpTokenin, "%s %s\n", &token, &token1);
        return(es);
        }

    es = expression();
    if(es > 0) return(es);
    if(strcmp(token, ";") == 0){
        fscanf(fpTokenin, "%s %s\n", &token, &token1);
        return(es);
        }
    else{
        es = 4;
        return(es);//�ٷֺ�
        }
}

//<expression>�� ID=<bool_expr>|<bool_expr>
int expression()
{
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
}



 //<bool_expr>-><additive_expr> |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >
int bool_expr()
{
    int es = 0;

    es = additive_expr();
    if(es > 0) return(es);
    if(strcmp(token, ">") == 0 || strcmp(token, ">=") == 0
            || strcmp(token, "<") == 0 || strcmp(token, "<=") == 0
            || strcmp(token, "==") == 0 || strcmp(token, "!=") == 0)  {

        char token2[20];
        strcpy(token2, token); //���������
        fscanf(fpTokenin, "%s %s\n", &token, &token1);
        es = additive_expr();
        if(es > 0) return(es);
        if(strcmp(token2, ">") == 0)
                 strcpy(codes[codesIndex++].opt, "GT");
        if(strcmp(token2, ">=") == 0)
                 strcpy(codes[codesIndex++].opt, "GE");
        if(strcmp(token2, "<") == 0)
                 strcpy(codes[codesIndex++].opt, "LES");
        if(strcmp(token2, "<=") == 0)
                 strcpy(codes[codesIndex++].opt, "LE");
        if(strcmp(token2, "==") == 0)
                 strcpy(codes[codesIndex++].opt, "EQ");
        if(strcmp(token2, "!=") == 0)
               strcpy(codes[codesIndex++].opt, "NOTEQ");
        }
    return(es);
}

//<additive_expr>��<term>{(+|-)< term >}
int additive_expr()
{
    int es = 0;
    es = term();
    if(es > 0) return(es);
//
//
//
//
//
//
//
//
//
//
//

    return(es);
}

//< term >��<factor>{(*| /)< factor >}
int term()
{
    int es = 0;

//
//
//
//
//
//
//
//
//
//
//
//
//
    return(es);
}

//< factor >��'('<additive_expr>')'| ID|NUM
int factor()
{
    int es = 0;

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
    return(es);
}

//ɨ�赽��ʶ���Ķ����Գ���ʱ�����������ű�
int insert_Symbol(enum Category_symbol category, char *name)
{
    int i, es = 0;

    if(symbolIndex >= maxsymbolIndex) return(21);
    switch (category) {
            case function:
                for(i = symbolIndex - 1; i >= 0; i--) {//����ű�
                    if((strcmp(symbol[i].name, name) == 0)&&(symbol[i].kind==function)){
                        es = 32; //32��ʾ�������ظ�
                        break;
                        }
                    }
                symbol[symbolIndex].kind=function;
                break;
            case variable:
                for(i = symbolIndex - 1; i >= 0; i--) {//����ű�
                    if((strcmp(symbol[i].name, name) == 0)&&(symbol[i].kind==variable)){
                        es = 22; //22��ʾ�����ظ�����
                        break;
                        }
                    }
                symbol[symbolIndex].kind=variable;
                symbol[symbolIndex].address = offset;
                offset++;//����һ����Ԫ��������ָ���
                break;
            }
    if(es > 0)   return(es);
    strcpy(symbol[symbolIndex].name, name);
    symbolIndex++;
    return es;
    }

//ȡ�ñ�ʶ���ڷ��ű��е�λ��
int lookup(char *name, int *pPosition)
{
//
//
//
//
//
//
//
//
//
//    return(es);
}

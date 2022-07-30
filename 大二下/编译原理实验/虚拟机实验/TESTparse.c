//TESTparse 语法、语义分析及代码生成
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

#define maxsymbolIndex 100//定义符号表的容量
enum Category_symbol {variable,function};//标志符的类型

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

char token[20], token1[40]; //单词类别值、单词自身值
char tokenfile[30];//单词流文件的名字
char Codeout[30]; //输出文件名

FILE *fpTokenin;  //单词流文件指针
FILE *fpCodeBinary;   //中间代码二进制文件指针
FILE *fpCodeText; //中间代码文本文件指针

struct //符号表
{
    char name[20];
    enum Category_symbol kind;
    int address;
} symbol[maxsymbolIndex];

typedef struct Code
{
    char opt[10];    //操作码
    int operand;     //操作数
} Code;
Code codes[200];    //存放中间代码的结构体数组

int codesIndex;  //codes数组中第一个空元素的下标，0序（下一条要生成的代码在codes中的位置）
int symbolIndex = 0; //symbol数组中第一个空元素的下标，0序（下一个要填入的标识符在符号表中的位置）
int offset;//局部变量在所定义函数内部的相对地址


//语法、语义分析及代码生成程序
int TESTparse()
{
    codesIndex = 0;
    int i;
    int es = 0;
    printf("请输入单词流文件名（包括路径）：");
    scanf("%s", tokenfile);
    if((fpTokenin = fopen(tokenfile, "r")) == NULL){
        printf("\n打开%s错误!\n",tokenfile );
        es = 10;
        return(es);
       }
    es = program();
    fclose(fpTokenin);

    printf("==语法、语义分析及代码生成程序结果==\n");
    switch(es){
        case 0: printf("语法、语义分析成功并抽象机汇编生成代码!\n"); break;
        case 10: printf("打开文件 %s失败!\n", tokenfile); break;
        case 1: printf("缺少{!\n"); break;
        case 2: printf("缺少}!\n"); break;
        case 3: printf("缺少标识符!\n"); break;
        case 4: printf("少分号!\n"); break;
        case 5: printf("缺少(!\n"); break;
        case 6: printf("缺少)!\n"); break;
        case 7: printf("缺少操作数!\n"); break;
        case 11: printf("函数开头缺少{!\n"); break;
        case 12: printf("函数结束缺少}!\n"); break;
        case 13:printf("最后一个函数的名字应该是main}!\n"); break;
        case 21: printf("符号表溢出!\n"); break;
        case 22: printf("变量%s重复定义!\n",token1); break;
        case 23: printf("变量未声明!\n"); break;
        case 24:printf("程序中main函数结束后，还有其它多余字符\n");break;
        case 32: printf("函数名重复定义!\n"); break;
        case 34: printf("call语句后面的标识符%s不是变量名!\n",token1 ); break;
        case 35: printf("read语句后面的标识符不是变量名!\n"); break;
        case 36: printf("赋值语句的左值%s不是变量名!\n",token1); break;
        case 37: printf("因子对应的标识符不是变量名!\n"); break;
        }

    printf("请输入要生成的文本形式的中间代码文件的名字（包括路径）：");
    scanf("%s", Codeout);
    if((fpCodeText = fopen(Codeout, "w")) == NULL) {
        printf("\n创建%s错误!\n", Codeout);
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

    printf("请输入要生成的二进制形式的中间代码文件的名字（结构体存储）:");
    scanf("%s",Codeout);
    if((fpCodeBinary = fopen(Codeout,"wb")) == NULL) {
        printf("\n创建%s错误!\n", Codeout);
        es = 10;
        return(es);
        }
    fwrite(codes,sizeof(Code),codesIndex,fpCodeBinary);
    fclose(fpCodeBinary);
    return(es);
}

//<program> →{ fun_declaration }<main_declaration>
//<fun_declaration> → function ID’(‘ ‘ )’< function_body>
//<main_declaration>→  main’(‘ ‘ )’ < function_body>

int program()
{
    int es = 0, i;
    strcpy(codes[codesIndex++].opt,"BR");//codes数组的第一条指令是无条件转移到main函数的入口，入口地址需要返填

    fscanf(fpTokenin, "%s %s\n", token, token1);
    while(!strcmp(token, "function")) {//判断是否“普通函数的定义”
       fscanf(fpTokenin, "%s %s\n", token, token1);

       es=fun_declaration();

       if(es !=0) return es;
       fscanf(fpTokenin, "%s %s\n", token, token1);
       }
    if(strcmp(token, "ID")){//整个程序的最后是main函数的定义，其类别值为“ID”
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

    if(!feof(fpTokenin))    //检测源程序中，程序结束后还有语句的情况。
	   return (es=24);

    //输出符号表的内容
    printf("     符号表\n");
    printf(" 名字\t \t类型 \t地址\n");
    for(i = 0; i < symbolIndex; i++)
        printf("  %-8s \t%d \t%d\n", symbol[i].name, symbol[i].kind,symbol[i].address);
    return(es);
}

//<fun_declaration> → function ID’(‘ ‘ )’< function_body>
int fun_declaration()
{
    int es=0;
    if (strcmp(token,"ID")){
            es=2;
            return es;
        }
    insert_Symbol(function,token1);//将函数名插入符号表

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

//<main_declaration>→ main’(‘ ‘ )’ < function_body>
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

    codes[0].operand=codesIndex;//返填codes数组的第0条指令的转移目标为main函数的函数体入口

    fscanf(fpTokenin, "%s %s\n", token, token1);

    es= function_body();
    return es;
}

//<function_body>→'{'<declaration_list><statement_list>'}'
int function_body()
{
    int es=0;

    if(strcmp(token,"{")){//判断是否'{'
        es=11;
        return(es);
        }
    symbol[symbolIndex-1].address=codesIndex;
    //把函数体的入口地址填入函数名在符号表中的地址字段
    offset=2;
    //进入一个新的函数，变量的相对地址从2开始
    fscanf(fpTokenin,"%s %s\n",&token,&token1);

    es=declaration_list();

    if (es>0) return(es);
    strcpy(codes[codesIndex].opt, "ENTER");//函数体的开始
    codes[codesIndex].operand=offset;
    codesIndex++;

    es=statement_list();

    if (es>0) return(es);
    if(strcmp(token,"}")){//判断是否'}'
        es=12;
        return(es);
        }
    strcpy(codes[codesIndex++].opt, "RETURN");//函数体的结束
    return es;
}

//<declaration_list>→{<declaration_stat>}
int declaration_list()
{
    int es = 0;

    while(strcmp(token, "int") == 0) {
        es = declaration_stat();
        if(es > 0) return(es);
        }
    return(es);
}

//<declaration_stat>→int ID;
int declaration_stat()
{
    int es = 0;

    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    if(strcmp(token, "ID"))	return(es = 3); //不是标识符

    es = insert_Symbol(variable,token1); //插入符号表

    if(es > 0) return(es);
    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    if(strcmp(token, ";"))	return(es = 4);
    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    return(es);
}

//<statement_list>→{<statement>}
int statement_list()
{
    int es = 0;

    while(strcmp(token, "}"))  {
        es = statement();
        if(es > 0) return(es);
        }
    return(es);
}

//<statement>→ <if_stat>|<while_stat>|<for_stat>
//               |<compound_stat> |<expression_stat>| <call _stat>
int statement()
{
    int es = 0;

    if(es == 0 && strcmp(token, "if") == 0) es = if_stat(); //<if语句>
    if(es == 0 && strcmp(token, "while") == 0) es = while_stat(); //<while语句>
    if(es == 0 && strcmp(token, "for") == 0) es = for_stat(); //<for语句>
    //可在此处添加do语句调用
    if(es == 0 && strcmp(token, "read") == 0) es = read_stat(); //<read语句>
    if(es == 0 && strcmp(token, "write") == 0) es = write_stat(); //<write语句>
    if(es == 0 && strcmp(token, "{") == 0) es = compound_stat(); //<复合语句>
    if(es == 0 && strcmp(token, "call") == 0) es = call_stat();//<函数调用语句>
    if(es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0)) es = expression_stat(); //<表达式语句>
    return(es);
}

//<if_stat>→ if '('<expr>')' <statement > [else < statement >]
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

//<while_stat>→ while '('<expr >')' < statement >
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

//<for_stat>→ for'('<expr>;<expr>;<expr>')'<statement>
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

//<write_stat>→write <expression>;
int write_stat()
{
    int es = 0;

    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    es = expression();
    if(es > 0)return(es);
    if(strcmp(token, ";"))  return(es = 4); //少分号
    strcpy(codes[codesIndex++].opt, "OUT");
    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    return(es);
}

//<read_stat>→read ID;
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

//<compound_stat>→'{'<statement_list>'}'
int compound_stat()    //复合语句函数
{
    int es = 0;

    fscanf(fpTokenin, "%s %s\n", &token, &token1);
    es = statement_list();
    fscanf(fpTokenin,"%s %s\n",&token,&token1);
    return(es);
}

//< call _stat>→call ID( )
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

//<expression_stat>→<expression>;|;
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
        return(es);//少分号
        }
}

//<expression>→ ID=<bool_expr>|<bool_expr>
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
        strcpy(token2, token); //保存运算符
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

//<additive_expr>→<term>{(+|-)< term >}
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

//< term >→<factor>{(*| /)< factor >}
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

//< factor >→'('<additive_expr>')'| ID|NUM
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

//扫描到标识符的定义性出现时，将其插入符号表
int insert_Symbol(enum Category_symbol category, char *name)
{
    int i, es = 0;

    if(symbolIndex >= maxsymbolIndex) return(21);
    switch (category) {
            case function:
                for(i = symbolIndex - 1; i >= 0; i--) {//查符号表
                    if((strcmp(symbol[i].name, name) == 0)&&(symbol[i].kind==function)){
                        es = 32; //32表示函数名重复
                        break;
                        }
                    }
                symbol[symbolIndex].kind=function;
                break;
            case variable:
                for(i = symbolIndex - 1; i >= 0; i--) {//查符号表
                    if((strcmp(symbol[i].name, name) == 0)&&(symbol[i].kind==variable)){
                        es = 22; //22表示变量重复定义
                        break;
                        }
                    }
                symbol[symbolIndex].kind=variable;
                symbol[symbolIndex].address = offset;
                offset++;//分配一个单元，数据区指针加
                break;
            }
    if(es > 0)   return(es);
    strcpy(symbol[symbolIndex].name, name);
    symbolIndex++;
    return es;
    }

//取得标识符在符号表中的位置
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

#include<iostream>
#include<string>
#include<stack>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
using namespace std;
typedef long long ll;
typedef int Status;
typedef struct{
    char *base;
    char *top;
    int StackSize;
}SqStack;
Status InitStack(SqStack&S){
    S.base = (char*)malloc(110*sizeof(char));
    if(!S.base) return OVERFLOW;
    S.top = S.base;
    S.StackSize = 110;
    return OK;
}
Status push(SqStack &S,char e){
    if(S.top - S.base==S.StackSize) return ERROR;
    *S.top++ = e;
    return OK;
}
Status pop(SqStack&S,char e){
    if(S.top==S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}
char GetTop(SqStack S){
    if(S.top!=S.base) return *(S.top-1);
}
bool StackEmpty(SqStack&S){
    if(S.top==S.base) return true;
    return false;
}
int main()
{
    //freopen("i.txt","r",stdin);
    char s[110],str[110];
    char c;
    int cnt = 0;
    while(scanf("%s",str)!=EOF&&str[0]!='.'){
        for(int i=0;str[i];i++){
            if(str[i]=='('||str[i]=='{'||str[i]=='['||str[i]==')'||str[i]=='}'||str[i]==']')
                s[cnt++] = str[i];
            else if(str[i]=='/'&&str[i+1]=='*'){
                s[cnt++] = str[i];
                s[cnt++] = str[i+1];
                i++;
            }else if(str[i]=='*'&&str[i+1]=='/'){
                s[cnt++] = str[i];
                s[cnt++] = str[i+1];
                i++;
            }
        }
    }
    s[cnt++]='\0';
    SqStack S;
    InitStack(S);
    bool flag = true;
    for(int i=0;s[i];i++){
        if(s[i]=='('||s[i]=='{'||s[i]=='[')
            push(S,s[i]);
        else if(s[i]=='/'&&s[i+1]=='*'){
            push(S,s[i]);
            push(S,s[i+1]);
            i++;
        }
        else if(s[i]==')'){
            if(!StackEmpty(S)&&GetTop(S)=='('){
                pop(S,'(');
            }else{
                c = s[i];
                flag = false;
                break;
            }
        }
        else if(s[i]==']'){
            if(!StackEmpty(S)&&GetTop(S)=='['){
                pop(S,'[');
            }else{
                c = s[i];
                flag = false;
                break;
            }
        }
        else if(s[i]=='}'){
            if(!StackEmpty(S)&&GetTop(S)=='{'){
                pop(S,'{');
            }else{
                c = s[i];
                flag = false;
                break;
            }
        }
        else if(s[i]=='*'&&s[i+1]=='/'){
            if(!StackEmpty(S)&&GetTop(S)=='*'){
                pop(S,'*');
                if(!StackEmpty(S)&&GetTop(S)=='/')
                    pop(S,'/');
                else{
                    c = s[i];
                    flag = false;
                    break;
                }
            }else{
                c = s[i];
                flag = false;
                break;
            }
            i++;
        }
    }
    if(flag&&StackEmpty(S)) printf("YES\n");
    else{
        printf("NO\n");
        if(!StackEmpty(S)){
            char x = GetTop(S);
            if(x=='(')
                cout<<'('<<'-'<<'?'<<endl;
            else if(x=='[')
                cout<<'['<<'-'<<'?'<<endl;
            else if(x=='{')
                cout<<'{'<<'-'<<'?'<<endl;
            else if(x=='*')
                cout<<'/'<<'*'<<'-'<<'?'<<endl;
        }else{
            if(c==')')
                cout<<'?'<<'-'<<')'<<endl;
            else if(c==']')
                cout<<'?'<<'-'<<']'<<endl;
            else if(c=='}')
                cout<<'?'<<'-'<<'}'<<endl;
            else if(c=='*')
                cout<<'?'<<'-'<<'*'<<'/'<<endl;
        }
    }
}

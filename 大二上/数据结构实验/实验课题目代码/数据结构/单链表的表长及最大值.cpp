#include<stdio.h>
#include<stdlib.h>
#define M 10
#include <malloc.h>

using namespace std;

typedef int datatype;

typedef struct Node
{
    datatype data;
    struct Node *next;
}*LinkList;

LinkList Creat_LinkList();
int Length_LinkList(LinkList L);

LinkList Creat_LinkList(){
   int n;
   scanf("%d",&n);
   LinkList L = (LinkList)malloc(sizeof(LinkList));
   L->data = n;
   L->next = NULL;
   int n1;
   while(scanf("%d",&n1)!=-1){
        LinkList L2 = (LinkList)malloc(sizeof(LinkList));
        L2->data = n1;
        L->next = L2->next;
        L2->next = L;
    }
    return L;
}

int Length_LinkList(LinkList L){
    int num = 0;
    while(L!=NULL && L->next!=NULL){
        num++;
        L = L->next;
    }
    return num;
}

int main()
{
    LinkList L;
    L = Creat_LinkList();
    printf("%d",Length_LinkList(L) );

    return 0;
}

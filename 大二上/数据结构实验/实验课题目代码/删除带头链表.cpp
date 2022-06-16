//�⺯��ͷ�ļ�����
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

//����״̬�붨��
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define NULL        0

typedef int  Status;
typedef int  ElemType; //�������Ա��е�Ԫ�ؾ�Ϊ����

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

//����������
Status ListCreate_L(LinkList &L,int n)
{
    LNode *rearPtr,*curPtr;
    L=(LNode*)malloc(sizeof (LNode));
    if(!L)exit(OVERFLOW);
    L->next=NULL;
    rearPtr=L;
    for (int i=1;i<=n;i++){
        curPtr=(LNode*)malloc(sizeof(LNode));
        if(!curPtr)exit(OVERFLOW);
        scanf("%d",&curPtr->data);
        curPtr->next=NULL;
        rearPtr->next=curPtr;
        rearPtr=curPtr;
    }
    return OK;
}
//�����������
void ListPrint_L(LinkList L)
{
    LNode *p=L->next;
    if(!p){
        printf("�ձ�");
        return;
    }
    while(p!=NULL)
    {
       if(p->next!=NULL)
           printf("%d ",p->data);
       else
           printf("%d",p->data);
          p=p->next;
    }
}
//��������Ҫʵ�ֵĺ���

LinkList ReverseList(LinkList head)
{
    LinkList prev ;
    LinkList curr = head;
    while (curr) {
        LinkList next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void ListLocateAndDel_L(LinkList L, ElemType x){
    LinkList p = L;
    LinkList q = p;
    p = ReverseList(p);
    ListPrint_L(p);
}

int main()
{
    LinkList L;
    int n;
    int x;
    scanf("%d",&n);  //����������Ԫ�ظ���
    if(ListCreate_L(L,n)!= OK) {
          printf("����ʧ�ܣ�����\n");
          return -1;
    }
   scanf("%d",&x); //���������Ԫ��
   ListLocateAndDel_L(L,x);
   ListPrint_L(L);
   return 0;
}

/* ����������д�� */

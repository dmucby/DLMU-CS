#include<iostream>
#include<cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// #define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

//预定义常量
#define GUARD   -99
#define OK      1
#define ERROR   0

//函数结果的类型
typedef int Status;
typedef int ElemType;
typedef struct LNode {
    int data;
    struct LNode *next;
}LNode, *LinkList;

//输出带头结点的单链表L
void printLinkList(LinkList L) {
    LNode *p=L;
    D(printf("单链表的内容：\n");)
    while(p) {
        printf("[%d]-->", p->data);
        p=p->next;
    }
    printf("\n");
}


//创建一个带头结点的长度为n的单链表L
Status CreateLinkList(LinkList &L, int n) {
    LinkList pf, p;
    int i;
    //[1]创建表L的头结点
    L=(LinkList)malloc(sizeof(LNode));
    L->data=n;
    L->next=NULL;
    pf=L;
    D(printf("顺序输入%d个自然数，即单链表的数据：\n", n);)
    for (i=0;i<n;i++) {
        //[2]创建新结点p，与它的前驱结点pf链接
        p=(LinkList)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next=pf->next;
        pf->next=p;
        pf=p;
    }

    return OK;
}

//创建一个带头结点的单链表L，输入GUARD表示结束
void CreateLinkList(LinkList &L) {
    LinkList pf, p;
    int length=0;
    //[1]创建表L的头结点
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    pf=L;
    D(printf("输入某线性表各个元素的值(自然数)，%d表示输入结束！\n", GUARD);)
    p=(LinkList)malloc(sizeof(LNode));
    scanf("%d", &p->data);
    while(p->data!=GUARD)
    {
        p->next=pf->next;
        pf->next=p;
        pf=p;
        length++;
        p=(LinkList)malloc(sizeof(LNode));
        scanf("%d", &p->data);
    }
    L->data=length;
    printLinkList(L);
}


void ChangeLinkList(LinkList &L){

}

int Count_LinkList(LinkList &L){
    LinkList s = L;
    s = s->next;
    int cot = 0;
    while(s!=NULL){
        if(s->data % 2 == 0){
            cot++;
        }
        s = s->next;
    }
    return cot;
}

int main(int argc, char* argv[])
{
    int choice, i, max, min;
    ElemType elem;
    LinkList la, lb, lc;
    for (;;)
    {
        D(printf("\n           链表的基本操作  \n");)
        D(printf("             1.创建一个线性表\n");)
        D(printf("             2.求表中偶数个数\n");)
        D(printf("             3.交换偶数\n");)
        D(printf("             4.退出系统\n");)

        D(printf("请选择：");)
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:  D(printf("请选择链表的长度:");)
                 scanf("%d", &i);
                 CreateLinkList(la, i) ;
                 printLinkList(la); break;
        case 2:  D(printf("链表偶数个数为:"));
                 printf("%d\n", Count_LinkList(la)); break;
        case 3:  D(printf("偶数交换后的链表为"));
                 ChangeLinkList(la);
                 printLinkList(la);
                 break;
        case 4:  D(printf("请退出系统!\n");) exit(0); break;
        }
    }
    return 0;
}

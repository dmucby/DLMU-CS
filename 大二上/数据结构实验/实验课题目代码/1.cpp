#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// #define DEBUG
//#ifdef DEBUG
#define D(x) x
//#else
#define D(x)
//#endif

//预定义常量
#define GUARD   -99
#define OK      1
#define ERROR   0
#include<algorithm>

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


//T1:查找带头结点的单链表L中第i个节点的值e，头结点数据保存线性表的length
Status GetLinkElem(LinkList L, int i, ElemType &e){
    LinkList p = L;
    for(int j=0;j<i;j++){
        p=p->next;
    }
    if(p==NULL){
        return ERROR;
    }
    e = p->data;
    return OK;
}

//T2:在带头结点的单链表L中第i个位置之前插入元素e
Status LinkListInsert(LinkList &L, int i, ElemType e){
    L->data+=1;
    LinkList p = L;
    p = p->next;
    for(int j=0;j<i-2;j++){
        p= p->next;
    }
    if(p==NULL){
        return ERROR;
    }
    LNode *m = new(LNode);
    m->data = e;
    m->next = p->next;
    p->next = m;
    return OK;
}

//T3:在带头结点的单链表L中，删除第i个元素
Status LinkListDelete(LinkList &L, int i){
    LinkList p = L;
    p ->data -=1;
    for(int j=0;j<i-1;j++){
        p=p->next;
    }
    if(p==NULL){
        return ERROR;
    }
    LinkList m = p->next;
    p->next = p->next->next;
    free(m);
    return OK;
}

void sortList(LinkList head,int a) {
    int i = 0;
    int j = 0;
    //用于变量链表
    LinkList  L = head;
    //作为一个临时量
    LinkList  p;
    LinkList  p1;
    //如果链表为空直接返回
    if (a == 0)return;

    for (i = 0; i < a - 1; i++) {
        L = head->next;
        for (j = 0; j < a- i - 1; j++) {
            //得到两个值
            p = L;
            p1 = L->next;
            //如果前面的那个比后面的那个大，就交换它们之间的是数据域
            if (p->data > p1->data) {
                int temp = p->data;
                p->data = p1->data;
                p1->data = temp;
            }
            L = L->next;
        }
    }
}

//T4:已知单链表La和Lb的元素按值非递减排列。归并La和Lb得到新的单链表Lc。要求Lc的元素按值非递减排列。
Status MergeLinkList(LinkList La, LinkList Lb, LinkList &Lc){
    if(La->next == NULL) {
            Lc=Lb; return OK;
    }
    if(Lb->next == NULL) {
            Lc=La ;return OK;
    }
    Lc=(LinkList)malloc(sizeof(LNode));//忘记分配空间 一直报错
    int a = La->data,b = Lb->data,num=0;
    sortList(La,a);
    sortList(Lb,b);
    Lc->data = a+b;
    La = La->next;
    Lb = Lb->next;
    Lc->next = NULL;
    LinkList p = Lc;
    while(La!=NULL && Lb!=NULL){
        if(La->data<=Lb->data){
            p->next = La;
            La = La->next;
        }
        else{
            p->next = Lb;
            Lb = Lb->next;
        }
        p = p->next;
        num++;
    }
    if(La!=NULL){
       p->next = La;
    }
    if(Lb !=NULL){
       p->next = Lb;
    }
    return OK;
}

//T5:从一个递增有序的带头结点的单链表L中删除值<=max且>=min的结点
Status deleteallnodes(LinkList &L, ElemType min, ElemType max){
    //int length =L ->data;
    LinkList p=L->next;
    LinkList q=L;
    while(p!=NULL){
        if(p->data<=max && p->data>=min){
            L ->data --;
            q->next = p->next;
            free(p);
            p=q->next;
        }
        else{
            p = p->next;
            q = q->next;
        }
    }
    if(p==NULL){
        return ERROR;
    }
    return OK;
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
        D(printf("             2.线性表的长度\n");)
        D(printf("             3.读取第i个位置的元素\n");)
        D(printf("             4.插入元素到线性表里\n");)
        D(printf("             5.删除线性表里的元素\n");)
        D(printf("             6.将非递减线性表Lb归并到非递减线性表La，形成新非递减线性表Lc\n");)
        D(printf("             7.从一个递增有序的带头结点的单链表L中删除值<=max且>=min的结点\n");       )
        D(printf("             8.退出系统\n");)

        D(printf("请选择：");)
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:  D(printf("请选择链表的长度:");)
                 scanf("%d", &i);
                 CreateLinkList(la, i) ;
                 printLinkList(la); break;
        case 2:  D(printf("链表长度为:"));
                 printf("%d\n", la->data); break;
        case 3:  D(printf("请选择所要取出元素的位置:");)
                 scanf("%d", &i);
                 GetLinkElem(la, i, elem);
                 D(printf("单链表L中第%d个元素为：", i);)
                 printf("%d \n", elem);
                 break;
        case 4:  D(printf("请选择所要插入元素的位置:");)
                 scanf("%d", &i);
                 D(printf("请选择所要插入的元素:");)
                 scanf("%d", &elem);
                 LinkListInsert(la, i, elem);
                 printLinkList(la); break;
        case 5:  D(printf("请选择所要删除元素的位置:");)
                 scanf("%d", &i);
                 LinkListDelete(la,i);
                 printLinkList(la); break;
        case 6:  CreateLinkList(la);
                 CreateLinkList(lb);
                 MergeLinkList(la, lb, lc);
                 printLinkList(lc); break;
        case 7:  D(printf("请选择min和max大小:");)
                 scanf("%d %d", &min, &max);
                 deleteallnodes(lc, min, max);
                 printLinkList(lc); break;
        case 8:  D(printf("请退出系统!\n");) exit(0); break;
        }
    }
    return 0;
}
/* 请在这里填写答案 */

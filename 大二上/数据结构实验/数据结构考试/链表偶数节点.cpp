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

//Ԥ���峣��
#define GUARD   -99
#define OK      1
#define ERROR   0

//�������������
typedef int Status;
typedef int ElemType;
typedef struct LNode {
    int data;
    struct LNode *next;
}LNode, *LinkList;

//�����ͷ���ĵ�����L
void printLinkList(LinkList L) {
    LNode *p=L;
    D(printf("����������ݣ�\n");)
    while(p) {
        printf("[%d]-->", p->data);
        p=p->next;
    }
    printf("\n");
}


//����һ����ͷ���ĳ���Ϊn�ĵ�����L
Status CreateLinkList(LinkList &L, int n) {
    LinkList pf, p;
    int i;
    //[1]������L��ͷ���
    L=(LinkList)malloc(sizeof(LNode));
    L->data=n;
    L->next=NULL;
    pf=L;
    D(printf("˳������%d����Ȼ����������������ݣ�\n", n);)
    for (i=0;i<n;i++) {
        //[2]�����½��p��������ǰ�����pf����
        p=(LinkList)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next=pf->next;
        pf->next=p;
        pf=p;
    }

    return OK;
}

//����һ����ͷ���ĵ�����L������GUARD��ʾ����
void CreateLinkList(LinkList &L) {
    LinkList pf, p;
    int length=0;
    //[1]������L��ͷ���
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    pf=L;
    D(printf("����ĳ���Ա����Ԫ�ص�ֵ(��Ȼ��)��%d��ʾ���������\n", GUARD);)
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
        D(printf("\n           ����Ļ�������  \n");)
        D(printf("             1.����һ�����Ա�\n");)
        D(printf("             2.�����ż������\n");)
        D(printf("             3.����ż��\n");)
        D(printf("             4.�˳�ϵͳ\n");)

        D(printf("��ѡ��");)
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:  D(printf("��ѡ������ĳ���:");)
                 scanf("%d", &i);
                 CreateLinkList(la, i) ;
                 printLinkList(la); break;
        case 2:  D(printf("����ż������Ϊ:"));
                 printf("%d\n", Count_LinkList(la)); break;
        case 3:  D(printf("ż�������������Ϊ"));
                 ChangeLinkList(la);
                 printLinkList(la);
                 break;
        case 4:  D(printf("���˳�ϵͳ!\n");) exit(0); break;
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// #define DEBUG
//#ifdef DEBUG
#define D(x) x
//#else
#define D(x)
//#endif

//Ԥ���峣��
#define GUARD   -99
#define OK      1
#define ERROR   0
#include<algorithm>

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


//T1:���Ҵ�ͷ���ĵ�����L�е�i���ڵ��ֵe��ͷ������ݱ������Ա��length
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

//T2:�ڴ�ͷ���ĵ�����L�е�i��λ��֮ǰ����Ԫ��e
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

//T3:�ڴ�ͷ���ĵ�����L�У�ɾ����i��Ԫ��
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
    //���ڱ�������
    LinkList  L = head;
    //��Ϊһ����ʱ��
    LinkList  p;
    LinkList  p1;
    //�������Ϊ��ֱ�ӷ���
    if (a == 0)return;

    for (i = 0; i < a - 1; i++) {
        L = head->next;
        for (j = 0; j < a- i - 1; j++) {
            //�õ�����ֵ
            p = L;
            p1 = L->next;
            //���ǰ����Ǹ��Ⱥ�����Ǹ��󣬾ͽ�������֮�����������
            if (p->data > p1->data) {
                int temp = p->data;
                p->data = p1->data;
                p1->data = temp;
            }
            L = L->next;
        }
    }
}

//T4:��֪������La��Lb��Ԫ�ذ�ֵ�ǵݼ����С��鲢La��Lb�õ��µĵ�����Lc��Ҫ��Lc��Ԫ�ذ�ֵ�ǵݼ����С�
Status MergeLinkList(LinkList La, LinkList Lb, LinkList &Lc){
    if(La->next == NULL) {
            Lc=Lb; return OK;
    }
    if(Lb->next == NULL) {
            Lc=La ;return OK;
    }
    Lc=(LinkList)malloc(sizeof(LNode));//���Ƿ���ռ� һֱ����
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

//T5:��һ����������Ĵ�ͷ���ĵ�����L��ɾ��ֵ<=max��>=min�Ľ��
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
        D(printf("\n           ����Ļ�������  \n");)
        D(printf("             1.����һ�����Ա�\n");)
        D(printf("             2.���Ա�ĳ���\n");)
        D(printf("             3.��ȡ��i��λ�õ�Ԫ��\n");)
        D(printf("             4.����Ԫ�ص����Ա���\n");)
        D(printf("             5.ɾ�����Ա����Ԫ��\n");)
        D(printf("             6.���ǵݼ����Ա�Lb�鲢���ǵݼ����Ա�La���γ��·ǵݼ����Ա�Lc\n");)
        D(printf("             7.��һ����������Ĵ�ͷ���ĵ�����L��ɾ��ֵ<=max��>=min�Ľ��\n");       )
        D(printf("             8.�˳�ϵͳ\n");)

        D(printf("��ѡ��");)
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:  D(printf("��ѡ������ĳ���:");)
                 scanf("%d", &i);
                 CreateLinkList(la, i) ;
                 printLinkList(la); break;
        case 2:  D(printf("������Ϊ:"));
                 printf("%d\n", la->data); break;
        case 3:  D(printf("��ѡ����Ҫȡ��Ԫ�ص�λ��:");)
                 scanf("%d", &i);
                 GetLinkElem(la, i, elem);
                 D(printf("������L�е�%d��Ԫ��Ϊ��", i);)
                 printf("%d \n", elem);
                 break;
        case 4:  D(printf("��ѡ����Ҫ����Ԫ�ص�λ��:");)
                 scanf("%d", &i);
                 D(printf("��ѡ����Ҫ�����Ԫ��:");)
                 scanf("%d", &elem);
                 LinkListInsert(la, i, elem);
                 printLinkList(la); break;
        case 5:  D(printf("��ѡ����Ҫɾ��Ԫ�ص�λ��:");)
                 scanf("%d", &i);
                 LinkListDelete(la,i);
                 printLinkList(la); break;
        case 6:  CreateLinkList(la);
                 CreateLinkList(lb);
                 MergeLinkList(la, lb, lc);
                 printLinkList(lc); break;
        case 7:  D(printf("��ѡ��min��max��С:");)
                 scanf("%d %d", &min, &max);
                 deleteallnodes(lc, min, max);
                 printLinkList(lc); break;
        case 8:  D(printf("���˳�ϵͳ!\n");) exit(0); break;
        }
    }
    return 0;
}
/* ����������д�� */

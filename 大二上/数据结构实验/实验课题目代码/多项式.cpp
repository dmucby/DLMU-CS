#include <stdio.h>
#include <stdlib.h>

// #define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

#define GUARD   -99
#define Status int

typedef struct PNode
{
    int coef;       // ϵ��
    int expn;       // ָ��
    struct PNode *next;
} PNode, *Polynomial;

//�������ʽ����
void printPolyn(Polynomial &p){
    PNode *L = p;
    printf("Polyn [%d]: ", L->expn);//ͷ����ϵ���������ʽ�ĳ���
    L = L->next;
    while(L)
    {
        if (L->next)
        {
            if(L->expn!=0)
                printf("%d*x^%d ",L->coef,L->expn);
            else
                printf("%d ",L->coef);
        } else
        {
            if(L->expn!=0)
                printf("%d*x^%d",L->coef,L->expn);
            else
                printf("%d",L->coef);
        }

        L = L->next;
    }

    printf("\n");
}

//�ں��ʵ�λ�ò����½�㣬ʹ�ö���ʽ��ָ���Ӹߵ�������
Status InsertPolyNode(Polynomial &p, int coef, int expn){

    PNode* pre, * q;
    PNode* s = new PNode;
    s->coef = coef;
    s->expn = expn;
    pre = p; // pre���ڱ���q��ǰ�����, ��ͷ�ڵ�p
    q=p->next;
    while(q&&q->expn>s->expn){// ͨ���Ƚ�ָ���ҳ���һ��С�ڻ�����������ָ������*q
        pre=q;
        q = q->next;
    }
    if (q){
        if (q->expn==s->expn && q->coef+s->coef!=0){//���ָ������Ҷ�Ӧϵ���Ͳ�Ϊ0������¸ý��
            q->coef=q->coef+s->coef;
        }
        else if (q->expn==s->expn && q->coef+s->coef==0){//���ָ������Ҷ�Ӧϵ����Ϊ0����ɾ���ý��
            pre->next=q->next;
           // q=q->next;
            delete s;
            delete q;
            p->expn--;
        }
        else if (q->expn!=s->expn){//���ָ������ȣ���ɾ�����½��
            pre->next=s;
            s->next=q;
            p->expn++;
        }
    }
    else//���qΪ�գ�������½��
    {
        pre->next=s;
        s->next=q;
        p->expn++;
    }

    return 1;
 }

//���ݼ������봴��һ������ʽ
Status CreatePolynomail(Polynomial &p)
{
    p = new PNode;
    p->next = NULL;
    p->coef = 0;
    p->expn = 0;
    int length;
    int ceof[100];
    int expn[100];
    int i=0;

    D(printf("�������ʽϵ�����У���-99����: \n"); )
    scanf("%d", &ceof[i]);
    while(ceof[i]!=GUARD)
    {
        i++;
        scanf("%d", &ceof[i]);
    }

    i=0;
    D(printf("�������ʽָ�����У���-99����: \n");)
    scanf("%d", &expn[i]);

    while(expn[i]!=GUARD)
    {
        i++;
        scanf("%d", &expn[i]);
    }

    length=i;
    /*���������ϵ����ָ�����鴴������ʽ�����б�*/

    for(i=0; i<length; i++)
        InsertPolyNode(p, ceof[i], expn[i]);

    return 1;
}

//����ʽ�ӷ���pa = pa + pb
Status AddPolyn(Polynomial &pa,Polynomial pb){
    Polynomial pc = pa;
    Polynomial pbb = pb;
    Polynomial paa = pa;

    if(pa->next==NULL){
        pa = pb;
        return 1;
    }
    if(pb->next==NULL){
        return 1;
    }
    pa = pa->next;
    pb = pb->next;
    while(pa!=NULL && pb!=NULL){
        if(pa->expn==pb->expn){ //ָ����ͬ���
            pa->coef = pa->coef + pb->coef;
            paa = pa;
            pa = pa->next;
            pb = pb->next;
        }//��ͬ �жϴ�С ֱ�����ں���
        else{
            if(pa->expn>pb->expn){
                paa = pa;
                pa = pa->next;
            }else{
                 if(pb->expn>pa->expn){
                pbb = pb->next;
                pb->next = pa;
                paa->next = pb;
                paa = pb;
                pb = pbb;
                }

            }
        }
    }
    pa = pc;
    pa = pa->next;
    Polynomial p=pa->next;
    Polynomial q=pa;
    while(p!=NULL){
        if(p->coef==0){
            q->next = p->next;
            free(p);
            p=q->next;
        }
         else{
            p = p->next;
            q = q->next;
        }
    }
    pa = pc;
    int length = 0;
    pa = pa->next;
    while(pa!=NULL){
        pa = pa->next;
        length++;
    }
    pa = pc;
    pa->expn = length;
    return 1;
}

//����ʽ�˷���pc = pa*pb
Status MultiplyPolyn(Polynomial &pc,Polynomial pa,Polynomial pb){
    Polynomial pbb =pb;
    PNode* s = new PNode;
    s->next = NULL;
    pa = pa->next;
    pb = pb->next;
    while(pa!=NULL){
        while(pb!=NULL){
            InsertPolyNode(s,pa->coef*pb->coef,pa->expn+pb->expn);
            pb = pb->next;
        }
        pa = pa->next;
        pb = pbb;
    }
    pc = s;
    return 1;
}

//�Զ���ʽpa��һ�׵�
Status DerivativePolyn(Polynomial& pa){
    PNode* s = new PNode;
    s->next = NULL;
    pa = pa->next;
    while(pa!=NULL){
        InsertPolyNode(s,pa->coef*pa->expn,pa->expn-1);
        pa = pa->next;
    }
    pa = s;
    return 1;
}

int main()
{
    int choice, expn;
    int coef;
    Polynomial p,p1,p2,p3;
    for (;;)
    {
        D(printf("\n           ����ʽ�Ļ�������  \n");)
        D(printf("             1.����һ������ʽ\n");)
        D(printf("             2.����һ��\n");)
        D(printf("             3.����ʽ���\n");)
        D(printf("             4.����ʽ���\n");)
        D(printf("             5.����ʽ��\n");)
        D(printf("             6.�˳�ϵͳ\n");)

        D(printf("��ѡ��");)
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:  CreatePolynomail(p);
                 printPolyn(p);
                 break;
        case 2:  D(printf("����Ҫ�������ϵ��: ");)
                 scanf("%d", &coef);
                 D(printf("����Ҫ�������ָ��: ");)
                 scanf("%d", &expn);
                 InsertPolyNode(p, coef, expn);
                 printPolyn(p);
                 break;
        case 3:  CreatePolynomail(p1);
                 printPolyn(p1);
                 CreatePolynomail(p2);
                 printPolyn(p2);
                 D(printf("����ʽ��͵�: ");)
                 AddPolyn(p1, p2);
                 printPolyn(p1);
                 break;
        case 4:  CreatePolynomail(p1);
                 printPolyn(p1);
                 CreatePolynomail(p2);
                 printPolyn(p2);
                 D(printf("����ʽ�����: ");)
                 MultiplyPolyn(p3,p1,p2);
                 printPolyn(p3);
                 break;
        case 5:  D(printf("����ʽ�󵼵�: ");)
                 DerivativePolyn(p);
                 printPolyn(p);
                 break;
        case 6:  D(printf("���˳�ϵͳ!\n");) exit(0); break;
        }
    }
    return 1;
}
/* ����������д�� */

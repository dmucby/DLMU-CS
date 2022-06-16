#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

#define KeyType int
#define ENDFALG -99

// ��������������洢
typedef struct{
    KeyType key; //����
    // otherinfo ����������
}ElemType;

typedef struct BSTNode{
    ElemType data;
    struct BSTNode *lchild, *rchild;
}BSTNode,*BSTree;

// �����������ݹ����
BSTree SearchBST(BSTree T,KeyType key){
    if(T->data.key == key) return T;
    else if(key < T->data.key) return SearchBST(T->lchild,key);
    else return SearchBST(T->rchild,key);
}

// �����������Ĳ���
void InsertBST(BSTree &T,ElemType e){
    if(!T){
        BSTree S = (BSTree)malloc(sizeof(BSTNode));// new BSTNode ò�ƴ���
        S->data = e;
        S->lchild=S->rchild=NULL;
        T=S;
    }
    else if(T->data.key > e.key){
            InsertBST(T->lchild,e);
        }
    else{
        InsertBST(T->rchild,e);
    }
}

// �����������Ĵ���
void CreatBST(BSTree &T){
    T = NULL;
    ElemType e;
    cin>>e.key;
    while(e.key != ENDFALG){
        InsertBST(T,e);
        cin>>e.key;
    }
}

// ������������ɾ��
void DeleteBST(BSTree T,KeyType key){
    BSTree f,p,q,s; // fΪ���ڵ� pΪ���ڵ� q��ɾ���ڵ� sΪ�ӽڵ�
    p = T;f = NULL;
    BSTree PL = p->lchild;
    BSTree PR = p->rchild;
    p = SearchBST(T,key);
    if(!p) return;
    q = p;
    if((p->rchild)&&(p->lchild)){
        // �ҵ�һ���� �ӽڵ�������һ����� q�������丸�ڵ�
        s = p->lchild;
        while(s){
            q=s;s = s->rchild;
        }
        // ��s�ӵ�ԭp�����ٽ�s
        p->data = s->data;
         // s��������(��ΪsΪ���ҽ��϶�����������ֻ��Ҫ������������������)
        // ��Ϊq����������s,��sɾ����,q����������Ҫ����
        if(p!=q) q->rchild = s->lchild;  // ��ʱ s,p����ͬ����Ҫ��s�����������ӣ�����Ϊ��϶�����q����������q��������
        else q->lchild = s->lchild;     // ��ʱ p��q��ͬ ��s,p,q������ͬ ֻ��Ҫ��s���Ӽ���
        delete s;
        return ;

    }else if(!p->rchild){
        p = p->rchild;
    }
    else if(!p->lchild){
        p = p->lchild;
    }
    if(!f) T=p; // ��ɾ���Ϊ���ڵ�
    else if(q==f->lchild) f->lchild = p;//��Ϊq�������ҽڵ�ĸ��ڵ㣬ֻ��Ҫ������������������
    else f->rchild = p;
    delete q;
}

// ��ӡ����������
void printBSTree(BSTree &T){
    printBSTree(T->lchild);
    printf("%d ",T->data.key);
    printBSTree(T->rchild);
}

int main(){
    BSTree T;
    CreatBST(T);
    printBSTree(T);
    printf("\n");
    DeleteBST(T,2);
    printBSTree(T);
    return 0;
}

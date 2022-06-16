#include<iostream>
#include<cstdio>
#include<queue>
#include<stack>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include <sys/time.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void PreOrderTraverse(BiTree T)//二叉树的先序遍历
{
    cout<<T->data;
    if(T->lchild){
        cout<<"(";
        PreOrderTraverse(T->lchild);
    }
    if(T->rchild){
        cout<<",";
        PreOrderTraverse(T->rchild);
    }
    if((!T->rchild) && (!T->lchild)){
        cout<<")";
    }
}

void CreateBiTree(BiTree *T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        *T=NULL;
    else
    {
        *T=(BiTree  )malloc(sizeof(BiTNode));
        if(ch=='*')
            exit(-1);
        (*T)->data=ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

int main()
{
    BiTree T;
    CreateBiTree(&T);
    PreOrderTraverse (T);
    return 0;
}

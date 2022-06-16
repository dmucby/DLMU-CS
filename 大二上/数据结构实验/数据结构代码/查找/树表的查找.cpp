#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

#define KeyType int
#define ENDFALG -99

// 二叉排序树链表存储
typedef struct{
    KeyType key; //主键
    // otherinfo 其他数据项
}ElemType;

typedef struct BSTNode{
    ElemType data;
    struct BSTNode *lchild, *rchild;
}BSTNode,*BSTree;

// 二叉排序树递归查找
BSTree SearchBST(BSTree T,KeyType key){
    if(T->data.key == key) return T;
    else if(key < T->data.key) return SearchBST(T->lchild,key);
    else return SearchBST(T->rchild,key);
}

// 二叉排序树的插入
void InsertBST(BSTree &T,ElemType e){
    if(!T){
        BSTree S = (BSTree)malloc(sizeof(BSTNode));// new BSTNode 貌似错误
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

// 二叉排序树的创建
void CreatBST(BSTree &T){
    T = NULL;
    ElemType e;
    cin>>e.key;
    while(e.key != ENDFALG){
        InsertBST(T,e);
        cin>>e.key;
    }
}

// 二叉排序树的删除
void DeleteBST(BSTree T,KeyType key){
    BSTree f,p,q,s; // f为父节点 p为本节点 q被删除节点 s为子节点
    p = T;f = NULL;
    BSTree PL = p->lchild;
    BSTree PR = p->rchild;
    p = SearchBST(T,key);
    if(!p) return;
    q = p;
    if((p->rchild)&&(p->lchild)){
        // 找到一个左 子节点中最大的一个结点 q来保存其父节点
        s = p->lchild;
        while(s){
            q=s;s = s->rchild;
        }
        // 把s接到原p处，再将s
        p->data = s->data;
         // s有左子树(因为s为最右结点肯定无右子树，只需要连接它的左子树即可)
        // 因为q的右子树是s,把s删除后,q的右子树需要连接
        if(p!=q) q->rchild = s->lchild;  // 此时 s,p不相同，需要将s的左子树连接，又因为其肯定大于q，所以连到q的右子树
        else q->lchild = s->lchild;     // 此时 p和q相同 即s,p,q三点相同 只需要将s连接即可
        delete s;
        return ;

    }else if(!p->rchild){
        p = p->rchild;
    }
    else if(!p->lchild){
        p = p->lchild;
    }
    if(!f) T=p; // 被删结点为根节点
    else if(q==f->lchild) f->lchild = p;//因为q保存最右节点的根节点，只需要将其连到左子树即可
    else f->rchild = p;
    delete q;
}

// 打印二叉搜索树
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

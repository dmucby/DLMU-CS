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

using namespace std;
typedef int KeyType;            //定义关键字类型
typedef struct node                   //记录类型
{
    KeyType key;                      //关键字项
    struct node *lchild,*rchild;    //左右孩子指针
} BSTNode;

int ReadData(int a[]);   //键盘输入若干个整数，顺序保存在数组a中，并返回输入整数的数量。由裁判程序实现，细节不表。
BSTNode *CreatBST(KeyType A[],int n);    //顺序读入数组A中的关键字, 依序建立一棵二叉排序树并返回根结点指针.
int DeleteBST(BSTNode *&bt,KeyType k);   //在bt中删除关键字为k的节点. 找到关键字k并删除返回1，否则返回0。
int SearchBST(BSTNode *bt,KeyType k);    //输出从根节点到查找到的节点的路径 ,如果找到k,返回1，否则返回0。提示：输出语句格式如：printf("%d ",bt->key);
void InorderTraversal(BSTNode *bt);      //中序遍历并输出该二叉排序树。由裁判程序实现，输出语句格式如：printf("%d ",bt->key);
void PreorderTraversal(BSTNode *bt);     //先序遍历并输出该二叉排序树。由裁判程序实现，输出语句格式如：printf("%d ",bt->key);

int main()
{
    BSTNode *bt=NULL;
    KeyType k,X;
    int a[100],N,flag;
    N=ReadData(a);  //键盘读入N个整数，顺序保存在数组a中. 裁判程序实现，细节不表。
    bt=CreatBST(a,N); //根据数组a,创建一棵BST树
    printf("Preorder: "); PreorderTraversal(bt); printf("\n"); //先序遍历并输出该二叉排序树。
    scanf("%d", &k);  //输入待查找的关键字k
    flag = SearchBST(bt,k);printf("\n");//查找k，并输出从根节点到查找到的节点的路径 ,如果找到k,返回1，否则返回0
    scanf("%d", &k);  //输入待删除的关键字k
    DeleteBST(bt,k);  //在二叉排序树中删除关键字为k的结点。
    printf("Inorder: "); InorderTraversal(bt); printf("\n");   //中序遍历并输出该二叉排序树。
    return 0;
}

/* 请在这里填写答案 */


//键盘输入若干个整数，顺序保存在数组a中，并返回输入整数的数量。由裁判程序实现，细节不表。
int ReadData(int a[]){
    int n ;
    cin>>n;
    for(int i = 0;i<n;i++){
        cin>>a[i];
    }
    return n;
}

// 哨兵节点
BSTNode __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL(){
    NIL->key = -1;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

BSTNode *getNewNode(int value){
    BSTNode *p = (BSTNode*)malloc(sizeof(BSTNode));
    p->key = value;
    p->lchild = p->rchild = NIL;
    return p;
}

BSTNode *insert(BSTNode *root,int target){
    if(root == NIL) return getNewNode(target);
    if(root->key == target) return root;
    if(root->key > target){
        root->lchild = insert(root->lchild,target);
    }else{
        root->rchild = insert(root->rchild,target);
    }
    return root;
}

//顺序读入数组A中的关键字, 依序建立一棵二叉排序树并返回根结点指针.
BSTNode *CreatBST(KeyType A[],int n){
    BSTNode *root = NIL;
    for(int i=0;i<n;i++){
        root = insert(root,A[i]);
    }
    return root;
}

BSTNode *get_pre(BSTNode *root){
    BSTNode *tmp = root;
    while(tmp->rchild!=NIL){
        tmp = tmp->rchild;
    }
    return tmp;
}

BSTNode *erase(BSTNode *&root,int target,int &n){
    if(root == NIL){
        n = 0;
        return root;
    }
    if(root->key > target){
        root->lchild = erase(root->lchild,target,n);
    }else if(root->key < target){
        root->rchild = erase(root->rchild,target,n);
    }else {
        // 可以将度为1和叶子节点合并 NIL好处
        if(root->lchild == NIL && root->rchild == NIL){
            free(root);
            return NIL;
        }else if(root->lchild == NIL || root->rchild == NIL){
            BSTNode *tmp = (root->lchild != NIL ? root->lchild:root->rchild);
            free(root);
            return tmp;
        }else{
            BSTNode *tmp = get_pre(root->lchild);
            root->key = tmp->key;
            root->lchild = erase(root->lchild,tmp->key,n);
        }
    }
    return root;
}

//在bt中删除关键字为k的节点. 找到关键字k并删除返回1，否则返回0。
int DeleteBST(BSTNode *&bt,KeyType k){
    int flag = 1;
    bt = erase(bt,k,flag);
    return flag;
}

void dfs(BSTNode *root,KeyType k,vector<KeyType> &ans,KeyType &n){
    if(root == NULL){
        n = 0;
        return;
    }if(root->key > k){
        ans.push_back(root->key);
        dfs(root->lchild,k,ans,n);
    }else if(root->key < k){
        ans.push_back(root->key);
        dfs(root->rchild,k,ans,n);
    }else{
        ans.push_back(root->key);
        return ;
    }
}

//输出从根节点到查找到的节点的路径 ,如果找到k,返回1，否则返回0。提示：输出语句格式如：printf("%d ",bt->key);
int SearchBST(BSTNode *bt,KeyType k){
    vector<KeyType> ans;
    int n = 1;
    dfs(bt,k,ans,n);
    if(n == 0){
        return 0;
    }else{
        for(unsigned int i = 0;i<ans.size();i++){
            cout<<ans[i]<<" ";
        }
    }
    return 1;
}

//中序遍历并输出该二叉排序树。由裁判程序实现，输出语句格式如：printf("%d ",bt->key);
void InorderTraversal(BSTNode *bt){
    if(bt == NIL) return ;
    InorderTraversal(bt->lchild);
    printf("%d ",bt->key);
    InorderTraversal(bt->rchild);
    return ;
}

//先序遍历并输出该二叉排序树。由裁判程序实现，输出语句格式如：printf("%d ",bt->key);
void PreorderTraversal(BSTNode *bt){
    if(bt== NIL) return ;
    printf("%d ",bt->key);
    PreorderTraversal(bt->lchild);
    PreorderTraversal(bt->rchild);
    return ;
}


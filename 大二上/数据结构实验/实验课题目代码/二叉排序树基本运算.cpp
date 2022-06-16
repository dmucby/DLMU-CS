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
typedef int KeyType;            //����ؼ�������
typedef struct node                   //��¼����
{
    KeyType key;                      //�ؼ�����
    struct node *lchild,*rchild;    //���Һ���ָ��
} BSTNode;

int ReadData(int a[]);   //�����������ɸ�������˳�򱣴�������a�У������������������������ɲ��г���ʵ�֣�ϸ�ڲ���
BSTNode *CreatBST(KeyType A[],int n);    //˳���������A�еĹؼ���, ������һ�ö��������������ظ����ָ��.
int DeleteBST(BSTNode *&bt,KeyType k);   //��bt��ɾ���ؼ���Ϊk�Ľڵ�. �ҵ��ؼ���k��ɾ������1�����򷵻�0��
int SearchBST(BSTNode *bt,KeyType k);    //����Ӹ��ڵ㵽���ҵ��Ľڵ��·�� ,����ҵ�k,����1�����򷵻�0����ʾ���������ʽ�磺printf("%d ",bt->key);
void InorderTraversal(BSTNode *bt);      //�������������ö������������ɲ��г���ʵ�֣��������ʽ�磺printf("%d ",bt->key);
void PreorderTraversal(BSTNode *bt);     //�������������ö������������ɲ��г���ʵ�֣��������ʽ�磺printf("%d ",bt->key);

int main()
{
    BSTNode *bt=NULL;
    KeyType k,X;
    int a[100],N,flag;
    N=ReadData(a);  //���̶���N��������˳�򱣴�������a��. ���г���ʵ�֣�ϸ�ڲ���
    bt=CreatBST(a,N); //��������a,����һ��BST��
    printf("Preorder: "); PreorderTraversal(bt); printf("\n"); //�������������ö�����������
    scanf("%d", &k);  //��������ҵĹؼ���k
    flag = SearchBST(bt,k);printf("\n");//����k��������Ӹ��ڵ㵽���ҵ��Ľڵ��·�� ,����ҵ�k,����1�����򷵻�0
    scanf("%d", &k);  //�����ɾ���Ĺؼ���k
    DeleteBST(bt,k);  //�ڶ�����������ɾ���ؼ���Ϊk�Ľ�㡣
    printf("Inorder: "); InorderTraversal(bt); printf("\n");   //�������������ö�����������
    return 0;
}

/* ����������д�� */


//�����������ɸ�������˳�򱣴�������a�У������������������������ɲ��г���ʵ�֣�ϸ�ڲ���
int ReadData(int a[]){
    int n ;
    cin>>n;
    for(int i = 0;i<n;i++){
        cin>>a[i];
    }
    return n;
}

// �ڱ��ڵ�
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

//˳���������A�еĹؼ���, ������һ�ö��������������ظ����ָ��.
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
        // ���Խ���Ϊ1��Ҷ�ӽڵ�ϲ� NIL�ô�
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

//��bt��ɾ���ؼ���Ϊk�Ľڵ�. �ҵ��ؼ���k��ɾ������1�����򷵻�0��
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

//����Ӹ��ڵ㵽���ҵ��Ľڵ��·�� ,����ҵ�k,����1�����򷵻�0����ʾ���������ʽ�磺printf("%d ",bt->key);
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

//�������������ö������������ɲ��г���ʵ�֣��������ʽ�磺printf("%d ",bt->key);
void InorderTraversal(BSTNode *bt){
    if(bt == NIL) return ;
    InorderTraversal(bt->lchild);
    printf("%d ",bt->key);
    InorderTraversal(bt->rchild);
    return ;
}

//�������������ö������������ɲ��г���ʵ�֣��������ʽ�磺printf("%d ",bt->key);
void PreorderTraversal(BSTNode *bt){
    if(bt== NIL) return ;
    printf("%d ",bt->key);
    PreorderTraversal(bt->lchild);
    PreorderTraversal(bt->rchild);
    return ;
}


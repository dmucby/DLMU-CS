/*
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

string ss;

struct node
{
    char data,parent;
    node * lchild,*rchild;
    node() :lchild(NULL), rchild(NULL),parent('0'){}
};

void preOrder(node *  &root,int & index,char par_char)
{
    if(index>=ss.size())
    {
        return ;
    }
    if(ss[index]=='0')
    {
        root=NULL;
        index++;
    }
    else
    {
        root=new node;
        root->data=ss[index];
        if(index==0){
            root->parent = '0';
        }
        else{
            root->parent=par_char;
        }
        index++;
        preOrder(root->lchild,index,root->data);
        preOrder(root->rchild,index,root->data);
    }
}

void check(node * root,char s){
    if(root==NULL) return;
    if(s==root->data){
        cout<<root->parent<<endl;
        return;
    }
    check(root->lchild,s);
    check(root->rchild,s);
}

int main(){
    getline(cin,ss);
    node * root=NULL;
    int index=0;int m;char s;
    cin>>m;
    preOrder(root,index,' ');
    node * ans = root;
    for(int i=0;i<m;i++){
        cin>>s;
        check(root,s);
    }
    return 0;
}
*/
#include<stdio.h>
#include <stdlib.h>
#include<cstdio>
#include<cstdlib>
typedef struct NODE {
    int data;
    struct NODE* left;
    struct NODE* right;
}node, *link;

int cnt;
int num[200000]; //´æ´¢¶þ²æÊ÷ÔªËØ

void create(link &t)
{
    int n;
    scanf("%d",&n);
    getchar();
    if (n == 0)
    {
        t = NULL;
        return;
    }
    else
    {
        t = (link)malloc(sizeof(node));
        t->data = n;
        num[cnt] = n;
        cnt++;
        create(t->left);
        create(t->right);
    }
}

void find(link t, int k)
{
    if (t == NULL)
        return;
    if ((t->left != NULL && t->left->data == k )|| (t->right != NULL && t->right->data == k))
    {
        printf("%d\n",t->data);
        return;
    }
    find(t->left, k);
    find(t->right, k);

}



int jud(int k)
{
    for (int i = 0; i < cnt; i++)
    {
        if (num[i] == k)
            return 1;
    }
    return 0;
}

int main()
{
    link tree;
    create(tree);
    int m;
    scanf("%d",&m);
    for (int i = 0; i < m; i++)
    {
        int k;
        scanf("%d",&k);
        if (jud(k))
        {
            if (tree->data == k)
                printf("0\n");
            else
                find(tree, k);
        }
        else
            printf("0\n");
    }
    return 0;
}

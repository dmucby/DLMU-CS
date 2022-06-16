#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include<cstdio>
#include<cstdlib>
using namespace std;

string ss;

typedef struct node
{
    char data;
    struct Treenode * lchild,*rchild;
}Treenode;

/*
void preOrder(node *  &root,int & index)
{
    if(index>=ss.size())
    {
        return ;
    }
    if(ss[index]==' ') index++;
    if(ss[index]=='0')
    {
        root=NULL;
        index++;
    }
    else
    {
        root=new node;
        root->data=ss[index];
        index++;
        preOrder(root->lchild,index);
        preOrder(root->rchild,index);

    }
}
*/

node preOrder(){
    int ch;
    node T;
    scanf("%d",&ch);
    if(ch==0){
        return NULL;
    }
    else{
        T = new node;
        T->data = ch;
        T->lchild = preOrder();
        T->rchild = preOrder();
    }
    return T;
}

void preorder(node * root)
{
    if(root==NULL)
    {
        return ;
    }
    cout<<root->data<<" ";
    preorder(root->lchild);
    preorder(root->rchild);
}

void inOrder(node * root)
{
    if(root==NULL)
    {
        return ;
    }
    inOrder(root->lchild);
    cout<<root->data<<" ";
    inOrder(root->rchild);
}

void postorder(node * root){
    if(root==NULL)
    {
        return ;
    }
    postorder(root->lchild);
    postorder(root->rchild);
    cout<<root->data<<" ";
}

int main()
{
    /*getline(cin,ss);
    node * root=NULL;
    int index=0;
    preOrder(root,index);
    node * s = root;
    */
    node T = preOrder();
    preorder(s);
    cout<<endl;
    inOrder(s);
    cout<<endl;
    postorder(s);
    return 0;
}


/*void preorder(int index){
    for(int i=0;i<n;i++){
        if(index>=n||ans[i]=='0'){
          continue;
        }
        cout<<res[i]<<" ";
    }
    return;
}
void inorder(int index){
    if(index>=n||ans[index]=='0')
        return ;
    inorder(index*2+1);
    cout<<ans[index]<<" ";
    inorder(index*2+2);
}
void postorder(int index){
    if(index>=n||ans[index]=='0')
        return ;
    postorder(index*2+1);
    postorder(index*2+2);
    cout<<ans[index]<<" ";
}

void createTree(int k,int index)
{
    if(index>=n)
    {
        return ;
    }
    if(res[index]=='0')
    {
        index++;
    }
    else
    {
        ans[k]=res[index];
        index++;k++;
        createTree(,index);
        createTree(,index);

    }
}

int main(){
    getline(cin,s);
    //getchar();
    for(int i=0;i<s.size();i++){
       if(s[i]==' '){continue;}
       res.push_back(s[i]);
    }
    n = ans.size();
    createTree(0,0);
    preorder(0);
    cout<<endl;
    inorder(0);
    cout<<endl;
    postorder(0);
    return 0;
}
*/

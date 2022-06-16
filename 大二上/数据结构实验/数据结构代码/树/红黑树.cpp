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

#define NIL &(node::__NIL)

struct node {
    node(int key = 0, int color = 0, node *lchild = NIL, node *rchild = NIL) :
        key(key), color(color), lchild(lchild), rchild(rchild) {}
        int key, color; // 0 red, 1 black
        node *lchild, *rchild;
        static node __NIL;
};

node node::__NIL(0, 1);

node *getNewNode(int key){
    return new node(key);
}

node *left_rotate(node *root){
    node *tmp = root->rchild;
    root->rchild = tmp->lchild;
    tmp->lchild = root;
    return tmp;
}

node *right_rotate(node *root){
    node *tmp = root->lchild;
    root->lchild = tmp->rchild;
    tmp->rchild = root;
    return tmp;
}

bool has_red_color(node *root){
    return root->lchild->color == 0 || root->rchild->color == 0;
}

node *insert_maintain(node *root){
    int flag = 0;
    if(root->lchild->color == 0 && has_red_color(root->lchild)) flag = 1;
    if(root->rchild->color == 0 && has_red_color(root->rchild)) flag = 2;
    if(flag == 0) return root;
    // 情况 1
    if(root->lchild->color == 0 && root->rchild->color == 0){
        root->color = 0;
        root->lchild->color = root->rchild->color = 1;
        return root;
    }
    // 情况 2
    if(flag == 1){// L类型
        if(root->lchild->rchild->color == 0){//LR
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    }else{// R类型
        if(root->rchild->lchild->color == 0){//RL
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    root->color = 0;
    root->lchild->color=root->rchild->color = 1;
    return root;
}

node *__insert(node *root,int key){
    if(root == NIL) return getNewNode(key);
    if(key == root->key) return root;
    if(key < root->key){
        root->lchild = __insert(root->lchild,key);
    }
    else if(key > root->key){
        root->rchild = __insert(root->rchild,key);
    }

    return insert_maintain(root);
}

node *insert(node *root,int key){
    root = __insert(root,key);
    root->color = 1;
    return root;
}

void clear(node *root){
    if(root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    delete root;
    return ;
}

void print(node *root){
    printf("( %d | %d, %d, %d)\n",root->color,root->key,root->lchild->key,root->rchild->key);
    return ;
}

void output(node *root){
    print(root);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main(){
    int val;
    node *root = NIL;
    while(cin >> val){
        root = insert(root,val);
        cout<<endl<<" == rbtree print ====" <<endl;
        output(root);
        cout<<" === rbtree print done ===" <<endl;
    }
    return 0;
}

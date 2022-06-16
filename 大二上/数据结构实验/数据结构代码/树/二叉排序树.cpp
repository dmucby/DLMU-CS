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

typedef struct Node{
    int value,h;
    struct Node *left,*right;
}Node;

// 哨兵节点
Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL(){
    NIL->value = -1;
    NIL->left = NIL->right = NIL;
    NIL->h = 0;
    return ;
}

Node *getNewNode(int value){
    Node *p = (Node*)malloc(sizeof(Node));
    p->value = value;
    p->left = p->right = NIL;
    p->h = 1;
    return p;
}

void update_h(Node *root){
    root->h = max(root->left->h,root->right->h) + 1;
    return ;
}

Node *left_rotate(Node *root){
    Node *tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    update_h(root);
    update_h(tmp);
    return tmp;
}

Node *right_rorate(Node *root){
    Node *tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    update_h(root);
    update_h(tmp);
    return tmp;
}

Node *maintain(Node *root){
    if(abs(root->left->h-root->right->h) <= 1) return root;
    if(root->left->h > root->right->h){// 左子树更高
        if(root->left->right->h > root->left->left->h){ //LR
            root->left = left_rotate(root->left);
        }
        root = right_rorate(root);
    }else{// 右子树更高
        if(root->right->left->h > root->right->right->h){ //RL
            root->right = right_rorate(root->right);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root,int target){
    if(root == NIL) return getNewNode(target);
    if(root->value == target) return root;
    if(root->value > target){
        root->left = insert(root->left,target);
    }else{
        root->right = insert(root->right,target);
    }
    update_h(root);
    return maintain(root);
}

Node *get_pre(Node *root){
    Node *tmp = root;
    while(tmp!=NIL){
        tmp = tmp->right;
    }
    return tmp;
}

Node *erase(Node *root,int target){
    if(root == NIL) return root;
    if(root->value > target){
        root->left = erase(root->left,target);
    }else if(root->value < target){
        root->right = erase(root->right,target);
    }else {
        // 可以将度为1和叶子节点合并 NIL好处
        if(root->left == NIL && root->right == NIL){
            free(root);
            return NIL;
        }else if(root->left == NIL || root->right == NIL){
            Node *tmp = (root->left != NIL ? root->left:root->right);
            free(root);
            return tmp;
        }else{
            Node *tmp = get_pre(root->left);
            root->value = tmp->value;
            root->left = erase(root->left,tmp->value);
        }
    }
    update_h(root);
    return maintain(root);
}

void clear(Node *root){
    if(root == NULL) return;
    clear(root->left);
    clear(root->right);
    free(root);
    return;
}

void in_order(Node *root){
    if(root == NIL) return ;
    in_order(root->left);
    printf("%d ",root->value);
    in_order(root->right);
    return ;
}

void output(Node *root){
    if(root == NIL) return ;
    printf("%d (%d) | %d,%d\n",root->value,root->h,root->left->value,root->right->value);
    output(root->left);
    output(root->right);
    return ;
}

int main(){
    srand(time(0));
    Node *root = NIL;
    int n;
    cin>>n;
    int val;
    for(int i=0;i<n;i++){
        cin>>val;
        printf("\ninsert %d to BST: \n",val);
        root = insert(root,val);
        output(root);
    }
    clear(root);
    return 0;
}

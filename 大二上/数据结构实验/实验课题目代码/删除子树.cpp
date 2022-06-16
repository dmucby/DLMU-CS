#include<stdio.h>
#include <stdlib.h>
#include<cstdio>
#include<cstdlib>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
}node, *link;

int flag;

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
        create(t->left);
        create(t->right);
    }
}

void del(link &t, int k)
{
    if (t == NULL)
        return;
    if (t->data == k)
    {
        t = NULL;
        return;
    }
    if (t->left != NULL)
    del(t->left, k);
    if (t->right != NULL)
    del(t->right, k);
 }

void ok(link t, int k)
{
    if (t == NULL )
        return;
    if (t->data == k)
    {
        flag = 1;
        return;
    }

    if (t->left != NULL)
    ok(t->left, k);
    if (t->right != NULL)
    ok(t->right, k);
}

 void pri(link t)
 {
    if (t)
    {
        pri(t->left);
        printf("%d ",t->data);
        pri(t->right);
    }
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
        ok(tree, k);
        if (flag)
        {
            del(tree, k);
            pri(tree);
            printf("\n");
        }
        else
            printf("0\n");
        flag = 0;
    }
}

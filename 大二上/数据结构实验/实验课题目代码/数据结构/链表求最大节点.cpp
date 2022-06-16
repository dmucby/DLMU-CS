#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>
#define INF -10e6
#include <malloc.h>
#include<algorithm>

struct Node {
    int data;
    struct Node* next;
};

/* 建立单链表并返回单链表的头指针 */
struct Node* buildLinkedList(int* arr, int n);

/* 求单链表值最大的结点 */
struct Node* getMax(struct Node* head);

struct Node* buildLinkedList(int* arr, int n)
{
    Node* L = new Node;
    Node* K = L;
    for (int i = 0; i < n; i++)
    {
        K->data = arr[i];
        K->next = new Node;
        if (i == n - 1)
            K->next = NULL;
        K = K->next;
    }

    return L;
}

struct Node* getMax(struct Node* head)
{
    if (head == NULL)
        return NULL;
    int max = head->data;
    Node* max_N = head;
    while (head != NULL)
    {
        if (head->data >= max)
        {
            max = head->data;
            max_N = head;
        }
        head = head->next;
    }
    return max_N;
}




int main(int argc, char const *argv[])
{
    int *a, n, i;
    scanf("%d", &n);
    a = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    struct Node* head = NULL;

    head = buildLinkedList(a, n);

    struct Node* pMax = getMax(head);
    while (pMax){
        printf("%d\n", pMax->data);
        pMax = pMax->next;
    }
    free(a);

    return 0;
}



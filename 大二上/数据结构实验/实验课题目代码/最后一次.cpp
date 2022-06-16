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

struct LinkList{
    int data;
    LinkList *next;
};

void print(LinkList *L){
    LinkList *p = L;
    while(p!=NULL){
        cout<<p->data<<" ";
        p = p->next;
    }
    return ;
}

LinkList *getNewNode(LinkList *L,int target){
    LinkList *p = new (LinkList);
    p->data = target;
    p->next = L->next;
    L->next = p;
    return L;
}

void ReadData(LinkList *L){
    int n,x;
    cin>>n;
    for(int i=0;i<=n;i++){
        cin>>x;
        if(x==-99){
            return;
        }else{
            L = getNewNode(L,x);
            print(L);
        }
    }
    return ;
}

LinkList *erase(LinkList *L){
    LinkList *p = L;
    LinkList *pre = L;
    p = p->next;
    while(p != NULL){
        if(p->data %2 ==1){
            pre->next = p->next;
            free(p);
            p = pre->next;
        }
        else{
            p = p->next;
            pre = pre->next;
        }
    }
    return L;
}

int main(){
    LinkList *L;
    L = new (LinkList);
    L->data = 0;
    L->next = NULL;
    ReadData(L);
    L = erase(L);
    print(L);
    return 0;
}

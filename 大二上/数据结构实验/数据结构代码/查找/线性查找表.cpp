#include<stdio.h>
#include<stdlib.h>
#define KeyType int
#define InforType int

typedef struct{
    KeyType key;
    InforType otherinfo;
}ElemType;

typedef struct{
    ElemType *R;
    int length;
}SSTable,*Node;

void init(SSTable ST){
    ST.length = 10;
    for(int i=0;i<=9;i++){
        ST.R[i].key = i;
    }
    for(int i=0;i<ST.length;i++){
        printf("%d ",ST.R[i]);
    }
}

// Ë³Ðò²éÕÒÊµÏÖ£¨ÉèÖÃÉÚ±ø£©
int Search(SSTable ST,KeyType key){
    ST.R[0].key = key; // ÉèÖÃÉÚ±ø
    int i=ST.length;
    for(;ST.R[i].key != key;--i);
    printf("%d\n",ST.R[i]);
    return i;
}

int main(){
    SSTable ST;
    init(ST);
    printf("\n");
    printf("%d\n",Search(ST,10));
}

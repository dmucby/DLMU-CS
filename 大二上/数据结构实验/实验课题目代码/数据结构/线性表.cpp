#include<stdio.h>
#include<stdlib.h>
#define OK 1;
#define ERROR 0;

typedef struct Vector{
    int *data;
    int size,length;
}Vector;

void init(int size,Vector *vector){
    vector->size = size;
    vector->length = 0;
    vector->data = (int*)malloc(sizeof(int) * size);
}

int insert(){

}

int delete(){

}

void clear(){

}

void expand(){

}

int search(){

}

int empty(){

}

void print(){

}

int pre_find(){

}

int next_find(){

}

int main(){

}

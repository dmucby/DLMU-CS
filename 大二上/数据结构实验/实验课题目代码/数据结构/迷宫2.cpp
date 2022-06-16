#include <stdio.h>
#include<stdlib.h>
#define M 10
#define N 10
#define STACK_INIT_SIZE 100
#define STACK_INC 10
int flag=0;
typedef struct{
	int x;
	int y;
}Position;

typedef struct{
	Position pos;
	int id;
	int dir;
}ElemType;

typedef struct{
	ElemType *base;
	ElemType *top;
	int StackSize;
}SqStack;

void InitStack(SqStack &S){
	S.base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	S.top=S.base;
	S.StackSize=STACK_INIT_SIZE;
}

void push(SqStack &S,ElemType e){
	if(S.top-S.base>=S.StackSize){
		S.base=(ElemType *)realloc(S.base,(STACK_INIT_SIZE+STACK_INC)*sizeof(ElemType));
		S.top=S.base+S.StackSize;
		S.StackSize+=STACK_INC;
	}
	*S.top=e;
	S.top++;
}

void pop(SqStack &S,ElemType &e){
	S.top--;
	e.dir=(*(S.top)).dir;
	e.id=(*(S.top)).id;
	e.pos.x=(*(S.top)).pos.x;
	e.pos.y=(*(S.top)).pos.y;
}

int StackEmpty(SqStack	S){
	if(S.base==S.top)return 1;
	return 0;
}


void iniarr(int (*p)[N]){
    int i,j;
    int maze[M][N]={1,1,1,1,1,1,1,1,1,1,
    				1,0,1,1,1,0,0,1,0,1,
    				1,0,1,1,0,1,1,1,0,1,
                    1,0,1,1,0,0,0,1,0,1,
                    1,0,1,1,0,1,0,1,0,1,
                    1,0,0,0,0,1,0,1,0,1,
                    1,1,1,1,1,1,0,1,0,1,
                    1,0,1,1,1,0,0,1,0,1,
                    1,1,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1};/***/
    printf("打印迷宫:\n");
    for(i=0;i<M;i++)
    {
    	for(j=0;j<N;j++)
     	{
      		printf("%d",maze[i][j]);
            *(*(p+i)+j)=maze[i][j];/**利用二维数组*/
        }
        printf("\n");
    }
}

void Next(Position	&p,int d){
	switch(d){
		case(1):p.x++;break;
		case(2):p.y++;break;
		case(3):p.x--;break;
		case(4):p.y--;break;
	}
}
void seek(int maze[M][N]){
	int ever[M][N]={0};
	ElemType e;
	SqStack S;
	InitStack(S);
	Position curpos;
	curpos.x=1;
	curpos.y=1;
	int step=1;
	do{
		e.id=step;
		e.pos.x=curpos.x;
		e.pos.y=curpos.y;
		e.dir=1;
		if(maze[curpos.x][curpos.y]==0&&ever[curpos.x][curpos.y]==0){
			push(S,e);
			ever[curpos.x][curpos.y]=1;
			if(curpos.x==M-2&&curpos.y==N-2){
				while(!StackEmpty(S)){
					pop(S,e);
					printf("%d (%d,%d)\n",e.id,e.pos.x,e.pos.y);
				}
				flag=1;
				break;
			}
			Next(curpos,e.dir);
			step++;
		}else{
			if(!StackEmpty(S)){
				pop(S,e);
			}
			while(e.dir==4&&!StackEmpty(S)){
				pop(S,e);
				ever[e.pos.x][e.pos.y]=1;
			}
			if(e.dir<4){
				e.dir++;
				push(S,e);
				curpos.x=e.pos.x;
				curpos.y=e.pos.y;
				Next(curpos,e.dir);
			}
		}
	}while(!StackEmpty(S));
}

int main (){
	int array[M][N];
	iniarr(array);
	seek(array);
	if(flag==0){
		printf("没有出路\n");
	}
	return 0;
}

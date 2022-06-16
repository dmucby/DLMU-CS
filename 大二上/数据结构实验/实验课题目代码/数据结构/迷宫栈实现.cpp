#include<stdio.h>
#include<stdlib.h>
#define M 10
#define N 10
#define MAXSIZE 100

int flag = 0;// 判断是否可以走出迷宫

typedef struct{
    int x;
    int y;
}Position;

typedef struct{
    Position pos;
    int id; // 表示第几步
    int dir; //表示四种移动
}Elemtype;

typedef struct{
    Elemtype *base;
    Elemtype *top;
    int StackSize;
}Stack;

void Init(Stack &s){
    s.base=(Elemtype *) malloc(MAXSIZE*sizeof(Elemtype));
    s.top = s.base;
    s.StackSize = MAXSIZE;
}

void push(Stack &s,Elemtype e){
    if(s.top-s.base>=s.StackSize){
		s.base=(Elemtype *)realloc(s.base,(2*MAXSIZE)*sizeof(Elemtype));
		s.top=s.base+s.StackSize;
		s.StackSize+=MAXSIZE;
	}
    *s.top++=e;
    return ;
}

void pop(Stack &s,Elemtype &e){
    if(s.top == s.base){
        return ;
    }
    e = *--s.top;
    return ;
}

int isEmepty(Stack &s){
    if(s.top == s.base) return 1;
    return 0;
}

void print_mi(int (*p)[N]){
    int i,j;
    int maze[M][N]={0,0,0,0,0,0,0,0,0,0,
    				0,1,0,0,0,1,1,0,1,0,
    				0,1,0,0,1,0,0,0,1,0,
                    0,1,0,0,1,1,1,0,1,0,
                    0,1,0,0,1,0,1,0,1,0,
                    0,1,1,1,1,0,1,0,1,0,
                    0,0,0,0,0,0,1,0,1,0,
                    0,1,0,0,0,1,1,0,1,0,
                    0,0,1,1,1,1,1,1,1,0,
                    0,0,0,0,0,0,0,0,0,0};
                    // 路为1 墙为0
    printf("打印迷宫:\n");
    for(i=0;i<M;i++)
    {
    	for(j=0;j<N;j++)
     	{
      		printf("%d",maze[i][j]);
            *(*(p+i)+j)=maze[i][j];
        }
        printf("\n");
    }
}

// 模拟机器人的四种移动
void Next(Position &pos,int d){
    switch(d){
        case(1) :pos.x++;break;
        case(2) :pos.y++;break;
        case(3) :pos.x--;break;
        case(4) :pos.y--;break;
    }
    return ;
}

void seek(int maze[M][N]){
    int dp[M][N] ={0};//标记该路是否走过
    Elemtype e;
    Stack s;
    Init(s);
    Position cur_pos;//表示当前位置
    cur_pos.x = 1;
    cur_pos.y = 1;//初始化入口
    int step = 1;
    do{
        e.id = step;
        e.pos.x = cur_pos.x;
        e.pos.y = cur_pos.y;
        e.dir = 1;
        if(maze[cur_pos.x][cur_pos.y]==1 && dp[cur_pos.x][cur_pos.y]==0){
            //如果这条路没走过并且不是墙
            push(s,e);// 把该点入栈
            dp[cur_pos.x][cur_pos.y] = 1;//标记该路
            if(cur_pos.x == M-2 && cur_pos.y == N-2){
                while(!isEmepty(s)){
                    pop(s,e);
                    printf("%d (%d,%d)\n",e.id,e.pos.x,e.pos.y);
                }
                flag = 1; //表示能找到出口
                break;
            }
            Next(cur_pos,e.dir);//遍历下一个方向
            step++;
        }else{//该路走过或者是墙 直接把上一个状态出栈
            //如果栈不为空
            if(!isEmepty(s)){
                pop(s,e);
            }
            while(e.dir==4&&!isEmepty(s)){
				pop(s,e);
				dp[e.pos.x][e.pos.y]=1;
			}
            if(e.dir<4){
                //表明还有路可走
                e.dir++;
                push(s,e);
                // 退回上一个状态
                cur_pos.x = e.pos.x;
                cur_pos.y = e.pos.y;
                Next(cur_pos,e.dir);
            }
        }
    }while(!isEmepty(s));
}

int main(){
    int arr[M][N];
    print_mi(arr);
    seek(arr);
    if(flag==0){
        printf("该迷宫是死胡同！\n");
    }
    return 0;
}



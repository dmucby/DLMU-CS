# include<stdio.h>
# include<malloc.h>
# include<stdlib.h>
#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

#define Maxsize 100
#define MaxMatrixsize 2
#define GUARD -99

typedef struct
{
    int r;
    int c;
    int d;
}TupNode;
typedef struct
{
    int rows;
    int cols;
    int nums;
    TupNode data[Maxsize];
}TSMatrix;

//以从键盘输入一维数组的方式初始化一个稀疏矩阵
void inputMatrix(int A[MaxMatrixsize][MaxMatrixsize], int &M, int &N);
//稀疏矩阵加法 C=A+B
bool MatAdd(TSMatrix a,TSMatrix b,TSMatrix &c);
//稀疏矩阵的乘法 C=A*B
bool MatMul(TSMatrix a,TSMatrix b,TSMatrix &c);
//转置三元组表示的稀疏矩阵
void TranTat(TSMatrix t,TSMatrix &tb);

//创建稀疏矩阵的三元组表示
void CreatMat(TSMatrix &t)
{
    int A[MaxMatrixsize][MaxMatrixsize]={0};
    int m=MaxMatrixsize;
    int n=MaxMatrixsize;
    inputMatrix(A,m,n);
    int i,j;

    t.rows=m;
    t.cols=n;
    t.nums=0;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(A[i][j]!=0)
            {
                t.data[t.nums].r=i;t.data[t.nums].c=j;
                t.data[t.nums].d=A[i][j];t.nums++;
            }
        }
    }
}

//以三元组的方式输出矩阵内容
void DispMat(TSMatrix t)
{
    int i;
    if(t.nums<=0)
        return;
    printf("%dx%d    %d\n",t.rows,t.cols,t.nums);
    printf("---------\n");
    for(i=0;i<t.nums;i++)
            printf("%d  %d   %d\n",t.data[i].r,t.data[i].c,t.data[i].d);
}

//去i行j列的值
int getvalue(TSMatrix c,int i,int j)
{
    int k=0;
    while (k<c.nums && (c.data[k].r!=i || c.data[k].c!=j))
        k++;
    if (k<c.nums)
        return(c.data[k].d);
    else
        return(0);
}

//以从键盘输入一维数组的方式初始化一个稀疏矩阵
void inputMatrix(int A[MaxMatrixsize][MaxMatrixsize], int &M, int &N){
    int x,m,n;
    scanf("%d %d",&m,&n);
    M = m;
    N = n;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&x);
            if(x==-99){
                break;
            }
            A[i][j]=x;
        }
    }
}

//稀疏矩阵加法 C=A+B
bool MatAdd(TSMatrix a,TSMatrix b,TSMatrix &c){
    if(a.rows!=b.rows || a.cols != b.cols){
        return false;
    }
    int i=0,j=0,k=0;
    c.rows = a.rows;
    c.cols = a.cols;
    c.nums = 0;
    if(a.nums*b.nums == 0){
        return true;
    }
    while(i < a.nums && j < b.nums){
            // ab均不为空
        if(a.data[i].r < b.data[j].r || (a.data[i].r == b.data[j].r && a.data[i].c < b.data[j].c)){
            // 确保A在B前
            c.nums++;
            c.data[k++] = a.data[i++];
            // 将a付给c
        }
        else if(a.data[i].c == b.data[j].c && a.data[i].r == b.data[j].r){
            if(a.data[i].d + b.data[j].d !=0){
                c.data[k].c =a.data[i].c;
                c.data[k].r=a.data[i].r;
                c.data[k++].d=a.data[i].d+b.data[j].d;
                c.nums++;
            }
            i++;
            j++;
        }
        else if(a.data[i].r > b.data[j].r ||(a.data[i].r == b.data[j].r && a.data[i].c > b.data[j].c)){//b节点在a前
            c.nums++;
            c.data[k++] = b.data[j++];
        }
    }
    while(i < a.nums){//将矩阵a的剩余元素插入矩阵
        c.nums++;
        c.data[k++] = a.data[i++];
    }
    while(j < b.nums){//将矩阵b的剩余元素插入矩阵
        c.nums++;
        c.data[k++] = b.data[j++];
    }
    return true;
}

//稀疏矩阵的乘法 C=A*B
bool MatMul(TSMatrix a,TSMatrix b,TSMatrix &c){
    if(a.rows!=b.cols || a.rows != b.cols){
        return false;
    }
    int A[MaxMatrixsize][MaxMatrixsize] = { 0 };
    int B[MaxMatrixsize][MaxMatrixsize] = { 0 };
    int C[MaxMatrixsize][MaxMatrixsize] = { 0 };

    for (int i = 0; i < a.nums; i++) {
        A[a.data[i].r][a.data[i].c] = a.data[i].d;
    }
    for (int i = 0; i < b.nums; i++) {
        B[b.data[i].r][b.data[i].c] = b.data[i].d;
    }
    int rowA = a.rows;
    int rowB = b.rows;
    int colA = a.cols;
    int colB = b.cols;
    if (colA != rowB || rowA!=colB) {
        return false;
    }
    c.rows = a.rows;
    c.cols = b.cols;
    c.nums = 0;

    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            for (int k = 0; k < colA; k++) {
                C[i][j] += (A[i][k] * B[k][j]);
            }


            if (C[i][j] != 0)
            {
                c.data[c.nums].r = i;
                c.data[c.nums].c = j;
                c.data[c.nums].d = C[i][j];
                c.nums++;
            }
        }
    }
    return true;
}


//转置三元组表示的稀疏矩阵
void TranTat(TSMatrix t,TSMatrix &tb){
    int A[MaxMatrixsize][MaxMatrixsize] = { 0 };
    for (int i = 0; i < t.nums; i++) {
        A[t.data[i].r][t.data[i].c] = t.data[i].d;
    }

    int m = t.rows;
    int n = t.cols;
    tb.rows = t.cols;
    tb.cols = t.rows;
    tb.nums = 0;


    for (int i = 0; i < m; i++) {
        for (int j = i ; j < n; j++) {
            int tmp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = tmp;
            if (A[i][j] != 0)
            {
                tb.data[tb.nums].r = i;
                tb.data[tb.nums].c = j;
                tb.data[tb.nums].d = A[i][j];
                tb.nums++;
            }
            if (i == j) {
                continue;
            }
            if (A[j][i] != 0)
            {
                tb.data[tb.nums].r = j;
                tb.data[tb.nums].c = i;
                tb.data[tb.nums].d = A[j][i];
                tb.nums++;
            }
        }
    }
}

// 输入 4
// 1 1 1
// 2 2 1 2 3 4
// 对于矩阵不等的输出


// 对于特殊矩阵的乘法运算
//
//



int main()
{

    TSMatrix a,b,c;
    int m=MaxMatrixsize;
    int n=MaxMatrixsize;
    int choice;
    for (;;)
    {
        D(printf("\n           数组的基本操作——矩阵的稀疏表示  \n");)
        D(printf("             1.从终端以一维数组的方式输入一个矩阵\n");)
        D(printf("             2.以三元组的方式输出矩阵内容\n");)
        D(printf("             3.矩阵求和\n");)
        D(printf("             4.矩阵乘法\n");)
        D(printf("             5.矩阵的转置\n");)
        D(printf("             6.退出系统\n");)
        D(printf("请选择：");)
        scanf("%d", &choice);
        switch (choice)
        {
        case 1: CreatMat(a);
                break;
        case 2: D(printf("输入矩阵的三元组为:\n");)
                DispMat(a);
                break;
        case 3: D(printf("输输入矩阵1 : \n");)
                CreatMat(a);
                D(printf("输输入矩阵2 : \n");)
                CreatMat(b);
                MatAdd(a,b,c);
                D(printf("矩阵之和的三元组为:\n");)
                DispMat(c);
                break;
        case 4: D(printf("输输入矩阵1 : \n");)
                CreatMat(a);
                D(printf("输输入矩阵2 : \n");)
                CreatMat(b);
                MatMul(a,b,c);
                D(printf("矩阵之积的三元组为:\n");)
                DispMat(c);
                break;
        case 5: D(printf("转置矩阵的三元组为:\n");)
                TranTat(a, b);
                DispMat(b);
                break;
        case 6: D(printf("请退出系统!\n");)
                exit(0); break;
        }
    }
    return 1;
}
/* 请在这里填写答案 */

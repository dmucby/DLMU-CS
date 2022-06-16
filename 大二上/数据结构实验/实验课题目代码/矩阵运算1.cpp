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

//�ԴӼ�������һά����ķ�ʽ��ʼ��һ��ϡ�����
void inputMatrix(int A[MaxMatrixsize][MaxMatrixsize], int &M, int &N);
//ϡ�����ӷ� C=A+B
bool MatAdd(TSMatrix a,TSMatrix b,TSMatrix &c);
//ϡ�����ĳ˷� C=A*B
bool MatMul(TSMatrix a,TSMatrix b,TSMatrix &c);
//ת����Ԫ���ʾ��ϡ�����
void TranTat(TSMatrix t,TSMatrix &tb);

//����ϡ��������Ԫ���ʾ
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

//����Ԫ��ķ�ʽ�����������
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

//ȥi��j�е�ֵ
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

//�ԴӼ�������һά����ķ�ʽ��ʼ��һ��ϡ�����
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

//ϡ�����ӷ� C=A+B
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
            // ab����Ϊ��
        if(a.data[i].r < b.data[j].r || (a.data[i].r == b.data[j].r && a.data[i].c < b.data[j].c)){
            // ȷ��A��Bǰ
            c.nums++;
            c.data[k++] = a.data[i++];
            // ��a����c
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
        else if(a.data[i].r > b.data[j].r ||(a.data[i].r == b.data[j].r && a.data[i].c > b.data[j].c)){//b�ڵ���aǰ
            c.nums++;
            c.data[k++] = b.data[j++];
        }
    }
    while(i < a.nums){//������a��ʣ��Ԫ�ز������
        c.nums++;
        c.data[k++] = a.data[i++];
    }
    while(j < b.nums){//������b��ʣ��Ԫ�ز������
        c.nums++;
        c.data[k++] = b.data[j++];
    }
    return true;
}

//ϡ�����ĳ˷� C=A*B
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


//ת����Ԫ���ʾ��ϡ�����
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

// ���� 4
// 1 1 1
// 2 2 1 2 3 4
// ���ھ��󲻵ȵ����


// �����������ĳ˷�����
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
        D(printf("\n           ����Ļ����������������ϡ���ʾ  \n");)
        D(printf("             1.���ն���һά����ķ�ʽ����һ������\n");)
        D(printf("             2.����Ԫ��ķ�ʽ�����������\n");)
        D(printf("             3.�������\n");)
        D(printf("             4.����˷�\n");)
        D(printf("             5.�����ת��\n");)
        D(printf("             6.�˳�ϵͳ\n");)
        D(printf("��ѡ��");)
        scanf("%d", &choice);
        switch (choice)
        {
        case 1: CreatMat(a);
                break;
        case 2: D(printf("����������Ԫ��Ϊ:\n");)
                DispMat(a);
                break;
        case 3: D(printf("���������1 : \n");)
                CreatMat(a);
                D(printf("���������2 : \n");)
                CreatMat(b);
                MatAdd(a,b,c);
                D(printf("����֮�͵���Ԫ��Ϊ:\n");)
                DispMat(c);
                break;
        case 4: D(printf("���������1 : \n");)
                CreatMat(a);
                D(printf("���������2 : \n");)
                CreatMat(b);
                MatMul(a,b,c);
                D(printf("����֮������Ԫ��Ϊ:\n");)
                DispMat(c);
                break;
        case 5: D(printf("ת�þ������Ԫ��Ϊ:\n");)
                TranTat(a, b);
                DispMat(b);
                break;
        case 6: D(printf("���˳�ϵͳ!\n");)
                exit(0); break;
        }
    }
    return 1;
}
/* ����������д�� */

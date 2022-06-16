#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define n 6      //叶子数目
#define m 2*n-1  //结点总数
#define Maxval 1 //最大权值
typedef char datatype;
typedef struct //定义为结构类型
{
    float weight;//权值
    datatype data;
    int lchild, rchild, parent;
} hufmtree;
hufmtree tree[m];
typedef struct
{
    char bits[n];//编码数组位串，其中n为叶子结点数目
    int start;//编码在位串的起始位置
    datatype data;
} codetype;
codetype code[n];

void HUFFMAN(hufmtree tree[ ])//构建哈夫曼树
{
    int i, j, p1,p2;
    char 	ch;
    float small1,small2,f;
    for( i=0; i<m; i++)//初始化
    {
        tree[i].parent=0;
        tree[i].lchild=0;
        tree[i].rchild=0;
        tree[i].weight=0.0;
        tree[i].data= '0';
    }
    for(i=0; i<n; i++)
    {
        scanf("%f ", &f);//输入n个结点的权值
        tree[i].weight=f;
        scanf("%c", &ch);// 输入n个结点的值
        tree[i].data=ch;
    }
    for(i=n; i<m; i++)
    {
        p1=p2=0;//最小的两个权值所对应的数组tree下标
        small1=small2=Maxval;//最小的两个权值
        for ( j=0; j<=i-1; j++ )//最后一个存储的权值下标为i
            if ( tree[j].parent==0)//若此结点还未“放入”二叉树
            {
                if ( tree[j].weight<small1 )//若这个数比small1还小
                {
                    small2=small1;//small2是次小的
                    small1=tree[j].weight;
                    p2=p1;
                    p1=j;
                }
                else  if( tree[j].weight<small2 )
                {
                    small2=tree[j].weight;
                    p2=j;
                }
            }
        //运行到这里我们就找到了最小的两个权值
        tree[i].lchild=p1;//权值最小的两个两棵二叉树作为左子树和右子树，从而构造一棵心得二叉树
        tree[i].rchild=p2;
        tree[p1].parent=i;//这棵新的二叉树的根结点的权值为其左、右子树根结点的权值和
        tree[p2].parent=i;
        tree[i].weight = tree[p1].weight+tree[p2].weight;//将两个权值和放入数组tree中
    }
    ///注意编码完后tree数组只有一个元素没有父亲结点（对应的parent为0），即根结点，它的权值最大
    ///且我们所编码的元素都在叶子结点
}
void HUFFMANCODE(codetype code[ ],hufmtree tree[ ] )
//求出存放的哈夫曼编码的数组
{
    int i, c, p;
    codetype cd;
    for ( i=0; i<n; i++ )//按照输入顺序，每个元素向上层（其父亲结点）遍历得出其编码（一直遍历到根节点）
    {
        cd.start=n;//逆序存，编码最大长度不会超过n
        c=i;
        p=tree[c].parent;//p是一个中间变量，表示此时所在结点的父亲结点（在数组tree中对应的下标）
        cd.data=tree[c].data;//正在进行编码的元素
        while( p!=0 )//未遍历到根结点
        {
            cd.start--;
            if( tree[p]. lchild == c)//向左的分支标记为零
                cd.bits[cd.start]= '0';
            else
                cd.bits [cd.start]='1';
            c=p;//更新所在结点为其父亲结点
            p=tree[c].parent;//更新为此时所对应的父亲结点
        }
        code[i]=cd;//将第i个元素的编码存入数组code（结构体之间可以直接进行赋值操作）
        printf("%c:",cd.data );//输出cd的数据语句
        for(int k=cd.start; k<n; k++)
            printf("%c",cd.bits[k]);//紧跟着输出其编码
        printf("\n");

    }

}
void HUFFMANDECODE(codetype code[ ],hufmtree tree[ ])
{
    int i, b;
    int endflag=2;//2表示结束
    i=m-1;
    scanf ( "%1d", &b);//输入密码（整形输入，只不过格式化其长度为1）
    while ( b != endflag)
    {
        if( b==0)
            i=tree[i].lchild;
        else
            i=tree[i].rchild;
        if ( tree[i].lchild==0 )//遍历到叶子结点
        {
            putchar( code[i].data);//输出译码
            i=m-1;
        }
        scanf("%1d", &b);
    }
    if ((tree[i].lchild!=0)&&(i!=m-1))
        printf("\nERROR\n");
}
int main()
{
    printf("输入结点的权值和结点字母，用空格隔开:(如：0.4 a)\n");
    HUFFMAN( tree);
    printf("\n编码结果\n");
    HUFFMANCODE(code, tree );
    printf("\n开始译码，请输入密码：\n");
    HUFFMANDECODE(code, tree);
    printf("\n");
    return 0;
}
//0.4 A 0.3 B 0.1 C 0.1 D 0.02 E 0.08 F
//11101000101012


}


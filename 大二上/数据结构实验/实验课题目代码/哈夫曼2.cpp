#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define n 6      //Ҷ����Ŀ
#define m 2*n-1  //�������
#define Maxval 1 //���Ȩֵ
typedef char datatype;
typedef struct //����Ϊ�ṹ����
{
    float weight;//Ȩֵ
    datatype data;
    int lchild, rchild, parent;
} hufmtree;
hufmtree tree[m];
typedef struct
{
    char bits[n];//��������λ��������nΪҶ�ӽ����Ŀ
    int start;//������λ������ʼλ��
    datatype data;
} codetype;
codetype code[n];

void HUFFMAN(hufmtree tree[ ])//������������
{
    int i, j, p1,p2;
    char 	ch;
    float small1,small2,f;
    for( i=0; i<m; i++)//��ʼ��
    {
        tree[i].parent=0;
        tree[i].lchild=0;
        tree[i].rchild=0;
        tree[i].weight=0.0;
        tree[i].data= '0';
    }
    for(i=0; i<n; i++)
    {
        scanf("%f ", &f);//����n������Ȩֵ
        tree[i].weight=f;
        scanf("%c", &ch);// ����n������ֵ
        tree[i].data=ch;
    }
    for(i=n; i<m; i++)
    {
        p1=p2=0;//��С������Ȩֵ����Ӧ������tree�±�
        small1=small2=Maxval;//��С������Ȩֵ
        for ( j=0; j<=i-1; j++ )//���һ���洢��Ȩֵ�±�Ϊi
            if ( tree[j].parent==0)//���˽�㻹δ�����롱������
            {
                if ( tree[j].weight<small1 )//���������small1��С
                {
                    small2=small1;//small2�Ǵ�С��
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
        //���е��������Ǿ��ҵ�����С������Ȩֵ
        tree[i].lchild=p1;//Ȩֵ��С���������ö�������Ϊ�����������������Ӷ�����һ���ĵö�����
        tree[i].rchild=p2;
        tree[p1].parent=i;//����µĶ������ĸ�����ȨֵΪ����������������Ȩֵ��
        tree[p2].parent=i;
        tree[i].weight = tree[p1].weight+tree[p2].weight;//������Ȩֵ�ͷ�������tree��
    }
    ///ע��������tree����ֻ��һ��Ԫ��û�и��׽�㣨��Ӧ��parentΪ0����������㣬����Ȩֵ���
    ///�������������Ԫ�ض���Ҷ�ӽ��
}
void HUFFMANCODE(codetype code[ ],hufmtree tree[ ] )
//�����ŵĹ��������������
{
    int i, c, p;
    codetype cd;
    for ( i=0; i<n; i++ )//��������˳��ÿ��Ԫ�����ϲ㣨�丸�׽�㣩�����ó�����루һֱ���������ڵ㣩
    {
        cd.start=n;//����棬������󳤶Ȳ��ᳬ��n
        c=i;
        p=tree[c].parent;//p��һ���м��������ʾ��ʱ���ڽ��ĸ��׽�㣨������tree�ж�Ӧ���±꣩
        cd.data=tree[c].data;//���ڽ��б����Ԫ��
        while( p!=0 )//δ�����������
        {
            cd.start--;
            if( tree[p]. lchild == c)//����ķ�֧���Ϊ��
                cd.bits[cd.start]= '0';
            else
                cd.bits [cd.start]='1';
            c=p;//�������ڽ��Ϊ�丸�׽��
            p=tree[c].parent;//����Ϊ��ʱ����Ӧ�ĸ��׽��
        }
        code[i]=cd;//����i��Ԫ�صı����������code���ṹ��֮�����ֱ�ӽ��и�ֵ������
        printf("%c:",cd.data );//���cd���������
        for(int k=cd.start; k<n; k++)
            printf("%c",cd.bits[k]);//��������������
        printf("\n");

    }

}
void HUFFMANDECODE(codetype code[ ],hufmtree tree[ ])
{
    int i, b;
    int endflag=2;//2��ʾ����
    i=m-1;
    scanf ( "%1d", &b);//�������루�������룬ֻ������ʽ���䳤��Ϊ1��
    while ( b != endflag)
    {
        if( b==0)
            i=tree[i].lchild;
        else
            i=tree[i].rchild;
        if ( tree[i].lchild==0 )//������Ҷ�ӽ��
        {
            putchar( code[i].data);//�������
            i=m-1;
        }
        scanf("%1d", &b);
    }
    if ((tree[i].lchild!=0)&&(i!=m-1))
        printf("\nERROR\n");
}
int main()
{
    printf("�������Ȩֵ�ͽ����ĸ���ÿո����:(�磺0.4 a)\n");
    HUFFMAN( tree);
    printf("\n������\n");
    HUFFMANCODE(code, tree );
    printf("\n��ʼ���룬���������룺\n");
    HUFFMANDECODE(code, tree);
    printf("\n");
    return 0;
}
//0.4 A 0.3 B 0.1 C 0.1 D 0.02 E 0.08 F
//11101000101012


}


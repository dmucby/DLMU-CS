#include <stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct Node
{
char data;
int weight; //Ȩֵ
int parent; //���ڵ����ţ�Ϊ-1���Ǹ��ڵ�
int lchild, rchild; //���Һ��ӽڵ����ţ�Ϊ-1����Ҷ�ӽڵ�
}HTNode, *HuffmanTree; //�����洢�շ������е����нڵ�
typedef char **HuffmanCode; //�����洢ÿ��Ҷ�ӽڵ�ĺշ�������
char *str;
HuffmanTree create_HuffmanTree(int *wet, int n,char * o1);
void select_minium(HuffmanTree HT, int k, int &min1, int &min2);
int min(HuffmanTree HT, int k);
void HuffmanCoding1(HuffmanTree HT, HuffmanCode &HC, int n,int *num1);
void HuffmanDecode(HuffmanTree tree,int n,char * code);

//�������� �����ַ�����Ȩ·������
int countWPL2(HuffmanTree HT, int n)
{
int cur = 2 * n - 2; //��ǰ�������Ľڵ����ţ���ʼʱΪ���ڵ����
int countRoads=0, WPL=0;//countRoads����Ҷ�ӽ���·������
//�����úշ������󣬰�visit[]��������������ʱÿ���ڵ��״̬��־
//visit[cur]=0������ǰ�ڵ�����Һ��Ӷ���û�б�����
//visit[cur]=1��ʾ��ǰ�ڵ�������Ѿ������������Һ�����δ������
//visit[cur]=2��ʾ��ǰ�ڵ�����Һ��Ӿ���������
int visit[5000] = { 0 };//visit[]�Ǳ�ע����,��ʼ��Ϊ0����СӦͬ��Ϊ5000
//�Ӹ��ڵ㿪ʼ���������ص����ڵ����
//��curΪ���ڵ��parentʱ���˳�ѭ��
while (cur != -1)
{
//���Һ��Ӿ�δ�����������������
if (visit[cur]==0)
{
visit[cur] = 1; //�����������Ѿ�����������
if (HT[cur].lchild != -1)
{ //�����ǰ�ڵ㲻��Ҷ�ӽڵ㣬��·������+1���������������
countRoads++;
cur = HT[cur].lchild;
}
else
{ //�����ǰ�ڵ���Ҷ�ӽڵ㣬�����˽��Ĵ�Ȩ·�����ȣ������䱣������
WPL += countRoads * HT[cur].weight;
}
}
//�����ѱ���������ʼ���ұ����Һ���
else if (visit[cur]==1)
{
visit[cur] = 2;
if (HT[cur].rchild != -1)
{ //�����ǰ�ڵ㲻��Ҷ�ӽڵ㣬����±��룬���������ұ���
countRoads++;
cur = HT[cur].rchild;
}
}
//���Һ��Ӿ��ѱ��������˻ص����ڵ㣬ͬʱ·������-1
else
{
visit[cur] = 0;
cur = HT[cur].parent;
countRoads--;
}
}
return WPL;
}

void removeDuplicate2(char s[]) //��ȥ�ַ������ظ��ַ���������ԭ��˳�򲻱䣬���ַ���ʵ�ʳ��ȱ�Ϊ�����󳤶�
{
unsigned int check = 0;
int len = strlen(s);
int j = 0;
int v = 0;
for (int i = 0; i < len; i++)
{
v = s[i] - 'a';
if (!(check & (1 << v)))
{
s[j] = s[i];
j++;
check |= (1 << v);
}
}
s[j] = '\0';
}

//�������� ����Ȩֵ����num��char���ַ���ʵ����������
void InsertionSort(int *k,char num[],char *HC,int n)

{
int i = 0;
int j = 0;
int k1=0;
char tmp = 0;
char  t1;
for(i = 1;i<n;i++)
{
    k1=k[i];
    t1=HC[i];
    tmp = num[i];//�Ӵ�������ȡ����һ��Ԫ�ء�
    j = i-1; //i-1��Ϊ���������һ��Ԫ�أ��������Ԫ�����ڣ����±�
while(j>=0 && k1<k[j]) //ע���ж�����Ϊ������j>=0������б߽����ơ��ڶ���Ϊ�����ж�����
{
k[j+1]=k[j];
HC[j+1]=HC[j];
num[j+1] = num[j];//�����Ǻ���λ�ã�������Ԫ������ƶ�
j--;
}
k[j+1]=k1;
HC[j+1]=t1;
num[j+1] = tmp;//�ҵ�����λ�ã���Ԫ�ز��롣
    }
}

int main(){
    int i;
char data[26];
int num[26];
memset(num,0,4*26);
data[0]='a';
for(i=1;i<26;i++) //data����洢����Сд��ĸ
{
data[i]=(char)(data[i-1]+1);
}
str=(char *)malloc(sizeof(char ) * 5000);
scanf("%s",str);
int len=strlen(str);
for(i=0;i<len;i++) //ͳ���ַ����и��ַ�Ȩֵ
{
for(int j=0;j<26;j++)
{
if(str[i]==data[j]) num[j]++;
}
}
//int temp=num[0];

char  o1[5000];  //�ַ������Ϊ5000�����ֵ������Ϊ��ʼ�Ǹ���str���豣֤�ռ��㹻����ֹ���
strcpy(o1,str);
removeDuplicate2(o1);
int len1=strlen(o1);
//m=len1;
int n=0;
int num1[26];
for(int j=0;j<26;j++)  //�õ�str�ַ�˳��Ȩֵ����
{
     if(num[j]!=0) {
         for(int i=0;i<len1;i++){
           if(o1[i]==data[j]) num1[i]=num[j];
         }
         n++;
         //i++;
         //num1[i++]=num[j];   ���Թ���
        //printf("%c ",data[j]);
     }
}

//for(int i=0;i<len1;i++){
  //if(o1[i]==data[0]) num1[i]=temp; }
//printf("%d..",num1[0]);
HuffmanCode HC = NULL;
HuffmanTree hTree = create_HuffmanTree(num1, n,o1);
//InsertSort(num1,n);

char code1[5000],code2[5000];  //�ռ俪��5000����ͬ�� �Ӵ�o1
scanf("%s",code1);
scanf("%s",code2);
int WPL=countWPL2(hTree,n);
float judge=(float)WPL/8; // ���ѹ�����ı���С
int judge1=WPL/8;
printf("%d ",len);
if(judge>judge1) printf("%d\n",judge1+1);
else printf("%d\n",judge1);
HuffmanCoding1(hTree, HC, n,num1);
HuffmanDecode(hTree,n,code1);
printf("\n");
HuffmanDecode(hTree,n,code2);

//decode(hTree);
//HuffmanDecode(hTree,str,jie);
//printf("%s\n",a);
// printf("%s\n",n1);
return 0;
}


/*�������ܣ� ��������ṹ�崴��������Ӧ��������
���� Ȩֵ���飬�����С���Լ����ظ��ַ�����
��� ����������� */
HuffmanTree create_HuffmanTree(int *wet, int n,char * o1)
{

//һ����n��Ҷ�ӽڵ�ĺշ���������2n-1���ڵ�
int total = 2 * n - 1;
HuffmanTree HT = (HuffmanTree)malloc(total * sizeof(HTNode));
int i;
//���³�ʼ�����ȫ����-1��ʾ��
//�����ڱ��뺯���н���ѭ���ж�parent��lchild��rchild�����ʱ��
//������HT�����е��κ�һ���±����
//HT[0],HT[1]...HT[n-1]�д����Ҫ�����n��Ҷ�ӽڵ�

for (i = 0; i < n; i++)
{
    HT[i].data=o1[i];
    HT[i].parent = -1;
    HT[i].lchild = -1;
    HT[i].rchild = -1;
    HT[i].weight = *wet;
    wet++;
}
//HT[n],HT[n+1]...HT[2n-2]�д�ŵ����м乹�����ÿ�ö������ĸ��ڵ�

for (; i < total; i++)
{
    HT[i].parent = -1;
    HT[i].lchild = -1;
    HT[i].rchild = -1;
    HT[i].weight = 0;
    HT[i].data='.';
}

int min1, min2; //��������ÿһ��ѡ��������weight��С��parentΪ0�Ľڵ�

//ÿһ�ֱȽϺ�ѡ���min1��min2����һ�ζ�����,��󹹳�һ�úշ�����

for (i = n; i < total; i++)
{
    select_minium(HT, i, min1, min2);
    HT[min1].parent = i;
    HT[min2].parent = i;
    //�������Ӻ��Һ��ӿ��Է����������ɵ�Ҳ��һ�úշ�������ֻ�����õı��벻ͬ
    HT[i].lchild = min1;
    HT[i].rchild = min2;
    HT[i].weight = HT[min1].weight + HT[min2].weight;
}
return HT;

}
/*
��HT�����ǰk��Ԫ����ѡ��weight��С��parentΪ-1���������ֱ�����ű�����min1��min2��
*/
void select_minium(HuffmanTree HT, int k, int &min1, int &min2)
{
min1 = min(HT, k);
min2 = min(HT, k);
}

/*

��HT�����ǰk��Ԫ����ѡ��weight��С��parentΪ-1��Ԫ�أ�������Ԫ�ص���ŷ���
*/
int min(HuffmanTree HT, int k)
{

int i = 0;
int min;        //�������weight��С��parentΪ-1��Ԫ�ص����
int min_weight; //�������weight��С��parentΪ-1��Ԫ�ص�weightֵ

//�Ƚ���һ��parentΪ-1��Ԫ�ص�weightֵ����min_weight,�����Ժ�Ƚ��á�
//ע�⣬���ﲻ�ܰ���һ�����������ֱ�ӽ�HT[0].weight����min_weight��
//��Ϊ���HT[0].weight��ֵ�Ƚ�С����ô�ڵ�һ�ι��������ʱ�ͻᱻѡ�ߣ�
//��������ÿһ��ѡ����СȨֵ����������ıȽϻ�������HT[0].weight��ֵ�������жϣ�
//�����ֻ��ٴν���ѡ�ߣ��Ӷ������߼��ϵĴ���

while (HT[i].parent != -1)
    i++;
min_weight = HT[i].weight;
min = i;
//ѡ��weight��С��parentΪ-1��Ԫ�أ���������Ÿ���min
for (; i < k; i++)
{
    if (HT[i].weight < min_weight && HT[i].parent == -1)
    {
        min_weight = HT[i].weight;
        min = i;
    }
}
//ѡ��weight��С��Ԫ�غ󣬽���parent��1��ʹ����һ�αȽ�ʱ�����ų����⡣
HT[min].parent = 1;
return min;

}

/* �������� ʵ�ֶԶ�����code�ַ�����������
�������� �������������������ڵ��������������ַ���
������� ��������ַ���
�ѵ��� ����б𲻺Ϸ��������У�ͨ�����ñ���b��ÿ�δӸ���ʼ����ʱ��ֵ��Ϊ0��ÿ�ε���Ҷ�ڵ���b=1��
���ѭ������ʱb=0��˵�� �ַ�������������δ����Ҷ�ڵ�
*/

void HuffmanDecode(HuffmanTree tree,int n,char *code)
{

int i,c;
char out[5000];

//for(i=0; i<100; ++i) code[i] = '\0';    // ��ʼ��code���飨code�����洢���ģ�����char[]��

//scanf("%s",code);
char *m;
m = code;
int j=0;
c = 2*n -2;    //    ���������ĸ��ڵ��±�
int b;
memset(out,'\0',5000*sizeof(char));
while( *m != '\0') {
    b=0;
    if( *m== '0'){
        c = i =tree[c].lchild;
        if(tree[c].lchild==-1&&tree[c].rchild==-1){ // Ҷ�ӽڵ�
           out[j]=tree[i].data;  j++; b=1;
            c = 2*n - 2;    //if(tree[c].data=='.') b=0;p=p+tree[i].weight;
        }
    }
    if( *m == '1'){
        c = i = tree[c].rchild;
        if(tree[c].lchild == -1 && tree[c].rchild == -1) {    // Ҷ�ӽڵ�
            out[j]=tree[i].data;  j++;b=1;
         //if(tree[c].data=='.') b=0;p=p+tree[i].weight;
         //if(tree[c].lchild!=-1 || tree[c].data==-1) b=0;
            c = 2*n-2;    // ���´Ӹ�����
        }
    }
    m++;
}
//if(tree[c].data=='.') b=0;if(p!=k)
//printf("%d\n",k); if(tree[c].lchild!=-1 && *m=='\0')
if(b==0) printf("INVALID");
else printf("%s",out);

}

/*
��Ҷ�ӽڵ㵽���ڵ�������շ�����HT��n��Ҷ�ӽڵ�ĺշ������룬��������HC��
*/

void HuffmanCoding1(HuffmanTree HT, HuffmanCode &HC, int n,int *num1)
{

    //��������ָ��ÿ���շ������봮��ָ��
    HC = (HuffmanCode)malloc(n * sizeof(char *));
    //��ʱ�ռ䣬��������ÿ����õĺշ������봮
    //������n��Ҷ�ӽڵ�ĺշ���������Ҷ�ӽڵ�ı��볤���������n-1
    //���һ��'\0'����������˷�������鳤���Ϊn����
    char *code = (char *)malloc(n * sizeof(char));
    code[n - 1] = '\0';  //����������������ַ�����Ľ�����־
                     //��ÿ���ַ��ĺշ�������

    int i;
    for (i = 0; i < n; i++)
    {
        int current = i;           //���嵱ǰ���ʵĽڵ�
        int father = HT[i].parent; //��ǰ�ڵ�ĸ��ڵ�
        int start = n - 1;           //ÿ�α����λ�ã���ʼΪ�����������λ��
                                 //��Ҷ�ӽڵ�����շ�����ֱ�����ڵ�

        while (father != -1)
        {
            if (HT[father].lchild == current)   //��������ӣ������Ϊ0
                code[--start] = '0';
            else                              //������Һ��ӣ������Ϊ1
                code[--start] = '1';
            current = father;
            father = HT[father].parent;
    }

    //Ϊ��i���ַ��ı��봮����洢�ռ�
    HC[i] = (char *)malloc((n - start) * sizeof(char));

    //�����봮��code���Ƶ�HC
    strcpy(HC[i], code + start);
}
    char order[5000];
    strcpy(order,str);
    removeDuplicate2(order);
    InsertionSort(num1,order,*HC,n);
    for (int i =0; i<n; i++) {
        printf("%c:%s\n",order[i], HC[i]);
    }
    free(code); //�ͷű�����봮����ʱ�ռ�

}

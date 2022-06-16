#include <stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct Node
{
char data;
int weight; //权值
int parent; //父节点的序号，为-1的是根节点
int lchild, rchild; //左右孩子节点的序号，为-1的是叶子节点
}HTNode, *HuffmanTree; //用来存储赫夫曼树中的所有节点
typedef char **HuffmanCode; //用来存储每个叶子节点的赫夫曼编码
char *str;
HuffmanTree create_HuffmanTree(int *wet, int n,char * o1);
void select_minium(HuffmanTree HT, int k, int &min1, int &min2);
int min(HuffmanTree HT, int k);
void HuffmanCoding1(HuffmanTree HT, HuffmanCode &HC, int n,int *num1);
void HuffmanDecode(HuffmanTree tree,int n,char * code);

//函数功能 返回字符串加权路径长度
int countWPL2(HuffmanTree HT, int n)
{
int cur = 2 * n - 2; //当前遍历到的节点的序号，初始时为根节点序号
int countRoads=0, WPL=0;//countRoads保存叶子结点的路径长度
//构建好赫夫曼树后，把visit[]用来当做遍历树时每个节点的状态标志
//visit[cur]=0表明当前节点的左右孩子都还没有被遍历
//visit[cur]=1表示当前节点的左孩子已经被遍历过，右孩子尚未被遍历
//visit[cur]=2表示当前节点的左右孩子均被遍历过
int visit[5000] = { 0 };//visit[]是标注数组,初始化为0，大小应同设为5000
//从根节点开始遍历，最后回到根节点结束
//当cur为根节点的parent时，退出循环
while (cur != -1)
{
//左右孩子均未被遍历，先向左遍历
if (visit[cur]==0)
{
visit[cur] = 1; //表明其左孩子已经被遍历过了
if (HT[cur].lchild != -1)
{ //如果当前节点不是叶子节点，则路径长度+1，并继续向左遍历
countRoads++;
cur = HT[cur].lchild;
}
else
{ //如果当前节点是叶子节点，则计算此结点的带权路径长度，并将其保存起来
WPL += countRoads * HT[cur].weight;
}
}
//左孩子已被遍历，开始向右遍历右孩子
else if (visit[cur]==1)
{
visit[cur] = 2;
if (HT[cur].rchild != -1)
{ //如果当前节点不是叶子节点，则记下编码，并继续向右遍历
countRoads++;
cur = HT[cur].rchild;
}
}
//左右孩子均已被遍历，退回到父节点，同时路径长度-1
else
{
visit[cur] = 0;
cur = HT[cur].parent;
countRoads--;
}
}
return WPL;
}

void removeDuplicate2(char s[]) //消去字符串中重复字符，并保留原有顺序不变，且字符串实际长度变为修正后长度
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

//函数功能 根据权值数组num对char型字符串实现连带排序
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
    tmp = num[i];//从待插入组取出第一个元素。
    j = i-1; //i-1即为有序组最后一个元素（与待插入元素相邻）的下标
while(j>=0 && k1<k[j]) //注意判断条件为两个，j>=0对其进行边界限制。第二个为插入判断条件
{
k[j+1]=k[j];
HC[j+1]=HC[j];
num[j+1] = num[j];//若不是合适位置，有序组元素向后移动
j--;
}
k[j+1]=k1;
HC[j+1]=t1;
num[j+1] = tmp;//找到合适位置，将元素插入。
    }
}

int main(){
    int i;
char data[26];
int num[26];
memset(num,0,4*26);
data[0]='a';
for(i=1;i<26;i++) //data数组存储所有小写字母
{
data[i]=(char)(data[i-1]+1);
}
str=(char *)malloc(sizeof(char ) * 5000);
scanf("%s",str);
int len=strlen(str);
for(i=0;i<len;i++) //统计字符串中各字符权值
{
for(int j=0;j<26;j++)
{
if(str[i]==data[j]) num[j]++;
}
}
//int temp=num[0];

char  o1[5000];  //字符数组改为5000（最大值），因为开始是复制str，需保证空间足够，防止溢出
strcpy(o1,str);
removeDuplicate2(o1);
int len1=strlen(o1);
//m=len1;
int n=0;
int num1[26];
for(int j=0;j<26;j++)  //得到str字符顺序权值数组
{
     if(num[j]!=0) {
         for(int i=0;i<len1;i++){
           if(o1[i]==data[j]) num1[i]=num[j];
         }
         n++;
         //i++;
         //num1[i++]=num[j];   尝试过程
        //printf("%c ",data[j]);
     }
}

//for(int i=0;i<len1;i++){
  //if(o1[i]==data[0]) num1[i]=temp; }
//printf("%d..",num1[0]);
HuffmanCode HC = NULL;
HuffmanTree hTree = create_HuffmanTree(num1, n,o1);
//InsertSort(num1,n);

char code1[5000],code2[5000];  //空间开设5000理由同上 子串o1
scanf("%s",code1);
scanf("%s",code2);
int WPL=countWPL2(hTree,n);
float judge=(float)WPL/8; // 输出压缩后文本大小
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


/*函数功能： 根据所设结构体创建创建对应哈夫曼树
输入 权值数组，数组大小，以及无重复字符数组
输出 所求哈夫曼树 */
HuffmanTree create_HuffmanTree(int *wet, int n,char * o1)
{

//一棵有n个叶子节点的赫夫曼树共有2n-1个节点
int total = 2 * n - 1;
HuffmanTree HT = (HuffmanTree)malloc(total * sizeof(HTNode));
int i;
//以下初始化序号全部用-1表示，
//这样在编码函数中进行循环判断parent或lchild或rchild的序号时，
//不会与HT数组中的任何一个下标混淆
//HT[0],HT[1]...HT[n-1]中存放需要编码的n个叶子节点

for (i = 0; i < n; i++)
{
    HT[i].data=o1[i];
    HT[i].parent = -1;
    HT[i].lchild = -1;
    HT[i].rchild = -1;
    HT[i].weight = *wet;
    wet++;
}
//HT[n],HT[n+1]...HT[2n-2]中存放的是中间构造出的每棵二叉树的根节点

for (; i < total; i++)
{
    HT[i].parent = -1;
    HT[i].lchild = -1;
    HT[i].rchild = -1;
    HT[i].weight = 0;
    HT[i].data='.';
}

int min1, min2; //用来保存每一轮选出的两个weight最小且parent为0的节点

//每一轮比较后选择出min1和min2构成一课二叉树,最后构成一棵赫夫曼树

for (i = n; i < total; i++)
{
    select_minium(HT, i, min1, min2);
    HT[min1].parent = i;
    HT[min2].parent = i;
    //这里左孩子和右孩子可以反过来，构成的也是一棵赫夫曼树，只是所得的编码不同
    HT[i].lchild = min1;
    HT[i].rchild = min2;
    HT[i].weight = HT[min1].weight + HT[min2].weight;
}
return HT;

}
/*
从HT数组的前k个元素中选出weight最小且parent为-1的两个，分别将其序号保存在min1和min2中
*/
void select_minium(HuffmanTree HT, int k, int &min1, int &min2)
{
min1 = min(HT, k);
min2 = min(HT, k);
}

/*

从HT数组的前k个元素中选出weight最小且parent为-1的元素，并将该元素的序号返回
*/
int min(HuffmanTree HT, int k)
{

int i = 0;
int min;        //用来存放weight最小且parent为-1的元素的序号
int min_weight; //用来存放weight最小且parent为-1的元素的weight值

//先将第一个parent为-1的元素的weight值赋给min_weight,留作以后比较用。
//注意，这里不能按照一般的做法，先直接将HT[0].weight赋给min_weight，
//因为如果HT[0].weight的值比较小，那么在第一次构造二叉树时就会被选走，
//而后续的每一轮选择最小权值构造二叉树的比较还是先用HT[0].weight的值来进行判断，
//这样又会再次将其选走，从而产生逻辑上的错误。

while (HT[i].parent != -1)
    i++;
min_weight = HT[i].weight;
min = i;
//选出weight最小且parent为-1的元素，并将其序号赋给min
for (; i < k; i++)
{
    if (HT[i].weight < min_weight && HT[i].parent == -1)
    {
        min_weight = HT[i].weight;
        min = i;
    }
}
//选出weight最小的元素后，将其parent置1，使得下一次比较时将其排除在外。
HT[min].parent = 1;
return min;

}

/* 函数功能 实现对二进制code字符串进行译码
函数输入 哈夫曼树，哈夫曼树节点数量，待译码字符串
函数输出 译码完成字符串
难点解读 如何判别不合法输入序列：通过设置变量b，每次从根开始遍历时初值设为0，每次到达叶节点则b=1，
如果循环结束时b=0即说明 字符串遍历结束但未到达叶节点
*/

void HuffmanDecode(HuffmanTree tree,int n,char *code)
{

int i,c;
char out[5000];

//for(i=0; i<100; ++i) code[i] = '\0';    // 初始化code数组（code用来存储密文，类型char[]）

//scanf("%s",code);
char *m;
m = code;
int j=0;
c = 2*n -2;    //    哈夫曼树的根节点下标
int b;
memset(out,'\0',5000*sizeof(char));
while( *m != '\0') {
    b=0;
    if( *m== '0'){
        c = i =tree[c].lchild;
        if(tree[c].lchild==-1&&tree[c].rchild==-1){ // 叶子节点
           out[j]=tree[i].data;  j++; b=1;
            c = 2*n - 2;    //if(tree[c].data=='.') b=0;p=p+tree[i].weight;
        }
    }
    if( *m == '1'){
        c = i = tree[c].rchild;
        if(tree[c].lchild == -1 && tree[c].rchild == -1) {    // 叶子节点
            out[j]=tree[i].data;  j++;b=1;
         //if(tree[c].data=='.') b=0;p=p+tree[i].weight;
         //if(tree[c].lchild!=-1 || tree[c].data==-1) b=0;
            c = 2*n-2;    // 重新从根遍历
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
从叶子节点到根节点逆向求赫夫曼树HT中n个叶子节点的赫夫曼编码，并保存在HC中
*/

void HuffmanCoding1(HuffmanTree HT, HuffmanCode &HC, int n,int *num1)
{

    //用来保存指向每个赫夫曼编码串的指针
    HC = (HuffmanCode)malloc(n * sizeof(char *));
    //临时空间，用来保存每次求得的赫夫曼编码串
    //对于有n个叶子节点的赫夫曼树，各叶子节点的编码长度最长不超过n-1
    //外加一个'\0'结束符，因此分配的数组长度最长为n即可
    char *code = (char *)malloc(n * sizeof(char));
    code[n - 1] = '\0';  //编码结束符，亦是字符数组的结束标志
                     //求每个字符的赫夫曼编码

    int i;
    for (i = 0; i < n; i++)
    {
        int current = i;           //定义当前访问的节点
        int father = HT[i].parent; //当前节点的父节点
        int start = n - 1;           //每次编码的位置，初始为编码结束符的位置
                                 //从叶子节点遍历赫夫曼树直到根节点

        while (father != -1)
        {
            if (HT[father].lchild == current)   //如果是左孩子，则编码为0
                code[--start] = '0';
            else                              //如果是右孩子，则编码为1
                code[--start] = '1';
            current = father;
            father = HT[father].parent;
    }

    //为第i个字符的编码串分配存储空间
    HC[i] = (char *)malloc((n - start) * sizeof(char));

    //将编码串从code复制到HC
    strcpy(HC[i], code + start);
}
    char order[5000];
    strcpy(order,str);
    removeDuplicate2(order);
    InsertionSort(num1,order,*HC,n);
    for (int i =0; i<n; i++) {
        printf("%c:%s\n",order[i], HC[i]);
    }
    free(code); //释放保存编码串的临时空间

}

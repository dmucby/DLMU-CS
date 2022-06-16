#include<iostream>
#include<cstdio>
#include<queue>
#include<stack>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include <string.h>

using namespace std;

#define MAXVALUE  5000          //输入文本最大字符个数
#define MAXLEAF   256           //最大叶结点个数，即最大不同字符个数
#define MAXBIT    MAXLEAF-1     //编码最大长度
#define MAXNODE   MAXLEAF*2-1   //最大结点个数

typedef struct{
    int weight; // 节点权值，频率
    int parent,lchild,rchild;// 初始值-1
    char data; // 储存的字符
}HTNode,*HuffmanTree;

typedef struct{
    int bit[MAXBIT];  // 字符的哈夫曼编码
    int start;         // 该编码在bit数组中的开始位置
}HCode;

void str_input(char str[]){
    // 输入可包含空的字符串
    gets(str);
}

int TextStatistics(char text[],char ch[],float weight[],int &m){
    // 统计每种字符出现的频次，返回出现的不同字符的个数
    // 出现的字符放在ch中，对应权值放在weight中

    int text_index = 0;
    int ch_index = 0;
    int weight_index = 0; // 数组索引

    while(text[text_index]!='\0'){
        // 查询ch中是否有该字符，返回第一个出现的位置
        char* pos = strchr(ch,text[text_index]);
        // 如果ch为空或者没找到pos
        if(ch[0]==NULL || pos == NULL){

            ch[ch_index] = text[text_index];

            weight[ch_index]++;
            ch_index++;
        }
        // 如果有该字符
        else{
            // 找到索引位置更新频次
            weight_index = pos - ch;
            weight[weight_index]++;
        }
        text_index++;
    }
    m = text_index;
    ch[ch_index] = '\0';// 结束符
    int index = 0;
    while(weight[index]!=0){
        weight[index]/=text_index; // 检验是否超出范围
        index++;
    }
    return ch_index;
    // 返回有多少个不同字符串
}

// 从 HuffNodes[0..range]中，找到最小的结点索引赋给s1,s2 。已经找到过的结点，其parent不为-1
void select(HTNode HuffNodes[],int range,int *s1,int *s2){
	//先找第一个最小值 。
	float min1 = 5;

	for(int index1=0;index1<=range;index1++){

		if(HuffNodes[index1].weight < min1 && HuffNodes[index1].parent ==-1){
			//判断该结点是否被选过。如果该结点parent为-1，则其为没有选过的叶结点。否则，说明其被选过
				min1 = HuffNodes[index1].weight;
				*s1 = index1 ;
		}
	}


	//找第2个最小值
	float min2 = 5;
	for(int index2=0;index2<=range ;index2++){
		if(HuffNodes[index2].weight < min2 && HuffNodes[index2].parent ==-1 && index2!=*s1){
			//判断该结点是否被选过。还要判断其是否被s1选了
				min2 = HuffNodes[index2].weight;
				*s2 = index2 ;
		}
	}

}

void CreateHuffmanTree(HTNode HuffNodes[],float weight[], int n){
    if(n > MAXBIT) return ;
    if(n < 1 ) return;
    int m = 2*n-1; // 节点数

    int node_index = 0;
    // 初始化叶子 n个
    while(node_index < n){
        HuffNodes[node_index].weight = weight[node_index];
        HuffNodes[node_index].parent = -1;
        HuffNodes[node_index].lchild = -1;
        HuffNodes[node_index].rchild = -1;
        node_index++;
    }
    // 初始化非叶子节点
    while(node_index<m){
        HuffNodes[node_index].weight = 0;
        HuffNodes[node_index].parent = -1;
        HuffNodes[node_index].lchild = -1;
        HuffNodes[node_index].rchild = -1;
        node_index++;
    }
    int h1,h2;// 索引值
    for(int i = n;i< m ;i++){
            select(HuffNodes,i-1,&h1,&h2);
            HuffNodes[h1].parent = i;
            HuffNodes[h2].parent = i;
            HuffNodes[i].lchild = h1;
            HuffNodes[i].rchild = h2;
            HuffNodes[i].weight =  HuffNodes[h1].weight + HuffNodes[h2].weight;
    }
}

void HuffmanCode(HTNode HuffNodes[], HCode HuffCodes[], int n,int &code_max) {
    //生成Huffman编码，所有结点的Huffman编码存放在HuffCodes中（一个位置存储一个节点的哈夫曼编码，单个结点的哈夫曼编码在bit数组中
    int start;code_max = 1;
	for(int i =0 ;i<n;i++){
		int h = 0;
		start = n-2;//每个结点的哈夫曼编码的长度不超过（叶子结点个数n-1），因此bit数组只需要使用(n-1)的长度。
        //而哈夫曼编码是从哈夫曼树的叶子结点开始一直追溯到根结点按照左右赋予0/1值的，所以倒着编码，bit数组起始下标应该是(n-2)，每编码一位就减一
		for(int c = i , f=HuffNodes[i].parent ; f!=-1; c =f,f=HuffNodes[f].parent){
			if(c == HuffNodes[f].lchild) HuffCodes[i].bit[start--]=0;
			else HuffCodes[i].bit[start--]=1;
            h++;
		}
		code_max = max(code_max,h);
		HuffCodes[i].start = start+1;//记录第i个结点的哈夫曼编码在其对应bit数组中的起始位置
	}
}

/*
bool if_equels(int bit[],int s[]){
    for(int i=0;i<sizeof(bit) / sizeof(bit[0]);i++){
        for(int j=0;j<sizeof(s) / sizeof(s[0]);j++){
            if(s[j] != bit[i]) return false;
        }
    }
    return true;
}


void node_find(int s[],HCode HuffmanCodes[],char ch[],int &n){
    vector<char> res;
    int k = 0;
    for (int i=0; i<n; i++) {
        if(if_equels(HuffmanCodes[i].bit,s)){
            res.push_back(ch[i]);

        }
    }
    if(res.empty()){
        cout<<"INVALID"<<endl;
    }
    else{
        for(int i = 0;i<res.size();i++){
            cout<<res[i];
        }
        cout<<endl;
    }
    return ;
}



void HuffmanDecode(char ch[],HuffmanCode huffmanCodes[], int n,char *code){

    int i,c;
    char out[5000];

    for(i=0; i<100; ++i) code[i] = '\0';
    scanf("%s",code);
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
*/
int main(){
    HTNode HuffmanNodes[MAXNODE];
    HCode  HuffmanCodes[MAXLEAF];
    char text[MAXVALUE+1],ch[MAXLEAF];
    float weight[MAXLEAF],result[MAXNODE];
    int i,j,n,resultIndex;
    int s1[MAXLEAF],s2[MAXLEAF];// 输入的哈夫曼编码
    int m = 0;
    int code_max = 1;


    str_input(text);

    n = TextStatistics(text,ch,weight,m);


    CreateHuffmanTree(HuffmanNodes,weight,n);
    HuffmanCode(HuffmanNodes,HuffmanCodes,n,code_max);

    cout<<m<<" "<<code_max<<endl;

    for (i=0; i<n; i++) {
        printf("%c:", ch[i]);

        for(j=HuffmanCodes[i].start; j<n-1; j++)
            printf("%d", HuffmanCodes[i].bit[j]);

        printf("\n");
    }
/*
    char code1[MAXBIT],code2[MAXBIT];
    scanf("%s",code1);
    scanf("%s",code2);
    HuffmanDecode(ch,HuffmanCodes,code_max,code1);
    printf("\n");
    HuffmanDecode(ch,HuffmanCodes,code_max,code2);

    HuffmanDecode(ch,HuffmanCodes,);
*/

    return 0;
}


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

#define MAXVALUE  5000          //�����ı�����ַ�����
#define MAXLEAF   256           //���Ҷ�������������ͬ�ַ�����
#define MAXBIT    MAXLEAF-1     //������󳤶�
#define MAXNODE   MAXLEAF*2-1   //��������

typedef struct{
    int weight; // �ڵ�Ȩֵ��Ƶ��
    int parent,lchild,rchild;// ��ʼֵ-1
    char data; // ������ַ�
}HTNode,*HuffmanTree;

typedef struct{
    int bit[MAXBIT];  // �ַ��Ĺ���������
    int start;         // �ñ�����bit�����еĿ�ʼλ��
}HCode;

void str_input(char str[]){
    // ����ɰ����յ��ַ���
    gets(str);
}

int TextStatistics(char text[],char ch[],float weight[],int &m){
    // ͳ��ÿ���ַ����ֵ�Ƶ�Σ����س��ֵĲ�ͬ�ַ��ĸ���
    // ���ֵ��ַ�����ch�У���ӦȨֵ����weight��

    int text_index = 0;
    int ch_index = 0;
    int weight_index = 0; // ��������

    while(text[text_index]!='\0'){
        // ��ѯch���Ƿ��и��ַ������ص�һ�����ֵ�λ��
        char* pos = strchr(ch,text[text_index]);
        // ���chΪ�ջ���û�ҵ�pos
        if(ch[0]==NULL || pos == NULL){

            ch[ch_index] = text[text_index];

            weight[ch_index]++;
            ch_index++;
        }
        // ����и��ַ�
        else{
            // �ҵ�����λ�ø���Ƶ��
            weight_index = pos - ch;
            weight[weight_index]++;
        }
        text_index++;
    }
    m = text_index;
    ch[ch_index] = '\0';// ������
    int index = 0;
    while(weight[index]!=0){
        weight[index]/=text_index; // �����Ƿ񳬳���Χ
        index++;
    }
    return ch_index;
    // �����ж��ٸ���ͬ�ַ���
}

// �� HuffNodes[0..range]�У��ҵ���С�Ľ����������s1,s2 ���Ѿ��ҵ����Ľ�㣬��parent��Ϊ-1
void select(HTNode HuffNodes[],int range,int *s1,int *s2){
	//���ҵ�һ����Сֵ ��
	float min1 = 5;

	for(int index1=0;index1<=range;index1++){

		if(HuffNodes[index1].weight < min1 && HuffNodes[index1].parent ==-1){
			//�жϸý���Ƿ�ѡ��������ý��parentΪ-1������Ϊû��ѡ����Ҷ��㡣����˵���䱻ѡ��
				min1 = HuffNodes[index1].weight;
				*s1 = index1 ;
		}
	}


	//�ҵ�2����Сֵ
	float min2 = 5;
	for(int index2=0;index2<=range ;index2++){
		if(HuffNodes[index2].weight < min2 && HuffNodes[index2].parent ==-1 && index2!=*s1){
			//�жϸý���Ƿ�ѡ������Ҫ�ж����Ƿ�s1ѡ��
				min2 = HuffNodes[index2].weight;
				*s2 = index2 ;
		}
	}

}

void CreateHuffmanTree(HTNode HuffNodes[],float weight[], int n){
    if(n > MAXBIT) return ;
    if(n < 1 ) return;
    int m = 2*n-1; // �ڵ���

    int node_index = 0;
    // ��ʼ��Ҷ�� n��
    while(node_index < n){
        HuffNodes[node_index].weight = weight[node_index];
        HuffNodes[node_index].parent = -1;
        HuffNodes[node_index].lchild = -1;
        HuffNodes[node_index].rchild = -1;
        node_index++;
    }
    // ��ʼ����Ҷ�ӽڵ�
    while(node_index<m){
        HuffNodes[node_index].weight = 0;
        HuffNodes[node_index].parent = -1;
        HuffNodes[node_index].lchild = -1;
        HuffNodes[node_index].rchild = -1;
        node_index++;
    }
    int h1,h2;// ����ֵ
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
    //����Huffman���룬���н���Huffman��������HuffCodes�У�һ��λ�ô洢һ���ڵ�Ĺ��������룬�������Ĺ�����������bit������
    int start;code_max = 1;
	for(int i =0 ;i<n;i++){
		int h = 0;
		start = n-2;//ÿ�����Ĺ���������ĳ��Ȳ�������Ҷ�ӽ�����n-1�������bit����ֻ��Ҫʹ��(n-1)�ĳ��ȡ�
        //�������������Ǵӹ���������Ҷ�ӽ�㿪ʼһֱ׷�ݵ�����㰴�����Ҹ���0/1ֵ�ģ����Ե��ű��룬bit������ʼ�±�Ӧ����(n-2)��ÿ����һλ�ͼ�һ
		for(int c = i , f=HuffNodes[i].parent ; f!=-1; c =f,f=HuffNodes[f].parent){
			if(c == HuffNodes[f].lchild) HuffCodes[i].bit[start--]=0;
			else HuffCodes[i].bit[start--]=1;
            h++;
		}
		code_max = max(code_max,h);
		HuffCodes[i].start = start+1;//��¼��i�����Ĺ��������������Ӧbit�����е���ʼλ��
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
*/
int main(){
    HTNode HuffmanNodes[MAXNODE];
    HCode  HuffmanCodes[MAXLEAF];
    char text[MAXVALUE+1],ch[MAXLEAF];
    float weight[MAXLEAF],result[MAXNODE];
    int i,j,n,resultIndex;
    int s1[MAXLEAF],s2[MAXLEAF];// ����Ĺ���������
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


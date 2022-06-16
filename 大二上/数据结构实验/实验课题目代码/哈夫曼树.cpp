#include<iostream>
#include<cstdio>
#include<queue>
#include<stack>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include <sys/time.h>

#define MAX_N 1e10

using namespace std;

typedef struct Node{
    int weight;// 权值
    char value;//字符值
    struct Node *parent,*left,*right;// 父和子节点
}Node;

// 哨兵节点
Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL(){
    NIL->weight = MAX_N;
    NIL->value = NULL;
    NIL->left = NIL->right = NIL->parent = NIL;
    return ;
}

string str;
int weight[256];
char ch[256];
string code[256];
int ans;

struct cmp{
	bool operator ()(const Node T1, const Node T2){
		return T1.weight >= T2.weight;
	}
};
priority_queue<Node, vector<Node>, cmp> q;


/*

Node *getNewNode(int weight,char c){
    Node *p = (Node*)malloc(sizeof(Node));
    p->weight = weight;
    p->value = c;
    p->left = p->right = p->parent = NIL;
    return p;
}

Node *CreatHuffmanTre(Node *root){
    if(root == NIL) return getNewNode(target,value);
    for(int i=1;i<=)
}

void clear(Node *root){
    if(root == NULL) return;
    clear(root->left);
    clear(root->right);
    free(root);
    return;
}
*/

string code1;
void dfs(Node *p){
    if(p->left!=NIL && p->right!=NIL){
        code[int(p->value)] = code1;
        ans+= p->weight * code1.size();
        return;
    }
    code1.push_back('0');
    dfs(p->left);
    code1.pop_back();

    code1.push_back('1');
    dfs(p->right);
    code1.pop_back();
}

int main(){
    cin>>str;
    string s1,s2;
    int m = str.length();// 压缩前的长度
    for(int i=0;i<m;i++){
        ch[(int)str[i]] = str[i];
        weight[(int)str[i]]++;
    }
    for(int i=0;i<m;i++){
        ch[(int)str[i]] = str[i];
        weight[(int)str[i]]++;
    }
    Node *L, *R, *T;
	Node a, b;
	while (!q.empty())
	{
		a = q.top(), q.pop();
		L = (Node*)malloc(sizeof(Node));
		L->weight = a.weight, L->value = a.value;
		L->left = a.left, L->right = a.right;

		if(!q.empty())
		{
			b = q.top(), q.pop();
			R =(Node*)malloc(sizeof(Node));
			R->weight = b.weight, R->value = b.value;
			R->left = b.left, R->right = b.right;
		}
		else
			break;
		q.push({a.weight + b.weight, '-', L, R});
	}
	T = L;		//建立好的树结构

	dfs(T);

	cout << ans << endl;
	for (int i = 0; i < m; i++)
		cout << ch[(int)str[i]] << ":" << code[i] << endl;

	return 0;
}

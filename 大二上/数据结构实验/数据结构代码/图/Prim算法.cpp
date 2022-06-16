#include<iostream>
#include <cstring>
#define INF 10000
using namespace std;
const int N = 7;
bool visit[N];
int dist[N];
int graph[N][N] = { {INF,28,INF,INF,INF,10,INF},  //INF��������֮�䲻�ɴ�
                    {28,INF,16,INF,INF,INF,14},
                    {INF,16,INF,12,INF,INF,INF},
                    {INF,INF,12,INF,22,INF,18},
                    {INF,INF,INF,22,INF,25,24},
                    {10,INF,INF,INF,25,INF,INF},
                    {INF,14,INF,18,24,INF,INF}
                  };
int prim(int cur){
    int sum=0,i=0,j=0;
    int index = cur;
    cout<<index<<" ";
    memset(visit,false,sizeof(visit));
    visit[cur] = true;
    for(i=0;i<N;i++){
        dist[i] = graph[index][i];
    }
    for(i = 1;i<N;i++){
        int minor = INF;
        for(j = 0;j<N;j++){
            if(!visit[j] && dist[j] < minor){
                minor = dist[j];
                index = j;
            }
        }
        visit[index] = true;
        cout << index << " ";
        sum+=minor;
        for(j=0;j<N;j++){
            if(!visit[j] && dist[j]>graph[index][j]){
                dist[j] = graph[index][j];
            }
        }
    }
    cout<<endl;
    return sum;
}
/*
int prim(int cur)
{
    int index = cur;
    int sum = 0;
    int i = 0;
    int j = 0;
    cout << index << " ";
    memset(visit,false, sizeof(visit));
    visit[cur] = true;
    for(i = 0; i < N; i++)
        dist[i] = graph[cur][i];//��ʼ����ÿ����a�ڽӵĵ�ľ������dist
    for(i = 1; i < N; i++)
    {
        int minor = INF;
        for(j = 0; j < N; j++)
        {
            if(!visit[j] && dist[j] < minor)          //�ҵ�δ���ʵĵ��У����뵱ǰ��С������������С�ĵ�
            {
                minor = dist[j];
                index = j;
            }
        }
        visit[index] = true;
        cout << index << " ";
        sum += minor;
        for(j = 0; j < N; j++)
        {
            if(!visit[j] && dist[j]>graph[index][j])      //ִ�и��£��������뵱ǰ��ľ���������͸���dist
            {
                dist[j] = graph[index][j];
            }
        }
    }
    cout << endl;
    return sum;               //������С����������·��ֵ
}
*/
int main(){
    cout<<prim(0);
    return 0;
}

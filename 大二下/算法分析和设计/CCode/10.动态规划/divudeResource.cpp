#include <iostream>
using namespace std;
typedef struct
{
    float benefit;
    int A,B,C;
}Allot;
void AddChoice(Allot *Fx,float **temp,int stage,int n,float *fx[4])   //stage表示当前为第几阶段
{
    int i,j;
    for(i=0;i<=n;i++)
        for(j=0;j<=i;j++)
            temp[i][j]=fx[stage][j]+Fx[i-j].benefit;
}
void Updata(Allot *Fx,Allot *fore,int stage,int i,int j,int n)  //更新各个项目的资金分配情况
{
    int t;
    if(stage==2)
    {
        Fx[i].B=j;Fx[i].A=i-j;Fx[i].C=0;
    }
    else if(stage==3)
    {
        Fx[i].C=j;
        t=i-j;
        Fx[i].A=fore[t].A;Fx[i].B=fore[t].B;
    }
}
void Findmax(Allot *Fx,float **temp,int stage,int n)       //更新当前最大利益
{
    int i,j,pos,t;
    Allot fore[n+1];
    for(t=0;t<=n;t++)
        fore[t]=Fx[t];     //记录上一阶段各个项目的分配情况
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=i;j++)
        {
            if(temp[i][j]>=Fx[i].benefit)
            {
                Fx[i].benefit=temp[i][j];
                pos=j;
            }
        }
        Updata(Fx,fore,stage,i,pos,n);
    }
}
int main()
{
    Allot *Fx;
    char project='A';
    float *fx[4],**temp;
    int n,i,j,fund;            //一个项目最多分多少
    cout<<"单个最多分配的资金:";
    cin>>n;
    for(i=0;i<=3;i++)      //存放各个分配的利益
        fx[i]=new float[n+1];
    cout<<"请输入项目A、B、C三个项目的分配利益(包括分配0时):"<<endl;
    for(i=1;i<=3;i++)
    {
        cout<<"项目"<<char(project+i-1)<<":";
        for(j=0;j<=n;j++)
            cin>>fx[i][j];
    }
    Fx=new Allot[n+1];      //存放当前利益最大的分配方法
    for(i=0;i<=n;i++)      //第一阶段（将所有的资源都分配给A项目）
    {
        Fx[i].benefit=fx[1][i];Fx[i].A=i;Fx[i].B=Fx[i].C=0;
    }
    temp=new float *[n+1];
    for(i=0;i<=n;i++)
        temp[i]=new float[n+1];
    for(i=2;i<=3;i++)             //阶段二、三
    {
        AddChoice(Fx,temp,i,n,fx);
        Findmax(Fx,temp,i,n);
    }
    cout<<"\n请输入投资的金额:";
    cin>>fund;
    cout<<"可获得最大利益:"<<Fx[fund].benefit<<"\n各个项目资金分配:   A:"<<Fx[fund].A<<"   B:"<<Fx[fund].B<<"   C:"<<Fx[fund].C<<endl;
    return 0;
}
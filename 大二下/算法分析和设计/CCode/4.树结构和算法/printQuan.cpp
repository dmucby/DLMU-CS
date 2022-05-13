#include <stdio.h>
#include <stdlib.h>
int main()
{
    int a[50][50]={0};
    int n,i,j,x,y,total=0,x1,y1,x2,y2,kase1=0,kase2=0;
    //设置四个边界，当循环到边界时转向填充数据
    scanf("%d",&n);
    x=n;
    y=1;
    x1=1;
    x2=n;
    y1=1;
    y2=n;
    while(total<n*n){		
        while(y<=y2){
            a[x][y]=++total;
            y++;
        }
        y--;
        x2--;
        x--;
        while(x>=x1){
            a[x][y]=++total;
            x--;
        }
        x++;
        y2--;
        y--;
        while(y>=y1){
            a[x][y]=++total;
            y--;
        }
        y++;
        x1++;
        x++;
        while(x<=x2){
            a[x][y]=++total;
            x++;
        }
        x--;
        y1++;
        y++;
    }
    for(i=1;i<=n;i++){
        if(kase1){
            printf("\n");
        }
        kase1=1;
        kase2=0;
        for(j=1;j<=n;j++){
            if(kase2){
                printf(" ");
            }
            kase2=1;
            printf("%d",a[j][i]);
        }
    }
    return 0;
}

#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main(){
	int nums[5][5]={
		{9},
        {12,15},
        {10,6,8},
        {2,18,9,5},
        {19,7,10,4,16}
	};

	const int height = 5; //数塔高度
    const int len = 5; //数塔底部宽度
    int resultnums[height][len]; //结果数塔，存放路径数值和
    int path[height][len]; //计算结果数塔生成路径

    //初始化结果数塔
    for(int i = 0; i < len; i++)
    {
        resultnums[height - 1][i] = nums[height - 1][i];
    }
    for(int i = height - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            if (resultnums[i + 1][j] > resultnums[i + 1][j + 1]) {
                resultnums[i][j] = nums[i][j] + resultnums[i + 1][j];
                path[i][j] = j;
            } else {
                resultnums[i][j] = nums[i][j] + resultnums[i + 1][j + 1];
                path[i][j] = j + 1;
            }
        }
    }
    
    //打印路径
    printf("最大数值和为 %d\n",resultnums[0][0]);
    printf("路径为： %d",nums[0][0]);
    int j = path[0][0];
    for(int i = 1; i <= height - 1; i++){
        printf("->%d",nums[i][j]);
        j = path[i][j];
    }
    printf("\n");
	printf("%d\n",resultnums[0][0]);
}


#include<iostream>
#include<cstdio>

using namespace std;

void jeep(){
	int k = 1;
	int oil = 500;
	int dis = 500;
	do{
		printf("储油点 %d 距出发点距离 %d 储油量 %d\n",k,1000-dis,oil);
		k++; // 从第二个站点开始计算
		dis = dis + 500/(2*k-1); // 计算站点距离
		printf("%d\n",dis);
		oil = 500 * k; // 计算储油量
	}while(dis < 1000); // 
	oil = 500*(k-1)+(1000-dis)*(2*k-1);
	printf("%d\n",oil);
	return;
}

int main()
{
	jeep();
	return 0;
}
#include<iostream>

using namespace std;

int m = 4; // 三角形层数
int a[5][5];

void print(){
	for (int i = 0; i <= m; ++i) // 层数
	{
		for (int j = 0; j <= i; ++j) // 个数
		{
			if(j == 0){
				a[i][j] = 1;
				printf("%d ",a[i][j]);
			}else{
				a[i][j] = a[i-1][j]+a[i-1][j-1];
				printf("%d ",a[i][j]);
			}
		}
		printf("\n");
	}
	// for (int i = 0; i < m; ++i) // 层数
	// {
	// 	for (int j = 0; j < i+1; ++j) // 个数
	// 	{
	// 		printf("%d ",a[i][j]);
	// 	}
	// 	printf("\n");
	// }
}

int main(int argc, char const *argv[])
{
	print();
	return 0;
}
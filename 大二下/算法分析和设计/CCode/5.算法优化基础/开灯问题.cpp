int sum[51];
int k;
int n = 50;
void print(){
	for (int i = 1; i <= n; ++i)
	{
		sum[i] = 0;
	}
	for (int i = 2; i <= n; ++i) // i是下标
	{
		k = 1; // K代表从自己开始遍历
		// k=1 表示每次都从自己开始
		while(i * k <= n){ // 两个数相乘必定是i的倍数
			sum[i * k] = 1 - sum[i * k] // 用0，1模拟开关
			k++;
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		printf("%d\n",sum[i]);
	}
}
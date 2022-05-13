int a[num+1];
int num = 20;
#define INF 1000000
void maxAndMin(){
	int max = 0;
	int min = INF;
	int p,q,temp1,temp2,sum;
	for (int i = 0; i < num; ++i)
	{
		p = (i+1)%num;
		q = (num+i-1)%num;
		sum = a[p] * a[q];

		if(sum > max){
			temp1 = sum;
			sum = max;
			max = temp1;
		}

		if(sum <min){
			temp2 = sum;
			sum = min;
			min = temp2;
		}
	}

	printf("%d\n",max);
	printf("%d\n",min);
}
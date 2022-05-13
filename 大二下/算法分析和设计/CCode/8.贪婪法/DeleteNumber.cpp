void print(int *n,int s){
	int len = n.length();
	int data[len] = {0};
	int j1 = 0;
	int j = 0;
	int i = 0;
	for (int i = 1; i <= s; ++i)
	{
		for (int j = 0; j < len -1; ++j)
		{
			if(n[j] > n[j+1]){
			// 	n[j] = n[j+1];
			// 	if(){
			// 		data[i] = i + j; // 记录删除位置
			// 	}
			// }else{
			// 	data[i] = data[i-1]-1;
			// 	j1 = j;
			// 	break;
			// }	
			for(k=j;k<len-1;++k){
				a[k] = a[k+1];
			}
			break;
		}
		len--; // 递增序列
	}

	i = 0;
	while(n[i]==0 && i<=i-1){
		i++;
	}

	if(i==len){
		cout<<"0"<<endl;
	}
	else{
		for (int j = i; j <= len-1; ++j)
		{
			printf("%d \n",n[j]);
		}
	}
}

void deleteN(int *n,int b,int k){
	for (int i = b; i <= n.length - k; ++i)
	{
		n[i] = n[i+k]; // 删除从b到len-k之间的数
	}
}
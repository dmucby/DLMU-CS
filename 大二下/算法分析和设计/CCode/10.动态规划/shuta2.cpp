#include<iostream>
using namespace std;
int MAX(int a,int b){//MAX函数求最大值 
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}
int GetMaxSum(int **arr,int n){//n表示当前进行层数 （从第num-1到0阶） 
	if(n==0){//终止条件
		return arr[0][0];
	}
	else{
		for(int i=0;i<n;i++){
			arr[n-1][i]+=MAX(arr[n][i],arr[n][i+1]); //下一层数据中的大值加上该数据 
		}
		GetMaxSum(arr,n-1);//遍历所有层  
	}
}

int main(){
	int num;
	cin>>num;
	int **arr; //定义二维指针 
	arr=new int*[num];//动态分配空间 
	for(int i=0;i<num;i++){
		arr[i]=new int[num];
	}
	for(int i=0;i<num;i++){//数据读入 
		for(int j=0;j<=i;j++){
			cin>>arr[i][j];
		}
	}
	cout<<GetMaxSum(arr,num-1);//函数调用 
	for(int i=0;i<num;i++){//先删除一维指针，再删除二维指针 
		delete[]arr[i];
	}
	delete []arr;
	return 0;
} 

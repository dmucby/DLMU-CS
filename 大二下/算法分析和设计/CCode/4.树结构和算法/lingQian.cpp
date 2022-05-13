#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int solve();

int coinValue[] = {	50,20,10,5,2,1};
int x,y;
int money,coinUsed;

int solve(){
	int num = 0;
	for(int i = 0;i <= 5; ++i){
		coinUsed = 0;
		if(money > 0){
			coinUsed = money/coinValue[i];
			num += coinUsed;
		}
		money -= coinUsed * coinValue[i];
	}
	return num;
}

int main(){
	cin>>x>>y;
	cout<<endl;
	if(x > y){
		cout<<"请重新输入"<<endl;
	}else{
		money = y - x;
		int num = solve(money);
		cout<<num<<endl;
	}
	return 0;
}
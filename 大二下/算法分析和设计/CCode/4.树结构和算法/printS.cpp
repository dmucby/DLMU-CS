#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	int ans[5][5];
	int n = 4;
	for(int i = 0 ; i<= n ;i++){
		ans[i][i] = 0;
		ans[i][n-i] = 0;
	}
	for(int i = 0; i <= n ;++i){
		for(int j = 0; j<= n;++j){
			if(i + j < n && j > i){
				ans[i][j] = 1;
			}
			if(i + j < n && i > j){
				ans[i][j] = 2;
			}
			if(i + j > n && i > j){
				ans[i][j] = 4;
			}
			if(i + j > n && i < j){
				ans[i][j] = 3;
			}
		}
	}
	for(int i = 0; i <= n ;++i){
		for(int j = 0; j<= n;++j){
			cout<<ans[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
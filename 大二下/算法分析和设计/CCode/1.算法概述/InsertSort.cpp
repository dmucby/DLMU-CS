#include<iostream>
#include<vector>

using namespace std;

vector<int> InsertSort(std::vector<int> v,int len){
	for (int i = 1; i < len; ++i)
	{
		int key = v[i]; // new key
		int j = i-1;
		while(j >= 0 && v[j] > key){ // search the position and adjust
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = key; // insert
	}
	return v;
}

int main(int argc, char const *argv[])
{
	vector<int> list = vector<int>{};
	int x;
	
	for(int i = 0;i < 10;i++){
		x = rand()%1000;
		list.push_back(x);
		cout << list[i]<< " ";
	}
	cout<<endl;
	
	int len = list.size();
	//list = InsertSort(list,len);
	list = InsertSort2(list,len);

	for(int i = 0;i < 10;i++){
		cout << list[i]<< " ";
	}
	cout<<endl;

	return 0;
}
#include<iostream>
#include<stack>
using namespace std;

void Binary_conversion(int x){
    stack<int> s;
    while(x){
        s.push(x%2);
        x=x>>1;
    }
    while(!s.empty()){
        cout<<s.top();
        s.pop();
    }
    cout<<endl;
}

int main(){
    int x;
    cin>>x;
    Binary_conversion(x);
    return 0;
}

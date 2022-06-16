#include<iostream>
#include<string>
#include<stdio.h>
#include <sstream>

using namespace std;

int n;

string fori(string s,int len){
    string s1,s2;
    s1 = s.substr(len-1);
    s2 = s.substr(0,len-1);
    s1 = s1 + s2;
    return s1;
}

int main(){
    string s,s1,s2,m;
    cin>>n;
    getchar();
    for(int i=0;i<n;i++){
        getline(cin,m);
        istringstream s(m);
        s>>s1;
        s>>s2;
        int len = s1.size();
        int flag = -1;
        for(int i=0;i<len;i++){
            int pos = s2.find(s1,0);
            if(pos>=0){
                flag++;
            }
            s1 = fori(s1,len);
            cout<<s1<<endl;
        }
        if(flag>=0){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}


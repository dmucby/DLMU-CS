#include<iostream>
#include<string>
#include<stdio.h>


using namespace std;

void delete_str(string &s1,string s2,int len){
    while(1){
        int pos = s1.find(s2);
        if(pos<0){
            break;
        }
        s1.erase(pos,len);
    }
    return ;
}

int main(){
    string s1,s2;
    getline(cin,s1);
    getline(cin,s2);
    int len = s2.length();
    delete_str(s1,s2,len);
    cout<<s1<<endl;
    return 0;
}

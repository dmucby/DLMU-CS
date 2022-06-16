#include<iostream>
using namespace std;

int main(){
    char c;
    c= getchar();
    int num = 0;
    if (c>='0' && c<='9') { //Êý×Ö
        num = num*10 + c-'0';//±£´æÊý×Ö
    }
    cout<<c<<endl<<num;
    return 0;
}


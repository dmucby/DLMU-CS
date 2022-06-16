#include<stack>
#include<string>
#include<iostream>

using namespace std;
stack<char> ss;

bool test(string s) {
    for(int i=0;i<s.size();i++){
        switch(s[i]){
            case '{':
            case '[':
            case '(':ss.push(s[i]);break;
            case '}':if(ss.empty()||ss.top()!='{') return false;
                    else ss.pop();break;
            case ']':if(ss.empty()||ss.top()!='[') return false;
                    else ss.pop();break;
            case ')':if(ss.empty()||ss.top()!='(') return false;
                    else ss.pop();break;
        }


    }
    return ss.empty();
}

int  main(){
    string s;
    string res;
    while(1)
	{
		getline(cin,s);
		if(s==".")
			break;
		res=res+s;
	}
    if(test(res)){
        cout<<"YES\n";
    }
    else{
        char a = ss.top();ss.pop();
        char b = ss.top();
        switch(a){
             case '{':
            case '[':
            case '(':cout<<a<<"-?";break;
            case '}':
            case ']':
            case ')':cout<<"?-"<<a;break;
            case cout<<"/*"<<"-?";break;
        }
        if(a=='*' && b=='/'){
           cout<<"-?"<<"*/";break;
        }
    }
    return 0;
}

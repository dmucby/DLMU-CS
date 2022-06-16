#include<iostream>
#include<set>

using namespace std;

int main(){
    set<int> s;
    int n,m;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>m;
        if(s.empty()){
            s.insert(m);
        }
        else{
            if(s.lower_bound(m) == s.end()){
                s.insert(m);
            }
            else{
                s.erase(s.upper_bound(m));
                s.insert(m);
            }
        }
    }
    cout<<s.size();
    return 0;
}

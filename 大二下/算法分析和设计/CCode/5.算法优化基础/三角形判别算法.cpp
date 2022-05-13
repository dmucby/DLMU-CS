#include<iostream>
#include<stdio.h>

using namespace std;

void pirnt(int a,int b,int c){
	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	if(a>=b+c||b>=a+c||c>=a+b){
		printf("不能构成三角形");
		return;
	}
	if(a*a==c*c+b*b||b*b==a*a+c*c||c*c==a*a+b*b){
		flag1 = 1;
	}
	if(a==b&&a==c){
		flag2 = 1;
	}
	if(a==b||a==c||b==c){
		flag3 = 1;
	}
	string s1 = "能构成";
	string s2 = "等边";
	string s3 = "等腰";
	string s4 = "直角";
	string s5 = "三角形";
	string s6 = s1;
	if(flag2 ==1){
		s6 = s1+s2;
	}else if(flag3==1){
		s6 = s1+s3;
	}else if(flag1==1){
		s6 += s4;
	}
	cout<<s6+s5<<endl;
}

int main(int argc, char const *argv[])
{
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	pirnt(a,b,c);
	return 0;
}
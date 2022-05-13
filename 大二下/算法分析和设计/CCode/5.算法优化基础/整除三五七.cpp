#include<stdio.h>
#include<iostream>

using namespace std;

void print(int n){
	int k = (n % 3 == 0) + (n % 5 == 0) * 2 + (n % 7 == 0) * 4;
	switch(k){
		case 0:printf("none");break;
		case 1:printf("3");break;
		case 2:printf("5");break;
		case 3:printf("3 and 5");break;
		case 4:printf("7");break;
		case 5:printf("3 and 7");break;
		case 6:printf("5 and 7");break;
		case 7:printf("all");break;
	}
}


int main(int argc, char const *argv[])
{
	int n;
	scanf("%d",&n);
	printf("%d\n",n);
	print(n);
	printf("\n");
	return 0;
}
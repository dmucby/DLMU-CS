
#include<iostream>
#include<stdio.h>
#include<sstream>
#include<fstream>
#include<vector>
#include<stack>



using namespace std;

class TESTmachine {


public:


	int init();
	int run();





	
private:


	string ss;
	string in_fileName;
	ifstream fin;
	vector<string>oprations;
	stack<int>stk;
	stack<int>fun_stk;
	vector<int>label;
	vector<string>code;
	vector<int>data;
	int start;


};
#pragma warning(disable:4996)


#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctype.h>
#include<conio.h>
#include<string>
#include<fstream>
#include<list>
#include<unordered_set>
#define maxvartablep 500  
#define maxfuntablep 500


using namespace std;




class TESTparse {


public:
	
	class vartable{
	public:
		string name;
		int address;
		unordered_set<string>name_space;
	};

	struct {
		string name;
		int lid;
		vector<vartable>varlist;


	}fun[maxfuntablep];
	



	int parse();
	int name_def(string name);
	int lookup_fun(string fun_name);
	int lookup(string name, int* paddress);
	void print_nts(string nts_name, int tabs);
	void print_ts(string token, string taken, int tabs);
	int main_declaration(int tabs);
	int fun_declaration(int tabs);
	int program(int tabs);
	int function_body(int tabs);
	int declaration_list(int tabs);
	int declaration_stat(int tabs);
	int statement_list(int tabs);
	int statement(int tabs);
	int if_stat(int tabs);
	int while_stat(int tabs);
	int for_stat(int tabs);
	int write_stat(int tabs);
	int read_stat(int tabs);
	int compound_stat(int tabs);
	int assignment_expression(int tabs);
	int assignment_stat(int tabs);
	int bool_expression(int tabs);
	int arithmetic_expression(int tabs);
	int term(int tabs);
	int factor(int tabs);
	int call_stat(int tabs);
	int fun_def(string fun_name,int label_id);
	
	int do_stat(int tabs);
	int switch_stat(int tabs);



private:
	int flagout = 0;
	char token[20], taken[40];
	char Scanout[300], Codeout[300];
	FILE* fp, * fout;
	int vartablep = 0, labelp = 0, datap = 0;   
	int funlid = 0;
	string out2_fileName = "out2.txt";
	int curfun=0;
	ofstream outFile;
	int hs;    //增加一个hs的全局变量，用于记录当前的hs

};















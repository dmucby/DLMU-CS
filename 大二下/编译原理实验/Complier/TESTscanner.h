

#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
#include<assert.h>
#include<stack>
#include<unordered_set>


using namespace std;

class TESTscanner {

public:

	void getFile()
	{
		ifstream fin;
		fin.open(in_fileName, ios::in);
		if (!fin.is_open())
		{
			cout << "无法找到这个文件！" << endl;
			return;
		}
		char buff[1024] = { 0 };
		while (fin >> buff)
		{
			ss += buff;

		}
		fin.close();
	}






	void readTxt()
	{
		ifstream infile;
		infile.open(in_fileName);   //将文件流对象与文件连接起来 
		assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

		string s;
		while (getline(infile, s))
		{
			ss += s;
			ss += '\n';


		}
		infile.close();             //关闭文件输入流 
	}






	bool isKeyword(string &token) {
		int i = 0;
		int j = keyword.size();

		transform(token.begin(), token.end(), token.begin(), ::tolower);

		while (i <= j) {
			int m = (i + j) >> 1;
			if (token == keyword[m]) {
				return true;
			}
			else if (keyword[m] < token) {
				i = m + 1;

			}
			else {
				j = m - 1;
			}
		}
		return false;

	}



	bool isSword(char& ch) {
		int i = 0;
		int j = sword.size();

		while (i <= j) {
			int m = (i + j) >> 1;
			if (ch == sword[m]) {
				return true;
			}
			else if (sword[m] < ch) {
				i = m + 1;
			}
			else {
				j = m - 1;
			}
		}
		return false;

	}


	bool isDword(char& ch) {
		int i = 0;
		int j = dword.size();

		while (i <= j) {
			int m = (i + j) >> 1;
			if (ch == dword[m]) {
				return true;
			}
			else if (dword[m] < ch) {
				i = m + 1;
			}
			else {
				j = m - 1;
			}
		}
		return false;

	}

	void sortALL() {
		sort(keyword.begin(), keyword.end());
		sort(sword.begin(), sword.end());
		sort(dword.begin(), dword.end());

	}



	int scanner() {
		readTxt();
		ofstream outFile;
		outFile.open(inout_fileName);
		int n = ss.size();
		idx = 0;
		int res = 0;
		//cout << ss << endl;
		char ch = ss[idx++];
		//cout << ss << endl;

		hs = 1;

		sortALL();



		while (idx < n) {
			while (ch == ' ' || ch == '\n' || ch == '\t') {

				if (ch == '\n')hs++;      

				ch = ss[idx++];
			}
			string token = "";
			if (isalpha(ch)) {
				token += ch;
				ch = ss[idx++];
				while (isalnum(ch)) {
					token += ch;
					ch = ss[idx++];
				}
				if (isKeyword(token)) {
					outFile << token << "\t" << token << "\t"<<hs<<endl;
				}
				else {
					outFile << "ID\t";
					outFile << token << "\t"<<hs<<endl;
				}
			}
			else if (isdigit(ch)) {
				token += ch;
				ch = ss[idx++];
				while (isdigit(ch)) {
					token += ch;
					ch = ss[idx++];
				}
				if (isalpha(ch)) {
					while (isalpha(ch)) {
						token += ch;
						ch = ss[idx++];
					}
					std::cout << "在第" << hs << "行" << "ERROR :ID名称【" << token << "】不合法" << endl;
					res = -1;
				}

				outFile << "NUM\t" << token << "\t" << hs << endl;
			}
			else if (isSword(ch)) {
				token += ch;
				ch = ss[idx++];
				outFile << token << "\t" << token << "\t" << hs << endl;


			}
			else if (isDword(ch)) {
				token += ch;
				char fch = ch;
				ch = ss[idx++];
				char sch = ch;
				if (ch == '&' && sch == '&') {
					token += '&';
					ch = ss[idx++];
				}
				else if (ch == '|' && sch == '|') {
					token += '|';
					ch = ss[idx++];
				}
				else if (sch == '=' && fch != '|' && fch != '&') {
					token += '=';
					ch = ss[idx++];
				}

				outFile << token << "\t" << token << "\t" << hs << endl;


			}
			else if (ch == '/') {
				ch = ss[idx++];
				if (ch == '*') {
					ch = ss[idx++];
					int pos = ss.find("*/", idx);
					if (pos == std::string::npos) {
						std::cout << "在第" << hs << "行" << "ERROR :找不到/*所对应的后半截" << endl;
						res = -1;
						break;
					}
					idx = pos + 1;
					ch = ss[idx++];

				}
				else if (ch == '/') {
					ch = ss[idx++];
					while (ss[idx++] != '\n');
					hs++;   
				}
				else {
					token += '/';
					ch = ss[idx++];

				}
			}
			else {
				token += ch;
				ch = ss[idx++];
				std::cout << "在第" << hs << "行" << "ERROR :出现了意外的字符 【 " << token << " 】" << endl;
				res = -1;
			}



		}

		outFile.close();


		if (res == 0) {
			cout << "success,词法分析结果请在inout.txt中查看" << endl;
		}
		else if (res == -1) {
			cout << endl;
			cout << "error,存在词法分析错误请检查你的TEST代码" << endl;
		}
		return res;

	}


private:
	string ss;
	string in_fileName = "in.txt";
	string inout_fileName = "inout.txt";
	int idx;
	int hs;
	//unordered_set<string>ids;
	int error_id = 0;
	//这里的我是未排序的，后面有sortALL函数进行排序
	vector<string>keyword = { "if", "else", "for", "while", "do", "int","break", "read", "write","switch","case","default","double","char","function","call"};
	vector<char>sword = { '+', '-', '*' ,'{','}','(',')',';',',',':' ,'"' };
	vector<char>dword = { '<','>','=','!','&','|' };

};






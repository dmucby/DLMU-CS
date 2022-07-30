

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
			cout << "�޷��ҵ�����ļ���" << endl;
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
		infile.open(in_fileName);   //���ļ����������ļ��������� 
		assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

		string s;
		while (getline(infile, s))
		{
			ss += s;
			ss += '\n';


		}
		infile.close();             //�ر��ļ������� 
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
					std::cout << "�ڵ�" << hs << "��" << "ERROR :ID���ơ�" << token << "�����Ϸ�" << endl;
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
						std::cout << "�ڵ�" << hs << "��" << "ERROR :�Ҳ���/*����Ӧ�ĺ���" << endl;
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
				std::cout << "�ڵ�" << hs << "��" << "ERROR :������������ַ� �� " << token << " ��" << endl;
				res = -1;
			}



		}

		outFile.close();


		if (res == 0) {
			cout << "success,�ʷ������������inout.txt�в鿴" << endl;
		}
		else if (res == -1) {
			cout << endl;
			cout << "error,���ڴʷ����������������TEST����" << endl;
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
	//���������δ����ģ�������sortALL������������
	vector<string>keyword = { "if", "else", "for", "while", "do", "int","break", "read", "write","switch","case","default","double","char","function","call"};
	vector<char>sword = { '+', '-', '*' ,'{','}','(',')',';',',',':' ,'"' };
	vector<char>dword = { '<','>','=','!','&','|' };

};






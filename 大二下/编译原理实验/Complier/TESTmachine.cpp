#include"TESTmachine.h"
/**/



int TESTmachine::init() {

	cout << "TEST虚拟机开始初始化" << endl;
	int es = 0;
	in_fileName = "out.txt";

	fin.open(in_fileName);

	

	return es;

	
}


int TESTmachine::run() {
	int es = 0;
	
	//char Codein[300],code[1000][20];
	//int label[100]={0};
	//char lno[4];
	label.resize(100, 0);
	int codecount = 0;
	data.resize(100);


	string sline;

	while (fin>>sline) {
		//cout << "read from file:" << sline << endl;
		//code.push_back(sline
		if (sline == "START") {
			start = codecount;
		}
		if (sline[sline.size() - 1] == ':') {                     //将所有的LAEBL%d：全部找出来，并且每个LABEL后面跟的数字提取出来，存储到label数组中
			string num=sline.substr(5, sline.size() - 6);
			label[atoi(num.c_str())]=codecount;
			code.push_back(":" + num);
		}
		else {
			code.push_back(sline);
		}

		codecount++;


	}
	int n = code.size();
	for (int i = 0; i < n; i++) {                   //方便debug
	cout << code[i] << endl;
	}

	cout << " -------------------------------------------" << endl;
	int m = label.size();
	for (int i = 0; i < m; i++) {                      //方便debug
		if (label[i] == 0) {
			break;
		}
		cout << label[i] << endl;
	}
	cout << " -------------------------------------------" << endl;
	int idx = start;
	while (idx < codecount) {
		if (idx == 13) {

			cout << "where" << endl;
		}
		if (code[idx]=="LOAD") {
			idx++;
			stk.push(data[atoi(code[idx].c_str())]);
		}
		if (code[idx]=="LOADI") {
			idx++;
			stk.push( atoi(code[idx].c_str()));
		}
		if (code[idx] == "STO") {
			idx++;
			data[atoi(code[idx].c_str())] = stk.top();
		}
		if (code[idx] == "POP") {
			stk.pop();
		}
		if (code[idx] == "ADD") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a + b);

		}
		if (code[idx] == "SUB") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a - b);

		}
		if (code[idx] == "MULT") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a*b);
		}
		if (code[idx] == "DIV") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a / b);
		}
		if (code[idx] == "BR") {
			idx++;
			idx++;      //因为BR 后面跟的是LAEBL，LABEL后面才是数字  ，所以还要idx+1两次
			idx = label[atoi(code[idx].c_str())];       //这里是原本的label_id映射到对应的行数
		}
		if (code[idx] == "BRF") {
			idx++;
			idx++;
			if (stk.top()==0) idx = label[ atoi(code[idx].c_str())];
			stk.pop();
		}
		if (code[idx] == "EQ") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a == b);
		}
		if (code[idx] == "COPY") {
			stk.push(stk.top());
		}
		if (code[idx] == "NOTEQ") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a != b);
		}
		if (code[idx] == "GT") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a>b);
		}
		if (code[idx] == "LES") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a < b);
		}
		if (code[idx] == "GE") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a >= b);
		}
		if (code[idx] == "LE") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a <=b);
		}
		if (code[idx] == "AND") {
			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();
			stk.push(a && b);
		}
		if(code[idx]=="OR"){
		int b = stk.top();
		stk.pop();
		int a = stk.top();
		stk.pop();
		stk.push(a || b);
		}
		if (code[idx] == "NOT") {
			int a = stk.top();
			stk.pop();
			stk.push(!a);
		}
		if (code[idx] == "IN") {
			cout<<"输入:"<<endl;
			int num;
			cin >> num;
			stk.push(num);

		}
		if (code[idx] == "OUT") {
			idx++;
			cout << data[atoi(code[idx].c_str())] << endl;
		}
		if (code[idx] == "STOP") {
			break;
		}
		idx++;


	}

	

	
	return es;
	

}
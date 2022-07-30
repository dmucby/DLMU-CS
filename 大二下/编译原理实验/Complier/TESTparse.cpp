#include "TESTparse.h"


int TESTparse::name_def(string name)
{
	int  es = 0;
	
	int n = fun[curfun].varlist.size();

	for (int i = 0; i < n;i++)    
	{
		if (fun[curfun].varlist[i].name==name)
		{
			es = 22;     
			break;
		}
	}
	if (es > 0)    return(es);
	
	int address = datap;

	fun[curfun].varlist.push_back({ name ,address});

	datap++;        

	return(es);
}
int TESTparse::fun_def(string name,int label_id)
{
	int  es = 0;
	if (funlid >= maxfuntablep)   return(21);



	for (int i = 0; i < funlid;i++)    
	{
		if (fun[i].name==name)
		{
			es = 22;     
			break;
		}
	}
	if (es > 0)    return(es);
	fun[funlid].name = name;
	fun[funlid].lid = labelp;
	curfun = funlid;
	funlid++;
	return(es);
}

int TESTparse::lookup(string name, int* paddress)
{
	int es = 0;
	int n = fun[curfun].varlist.size();
	for (int i = 0; i <n; i++)
	{
		if (fun[curfun].varlist[i].name==name)
		{
			*paddress = fun[curfun].varlist[i].address;
			return(es);
		}
	}
	es = 23;
	return(es);  
}


int TESTparse::lookup_fun(string fun_name)
{
	for (int i = 0; i < funlid; i++) {
		if (fun_name == fun[i].name) {
			return i;
		}
	}

	return -1;
}


int TESTparse::parse()
{

	outFile.open(out2_fileName);
	if (!outFile.is_open())
	{
		cout << "无法找到out2.txt这个文件！" << endl;
		return -1;
	}


	outFile << "该文件下面会输出语法分析树" << endl;

	int es = 0;
	fp = fopen("inout.txt", "r");
	if (!fp)
	{
		printf("\n打开%s错误!\n", "cifa.txt");
		es = 10;
		return(es);
	}



	fout = fopen("out.txt", "w");
	if (!fout)
	{
		printf("\n创建%s错误!\n", Codeout);
		es = 10;
		return(es);
	}
	if (es == 0)
		es = program(0);

	printf("==语法、语义分析及代码生成程序结果==\n");
	switch (es)
	{
	case 0:cout << "语法、语义分析成功并抽象机汇编生成代码!" << endl; break;
	case 10:cout << "打开文件%s失败!\n" << Scanout << endl; break;
	case 1:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺失【{】"<<endl; break;    
	case 2:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺失【}】"<<endl; break;
	case 3:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺失【标识符】"<<endl; break;
	case 4:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺失【;】!"<<endl; break;
	case 5:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺失【(】"<<endl; break;
	case 6:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺失【)】"<<endl; break;
	case 7:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺失操作数!"<<endl; break;
	case 8:cout << "在第" << hs << "行" << "存在ERROR：" << "缺失【:】!" << endl; break;
	case 21:cout << "在第" << hs << "行" << "存在ERROR：" <<"符号表溢出!"<<endl; break;
	case 22:cout << "在第" << hs << "行" << "存在ERROR：" <<"变量重复定义!"<<endl; break;
	case 23:cout << "在第" << hs << "行" << "存在ERROR：" <<"变量未声明!"<<endl; break;
	case 101:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺失main函数声明"<<endl; break;
	case 102:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺失函数的声明"<<endl; break;
	case 103:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺失函数ID"<<endl; break;
	case 104:cout << "在第" << hs << "行" << "存在ERROR：" <<"函数ID未声明"<<endl; break;
	case 105:cout << "在第" << hs << "行" << "存在ERROR：" <<"重复定义函数"<<endl; break;
	case 106:cout << "在第" << hs << "行" << "存在ERROR：" <<"缺少【while】"<<endl; break;
	case 107:cout << "在第" << hs << "行" << "存在ERROR：" << "缺少常数表达式" << endl; break;

	}
	fclose(fp);
	fclose(fout);
	outFile.close();

	return(es);
}






void TESTparse::print_nts(string nts_name, int tabs) {

	for (int i = 0; i < tabs; i++) {
		outFile << "\t";
	}
	outFile << "<" << nts_name << ">" << endl;
}

void TESTparse::print_ts(string token, string taken, int tabs) {
	for (int i = 0; i < tabs; i++) {
		outFile << "\t";
	}
	outFile << token << " : " << taken << endl;
}


int TESTparse::main_declaration(int tabs) {
	int es = 0;
	fprintf(fout, "START\n");
	



	//fscanf(fp, "%s\t%s\n", token, taken);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);   //所有的fscanf   改成这个样子 这个很重要
	printf("%s : %s\n", token, taken);
	print_nts("main_declaration", tabs);


	for (int i = 0; i < tabs + 1; i++) {
		outFile << "\t";
	}


	outFile << "main" << " : " << "main" << endl;



	if (strcmp(token, "(")) {
		es = 5;
		return(es);
	}

	print_ts(token, taken, tabs + 1);


	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	if (strcmp(token, ")")) {
		es = 5;
		return es;

	}

	print_ts(token, taken, tabs + 1);


	es = function_body(tabs + 1);
	return es;

}


int TESTparse::fun_declaration(int tabs) {
	int es = 0;
	int  label1;
	label1 = labelp++;
	
	
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);



	print_nts("fun_declaration", tabs);

	if (strcmp(token, "ID")) {
		es = 103;
		return es;

	}
	int re=lookup_fun(taken);
	if (re!=-1) {
		es = 105;
		return es;
	}

	fun_def(taken, label1);
	fprintf(fout, "LABEL%d:\n", label1);
	
	
	for (int i = 0; i < tabs + 1; i++) {
		outFile << "\t";
	}

	outFile << "function" << " : " << "function" << endl;


	print_ts(token, taken, tabs + 1);




	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);
	if (strcmp(token, "(")) {
		es = 5;
		return(es);
	}





	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);


	if (strcmp(token, ")")) {
		es = 5;
		return es;

	}

	es = function_body(tabs + 1);
	return es;

}


int TESTparse::program(int tabs) {
	int es = 0;


	outFile << "<program>" << endl;
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);

	while (!strcmp(token, "function")) {
		es = fun_declaration(tabs + 1);
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);
		if (es) {
			return es;
		}
		curfun++;
	}

	if (strcmp(token, "ID") || strcmp(taken, "main")) {
		es = 101;
		return es;
	}
	es = main_declaration(tabs + 1);
	fprintf(fout, "STOP\n");  
	return es;


}


int TESTparse::function_body(int tabs)
{
	int es = 0, i;
	
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	for (int i = 0; i < tabs; i++) {
		outFile << "\t";
	}
	outFile << "<function_body>" << endl;
	if (strcmp(token, "{"))    
	{
		es = 1; 
		return(es);
	}


	for (int i = 0; i < tabs + 1; i++) {
		outFile << "\t";
	}
	outFile << token << " : " << taken << endl;
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	es = declaration_list(tabs + 1);
	if (es > 0)    return(es);

	es = statement_list(tabs + 1);
	if (es > 0)    return(es);

	/*
	if (strcmp(token, "}"))  
	{
		es = 2;
		return(es);
	}

	fscanf(fp, "%s\t%s\n", token, taken);
	printf("%s	:	%s\n", token, taken);
	cout << "where" << endl;
	es = statement_list();
	*/
	for (int i = 0; i < tabs + 1; i++) {
		outFile << "\t";
	}
	outFile << token << " : " << taken << endl;




	return(es);
}
int TESTparse::declaration_list(int tabs)
{
	int es = 0;

	print_nts("declaration_list", tabs);
	while (strcmp(token, "int") == 0)
	{



		es = declaration_stat(tabs + 1);

		if (es > 0)    return (es);
	}
	return(es);
}
int TESTparse::declaration_stat(int tabs)
{

	

	print_nts("declaration_stat", tabs);

	print_ts(token, taken, tabs + 1);

	int es = 0;
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	if (strcmp(token, "ID"))  return(es = 3);   
	print_ts(token, taken, tabs + 1);


	es = name_def(taken);                 
	if (es > 0)    return(es);


	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);

	while (!strcmp(token, ",")) {
		
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);
		if (strcmp(token, "ID"))  return(es = 3);  

		print_ts(token, taken, tabs + 1);
		es = name_def(taken);                 
		if (es > 0)    return(es);
		int address;
		es = lookup(taken, &address);

		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);
		print_ts(token, taken, tabs + 1);
		if (!strcmp(token, "=")) {


			fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
			printf("%s : %s\n", token, taken);

			es = arithmetic_expression(tabs + 1);
			if (es > 0)return es;
			fprintf(fout, "      STO %d\n", address);
			fprintf(fout, "      POP\n");
		}



	}
	if (strcmp(token, ";"))   return(es == 4);



	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	return(es);
}
int TESTparse::statement_list(int tabs)
{
	print_nts("statement_list", tabs);
	int es = 0;
	while (strcmp(token, "}"))
	{
		es = statement(tabs + 1);
		if (es > 0)    return(es);
	}

	return (es);
}
int TESTparse::statement(int tabs)
{

	print_nts("statement", tabs);


	int es = 0;
	if (es == 0 && strcmp(token, "if") == 0){
		es = if_stat(tabs + 1); 
		return es;
	}
	if (es == 0 && strcmp(token, "while") == 0) {
		es = while_stat(tabs + 1);  
		return es;
	
	} 
	if (es == 0 && strcmp(token, "for") == 0) {
		es = for_stat(tabs + 1); 
		return es;
	}
	if (es == 0 && strcmp(token, "read") == 0) {
		es = read_stat(tabs + 1); 
		return es;
	}
		
	if (es == 0 && strcmp(token, "write") == 0) {
		es = write_stat(tabs + 1); 
		return es;
	}

	if (es == 0 && strcmp(token, "switch") == 0) {
		es = switch_stat(tabs + 1);
		return es;
	}
		
		
	if (es == 0 && strcmp(token, "{") == 0) {
		es = compound_stat(tabs + 1); 
		return es;
	}
		
	if (es == 0 && (strcmp(token, "ID") == 0)) {
		es = assignment_stat(tabs + 1);
		return es;
	}
		
	if (es == 0 && (strcmp(token, "call") == 0)) {
		es = call_stat(tabs + 1);
		return es;
	}
	if (es == 0 && (strcmp(token, "do") == 0)) {
		es = do_stat(tabs + 1);
		return es;
	}


	return(es);
}




int TESTparse::if_stat(int tabs)
{
	
	print_nts("if_stat", tabs);
	print_ts(token, taken, tabs + 1);

	int es = 0, label1, label2;                
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);
	if (strcmp(token, "("))   return(es = 5); 
	print_ts(token, taken, tabs + 1);



	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);

	es = bool_expression(tabs + 1);
	if (es > 0)    return(es);
	if (strcmp(token, ")"))   return(es = 6);
	print_ts(token, taken, tabs + 1);
	label1 = labelp++;   
	fprintf(fout, "      BRF LABEL %d\n", label1); 
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);

	es = statement(tabs + 1);
	if (es > 0)    return(es);
	label2 = labelp++;  
	fprintf(fout, "      BR LABEL %d\n", label2);  
	
	if (strcmp(token, "else") == 0) 
	{
		fprintf(fout, "LABEL%d:\n", label1);
		print_ts(token, taken, tabs + 1);
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);

		es = statement(tabs + 1);
		if (es > 0)    return(es);
	}
	fprintf(fout, "LABEL%d:\n", label2); 
	return(es);
}
int TESTparse::while_stat(int tabs)
{
	
	print_nts("while_stat", tabs);
	print_ts(token, taken, tabs + 1);
	int es = 0, label1, label2;
	label1 = labelp++;
	fprintf(fout, "LABEL%d:\n", label1);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	if (strcmp(token, "("))   return(es = 5);
	print_ts(token, taken, tabs + 1);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	es = bool_expression(tabs + 1);
	if (es > 0)    return(es);
	if (strcmp(token, ")"))   return(es = 6);
	print_ts(token, taken, tabs + 1);
	label2 = labelp++;
	fprintf(fout, "      BRF LABEL %d\n", label2);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	es = statement(tabs + 1);
	if (es > 0)    return(es);
	fprintf(fout, "      BR LABEL %d\n", label1);
	fprintf(fout, "LABEL%d:\n", label2);
	return(es);
}


/*
for(label之前的;label 1;label 4){

	label 3
}
label 2;


*/

int TESTparse::for_stat(int tabs)
{
	
	print_nts("for_stat", tabs);
	print_ts(token, taken, tabs + 1);
	int es = 0, label1, label2, label3, label4;
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	if (strcmp(token, "("))   return (es = 5);

	print_ts(token, taken, tabs + 1);

	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	es = assignment_expression(tabs + 1);
	if (es > 0)    return(es);
	if (strcmp(token, ";"))   return(es = 4);
	print_ts(token, taken, tabs + 1);


	label1 = labelp++;
	fprintf(fout, "LABEL%d:\n", label1);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	es = bool_expression(tabs + 1);
	if (es > 0)    return(es);
	label2 = labelp++;
	fprintf(fout, "      BRF LABEL%d\n", label2);
	label3 = labelp++;
	fprintf(fout, "      BR LABEL%d\n", label3);
	if (strcmp(token, ";"))   return(es = 4);
	print_ts(token, taken, tabs + 1);
	label4 = labelp++;
	fprintf(fout, "LABEL%d:\n", label4);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	es = assignment_expression(tabs + 1);
	if (es > 0)    return(es);
	fprintf(fout, "      POP\n");
	fprintf(fout, "      BR LABEL%d\n", label1);
	if (strcmp(token, ")"))   return(es = 6);
	print_ts(token, taken, tabs + 1);

	fprintf(fout, "LABEL%d:\n", label3);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	es = statement(tabs + 1);
	if (es > 0)    return(es);
	fprintf(fout, "      BR LABEL%d\n", label4);
	fprintf(fout, "LABEL%d:\n", label2);
	return(es);

}
int TESTparse::write_stat(int tabs)
{
	
	print_nts("write_stat", tabs);
	print_ts(token, taken, tabs + 1);
	int es = 0;
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	int address;
	flagout = 1;
	es = lookup(taken, &address);
	printf("%s : %s\n", token, taken);

	es = arithmetic_expression(tabs + 1);
	if (es > 0)    return(es);
	if (strcmp(token, ";"))   return(es = 4);
	print_ts(token, taken, tabs + 1);
	fprintf(fout, "      OUT %d\n", address);
	flagout = 0;
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	return(es);
}
int TESTparse::read_stat(int tabs)
{
	
	print_nts("read_stat", tabs);
	print_ts(token, taken, tabs + 1);
	int es = 0, address;
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);

	if (strcmp(token, "ID"))  return(es = 3);
	print_ts(token, taken, tabs + 1);

	es = lookup(taken, &address);
	if (es > 0)    return(es);
	fprintf(fout, "      IN  \n");
	fprintf(fout, "      STO  %d\n", address);
	fprintf(fout, "      POP  \n");
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);

	if (strcmp(token, ";"))   return(es = 4);
	print_ts(token, taken, tabs + 1);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	return(es);
}
int TESTparse::compound_stat(int tabs)
{
	
	print_nts("compound_stat", tabs);
	print_ts(token, taken, tabs + 1);
	int es = 0;
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	es = statement_list(tabs + 1);


	print_ts(token, taken, tabs + 1);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);



	return(es);
}
int TESTparse::assignment_expression(int tabs)
{
	
	print_nts("assignment_expression", tabs);
	int es = 0, address;
	if (strcmp(token, "ID")) return es = 9;
	es = lookup(taken, &address);
	if (es > 0)return es;
	print_ts(token, taken, tabs + 1);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);


	if (strcmp(token, "=")) return es = 10;
	print_ts(token, taken, tabs + 1);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);



	es = arithmetic_expression(tabs + 1);
	if (es > 0)return es;
	fprintf(fout,"      STO %d\n", address);
	fprintf(fout,"      POP\n");
	return(es);
}
int TESTparse::assignment_stat(int tabs)
{
	
	print_nts("assignment_stat", tabs);
	int es = 0;
	while (strcmp(token, "ID") == 0)
	{
		print_ts(token, taken, tabs + 1);
		es = assignment_expression(tabs + 1);
		if (es > 0)    return (es);
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);
	}


	return(es);
}
int TESTparse::bool_expression(int tabs)
{
	print_nts("bool_expression", tabs);
	int es = 0;
	es = arithmetic_expression(tabs + 1);
	if (es > 0)    return(es);



	if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0
		|| strcmp(token, "<") == 0 || strcmp(token, "<=") == 0
		|| strcmp(token, "==") == 0 || strcmp(token, "!=") == 0)
	{
		print_ts(token, taken, tabs + 1);
		char token2[20];
		strcpy_s(token2, token);
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);
		es = arithmetic_expression(tabs + 1);

		print_ts(token, taken, tabs + 1);
		if (es > 0)    return(es);
		if (strcmp(token2, ">") == 0)   fprintf(fout, "      GT\n");
		if (strcmp(token2, ">=") == 0)   fprintf(fout, "      GE\n");
		if (strcmp(token2, "<") == 0)   fprintf(fout, "      LES\n");
		if (strcmp(token2, "<=") == 0)   fprintf(fout, "      LE\n");
		if (strcmp(token2, "==") == 0)   fprintf(fout, "      EQ\n");
		if (strcmp(token2, "!=") == 0)   fprintf(fout, "      NOTEQ\n");

	}
	return(es);
}
int TESTparse::arithmetic_expression(int tabs)
{
	print_nts("arithmetic_expression", tabs);
	int es = 0;
	es = term(tabs + 1);
	if (es > 0)    return(es);
	while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
	{
		print_ts(token, taken, tabs + 1);
		char token2[20];
		strcpy_s(token2, token);
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);

		es = term(tabs + 1);
		if (es > 0)    return(es);
		if (strcmp(token2, "+") == 0)   fprintf(fout, "      ADD\n");
		if (strcmp(token2, "-") == 0)   fprintf(fout, "      SUB\n");
	}
	return(es);
}
int TESTparse::term(int tabs)
{
	print_nts("term", tabs);
	int es = 0;
	es = factor(tabs + 1);
	if (es > 0)    return(es);
	while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
	{
		print_ts(token, taken, tabs + 1);
		char token2[20];
		strcpy_s(token2, token);
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);


		es = factor(tabs + 1);
		if (es > 0)    return(es);
		if (strcmp(token2, "*") == 0)   fprintf(fout, "      MULT\n");
		if (strcmp(token2, "/") == 0)   fprintf(fout, "      DIV\n");
	}
	return(es);
}
int TESTparse::factor(int tabs)
{

	print_nts("factor", tabs);
	int es = 0;
	if (strcmp(token, "(") == 0)
	{
		print_ts(token, taken, tabs + 1);
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);

		es = arithmetic_expression(tabs + 1);
		if (es > 0)    return(es);
		if (strcmp(token, ")"))   return(es = 6);
		print_ts(token, taken, tabs + 1);
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);

	}
	else
	{
		if (strcmp(token, "ID") == 0)
		{

			print_ts(token, taken, tabs + 1);
			int address;
			es = lookup(taken, &address);
			if (es > 0)    return(es);
			if (flagout == 0)
				fprintf(fout, "      LOAD %d\n", address);
			//fprintf(fout, "      LOAD %d\n", address);
			fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
			printf("%s : %s\n", token, taken);

			return(es);
		}
		if (strcmp(token, "NUM") == 0)
		{
			print_ts(token, taken, tabs + 1);
			fprintf(fout, "      LOADI %s\n", taken);
			fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
			printf("%s : %s\n", token, taken);

			return(es);
		}
		else
		{
			es = 7;
			return(es);
		}
	}
	return(es);
}






int TESTparse::call_stat(int tabs)
{

	
	print_nts("call_stat", tabs);
	print_ts(token, taken, tabs + 1);

	int es = 0;
	int fun_lid = 0;
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);
	if (strcmp(token, "ID"))   return(es = 103);  

	int res=lookup_fun(taken);
	if (res==-1) {
		es = 104;
		return es;
	}
	fprintf(fout, "      BR LABEL %d\n", res); 
	
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);
	if (strcmp(token, "(")) return (es = 5);

	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);
	if (strcmp(token, ")")) return (es = 6);


	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);
	if (strcmp(token, ";"))   return(es == 4);

	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	return(es);
}





int TESTparse::do_stat(int tabs)
{
	int es = 0;
	int label1, label2;
	

	print_nts("do_stat", tabs);
	print_ts(token, taken, tabs + 1);




	label1 = labelp++;

	label2 = labelp++;

	fprintf(fout, "LABEL%d:\n", label1);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	es = statement(tabs + 1);
	if (es > 0)    return(es);

	



	/*
	fscanf(fp, "%s\t%s\n", &token, &taken);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);
	if (strcmp(token, "{"))   return(es = 1);//少左括号




	fscanf(fp, "%s\t%s\n", &token, &taken);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);
	if (strcmp(token, "}"))   return(es = 2);//少左括号


	*/


	print_ts(token, taken, tabs + 1);
	if (strcmp(token, "while"))   return(es = 106);


	
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	if (strcmp(token, "("))   return(es = 5);




	print_ts(token, taken, tabs + 1);
	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	es = bool_expression(tabs + 1);
	if (es > 0)    return(es);
	if (strcmp(token, ")"))   return(es = 6);
	print_ts(token, taken, tabs + 1);


	fprintf(fout, "      BR LABEL %d\n", label1);
	fprintf(fout, "      BRF LABEL %d\n", label2);
	fprintf(fout, "LABEL%d:\n", label2);

	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);
	if (strcmp(token, ";"))   return(es == 4);

	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);


	return(es);

}

//switch (a) {
// 
//case	1:j = j + 1;
//case 2:j = j + 2;
//case 3:j = j + 4;
//case 4:j = j + 5;
//default: j = j + 6;

//}

int TESTparse::switch_stat(int tabs) {
	int es = 0;
	int case_label;



	int next_label;
	int new_label;
	int state_label;

	


	print_nts("switch_stat", tabs);
	print_ts(token, taken, tabs + 1);





	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	if (strcmp(token, "("))   return(es = 5);
	print_ts(token, taken, tabs + 1);

	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);

	es = arithmetic_expression(tabs + 1);
	if (es > 0)return es;
	//fprintf(fout, "      BRF LABEL %d\n", label1);
	


	if (strcmp(token, ")"))   return(es = 6);
	print_ts(token, taken, tabs + 1);

	//fprintf(fout, "      LOADI 0\n");


	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);
	if (strcmp(token, "{"))   return(es = 1);//少左括号



	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);

	
	while (!strcmp(token, "case")) {
		fprintf(fout, "      COPY\n");

		//fprintf(fout, "      BRF LABEL %d\n", label1);
		//state_label = labelp++;
		next_label = labelp++;
		
		cout << "where" << endl;
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);
		print_ts(token, taken, tabs + 1);

		if (strcmp(token, "NUM")) return es = 107;
		fprintf(fout, "      LOADI %s\n", taken);
		fprintf(fout, "      EQ\n");
		fprintf(fout, "      BRF LABEL %d\n", next_label);
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);
		print_ts(token, taken, tabs + 1);
		
		if (strcmp(token, ":")) return es = 8;


		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);
		print_ts(token, taken, tabs + 1);
		//fprintf(fout, "LABEL%d:\n", state_label);
		//fprintf(fout, "      POP\n");
		es = statement(tabs + 1);
		if (es > 0)    return(es);

		print_ts(token, taken, tabs + 1);
		fprintf(fout, "      BR LABEL %d\n", next_label);
		
		fprintf(fout, "LABEL%d:\n", next_label);

		
	}



	labelp++;

	if (!strcmp(token, "default")) {
		//next_label = labelp++;
		//fprintf(fout, "      BRF LABEL %d\n", next_label);
		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);
		print_ts(token, taken, tabs + 1);
		if (strcmp(":", token)) return es = 8;

		fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
		printf("%s : %s\n", token, taken);
		print_ts(token, taken, tabs + 1);
		
		es = statement(tabs + 1);
		if (es > 0)    return(es);


	}





	if (strcmp(token, "}"))   return(es = 2);//少左括号

	fscanf(fp, "%s\t%s\t%d\n", &token, &taken, &hs);
	printf("%s : %s\n", token, taken);
	print_ts(token, taken, tabs + 1);


	fprintf(fout, "      POP\n");

	return es;

}
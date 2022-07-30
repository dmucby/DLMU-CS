#include "TESTscanner.h"
#include "TESTparse.h"
#include"TESTmachine.h"



int main() {
	int res = 0;


	TESTscanner* testScanner = new TESTscanner();
	res=testScanner->scanner();
	if (res) {
		cout << "±àÒë³ÌĞòERROR!" << endl;
		return 0;
	}


	TESTparse* testParse = new TESTparse();
	testParse->parse();
	delete testParse;

	if (res) {
		cout << "±àÒë³ÌĞòERROR!" << endl;
	}


	TESTmachine* testMachine = new TESTmachine();
	res = testMachine->init();
	if (res) {
		cout << "TESTĞéÄâ»ú³õÊ¼»¯´íÎó" << endl;
		return -1;
	}

	
	res=testMachine->run();

	if (res != 0) {
		cout << "TESTĞéÄâ»úÔËĞĞ´íÎó" << endl;
	}

	
	delete testMachine;


}
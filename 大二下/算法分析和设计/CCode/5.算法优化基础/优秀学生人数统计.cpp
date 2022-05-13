#include<iostream>

int grade[51][6];

int count(){
	int sum = 0;
	for (int i = 0; i < 50; ++i)
	{
		int num = 0;
		for (int j = 0; j < 5; ++j)
		{
			if(grade[i][j] >= 90){
				num++;
			}
		}
		if(num >=3 ){
			sum++;
		}
		num = 0;
	}
	return sum;
}


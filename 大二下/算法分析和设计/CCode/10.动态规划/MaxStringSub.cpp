using namespace std;
#include <iostream>
#include <string>

int main()
{
	//定义字符串及长度
	string str1 ;//="qwerff";
	string str2;//="fqwerfo";
	cin >> str1;
	cin >> str2;
	int lenStr1 = str1.length();
	int lenStr2 = str2.length();

	int max=0,count;//接受最大长度
	int tag[256][256];//定义动态规划数组
	for(int i=1;i<=lenStr1;i++)
	{
		for(int j = 1;j<=lenStr2;j++)
		{
			//匹配到值
			if(str1[i-1]==str2[j-1])
			{
				/*tag[i-1][j-1]在刚开始str1与str2开始匹配到时值为0，那么对应的
				 tag[i][j](即当前的最大字符长度是0+1=1，以后过程雷同)
				 */
				tag[i][j]= tag[i-1][j-1]+1;
				count=tag[i][j];
				if(count>max)max =count;//获取最大字符长度
			}
		}
	}
	cout<<max<<endl;
	return 0;
}

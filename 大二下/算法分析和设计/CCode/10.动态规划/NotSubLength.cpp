#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int array[10] = {3, 18, 7, 14, 10, 12, 23, 41, 16, 24};
    vector<int> nums(array, array + 10);
    vector<int> maxLen(nums.size());  //记录长度

    maxLen[0] = 1;

    for (int i = 1; i < nums.size(); ++i)
    {
        int maxL = 0, maxI = -1;
        for (int k = i - 1; k >= 0; --k)
        {
            if(nums[k] > nums[i])
                continue;
            if(maxLen[k] > maxL)
            {
                maxL = maxLen[k];
                maxI = k;
            }
        }

        maxLen[i] = maxL + 1;
    }

    int maxL = maxLen[0];
    for(int i = 1; i < nums.size(); ++i)  //找出长度最长的不下降子序列，即maxLen[i]最大的情况
    {
        if(maxLen[i] > maxL)
            maxL = maxLen[i];
    }

    cout<<maxL<<endl;
    return 0;
}

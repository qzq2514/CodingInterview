#include<iostream>
#include<vector>
#include<deque>
using namespace std;

vector<int> findMaxinWindows(vector<int> nums,int winSize)
{
	vector<int> maxinWindows;
	if(nums.size()<winSize || winSize<=0)
		return maxinWindows;

	//存放窗口内最大值的候选数值的下标,按照对应的数值大小是降序排序的
	deque<int> index;

	//遍历nums中前winSize个数,组成第一个滑动窗口
	for(int i=0;i<winSize;i++)
	{
		//不断弹出index中比当前数值nums[i]小的数值
		while(!index.empty() && nums[i]>=nums[index.back()])
			index.pop_back();
		index.push_back(i);

	}

	for(int i=winSize;i<nums.size();i++)
	{
		//index.front()是上一个窗口内最大值,以下一行表示
		//将上一个窗口内最大值保存到最终结果内
		maxinWindows.push_back(nums[index.front()]);
		//和19、20行同理
		while(!index.empty() && nums[i]>=nums[index.back()])
			index.pop_back();
		//弹出已经滑出当前窗口的值,比如:
		//滑动窗口最后一个元素下标为8,winSize=3,那么如果index头部元素下标是5,
		//那么肯定就不在当前的滑动窗口内(当前滑动窗口内元素的下标是6、7、8)
		if(!index.empty() && index.front()<=int(i-winSize))
			index.pop_front();
		index.push_back(i);
	}
	//保存最后一个滑动窗口内的最大值结果
	maxinWindows.push_back(nums[index.front()]);
	return maxinWindows;
}
int main()
{
	int arr[8] = {2,3,4,2,6,2,5,1};
	vector<int> nums(arr,arr+8);

	vector<int> result = findMaxinWindows(nums,3);
	for(int i=0;i<result.size();i++)
		cout<<result[i]<<" ";
	cout<<endl;
	return 0;
}
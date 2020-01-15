#include<iostream>
using namespace std;

//找到数组中任意一个值和下标相等的元素
int getNumberSameAsIndex_any(const int arr[],int len)
{
	if(arr==NULL || len<=0)
		return -1;
	int left = 0;
	int right = len-1;
	while(left<=right)
	{
		int middle_index = (left+right)>>1;
		if(arr[middle_index] == middle_index) 
			return middle_index;

		//如果当前数arr[middle_index] > middle_index,那么因为原数组中每个数是唯一的且单调增的,
		//那么后面的数arr[middle_index+k]肯定是大于他的索引middle_index,
		//那么剩下只需要在前半部分找就行
		if (arr[middle_index] > middle_index)
			right = middle_index-1;
		else   
			left = middle_index+1;  //如果小于,同理

	}
	return -1;
}


//拓展:查找所有本身(arr[middle_index])等于下标(middle_index)的数
//首先要知道这肯定是一个下标连续的范围,该范围的左侧满足:本身均小于下标,右侧满足:本身均大于下标

//找到第一个下标和本身相等的数字
//因为单调递增,其实也就是查找第一个本身大于等于下标的数
int getNumberSameAsIndex_start(const int arr[],int len)
{
	if(arr==NULL || len<=0)
		return -1;
	int left = 0;
	int right = len-1;
	while(left<=right)
	{
		int middle_index = (left+right)>>1;

		//如果本身小于下标,则在右半部分找,否则在左半部分找
		if (arr[middle_index] < middle_index)
			left = middle_index+1; 
		else   
			right = middle_index-1;
	}
	//和之前的二分一样,寻找第一个则返回的是left
	if(left<len && arr[left] == left)
		return left;
	return -1;
}

//找到最后一个下标和本身相等的数字
//因为单调递增,其实也就是查找最后一个本身小于等于下标的数
int getNumberSameAsIndex_end(const int arr[],int len)
{
	if(arr==NULL || len<=0)
		return -1;
	int left = 0;
	int right = len-1;
	while(left<=right)
	{
		int middle_index = (left+right)>>1;

		cout<<left<<" "<<right<<" middle_index:"<<middle_index<<endl;
		//如果本身小于等于下标,则在右半部分找,否则在左半部分找
		if (arr[middle_index] <= middle_index)
			left = middle_index+1;   //右半部分都是本身大于下标的
		else   
			right = middle_index-1;
	}
	//和之前的二分一样,寻找最后一个则返回的是left-1
	if(left-1>=0 && arr[left-1] == left-1)
		return left-1;
	return -1;
}

int main()
{
	const int len=9;
	int arr[len]={-5,-2,0,3,4,5,6,9,10};
	int num = getNumberSameAsIndex_any(arr,len);
	if(num<0)
        cout<<"No number is in the same index as itself!"<<endl;
	else
		cout<<"Number "<<": "<<num<<" is at "<<num<<"th!"<<endl;


	int same_start = getNumberSameAsIndex_start(arr,len);
	int same_end = getNumberSameAsIndex_end(arr,len);
	cout<<"Numbers of digits whose index is same as itself is: "<<same_end-same_start+1<<
	      " (range of indices:"<<same_start<<"~"<<same_end<<")"<<endl;

	return 0;
}
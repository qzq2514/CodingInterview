#include<iostream>
using namespace std;
//0~n-1范围共有n个数,但是排序好的数组长度只有n-1,肯定丢失了一个数,
//因为是排好序的,所以这个丢失的数就是第一个其本身值和其下标不相等的数字

int getMissingNum(const int arr[],int len)
{
	if(arr==NULL || len<=0)
		return -1;
	int left = 0;
	int right = len-1;
	while(left<=right)
	{
		int middle_index = (left+right)>>1;
		if(arr[middle_index] != middle_index) 
		{
			//如果当前下标和对应值不相等,那么有两种情况这个值就是消失的那个数(即第一个下标不等于其本身的数):
			//1.其前面已经没有数,其是数组第一个元素
			//2.其不是数组第一个元素,但是其前面的数字“各在其位”
			if(middle_index==0 || arr[middle_index-1] == middle_index-1)
				return middle_index;
			//如果其本身和下标已经不相等了,但是经过上面的判断不是第一个不相等的的,那么说明第一个不想等的一定在前半部分
		    right = middle_index-1;
		}
		else   //如果相等,那么因为数组是已经排序好的,那么说明第一个不想等的在后半部分
			left = middle_index+1;

	}
	//到这里说明0~n-1都是"各在其位",那么丢失的就是最后一个
	if(left==len)
		return len;
	return -1;
}
int main()
{
	const int len=9;
	int arr[len]={0,1,2,3,4,5,6,7,8};
	cout<<"Missing number is: "<<getMissingNum(arr,len)<<endl;
	return 0;
}
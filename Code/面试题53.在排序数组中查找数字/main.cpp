#include<iostream>
using namespace std;
//方案:递归找数字k在数组arr中第一次和最后一个出现的下标
int GetFirst_rec(int arr[],int k,int start,int end)
{
	if(start>end)
		return -1;

	int mid_index = (start+end)/2;
	int mid = arr[mid_index];
	if(mid == k)
	{
		//两种情况下,在mid_index位置上的数就是排序数组arr中第一个出现的k:
		//1.如果当前数字不是数组的第一个,且它前面一个不是k
		//2.当前就是第一个数,其前面没有数了
		if((mid_index>0 && arr[mid_index-1]!=k) || mid_index==0)
			return mid_index;
		else
			//如果不是第一个,那么就在前半段继续找
			end = mid_index-1;
	}
	//下面就是一般二分查找的思想
	else if(mid>k)
		end = mid_index-1;
	else
		start = mid_index+1;

	return GetFirst_rec(arr,k,start,end);
}
int GetLast_rec(int arr[],int len,int k,int start,int end)
{
	if(start>end)
		return -1;

	int mid_index = (start+end)/2;
	int mid = arr[mid_index];
	if(mid == k)
	{
		//和GetFirst_rec一样,有两种情况下,在mid_index位置上的数就是排序数组arr中最后一个出现的k:
		//1.如果当前数字不是数组的最后一个个,且它后面一个不是k
		//2.当前就是第最后一个数,其后面没有数了
		if((mid_index< len-1 && arr[mid_index+1]!=k) || mid_index==len-1)
			return mid_index;
		else
			//如果不是最后一个,那么就在后半段继续找
			start = mid_index+1;
	}
	//下面就是一般二分查找的思想
	else if(mid>k)
		end = mid_index-1;
	else
		start = mid_index+1;

	return GetLast_rec(arr,len,k,start,end);
}

//GetFirst_rec的非递归形式的实现:找到指定数在数组中第一次出现的下标
int GetFirst_bin(int arr[],int k,int len)
{
	if(arr==NULL || len<=0)
		return -1;

	int start = 0;
	int end = len-1;
	while(start<=end)
	{
		int mid_index = (start+end)/2;
		int mid = arr[mid_index];
		if(mid == k)
		{
			//两种情况下,在mid_index位置上的数就是排序数组arr中第一个出现的k:
			//1.如果当前数字不是数组的第一个,且它前面一个不是k
			//2.当前就是第一个数,其前面没有数了
			if((mid_index>0 && arr[mid_index-1]!=k) || mid_index==0)
				return mid_index;
			else
				//如果不是第一个,那么就在前半段继续找
				end = mid_index-1;
		}
		//下面就是一般二分查找的思想
		else if(mid>k)
			end = mid_index-1;
		else
			start = mid_index+1;
	}
	return -1;
}

//GetLast_rec的非递归形式的实现:找到指定数在数组中最后一次出现的下标
int GetLast_bin(int arr[],int k,int len)
{
	if(arr==NULL || len<=0)
		return -1;

	int start = 0;
	int end = len-1;
	while(start<=end)
	{
		int mid_index = (start+end)/2;
		int mid = arr[mid_index];
		if(mid == k)
		{
			//和GetFirst_rec一样,有两种情况下,在mid_index位置上的数就是排序数组arr中最后一个出现的k:
			//1.如果当前数字不是数组的最后一个个,且它后面一个不是k
			//2.当前就是第最后一个数,其后面没有数了
			if((mid_index< len-1 && arr[mid_index+1]!=k) || mid_index==len-1)
				return mid_index;
			else
				//如果不是最后一个,那么就在后半段继续找
				start = mid_index+1;
		}
		//下面就是一般二分查找的思想
		else if(mid>k)
			end = mid_index-1;
		else
			start = mid_index+1;
	}
	return -1;
}

//一般二分查找:第一个大于等于k的数,最后判断是不是等于k
int GetFirst_bin_s2(int arr[],int k,int len)
{
	if(arr==NULL || len<=0)
		return -1;

	int start = 0;
	int end = len-1;
	while(start<=end)
	{
		int mid_index = (start+end)/2;
		int mid = arr[mid_index];
		if(mid < k)
			start = mid_index+1;
		else
			end = mid_index-1;
	}

	if(start<len && arr[start]==k)
		return start;
	else
		return -1;
}

//一般二分查找:最后一个小于等于k的数,最后判断是不是等于k
int GetLast_bin_s2(int arr[],int k,int len)
{
	if(arr==NULL || len<=0)
		return -1;

	int start = 0;
	int end = len-1;
	while(start<=end)
	{
		int mid_index = (start+end)/2;
		int mid = arr[mid_index];
		if(mid <= k)
			start = mid_index+1;
		else
			end = mid_index-1;
	}

	if(start-1>=0 && arr[start-1]==k)
		return start-1;
	else
		return -1;
}

int main()
{
	int findNum = 3;const int num = 12;
	int arr[num]={0,1,2,3,3,3,3,4,7,7,8,8};
	int firstInd = GetFirst_rec(arr,findNum,0,num-1);
	int lastInd = GetLast_rec(arr,num,findNum,0,num-1);
	cout<<"First_rec: "<<firstInd<<"  GetFirst_bin: "<<GetFirst_bin(arr,findNum,num)
	                                <<"  GetFirst_bin_s2: "<<GetFirst_bin_s2(arr,findNum,num)<<endl;
	cout<<"Last_rec:"<<lastInd<<"  GetLast_bin: "<<GetLast_bin(arr,findNum,num)
									<<"  GetLast_bin_s2: "<<GetLast_bin_s2(arr,findNum,num)<<endl;;
	int count = firstInd!=-1?lastInd - firstInd+1:0;
	cout<<"Number "<<findNum<<" appears "<<count<<" times!"<<endl;
	return 0;
}
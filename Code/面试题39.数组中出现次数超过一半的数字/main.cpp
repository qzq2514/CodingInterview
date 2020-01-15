#include<iostream>
using namespace std;

int partition(int arr[],int len,int begin,int end)
{
	if(arr==NULL || len<=0 || begin<0 || end>=len)
		return -1;

	int mid = begin + (end-begin)/2;
	swap(arr[mid],arr[end]);     //取中间的数字作为标兵并放在最后

	int small = begin-1;      //small+1是下一个小于标兵数字所要存放的位置下标
	for(int i=begin;i<end;i++)
	{
		if(arr[i] < arr[end])
		{
			small++;
			//这句没有也行,但是逻辑上应该判断下,如果要交换的两个位置上的数值一样,就不要交换
			if(arr[i]!=arr[small])   
				swap(arr[i],arr[small]);
		}
	}
	swap(arr[end],arr[++small]);
	return small;
}
void quick_sort(int arr[],int len,int begin,int end)
{
	if(begin == end)
		return;
	int indx = partition(arr,len,begin,end);
	if(indx>begin)
		quick_sort(arr,len,begin,indx-1);
	if(indx<end)
		quick_sort(arr,len,indx+1,end);
}
bool checkIsHalf(int arr[],int len,int number)
{
	int count=0;
	for(int i=0;i<len;i++)
		if(arr[i] == number)
			count++;
	return count*2 >= len;     //这里放宽点条件,如果正好出现一半次数,也返回True
}

//方法一基本支撑点:如果存在出现出现一半次数以上的数字,那么该数一定是排序后的数组的中位数
//但是对于正好出现一半次数的数,是可能不正确的,如(2,2,2,3,4,5)
int MoreThanHalfNum_s1(int arr[],int len)
{
	if(arr==NULL || len<=0)
		return -1;
	//吐过数组中存在出现次数超过一半的数字,那么中位数必定是该数
	quick_sort(arr,10,0,len-1);
	for(int i=0;i<len;i++)
		cout<<arr[i]<<" ";
	cout<<endl;

	int mid_num = arr[len/2];
	return checkIsHalf(arr,len,mid_num)?mid_num:-1;
}
//方法二基本支撑点:如果存在一半次数以上的数字,那么该数字出现的次数比其他所有数的和还要多
//注意该方法是找不到正好出现一半次数的数字,如{3,2,2,3,4,2},在checkIsHalf之前找到的是restlt=4
int MoreThanHalfNum_s2(int arr[],int len)
{
	if(arr==NULL || len<=0)
		return -1;
	int restlt = arr[0];
	int times = 1;
	for(int i=1;i<len;i++)
	{
		cout<<"restlt:"<<restlt<<"  "<<times<<endl;
		if(times==0)
		{
			restlt = arr[i];
			times = 1;
		}
		else if(restlt == arr[i])
			times++;
		else
			times--;
	}
	cout<<"restlt:"<<restlt<<"  "<<times<<endl;
	return checkIsHalf(arr,len,restlt)?restlt:-1;
}

int main()
{
	const int len=6;
	// int arr[len]={3,9,2,2,5,2,4,2,2,7};
	int arr[len]={3,2,2,3,4,2};
	int hafl_value=MoreThanHalfNum_s2(arr,len);
	cout<<"Have half:"<<(hafl_value>=0)<<"  ";
	if(hafl_value>=0)
		cout<<"half_value:"<<hafl_value<<endl;
	return 0;
}
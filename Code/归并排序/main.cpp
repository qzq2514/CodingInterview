#include<iostream>
using namespace std;

void merge_sort_core(int *data,int *copy,int start,int end)
{
	if(start == end)
		return ;
	int length = (end-start)/2;
	int rightStart=start+length+1;
	merge_sort_core(data,copy,start,start+length);
	merge_sort_core(data,copy,rightStart,end);

	int i = start+length;  //指向左边排序好的数组的最后一个元素
	int j = end;           //指向右边排序好的数组的最后一个元素
	int copyInd=end;
	while(i>=start && j>=rightStart)
		copy[copyInd--] = data[i]>data[j]?data[i--]:data[j--];

	for (;i>=start;i--)
		copy[copyInd--] = data[i];

	for (;j>=rightStart;j--)
		copy[copyInd--] = data[j];

	for(int m=start;m<=end;m++)
		data[m]=copy[m];
	return ;
}

void merge_sort(int *arr,int length)
{
	if(arr==NULL || length<=0)
		return;
	int *copy = new int[length];
	for (int i=0;i<length;i++)
		copy[i]=arr[i];
	merge_sort_core(arr,copy,0,length-1);
	delete[] copy;
}

int main()
{
	const int len=10;
	int arr[len]={5,3,6,4,7,10,2,8,9,1};
	merge_sort(arr,len);
	for(int i=0;i<len;i++)
		cout<<arr[i]<<" ";
	return 0;
}
#include<iostream>
using namespace std;


//暴力方法:每个数和后面的比较(O(n^2))
int inversePair_s1(int *arr,int length)
{
	if(arr==NULL || length<=0)
		return 0;
	int count = 0;
	for(int i=0;i<length;i++)
	{
		for(int j=i+1;j<length;j++)
		{
			if(arr[i]>arr[j])
			{
				// cout<<"("<<arr[i]<<","<<arr[j]<<")"<<endl;
				count++;
			}
		}
	}
	return count;
}

//基于归并排序的方法:(O(nlog(n)))
int inversePair_core(int *data,int *copy,int start,int end)
{
	if(start == end)
		return 0;
	int length = (end-start)/2;
	int rightStart=start+length+1;
	//原书上这里data,copy是反过来的,但是为了和归并排序相统一,我觉得还是不反过来,
	//并且在函数最后要将copy赋值给data,改变原数组,同时达到归并排序的目的

	int left=inversePair_core(data,copy,start,start+length);
	int right=inversePair_core(data,copy,rightStart,end);

	//到这里,当前数组的左半部分(start,start+length)和右半部分(start+length+1,end)都是已经排序好的了
	//便于计算两半部分之间的逆序对
	int i = start+length;  //指向左边排序好的数组的最后一个元素
	int j = end;           //指向右边排序好的数组的最后一个元素

	int count=0;
	int copyInd=end;
	while(i>=start && j>=rightStart)
	{
		if(data[i]>data[j])    //左边的数小于右边的,则是一个逆序对
		{
			//因为右边是从小到大排序好的,所以如果data[i]>data[j],
			//那么data[rightStart]到data[j]肯定都是小于data[i]的
			for(int k=j;k>=rightStart;k--)
				cout<<"("<<data[i]<<","<<data[k]<<")"<<endl;
			copy[copyInd--]=data[i--];
			count+=j-start-length;
		}
		else
		    copy[copyInd--]=data[j--];
	}

	//到这里肯定i或j其中一个已经到了自己那半部分的起始,那么就直接将另一剩下的直接赋值
	for (;i>=start;i--)
		copy[copyInd--] = data[i];

	for (;j>=rightStart;j--)
		copy[copyInd--] = data[j];

	for(int m=start;m<=end;m++)
		data[m]=copy[m];

	return left+right+count;
}

int inversePair_s2(int *arr,int length)
{
	if(arr==NULL || length<=0)
		return 0;
	int *copy = new int[length];
	for (int i=0;i<length;i++)
		copy[i]=arr[i];
	int count = inversePair_core(arr,copy,0,length-1);
	delete[] copy;
	return count;
}

int main()
{
	const int len=10;
	int arr[len]={5,3,6,4,7,10,2,8,9,1};
	int count1 = inversePair_s1(arr,len);
	cout<<endl<<"Number of inversePair_s1 : "<<count1<<endl;
	int count2 = inversePair_s2(arr,len);
	cout<<endl<<"Number of inversePair_s2 : "<<count2<<endl;
	for(int i=0;i<len;i++)
		cout<<arr[i]<<" ";
	return 0;
}
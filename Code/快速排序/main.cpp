#include<iostream>
#include<string>
#include<algorithm>//sort函数包含的头文件
using namespace std;

int partition(int arr[],int len,int start, int end)
{
	if(arr==NULL || len<=0 ||start<0 ||end>=len)
	{
		cout<<"error"<<endl;
		return -1;
	}

	int mid=start+(end-start)/2;      //以中间的数字作为标兵
	swap(arr[mid],arr[end]);          //将标兵放到最后

	int small=start-1;                //下一个小于标兵的数字最终被保存到数组的(small+1)位置
	for(int i=start;i<end;i++)        
	{
		if(arr[i]<arr[end])           //除了最后一个数字，其他数字都与标兵进行比较
		{
			small++;                //这时small就是下一个小于标兵的数字所要存放的下标位置
			if (arr[i]!=arr[small])
				swap(arr[i],arr[small]);   //当前arr[i]小于标兵,则将其放在small位置
		}
	}
	//这时,下标0~small的数都是小于标兵的数字
	swap(arr[++small],arr[end]);
	return small;
}
void quick_sort(int arr[],int len,int start, int end)
{
	if(start==end)
		return ;

	//这里的index是该轮排序后标兵所在的位置,则(start~index-1均小于标兵,index+1~end均大于等于标兵)
	int index=partition(arr,len,start,end);   
	if(index>start)                       
		quick_sort(arr,len,start,index-1);
	if(index<end)
		quick_sort(arr,len,index+1,end);
}
int main()
{
	int arr[10]={0,9,2,8,5,2,4,5,7,6};

	// int small=partition(arr,10,0,9);
	// cout<<"small:"<<small<<endl;

	quick_sort(arr,10,0,9);
	for(int i=0;i<10;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	return 0;
}
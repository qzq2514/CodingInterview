#include<iostream>
using namespace std;

//查看start~end数字一共在arr中出现了几次
int Count(const int arr[],int len,int start,int end)
{
    if(arr==NULL)
    	return 0;
    int count=0;
    for(int i=0;i<len;i++)
    	if (arr[i]>=start && arr[i]<=end)
    		count++;
    return count;
}

int check_duplicate(int arr[],int len)
{
	if (arr==NULL || len<=0)
		return -1;
	int start=1,end=len-1;
	while(start<=end)
	{
		int mid=((end-start)>>1)+start;
		int count=Count(arr,len,start,mid);
		cout<<start<<"--"<<mid<<"---"<<count<<endl;
		if (start == end)
		{
			if (count>1)
				return start;
			else
				break;
		}

		if(count>(mid-start+1))    //数字start~mid出现次数了超过end-mid+1次,那么重复元素肯定在start~mid中
			end=mid;
		else                      //因为肯定存在重复元素,不在start~mid那么肯定就在mid+1~end中
			start=mid+1;

	}
	return -1;

}

int main()
{
	//数组长度为n,数组中的元素为1~n-1范围(所以必然有重复元素)
	//需要提出的是,该方法不能就确保找到重复的元素,比如底下的numbers[10],第一次二分的时候,
	//1~5出现了5次,那么该算法就会认为1~5中没有重复元素
	// int numbers[10]={0,2,3,4,5,5,7,8,6,9};   
	int numbers[8]={2,3,5,4,3,2,6,7};
	int duplicate_num = check_duplicate(numbers,8);
	cout<<"duplicate_num:"<<duplicate_num<<endl;
	return 0;
}
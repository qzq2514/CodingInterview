#include<iostream>
using namespace std;

//找到严格递增数组中所有和等于指定数sum的数对.
//思路:初始化两个指针指向数组头(start)和尾(end),不断计算当前两个指针指向的数的和,
//等于sum则找到可直接打印,小于则向后移动start指针,大于则向前移动end指针.该方案时间复杂度为O(n)

//解释:首先一般思路是O(n^2)的方法,暴力计算两两数之间的和并与sum比较,
//但是该方法没有充分利用到数组是升序的特点,比如{-1,0,1,2,5,9,10}找和为7的数对,那么在找到2+5后,
//2就不用再和5之后的数进行配对,5也不用和2之前的数进行配对.
//而O(n)的方案则利用这个特点,两个指针在寻找的过程中改不断向中间逼近,不会向两端发散,
//同时在找到一个数对后,因为数组递增,那么如果还存在其他数对的和为sum,那么这两个数一定在已经找打的数对中间,
//所以在逼近的过程中可以找到所有的符合条件的数对

//假设:若找到一组数对arr[i]+arr[j]=sum,且存在另一组数对arr[i+k]+arr[j+p]=sum
//反证明:因为数组严格递增,所以arr[i+k]>arr[i],arr[j+p]>arr[j],所以:
//arr[i+k]+arr[j+p]>arr[i]+arr[j]=sum,与假设矛盾

void findSum(int arr[],int len,long long sum)
{
	if(arr==NULL || len <2)
		return ;
	int start = 0;
	int end = len-1;
	while(start<end)
	{
		long long curSum = arr[start]+arr[end];
		if(curSum == sum)
		{
			cout<<arr[start]<<" + "<<arr[end]<<" = "<<sum<<endl;
			end--;
		}
		else if(curSum<sum)
			start++;
		else
			end--;
	}
	return ;
}

int main()
{
	const int len = 10;
	long long sum = 23;
	int arr[len] = {1,3,4,8,10,13,15,18,21,22};
	findSum(arr,len,sum);
	return 0;
}
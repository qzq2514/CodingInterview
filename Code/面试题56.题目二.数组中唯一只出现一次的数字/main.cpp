#include<iostream>
#include<memory.h>
using namespace std;

//题目:数组中除了某个数num,其他数都出现三次,找出这个数num

//方案:把每个数的二进制形式的对应位上加起来,那么因为除了一个数num出现一次,
//其他数(有n个)都出现三次,所以最终结果每位上也就两种结果:
//1. 3a*1+3(n-a)*0+1 = 3a+1  
//2. 3a*1+3(n-a)*0+0 = 3a
//以上第一种不能被3整除,且此时num对应位上是1,而第二种能被3整除,此时num对应位上是0
//根据这个特点就能复原出num

//推广:如果数组中除了某个数num,其他数都出现k次,找出这个数num
//那么同样思路,最后和结果上每位判断是否能被k整除

int findAppearceOnce(int arr[],int len)
{
	if(arr==NULL || len<=0)
		return 0;

	// int size = 8*sizeof(int);
	// int *bitCount = new int[size];
	// memset(bitCount,0,sizeof(bitCount));

	int size = 32;
	int bitCount[32] = {};
	for(int i=0;i<len;i++)
	{
		int cur_num = arr[i];
		for(int j=0;j<size;j++)
		{
			bitCount[j] += cur_num & 1;
			cur_num = cur_num>>1; 
		}
	}

	//bitCount中下标0~31依次存放从低位到高位的统计结果
	// for(int k=0;k<size;k++)
	// 	cout<<bitCount[k]<<" ";
	// cout<<endl;

	//注意因为在循环中result不断左移,最先加进去的bitCount[k]%3会变成高位
	//所要从下标要从size-1遍历到0
	int result=0;
	for(int k=size-1;k>=0;k--)
	{
		result = result<<1;   //将结果左移,保证此时最低位为0
		result += bitCount[k]%3; //直接加上0或者1就能将result的最低位置为0或1
	}
	return result;
}
int main()
{
	cout<<"sizeof(int):"<<sizeof(int)<<endl;
	const int len =10;
	int arr[len]={2,2,4,4,6,2,4,6,6,5};
	int num = findAppearceOnce(arr,len);

	for(int k=0;k<len;k++)
		cout<<arr[k]<<" ";
	cout<<endl<<"Once appearing num : "<<num<<endl;
	return 0;
}
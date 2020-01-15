#include<iostream>
using namespace std;

//非动态规划方法
//本方法找到最大子数组和,并打印出该最大子数组的起始坐标以便更好理解该方法
int GreaterstNumber_s1(int arr[],int len)
{
     if(arr==NULL || len<=0)
     	return -1;

     int greatestNumber = 0;
     int curSum = 0,start = -1, end = -1;
     for(int i=0;i<len;i++)
     {
     	//如果当前的候选最大连续子数组和curSum小于等于0,那么说明之前的数字是"零贡献"甚至"负贡献"的,
     	//就完全没必要把之前的数值加进来了
     	if(curSum <= 0)
     	{
     		curSum = arr[i];
     		start = i;    //相当于重新找子数组了
     	}
     	else
     	//如果当前的curSum大于0,那么直接把当前值arr[i]加进来,因为即便当前的值arr[i]是负数,
     	//那么也有可能后面遇到一个更大的整数,把arr[i]造成的"负贡献"变成"正贡献"
     		curSum += arr[i];    //到这里不要更新end,因为万一数组最后一个数字是负数,也会把end更新了

     	//更新最后结果
     	if(curSum>greatestNumber)
     	{
     		greatestNumber = curSum; 
     		end = i;             //正确的应该是在更新greatestNumber的时候更新end
     	}
     }
     cout<<"["<<start<<"]~["<<end<<"]:";
    return greatestNumber;
}

int GreaterstNumber_s2(int arr[],int len)
{
	if(arr==NULL || len<=0)
     	return -1;

   //工台规划:dp[i]表示以arr[i]结尾的子数组的最大值
   int *dp = new int[len];
   int greatestNumber = -1; 
   dp[0] = arr[0];
   for(int i=1;i<len;i++)
   {
       dp[i] = max(arr[i],dp[i-1]+arr[i]);
       greatestNumber = max(dp[i],greatestNumber);
   }

   return greatestNumber<0?-1:greatestNumber;
}
int main()
{
	const int len = 8;
	int arr[len]={1,-2,3,10,-4,7,2,-5};
	for(int i=0;i<len;i++)
		cout<<arr[i]<<" ";
	cout<<endl;
	cout<<"GreaterstNumber_s1: "<<GreaterstNumber_s1(arr,len)<<endl;
	cout<<"GreaterstNumber_s2: "<<GreaterstNumber_s2(arr,len)<<endl;
	return 0;
}
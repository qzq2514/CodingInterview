#include<iostream>
using namespace std;

//选定股票买入和卖出时间，争取最大的利润
int maxDiff(int arr[],int len,int &buyValue,int &sellValue)
{
	if(arr==NULL || len<2)
		return -1;
	buyValue = arr[0];
	sellValue = arr[1];
	int maxDiffValue = sellValue-buyValue;
	for(int i=2;i<len;i++)
	{
		//如果当前时间卖出,记录之前的最小价格,即为当前最大的利润
		if(arr[i-1]<buyValue)
			buyValue = arr[i-1];
		int curMaxDiff = arr[i] - buyValue;
		//更新最大利润
		if(curMaxDiff>maxDiffValue)
		{
			sellValue = arr[i];
			maxDiffValue = curMaxDiff;
		}
	}
	return maxDiffValue;
}
int main()
{
	const int len = 8;
	int arr[len]={9,11,8,5,7,12,16,14};
	int buyValue = 0;int sellValue = 0;
	int maxDiffValue = maxDiff(arr,len,buyValue,sellValue);
	for(int i=0;i<len;i++)
		cout<<arr[i]<<" ";
	cout<<"\nMax profit: "<<maxDiffValue<<" (Buy at "<<buyValue<<" and sell at "<<sellValue<<")."<<endl;
	return 0;
}
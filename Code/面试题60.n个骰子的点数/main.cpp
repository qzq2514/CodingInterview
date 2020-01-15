#include<iostream>
#include<memory>
#include<math.h>
using namespace std;
int g_maxValue=6;   //骰子最大数为6

//递归方法:dfs

//n:原始总投骰子的次数n
//curCount:开始第curCount次投骰子
//curSum当前dfs这条路的当前和
//countSum:前curCount次投骰子的计数结果,还未将第第curCount次投的结果记入
void count(int n,int curCount,int curSum,int * countSum)
{
	if(curCount>n+1)
		return;
	if(curCount==n+1)
		countSum[curSum-n]++;
	for(int i=1;i<=g_maxValue;i++)
		count(n,curCount+1,curSum+i,countSum);
}
void printProb_recursion(int n)
{
	int maxSum = g_maxValue * n;
	int *countSum = new int[maxSum-n+1];  //投n次骰子,共有6*n-n+1中可能的点数和
	for(int i=n;i<=maxSum;i++)
		countSum[i-n]=0;                 //countSum[i-n]保存和为i-n的次数

	count(n,1,0,countSum);
	double allCount = pow(double(g_maxValue),n);
	for(int i=n;i<=maxSum;i++)
	{
		double rate = countSum[i-n] / allCount;
		cout<<i<<" : "<< rate <<"("<<countSum[i-n]<<")"<<endl;
	}
}

//动态规划:
//思路核心:在投了第k次后和为i出现的次数是上一次投了之后和为i-6到i-1的总次数之和
void printProb_dp(int n)
{
	if(n < 1)
		return ;
	int maxSum = g_maxValue * n;
	int* countSum[2];
	countSum[0] = new int[maxSum+1];   //因为中间过程有可能统计和为比较小(小于n),所以定义长度为maxSum+1的数组
	countSum[1] = new int[maxSum+1];   //countSum[0][i]和countSum[1][i]均表示当前和为i出现的次数
	for(int i=0;i<=maxSum;i++)
	{
		countSum[0][i]=0;
		countSum[1][i]=0;
	}
	int flag=0;
	//初始化:在投了第一个骰子后,每个点数可能出现的次数都是1
	for (int i=1;i<=g_maxValue;i++)
		countSum[flag][i]=1;

	//开始之后继续投骰子,这时countSum[flag]保存上一次投之后的结果,
	//countSum[1-flag]用于保存这一轮投了之后的结果
	for(int k=2;k<=n;k++)
	{
		//因为这轮投了骰子之后,就共投了k次骰子,那么最小的数肯定是k,所以小于k的就不可能出现
		for(int i=0;i<k;i++)
			countSum[1-flag][i]=0;

		//这轮投了骰子之后,就共投了k次骰子,和的范围是k~g_maxValue*k
		for(int i=k;i<=g_maxValue*k;i++)
		{	
			//统计这轮之后骰子的结果:
			//countSum[1-flag][i]表示这轮之后和为i的次数,因为这轮的投骰子可能出现1~6
			//所以其是上一轮的结果countSum[flag]中次数为i-6~i-1的次数和
			countSum[1-flag][i]=0;
			for(int j=1;j<=i && j<=g_maxValue;j++)
				countSum[1-flag][i] += countSum[flag][i-j];
		}
		//交换两个数组
		flag=1-flag;
	}

	double allCount = pow(double(g_maxValue),n);
	for(int i=n;i<=maxSum;i++)
	{
		//虽然countSum[1-flag]是保存每轮之后的计数结果,但是最后一轮后又交换了一次,
		//所以最终的结果存在countSum[flag]中
		double rate = countSum[flag][i] / allCount;
		cout<<i<<" : "<< rate <<"("<<countSum[flag][i]<<")"<<endl;
	}
	delete[] countSum[0];
	delete[] countSum[1];
}
int main()
{  
    int n=4;
	printProb_recursion(n);
	cout<<"--------------"<<endl;
	printProb_dp(n);
	return 0;
}
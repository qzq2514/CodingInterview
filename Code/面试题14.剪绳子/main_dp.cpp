#include<iostream>
#include<memory.h>
#include<math.h>
using namespace std;

//长度为len的绳子剪成m段,其中len>1,m>1,求最后所有小绳子长度乘积的最大值
#define MAX_LEN 1000+1
int maxProductCut_dp(int len)
{
	if(len<2) return 0;
	else if(len==2) return 1;  //因为m>1说明必须要剪,所以长度为2时最大乘积为1(1x1),长度为3是最大乘积为2(1x2)
	else if(len==3) return 2;
	int dp[MAX_LEN],res;
	memset(dp,0,sizeof(dp));

    //要注意,在之后的动态规划中,dp[i]表示长度为i的绳剪了之后最大乘积,
    //而长度为2时,可以直接作为一段不用再剪,所以dp[2]=2,其余长度为2时绳子剪了之后最大乘积是不同道理的
    //长度为3时同理,不用剪是最大的,长度为1时和0时不能剪,就是本身
    dp[0]=0;dp[1]=1;
	dp[2]=2,dp[3]=3;        
	for(int i=4;i<=len;i++)
	{
		for(int j=1;j<=i/2;j++)
		{
		     dp[i]=max(dp[i],dp[j]*dp[i-j]);   //因为之后长度为i必须至少剪一刀,所以j从1开始
		     // cout<<i<<"_in:"<<dp[i]<<endl;     //如果可以不剪,那么j就可从下标0开始,且此时要将dp[0]重新赋值为1.且dp[i]都要初始化为i
		}   								   //(但是还是剪了之后乘积最大)
		 // cout<<i<<"_out-----------:"<<dp[i]<<endl;
	}
	return dp[len];
}
int maxProductCut_greedy(int len)
{
	if(len<2) return 0;
	else if(len==2) return 1;  
	else if(len==3) return 2;

	//贪婪算法,可以证明如果在len>=5的时候,尽可能地剪长度为3的绳子,但是如果最后剪的那次之前的绳子剩下长度为4的时候,
	//就不要在剪出一个3,而是剪出两个2(证明省略)
	int timesOf3=len/3;
	if (len%3==1)
		timesOf3-=1;	
	int timesOf2=(len-timesOf3*3)/2;

	return (int)pow(3,timesOf3)*(int)pow(2,timesOf2);
}
int main()
{
	int len=8;
	cout<<"len:"<<len<<endl;
	cout<<"dp:"<<maxProductCut_dp(len)<<endl;
	cout<<"greedy:"<<maxProductCut_greedy(len)<<endl;
	return 0;
}
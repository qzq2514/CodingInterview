#include<iostream>
#include <limits>
using namespace std;

const int len=3;
int uglyFactors[len]={2,3,5};


bool checkUgly(int number)
{
	int *count = new int[len];

	for(int i=0;i<len;i++)
	{	
		count[i]=0;
		while(number%uglyFactors[i]==0)
		{
			count[i]++;
			number/=uglyFactors[i];
		}
	}
	//打印出每个丑数的2、3、5因子的幂次数,可能会有规律
	// if(number==1)
	// {
	// 	cout<<"count:";
	// 	for(int i=0;i<len;i++)
	// 	   cout<<count[i]<<" ";
	// 	cout<<endl;
	// }
		
	
	return number==1;
}
//暴力办法寻找丑数
int getUglyNumber_s1(int index)
{
     int number=1;
     int cur_index=1;   //第一个丑数是1
     while(cur_index<index)
     {
     	number++;
     	if(checkUgly(number))
     		cur_index++;
     }

     return number;
}

//非暴力方式,按照规律，跳过非丑数,旨在丑数上一个个找,
int getUglyNumber_s2(int index)
{
	int *uglyNumers = new int[index+1];
	//pFactor[i]表示将uglyNumers中的所有数分别乘以因子uglyFactors[i]后第一个大于当前最大丑数uglyNumers[nextIndex-1]的下标
	//如当前已经找到丑数uglyNumers=[0,1,2,3,4,5,6](第一个0完全用于补位),那么pFactor[0]=4,pFactor[1]=3,pFactor[2]=2
	int *pFactor = new int[len];  

	uglyNumers[1]=1;
	int nextIndex=2;
	for(int i=0;i<len;i++)
		pFactor[i] = 1;          

	while(nextIndex<=index)
	{
		int nextUglyNum = numeric_limits<int>::max();

		//以乘以各自的因子后最小的值作为下一个丑数
		for(int i=0;i<len;i++)
			nextUglyNum = min(nextUglyNum,uglyNumers[pFactor[i]]*uglyFactors[i]);
		
		uglyNumers[nextIndex] = nextUglyNum;

		//更新pFactor
		for(int i=0;i<len;i++)
		{
			while(uglyNumers[pFactor[i]]*uglyFactors[i] <= nextUglyNum)
				pFactor[i]++;
		}
		nextIndex++;
	}
	return uglyNumers[index];
}
int main()
{	
	//用于打印2/3/5幂次数
	// getUglyNumber_s1(100);

	for(int index=1;index<100;index++)
	{
		int UglyNumber_s1=getUglyNumber_s1(index);
		int UglyNumber_s2=getUglyNumber_s2(index);
		cout<<index<<": "<<UglyNumber_s1<<" "<<UglyNumber_s2<<endl;
	}
	return 0;
}
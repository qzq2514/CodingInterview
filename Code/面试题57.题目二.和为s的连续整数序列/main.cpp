#include<iostream>
using namespace std;

//问题:在1,2,3,4,5,6,....中找到所有和等于tarSum的连续正数序列
void print_seq(int start,int end)
{
	if(start>end)
		return ;
	cout<<start;
	int sum=start;
	for(int i=start+1;i<=end;i++)
	{
		sum+=i;
		cout<<"+"<<i;
	}
	cout<<"="<<sum<<endl;
}

void findSeqs_s1(int tarSum)
{
	int start=1;
	int end=2;
	int curSum = start+end;
	while(start<end)
	{
		//如果当前序列和小于tarSum,那么就增大end扩大序列范围
		if(curSum<tarSum)
		{
			end++;
			curSum+=end;
		}
		else
		{
			//注意找到一个合适的序列后,仍然要增大start或者end,
			//开始找下一个序列,不然while死循环
			if(curSum==tarSum)
				print_seq(start,end);
			//如果当前序列和大于tarSum,那么就增大start减小序列范围
			curSum-=start;
			start++;
		}
	}
    return;
}

//本想探究另一种类似的方法,findSeqs_s1是初始化start=1、end=2,即从和最小的序列开始,
//我想的是初始化start=1、end=tarSum,从和最大的序列开始但是有个问题是,start和1、end往中间走,
//都是导致范围变小,进而导致和变小,而没办法变大,就无法寻找,虽然在过程中start可以变小,end可以变大,
//但是会导致之前找过的序列又被计算一次,甚至有可能其中一个或者两个指针不断"徘徊"陷入死循环,
//所以该方法在此思路下暂时不可取。
//而原方法,start和end同时从最小开始向最大值走去,start变大,序列范围变小即和变小;end变大,序列范围变大即和变大,
//这样有一种博弈的关系,同时start和end都是变大的,不会产生重复序列,就不会产生死循环。
//待新方法找到好思路再来更新。
int main()
{
	findSeqs_s1(15);
	// print_seq(1,10);
	return 0;
}
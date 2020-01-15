#include<iostream>
using namespace std;

//number与1(即二进制的00000001)进行与操作查看二进制的number最低位是不是1,之后不断将number右移1个位
//缺点:如果number<0,那么右移1个位时,会在左则补1,那么最终number会变成-1(即二进制的11111111),陷入死循环
int solution1(int number)
{
	int count=0;
	while(number)
	{
		count+=number&1;
		number=number>>1;

	}
	return count;
}

//不断将flag右移1,将flag与number与,即可判断number右数第i位是不是1,解决了number<0死循环的问题
//flag右移的次数等于整型的位数,即如果32位int,那么就要对flag右移32次
int solution2(int number)
{
	int count=0;
	int flag=1;
	while(flag)
	{
		if(number&flag)
			count++;
		flag=flag<<1;
	}
	return count;
}

//number减1后,会将其二进制最右边的1翻转为0,而再往右边的所有0会翻转为1,这时number&(number-1)就会将原来number的最右边的1翻转为0
//该方法while循环的次数和二进制number中1的个数是相等的
int solution3(int number)
{
	int count=0;
	while(number)
	{
		count++;
		number=number&(number-1);
	}
	return count;
}
int main()
{
	int N=-1000;       //32位的int
	cout<<"N:"<<endl; 
	// cout<<solution1(N)<<endl;   //N>=0时再调用
	cout<<solution2(N)<<endl;
	cout<<solution3(N)<<endl;
	return 0;
}
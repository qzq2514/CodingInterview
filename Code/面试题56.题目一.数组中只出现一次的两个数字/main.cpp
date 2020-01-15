#include<iostream>
using namespace std;

//思路核心:一个数和它本身异或为0
//思路:
//若数组中两个只出现一次的数为num1和num2,那么将数组中所有数异或,最终的结果是num1^num2,
//找到num1^num2的二进制形式中第一个为1的位,并将数组中所有的数根据该位是否为1分成两组,
//每组分别异或得到的结果就是num1和num2

//理解:
//1.相同的数肯定二进制形式完全一样,肯定被分到同一组
//2.num1和num2异或的结果在该位为1,那么num1和num2的两个二进制在该位肯定是不同的(即一个为1,一个为0),
//  那么num1和num2肯定会被分到不同的组中
//3.每组中只有一个数出现一次,那么剩下的数都是成对出现的,总体异或结果肯定为0,而任何数和0异或肯定等于本身,
//  所以最后每组异或的结果肯定就是该组中只出现一次的那个数。


//在num的二进制中从右到左找到第一个为1的位
unsigned int findFirstBit1(int num)
{
	int indexBit = 0;
	while((num & 1)==0 && indexBit < 8*sizeof(num))
	{
		num = num>>1;
		indexBit++;
	}
	return indexBit;
}
//判断num从右向左数的第indexBit位是不是1.(indexBit从0开始)
bool isBit1(int num,unsigned int indexBit)
{
     num = num>>indexBit;
     return num & 1;
}
void findTwoNumsAppearOnce(int arr[],int len,int &num1,int &num2)
{
	if(arr==NULL || len<=0)
		return ;

	int resultOR = 0;
	for(int i=0;i<len;i++)
	    resultOR ^= arr[i];

	unsigned int indexBit1 = findFirstBit1(resultOR);
	num1=num2=0;
	for(int i=0;i<len;i++)
	{
		if(isBit1(arr[i],indexBit1))
			num1^=arr[i];
		else
			num2^=arr[i];
	}
}
int main()
{
	const int len=8;
	int arr[len] = {1,2,1,3,3,4,4,5};
	for(int i=0;i<len;i++)
	    cout<<arr[i]<<" ";
	cout<<endl;

	int num1=0,num2=0;
	findTwoNumsAppearOnce(arr,len,num1,num2);
	cout<<num1<<" "<<num2<<endl;

	return 0;
}


#include<iostream>
using namespace std;

//方法一:暴力的求出0~N中每一个数各个位上的1
int numberOf1_core(int n)
{
	int res=0;
	while(n)
	{
		if(n%10==1)
			res++;
		n/=10;
	}
	return res;
}
int numberOf1_s1(int number)
{
	int res=0;
	for(int i=1;i<=number;i++)
	{
       res+=numberOf1_core(i);
	}
	return res;
}

//方法二:利用数字规律求出0~N之间1的个数
int powerBase10(unsigned int n)
{
	int res=1;
	for(int i=0;i<n;i++)
		res*=10;
	return res;
}
int numberOf1_s2_core(char* strN)
{
	if(strN==NULL || *strN<'0' || *strN>'9' || *strN == '\0')
		return 0;

	int first = (*strN)-'0';   //最高位数字
	int length = strlen(strN);

	if(length==1)
		return first>0?1:0;    //N只有一位数,即0~9,则包含1的个数取决于该数是不是大于0

	//1.计算最高位出现1的次数
	int numberFirst=0;
	if(first>1)
		//N最高位大于1,那么0~N中最高位出现1的次数为10的(length-1)次方
		//如N=22345,最高位(万位)出现1的是在10000~19999,即10的4次方
		numberFirst = powerBase10(length-1);
	else
		//N最高位等于1,那么0~N中最高位出现1的次数就是出去最高位后剩下的整数值加一
		//如N=12345,最高位(万位)出现1的是在10000~12345,2345+1=2346次
		//strN+1是从次高位算起转为整数
		numberFirst = atoi(strN+1)+1;

	//2.计算除去最高位外且除去0~atoi(strN+1)外其他位出现1的次数
	//如0~22345这里计算2236~22345范围内低四位出现1的次数
	//可以分成两批2236~12345和12236~22345,每一批内,在低四位内每位取1后,其他三位都可以取任意值,
	//(如2236~12345这一批,其低四位是包含0~9999所有值的,在千位取1时,变成1xxx,其他三位可以任意去0~9的数)
	//根据排列组合,每一批内,出现1的次数为4*10^3
	int otherNumber1 = first*(length-1)*powerBase10(length-2);

	//3.递归地求0~atoi(strN+1)范围内出现1的次数
	int number_recusive = numberOf1_s2_core(strN+1);

	return numberFirst+otherNumber1+number_recusive;
}

int numberOf1_s2(int number)
{
	if(number<=0)
		return 0;
	char strN[50];
	sprintf(strN,"%d",number);
	return numberOf1_s2_core(strN);
}

int main()
{
	int number=12345;

	int numberOf1 = numberOf1_s1(number);
	cout<<"numberOf1_s1:"<<numberOf1<<endl;
	numberOf1 = numberOf1_s2(number);
	cout<<"numberOf1_s2:"<<numberOf1<<endl;
	return 0;
}
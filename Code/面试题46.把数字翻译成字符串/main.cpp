#include<iostream>
using namespace std;


//递归:因为可能产生重复计算,所以效率会比较低
//f[i]=f[i+1] + g(i,i+1)*f(i+2)
int get_tran_count_dp(const char* number)
{
	if(number==NULL || (*number)=='\0')
		return 0;
    if((*(number+1))=='\0')
    	return 1;

    int digit1 = (*number)-'0';
	int digit2 = (*(number+1))-'0';
	int num = digit1*10+digit2;	
	int count = get_tran_count_dp(number+1);
	if (num>=10 && num<=25)
	{
		if((*(number+2))=='\0')
			count+=1;
		else
			count+=get_tran_count_dp(number+2);
	}
    return count;
}
int get_tran_count_s1(int number)
{
	if(number<0)
		return 0;
	//转为字符串形式后,便于遍历
	string numberStr = to_string(number);	
	const char* numberChar = numberStr.c_str();
	return get_tran_count_dp(numberChar);

}
//动态规划:自底向上的方法,不会产生重复计算
//counter[i]=counter[i+1] + g(i,i+1)*counter(i+2)
//其中如果number[i]和number[i+1]构成的两位数大于等于10小于等于25,则g(i,i+1)=1, 否则为0
int get_tran_count_s2(int number)
{
	if(number<0)
		return 0;
	//转为字符串形式后,便于遍历
	string numberStr = to_string(number);
	int len = numberStr.length();
	int *counter = new int[len];   //counter[i]表示从下标i到下标len-1之间数字的总共翻译次数
	counter[len-1] = 1;

	for(int i=len-2;i>=0;i--)
	{
		//默认i~len-1之间数字翻译种数和i+1~len-1之间数字翻译种数相等
		counter[i] = counter[i+1];      

		int digit1 = numberStr[i]-'0';
		int digit2 = numberStr[i+1]-'0';
		int num = digit1*10+digit2;
		if (num>=10 && num<=25)
		{
			//在i==len-2时,也就是只构建到两位数的时候,如果这两位数在10~25之间,那么直接在原本的种数上加一就行
			//比如12,一开始2可以构建一种(则有counter[len-1]),到1的时候,因为10<=12<=25,所以直接counter[len-2]直接再加一种,
			//即12共有2种翻译
			if(i==len-2)
				counter[i]+=1;                 
			else
			//而在i<len-2的时候,那么就直接可以用上卖弄动态规划的公式就行了
		   		counter[i]+=counter[i+2];
		}
	}
	return counter[0];
}
int main()
{
	int number = 12218;
	cout<<"number:"<<number<<"1-->"<<get_tran_count_s1(number)<<endl;
	cout<<"number:"<<number<<"2-->"<<get_tran_count_s2(number)<<endl;
	return 0;
}
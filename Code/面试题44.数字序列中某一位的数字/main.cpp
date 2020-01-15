#include<iostream>
#include<math.h>
using namespace std;
int getNumber(int index)
{
	if(index<0)
		return -1;
	if(index<=9)
		return index;     //索引小于等于9的就是前10个一位数,直接返回
	int length=2;
	index-=10;            //一位数0~9共有10个数
	while(true)
	{
		int cur_len_numbers = 9*pow(10,length-1);
		if(index<=cur_len_numbers*length)
		{
			int ind_num=index/length;    //原始index是在是第ind_num个length位数上(ind_num从0开始)
			int mod_num=index%length;    //原始index是在是第ind_num个length位数上从左向右数的第mod_num位(mod_num从0开始)
			int cur_num=pow(10,length-1) + ind_num;  //cur_num是上述所说的第ind_num个length位数上
			for(int i=0;i<length-mod_num-1;i++)     //在length位数上,从左向右数的第mod_num位就是从右向左数的第(length-mod_num-1)位
										   //如5位数,从左向右的第1位就是从右向左数的第3位
				cur_num/=10;               //不断消掉最后一位上的数字
			return cur_num%10;             //取最后一位上的数字就是最终要求的数字
		}
		index-=cur_len_numbers*length;
		length++;
	}
	return -1;
}
int main()
{
	const int index=1000;
	cout<<"index: "<<index<<"  --> "<<getNumber(index)<<endl;
	return 0;
}
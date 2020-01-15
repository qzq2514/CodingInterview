#include<iostream>
using namespace std;

int g_status=false;   //记录最终返回结果是否可信
int str2int(const char* str)
{
	int result = 0;
	if(str==NULL || *str=='\0')   //字符串为NULl或空字符串("")直接返回0,此时g_status=false
		return result; 

	//记录第一个是不是负号:但是不能写成如下两行的形式,因为正号可能不输入
	// bool isNeg=*str=='-'?true:false;   
	// str++;
	bool isPositive=true;
	if(*str=='+')
		str++;
	else if(*str=='-')
	{
		str++;
		isPositive=false;
	}

	if (*str=='\0')              //防止输入只有一个负号或者正号
		return result;
	
	//开始正式转换
	long long long_result=0;
	int flag = isPositive?1:-1;
	while(*str!='\0')
	{
		//包含不合法字符
		if(*str<'0' || *str>'9')
			return 0;
	
		long_result = long_result*10+flag*(*str-'0');

		//注意溢出
		if((!isPositive && long_result<(signed int)0x80000000) || 
			(isPositive && long_result>0x7FFFFFFF))
			return 0;
		//没有溢出开始转换下一个字符
		str++;
	}
	g_status=true;
	return long_result;
}
int main()
{
	cout<<str2int("+89989")<<" status:"<<g_status<<endl;
	return 0;
}
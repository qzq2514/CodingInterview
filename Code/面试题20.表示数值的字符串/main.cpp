#include<iostream>
using namespace std;


//对字符串*str表示的无符号整数进行扫描,
//相当于判断字符串*str前缀是不是至少有一个数字
//**str表示当前字符值,*str存放当前指向的字符的内存位置
bool scanUnsignedInt(const char **str)
{
	const char *org_point=*str;   //记录一开始指向的字符位置
	while(**str!='\0' && **str>='0' && **str<='9')
		(*str)++;   //记录的内存位置不断向后移
	return *str>org_point; //至少要有一个数字才行
}

//对字符串*str表示的可能带符号符号整数进行扫描
//相当于判断字符串*str前缀是不是整数(带不带符号都行)
bool scanInt(const char **str)
{
	if(**str=='+' || **str=='-')
		(*str)++;
	return scanUnsignedInt(str);
}

bool checkNumeric(const char *str)
{
	if(str==NULL)
		return false;
	//&str表示指针str的地址,这里是地址传参,后面修改形参*str会影响实参
	//这里判断字符串*str前缀是不是整数的同时,将指针str指向数字前缀的下一个字符
	bool numeric=scanInt(&str);

	if(*str=='.')  //判断小数
	{
		str++;
		//带有小数的情况:  .123 或者 123. 或者123.456
		//因为scanUnsignedInt只有在*str至少有一个数字做前缀才返回True,
		//所以为了对123.进行支持,要用||,即小数点前后只要至少有一个有数字就行,
		//其中小数点前的数字甚至可以带符号(+或-)
		numeric=scanUnsignedInt(&str) || numeric;
	}
	if(*str=='e' || *str=='E')  //判断指数
	{
		str++;
		//在保证之前符合条件的情况下(即numeric),若出现指数符号('e'或'E'),
		//那么指数符号后面必须是至少有一个整数(带不带符号都行),所以使用"&&"
		numeric = scanInt(&str) && numeric;
	}

	//遍历完可能有的一个小数点和一个指数符号后,此时必须整个字符串遍历结束,后面不能再有小数点或者指数符号之类
	return (*str)=='\0' && numeric;
}
int main()
{
	char str[] = "-34.0e+2";
	cout<<str<<" : ";
	if (checkNumeric(str))
		cout<<"True"<<endl;
	else
		cout<<"False"<<endl;
	return 0;
}
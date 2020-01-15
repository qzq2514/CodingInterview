#include<iostream>
using namespace std;
class Test
{
private:
	 int n1;
	 int n2;
	
public:
	//注意该程序就无法build,因为类的成员变量的初始化顺序是按照声明的顺序的,
	//因为n1比n2先声明,所以该无参构造函数会先通过n2+1初始化n1,而此时n2还未初始化,
	//即n2是一个为初始化的随机值,所以这就会导致程序build失败。
	//但是如果把n1、n2的声明顺序交换,则可以初始化成功,此时n2=1,n1=0;
	Test():n2(0),n1(n2+1){}
	void print()
	{cout<<"n1:"<<n1<<" n2:"<<n2<<endl;}
	
};
int main()
{
	Test test;
	test.print();
	return 0;
}
#include<iostream>
using namespace std;


//方法一:构造函数方法
//调用n次同一个类的构造函数,对其静态变量调用n次,每次n++,再求出和即可
class calSum{

public:
	calSum(){n++;sum+=n;};
	static void reset(){n=0;sum=0;};
	static unsigned int getSum(){return sum;}
private:
	//这里只是声明类的静态变量,后面必须在类外初始化才能调用
	static unsigned int n;
	static unsigned int sum;
};

// 需要在类的外部单独定义静态变量，以便为它分配空间,要用作用域分辨符告诉编译器静态变量隶属于哪个类
// 即类的静态变量必须在类外初始化
unsigned int calSum::n=0;
unsigned int calSum::sum=0;

int myGetSum_s1(int n)
{
	calSum::reset();
	calSum * temp = new calSum[n];
	delete[] temp;
	temp = NULL;
	return calSum::getSum();
}


//方法二:虚函数
//(C++中的虚函数的作用主要是实现了多态的机制。简而言之就是用父类型别的指针指向其子类的实例，然后通过父类的指针调用实际子类的成员函数)
//声明两个类的实例,其中一个类是另一个类的子类,在n!=0的时候调用子类的函数继续递归,n=0的时候调用父类函数结束递归
class V1;
V1* Array[2];

class V1{
public:
	virtual unsigned int Sum(unsigned int n)
	{
		//n=0的时候调用父类函数结束递归
		return 0;
	}
};
class V2:public V1{
public:
	virtual unsigned int Sum(unsigned int n)
	{
		//在n不等于0的时候调用子类的函数继续递归
		//n不等于0的时候,!!n即将n转为bool型的true,然后作为下标的时候会自动将true变成1,就调用了子类的同名函数
		//n=0的时候同理
		return Array[!!n]->Sum(n-1)+n;
	}
};

int myGetSum_s2(int n)
{
	//分别声明子类和父类的实例
	V1 v1;
	V2 v2;
	Array[0] = &v1;
	Array[1] = &v2;//体现多态:父类指针指向子类实例
	//初始调用子类的同名函数,开始在子类的同名函数不断递归,在父类的同名函数中结束递归
	return Array[1]->Sum(n);
}


//方法三:函数指针
//和方法二思路一致,使用两个函数,一个用于中间过程的不断递归,一个用于处理递归结束情况
//定义一个函数指针fun:可以指向任何参数和返回值类型均为unsigned int的函数
typedef unsigned int (*fun)(unsigned int);
unsigned int Sum_end(unsigned int n)
{
	return 0;
}
unsigned int myGetSum_s3(unsigned int n)
{
	//局部静态变量,在第一次调用myGetSum_s3时候分配内存,之后不断递归myGetSum_s3的时候不会重复分配内存
	static fun func[2]={Sum_end,myGetSum_s3};
	return n+func[!!n](n-1);
}



//方法四:使用模板
//当编译器看见myGetSum_s4<n>即为求1~n的和,就会生成对应的代码,但是求myGetSum_s4<n>
//需要myGetSum_s4<n-1>的代码,于是不断生成myGetSum_s4<n - 1>、myGetSum_s4<n - 2>...
//直到最后myGetSum_s4<1>和myGetSum_s4<1>的代码有了,结束生成
//结构体模板定义:
//template <一般变量类型 变量名 = 初始化值...> strcut 结构体名称
template <unsigned int n=0> struct myGetSum_s4
{
	//不断递归地使用模板定义带enum的结构体
    enum Value { N = myGetSum_s4<n - 1>::N + n};
};

//下面两个就是简单的模板参数为空的结构体
template <> struct myGetSum_s4<1>
{
    enum Value { N = 1};
};
template <> struct myGetSum_s4<0>
{
    enum Value { N = 1};
};

//复习:定义一个结构体,其成员变量包含一个枚举类型
struct myStruct{
   enum Value { N = 99999};
   const static int g=88;
};
enum v{red,blue};

int main()
{

	//n要非负整数,不然在s1中产生n个类实例会报错,
	//在s2和s3中负数n-1一直小于0,导致之后的!!n恒等于1,不会进入结束递归的函数,陷入死循环
	//s4中t同样n-1一直小于0,会不断生成模板
	const unsigned int n=9;            
	cout<<"s1: "<<myGetSum_s1(n)<<endl;
	cout<<"s2: "<<myGetSum_s2(n)<<endl;
	cout<<"s3: "<<myGetSum_s3(n)<<endl;
	cout<<"s4: "<<myGetSum_s4<n>::N<<endl; 
	cout<<"------------"<<endl;

	//访问struct中的枚举的元素直接"结构体名::枚举元素名"即可(因为默认枚举内的元素是结构体的静态常量,和myStruct中的g一样),
	//就像下面,而不能写成myStruct::Value::N,就像简单的访问枚举的元素,直接访问元素名就行
	cout<<myStruct::N<<" "<<myStruct::g<<endl;
	cout<<red<<" "<<blue<<endl;
	return 0;
}





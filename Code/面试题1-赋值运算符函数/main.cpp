#include<iostream>
using namespace std;
class myString{
public: 
	myString(char* pData=NULL);
	myString(const myString & str);   //复制构造函数,使用const引用作为形参,且必须返回类,才能连续赋值
	~myString(void);

	myString & operator=(const myString & str);
	void print();

private:
	char* m_pData;

};

// myString::myString(char* pData)
// {
// 	if(pData==NULL)     //使用空指针初始化实例
// 	{
// 		m_pData=new char[1];
// 		m_pData[0]='\0';
// 	}
// 	else
// 	{
// 		int length=strlen(pData);
// 		m_pData=new char[length+1];
// 		strcpy(m_pData,pData);
// 	}
// }

myString::myString(char *pData)
{
    if(pData == NULL)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        int length = strlen(pData);
        m_pData = new char[length + 1];
        strcpy(m_pData, pData);
    }
}

//实现复制构造函数
myString::myString(const myString & str)
{
	int length=strlen(str.m_pData);
	m_pData=new char[length+1];
	strcpy(m_pData,str.m_pData);
}
myString::~myString()
{
	delete[] m_pData;
}

//复习:引用只是相当于另一个变量或者实例的别名,不能把其当做是地址
//所以初始化时,myString& 表明是myString类型的一个别名
//可以通过名称前加上&获得别名的地址,以赋值给同类型的指针
//被赋值时,可以是直接一个另一变量名,或者 另一个变量地址前加一个*,如:*this

myString& myString::operator=(const myString& str)
{ 					  //自定义赋值运算函数,要考虑到:
	if(this == &str)     //1.判断赋值和被赋值的对象是同一个,因为不判断的话,如果是同一个,后面delete会把原来的实例也删除
		return *this;
	delete [] m_pData;//释放删除原来的值,不然下面重新new的话,原来的内存一直占用,且无法访问了
	m_pData=new char[strlen(str.m_pData)+1];
	strcpy(m_pData,str.m_pData);

	return *this;
}


//上一个赋值运算函数,有个小问题就是,如果在new char的时候因为内存不足导致抛出异常,
//那么就会因为之前已经执行了delete [] m_pData操作而导致m_pData是一个空指针,会导致程序崩溃
//解决办法就是在判断赋值和被赋值不是同一个实例后,新建一个临时实例,并交换临时实例和原被赋值实例的值,
//这样即便因为在交换前因为new分配内存出现了问题,那么也不会影响到原来要被赋值的实例
// myString& myString::operator=(const myString& str)
// {
// 	if(this != &str)
// 	{
// 		myString strTemp(str);

// 		char* pTemp=strTemp.m_pData;
// 		strTemp.m_pData=m_pData;
// 		m_pData=pTemp;
// 	}
// 	return *this;
// }
void myString::print()
{
	printf("%s",m_pData);
}
//========================测试

void Test1()
{
    printf("Test1 begins:\n");

    char* text = "Hello world-Test1";

    myString str1(text);
    myString str2;
    str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.print();
    printf(".\n");
}

// 赋值给自己
void Test2()
{
    printf("Test2 begins:\n");

    char* text = "Hello world-Test2";

    myString str1(text);
    str1 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str1.print();
    printf(".\n");
}
// 连续赋值
void Test3()
{
    printf("Test3 begins:\n");

    char* text = "Hello world-Test3";

    myString str1(text);
    myString str2, str3;
    str3 = str2 = str1;

    printf("The expected result is: %s.\n", text);
    printf("The actual result is: ");
    str2.print();
    printf(".\n");
    printf("The expected result is: %s.\n", text);
    printf("The actual result is: ");
    str3.print();
    printf(".\n");
}
int main()
{
	Test1();
    Test2();

	return 0;
}
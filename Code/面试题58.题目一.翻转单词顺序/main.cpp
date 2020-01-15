#include<iostream>
using namespace std;

void Reverse(char* pBegin,char* pEnd)
{
	if(pBegin==NULL || pEnd==NULL)
		return ;

	while(pBegin<pEnd)
	{
		char temp = *pBegin;
		*pBegin = *pEnd;
		*pEnd = temp;

		pBegin++;
		pEnd--;
	}
}
void reverse_sentence(char*str)
{
	char* pBegin = str;
	char* pEnd = str;
	while(*pEnd!='\0')
		pEnd++;
	--pEnd;

	//先翻转整个整个句子中所有字符
	Reverse(pBegin,pEnd);
	//令pBegin、pEnd此时分别动态代表句子中每个单词的第一个和最后一个字符位置
	pBegin=pEnd=str;
	while(*pBegin!='\0')
	{
		//pBegin、pEnd不断相加,找到第一个不等于空格字符
		if(*pBegin==' ')
		{
			pBegin++;
			pEnd++;
		}
		//pEnd找到了当前字符和下一个字符中间的空格
		else if(*pEnd==' ' || *pEnd=='\0')
		{
			//Reverse后只会修改指针指向位置的内容,不会修改指针的指向
			//所以Reverse之后,pBegin和pEnd依然分别指向当前单词的第一个和最后一个字符位置。
			Reverse(pBegin,--pEnd);
			//Reverse后再经过下一句之后pBegin和pEnd分别指向当前字符和下一个字符中间的第一个空格,开始寻找下一个字符
			pBegin = ++pEnd;  
		} 
		else
			pEnd++;
	}
}
int main()
{
	char str[]=" 123 45.  67 9 ";
	cout<<"Before reversing :"<<str<<endl;
	reverse_sentence(str);
	cout<<"After reversing  :"<<str<<endl;
	return 0;
}
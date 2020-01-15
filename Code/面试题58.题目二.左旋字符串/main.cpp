#include<iostream>
using namespace std;
void reverse(char* pBegin,char* pEnd)
{
	if(pBegin==NULL || pEnd==NULL)
		return;

	while(pBegin<pEnd)
	{
		char temp = *pBegin;
		*pBegin = *pEnd;
		*pEnd = temp;

		pBegin++;
		pEnd--;
	}
}

//左旋字符串str的前num个字符,将str分成两个部分,前num为第一部分,后面剩余的为第二组
//左旋步骤:1.翻转第一部分 2.翻转第二部分 3.翻转整个字符串
//但是如果先进行第三步,再进行第1、2部分,那么久变成右旋num个字符
char* leftRoateString(char* str,int num)
{
	if(str==NULL)
		return NULL;

	int len = strlen(str);
	if(len<=0 || num<0 || num>len)
		return NULL;
	char* pFirstStart = str;
	char* pFirstEnd = str+num-1;
	char* pSecondStart = str+num;
	char* pSecondEnd = str+len-1;

	reverse(pFirstStart,pFirstEnd);
	reverse(pSecondStart,pSecondEnd);

	reverse(pFirstStart,pSecondEnd);

	

	return str;
}
int main()
{
	char str[]="asdfghj";
	cout<<str<<endl;
	// reverse(str,str+6);
	char* str2=leftRoateString(str,2);
	cout<<str2<<endl;
	return 0;
}
#include<iostream>
#include<memory.h>
using namespace std;

//找到字符串中第一个只出现一次的字符
//只需要遍历两次字符串,第一次使用一个map形式记录每个字符出现的次数
//第二次找到第一个次数为1的字符
char firstNotReapting(char* str)
{
	if(str==NULL)
		return '\0';

	const int tabel_size=256;
	int count[tabel_size];
	memset(count,0,sizeof(count));

	char* p = str;
	while(*p != '\0'){
	   	count[(*p++)]++;
	}

	p = str;
	while(*p != '\0'){
	   	if(count[*p]==1)
	   		return *p;
	   	p++;
	}
	return '\0';
}

//拓展题:删除字符串中的重复字符
char* deleteReaptingChars(char* str)
{
	if(str==NULL)
		return NULL;

	const int tabel_size=256;
	int count[tabel_size];
	memset(count,0,sizeof(count));
	int len=strlen(str);

	char * result = new char[len+1];
	char* pStr = str;
	char* pResult = result;
	while(*pStr != '\0')
	{
		count[*pStr]++;
		if(count[*pStr]==1)
			*(pResult++)=*pStr;
		pStr++;
	}

	*pResult = '\0';
	return result;
}

//其余两个扩展题目:
//1.在字符串A中删除在字符串B中出现的字符
//2.判断两个字符串是不是变位词(即两个字符串中出现的字母相同,且每个字母出现的次数相同)
//这两个题目都是用map映射的方式,比较简单,不做处理


int main()
{
	char str[]="ksuehgsishernfsurkisj";
	char tar = firstNotReapting(str);
	cout<<"first not reapting char in "<<str<<":"<<tar<<endl;
	
	char str1[]="google";
	char *noRepeat = deleteReaptingChars(str1);
	cout<<str1<<" without repeating char is :"<<noRepeat<<endl;
	return 0;
}







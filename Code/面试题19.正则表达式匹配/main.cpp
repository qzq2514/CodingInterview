#include<iostream>
using namespace std;

//开始对当前str和pattern进行匹配
bool matchCore(char *str,char *pattern)
{
    if(*str=='\0' && *pattern=='\0')
    	return true;      //匹配到最后,字符串和正则式都用完了,则匹配成功
    if(*str!='\0' && *pattern=='\0')
    	return false;     //正则式用完了但是字符串还有字符,则匹配失败

    if(*(pattern+1) == '*')    //当正则式下一个是"*"字符
    {
    	//如果当前字符串第一个字符和正则式的第一个字符能匹配的上,那么在当正则式下一个是"*"字符时候
    	//开始对正则式的'*'到底匹配几次进行递归
    	if(*str==*pattern || (*pattern=='.' && *str!='\0'))
    	{
    		bool match_one=matchCore(str+1,pattern+2);   //'*'匹配一次
    		bool match_zero=matchCore(str,pattern+2);    //'*'匹配零次
    		bool match_multipy=matchCore(str+1,pattern);   //'*'匹配多次
    		return match_one||match_zero||match_multipy;
    	}
    	//如果当前字符串第一个字符和正则式的第一个字符不能匹配的上,那么就跳过"*",就相当于匹配零次
    	else
    		return matchCore(str,pattern+2);
    }

    //当正则式下一个不是"*"字符,那么就简单了,直接逐个字符匹配就行
    //但是要注意点,就是
    if(*str==*pattern || (*pattern=='.' && *str!='\0'))
    	 return matchCore(str+1,pattern+1);           //当前字符能匹配上,就匹配下一个
    return false;                                     //匹配不上,直接返回false;
}
bool match(char *str,char *pattern)
{
	if(str==NULL || pattern==NULL)
		  return false;

	return matchCore(str,pattern);
}
int main()
{
	char str[]="abbccccd";   //abbccccd
	char pattern[]="ab*.c*ccccd";  //ab*.c*ccccd
    cout<<str<<"  vs  "<<pattern<<endl;
    cout<<match(str,pattern)<<endl;
	return 0;
}
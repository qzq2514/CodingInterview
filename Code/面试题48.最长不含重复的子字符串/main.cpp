#include<iostream>
using namespace std;
int maxLength(string str)
{
	int *position = new int[26];
	int len = str.length();
	for(int i=0;i<26;i++)
		position[i]=-1;
	int cur_length=0;     //以上一个字符为结尾的最长不含重复字符的子字符串长度
	int max_length=0;

	int start=0,end=-1;   //最长不含重复字符的子字符串的起始坐标(便于理解)
	for (int i=0;i<len;i++)
	{
		int pre_position = position[str[i]-'a'];
		int dist = i-pre_position;   //当前字符距离上一次出现位置的距离
		if(pre_position<0 || dist>cur_length)
		{
			//如果当前字符之前都没出现过或者两次出现的距离大于cur_length
			//那么以当前字符*str结尾的最长不重复子字符串就是以*(str-1)结尾的最长不含
			//重复字符的子字符串再加上*str本身就行
			cur_length+=1;    
		}
		else    
		{
			//否则的话那么久从上一次出现该字符*str的下一个位置到当前位置截取的子字符串
			//作为以*str结尾的最长不重复子字符串
			cur_length=dist;
			
		}
			      

		position[str[i]-'a'] = i;
		if(cur_length>=max_length)
		{
			max_length=cur_length;
			//其实可以不用start,因为根据max_length和end就可以推断出start,这里写出来纯粹为了便于理解
			start = i-cur_length+1;  
			end = i;
		}
	}
	cout<<start<<"~"<<end<<endl;
	return max_length;
}
int main()
{
	string str ="arabcacfrcac";
	cout<<str<<" "<<maxLength(str)<<endl;
	return 0;
}
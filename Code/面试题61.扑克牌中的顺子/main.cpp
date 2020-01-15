#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//判断5个正整数是不是连续,其中出现的0可以当做任意正整数
int checkContinuous(int *arr,int len,vector<int> &chageInfo)
{
	if(arr==NULL || len<=1)
		return -1; //假定只有一个数,也判定为不是顺子,因为没有意义   

	sort(arr,arr+len);
	int numberOfZero = 0;

	for (int i=0;i<len && arr[i]==0;i++)
		numberOfZero++;

	bool isContinuous = true;
	for (int i=numberOfZero;i<len-1;i++)
	{
		//出现对子,是不可能是顺子的
		if(arr[i] == arr[i+1])
			return -1;
		//把相邻两个数的中间数添加到chageInfo(2、3是顺的,间隔长度定义为0,需要填充的数也为空)
		for(int k=arr[i]+1;k<arr[i+1];k++)
			chageInfo.push_back(k);
	}

	//0的个数大于间隔的次数,那么通过0变成间隔的数达到顺子的结果,否则没办法顺子
	// cout<<numberOfZero<<" "<<numberOfGap<<endl;
	int numberOfGap = chageInfo.size();
	if (numberOfZero<numberOfGap)
		return -1;
	if (numberOfZero==numberOfGap)
		return 1;    //0的个数正好等于间隔个数,那么0全部用来变成间隔的数字
	//0的个数大于间隔个数,那么0在填充完间隔的数字后,剩下的数可以用来接在当前顺子头部或者尾部
	//这里返回的信息可以代表到底剩余多少个0
	return 1+numberOfZero-numberOfGap; 

}
int main()
{
	const int len = 5;
	int arr[len] = {0,0,1,2,4};
	vector<int> chageInfo;
	int code = checkContinuous(arr,len,chageInfo);
	cout<<"Array:";
	for (int i=0;i<len;i++)
		cout<<arr[i]<<" ";
	if (code<0) 
		cout<<"---->not Continuous"<<endl;
	else 
	{
		cout<<"---->Continuous \nNumbers must to be filled are: ";
		if (chageInfo.empty())
    		cout<<"None"<<endl;
    	else
    	{
    		for(int i=0;i<chageInfo.size();i++)
			cout<<chageInfo[i]<<" ";
			cout<<endl;
    	}

		cout<<"Numbers can to be filled are: ";
		if(code==1)
			cout<<"None"<<endl;
    	else //有剩余的0,默认填充在尾部,(这里不考虑超过13的情况了,读者可自行再进行简单分析)
    	{
    		for(int i=1;i<=code-1;i++)
	    		cout<<arr[len-1]+i<<" ";
	    	cout<<endl;	
    	}

    	
    }
	return 0;
}
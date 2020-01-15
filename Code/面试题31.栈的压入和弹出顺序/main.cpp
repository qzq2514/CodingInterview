#include<iostream>
#include<stack>
using namespace std;

bool isPopOrderCorrect(int* pushArrary,int* popArrary,int len)
{
	if(pushArrary==NULL || popArrary==NULL || len<=0)
		return 0;

    int* nextPop=popArrary;
    int* nextPush=pushArrary;
    stack<int> dataStack;

    while(nextPop-popArrary<len)   //还没弹完，继续弹
    {
    	//如果栈为空,或者栈顶不是当前要弹出的数据,
    	//则一直按照入栈的顺序不断将数据压入栈中,直到保证当前要弹出的数据在栈顶
    	while(dataStack.empty() || dataStack.top()!=(*nextPop))
    	{
    		if(nextPush-pushArrary>=len)    //入栈数据都已经入完了,还没找到要弹出的数据,那么返回false
    			return false;
			dataStack.push(*nextPush);
			nextPush++;
    	}
    	dataStack.pop();  //在入栈顺序中找到了要弹出的顺序,则弹出当前数字,开始弹下一个数字
    	nextPop++;
    }

    //到这里,弹出数组已经遍历完,如果栈空,那么所有数都用完,返回true,否则返回false
    return dataStack.empty();
}
int main()
{
	//仅限数组中每个元素不同,且弹出和压入数组长度一样(其实不一样肯定false)
	const int len=5;
	int pushArrary[len]={1,2,3,4,5};
	int popArrary[len]={3,4,2,1,5};
	cout<<"push:";
	for(int i=0;i<len;i++)
	   cout<<pushArrary[i]<<" ";
	cout<<endl<<"pop :";
	for(int i=0;i<len;i++)
	   cout<<popArrary[i]<<" ";
    cout<<endl<<isPopOrderCorrect(pushArrary,popArrary,len)<<endl;
	return 0;
}






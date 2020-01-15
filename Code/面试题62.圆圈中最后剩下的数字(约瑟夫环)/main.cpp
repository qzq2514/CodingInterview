#include<iostream>
#include<vector>
#include<list>
using namespace std;

//bool数组模拟法
int Joseph_s1(int n,int k)
{
	bool *isLeft = new bool[n];
	for(int i=0;i<n;i++)
		isLeft[i]=true;

	int curId = -1;
	int leftNum = n;
	int count=0;
	while(leftNum>1)
	{
		curId = (curId+1)%n;
		if(isLeft[curId])
		{
			count++;
			if(count==3)
			{
				count=0;
				isLeft[curId]=false;
				leftNum--;
			}
		}
	}

	int lastId = -1;
	for(int i=0;i<n;i++)
	{
		if(isLeft[i])
			lastId=i;
	}
	return lastId;
}

//list链表模拟法
int Joseph_s2(int n,int k)
{
	if(n<1 || k<1)
		return -1;
	//最好用list类型,vector容易产生越界问题
	list<int> vec;
	for(int i=0;i<n;i++)
		vec.push_back(i);
		
	list<int>::iterator current=vec.begin();
	while(vec.size()>1)
	{
		//vec都是要剩下的号码,走k-1步找到下一个退出的号码
		//(因为初始current已经等于第一个数了,所以只需要走k-1步就行)
		for(int i=1;i<k;i++)
		{
			current++;
			if(current==vec.end())
				current = vec.begin();  
		}
		//current即为当前要退出的号码,准备从vec中删除
		//先找到下一个号码,然后删除当前号码,最后把下一个号码赋值给当前号码,开始下一次遍历
		list<int>::iterator next = ++current;  //必须使用current++或者++current指向下一个,不能current+1
		if(next == vec.end())
			next = vec.begin(); 

		--current;
		//使用vector时,这里erase会有问题,暂未解决,所以使用list即可
		vec.erase(current);
		current = next;
	}
	return *current;
}

//动态规划思维,详解见https://blog.csdn.net/qzq2514/article/details/100680847
int Joseph_dp(int n,int k)
{
	int res=0;
    for (int i=2;i<=n;i++)
        res=(res+k)%i;
    return res;
}
int main()
{
	int n=10;
	int k=3;
	int result_s1=Joseph_s1(n,k);
	int result_s2=Joseph_s2(n,k);
	int result_s3=Joseph_dp(n,k);
	cout<<"result_s1:"<<result_s1<<endl;
	cout<<"result_s2:"<<result_s2<<endl;
	cout<<"result_s3:"<<result_s3<<endl;

	return 0;
}




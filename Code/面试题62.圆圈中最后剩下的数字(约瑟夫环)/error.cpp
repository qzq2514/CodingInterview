#include<iostream>
#include<vector>
#include<list>
using namespace std;
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

int Joseph_s2(int n,int k)
{
	if(n<1 || k<1)
		return -1;
	//最好用list类型,vector容易产生越界问题
	vector<int> vec;
	for(int i=0;i<n;i++)
	{
		vec.push_back(i);
	}
		

	vector<int>::iterator current=vec.begin();
	while(vec.size()>1)
	{
		cout<<"======="<<endl;
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
		cout<<(current==vec.end())<<" "<<((++current)==vec.end())<<endl;
		vector<int>::iterator next = ++current;  //必须使用current++或者++current指向下一个,不能current+1
		cout<<(current==vec.end())<<" "<<(next==vec.end())<<endl;
		if(next == vec.end())
			next = vec.begin(); 

		--current;
		cout<<"------"<<endl;
		for(int i=0;i<vec.size();i++)
			cout<<vec[i]<<" ";
		cout<<endl;
		cout<<*current<<" "<<*next<<" "<<(current==vec.end())<<" "<<(next==vec.end())<<endl;
		vec.erase(current);
		cout<<"++++++++"<<endl;
		current = next;
	}
	return *current;
}
int main()
{
	int n=10;
	int k=3;
	int result_s1=Joseph_s1(n,k);
	int result_s2=Joseph_s2(n,k);
	cout<<"result_s1:"<<result_s1<<endl;
	// cout<<"result_s2:"<<result_s2<<endl;




	vector<int> vec;
	for(int i=0;i<n;i++)
		vec.push_back(i);
	vector<int>::iterator current=vec.end();
	current--;
	current++;
	cout<<"end:"<<(current==vec.end())<<endl;
	cout<<*current<<endl;
	vec.erase(--current);
	for(int i=0;i<n;i++)
		cout<<vec[i]<<endl;
	return 0;
}




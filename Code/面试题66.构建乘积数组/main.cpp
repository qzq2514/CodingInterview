#include<iostream>
#include<vector>
using namespace std;
void build(vector<long long> numbers,vector<long long> &result)
{
	long long temp=1; 
	result.push_back(temp);
	for(long long i=1;i<numbers.size();i++)
	{
		temp *= numbers[i-1];
		result.push_back(temp);   //先令result[i]=numbers[0]*numbers[1]*...*numbers[i-1]
	}
	temp=1;
	for(long long i=numbers.size()-2;i>=0;i--)
	{
		temp *= numbers[i+1];   //令当前的temp等于numbers[i+1]*numbers[i+2]*...*numbers[n-1]
		result[i]*=temp;   //此时将temp与result[i]相乘即为所求结果
	}
}
int main()
{
	const int len=10;
	long long arr[len] = {2,4,3,2,5,6,7,2,5,3};
	vector<long long> vec(arr,arr+len);
	vector<long long> result;
	build(vec,result);
	for(int i=0;i<result.size();i++)
		cout<<result[i]<<" ";
	cout<<endl;
	return 0;
}
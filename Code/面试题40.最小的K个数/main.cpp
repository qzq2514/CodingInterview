#include<iostream>
#include<set>
using namespace std;


//快排的核心,返回的是相对于原始数组arr的标兵位置,且在标兵左侧全部小于等于标兵,标兵右侧的数全部大于等于标兵
int partition(int arr[],int len,int start,int end)
{
	if(arr == NULL || len<=0 || start<0 || end>=len)
		return -1;

	int mid_indx = start+(end-start)/2;
	swap(arr[end],arr[mid_indx]);

	int small = start-1;
	for(int i=start;i<end;i++)
	{
		if(arr[i]<arr[end])
		{
			small++;
			if(arr[i]!=arr[small])
				swap(arr[i],arr[small]);
		}
	}
	swap(arr[++small],arr[end]);
	return small;
}

//方法一:使用快速排序的思想,找到下标为K-1的标兵,根据快排的思想,标兵左侧的数全部小于等于标兵,
//标兵右侧的数全部大于等于标兵,那么就很容易得到前K个数就是整个数组arr最小的K个数
void leastKnumbers_s1(int arr[],int len,int result[],int K)
{
	if(arr==NULL || result==NULL || K<=0 || len<K)
		return;

	int start = 0,end = len-1;
	int index = partition(arr,len,start,end);
	
	//不断排序数组和数组的部分,直到找到下标为K-1的标兵
	while(index!=K-1)
	{
		if(index>K-1)
		{
			end = index-1;
			index = partition(arr,len,start,end);
		}
		else
		{
			start = index+1;
			index = partition(arr,len,start,end);
		}
	}

	for(int i=0;i<K;i++)
		result[i]=arr[i];
}


//方法二:利用排序数组的性质,result是一个set集合,里面的元素自动排序
//本方法基本思想即为,result维护一个长度为K的集合,遍历原数组arr
//如果当前元素小于result中最大值,那么就把最大值删除,插入当前的值
//该方法相比较于第一种方法,其不会改变原数组
void leastKnumbers_s2(int arr[],int len,multiset<int,greater<int> > &result,int K)
{
    if(arr==NULL || K<=0 || len<K)
		return;

	for(int i=0;i<K;i++)
		result.insert(arr[i]);

	for(int i=K;i<len;i++)
	{
		if(arr[i] < (*result.begin()))
		{
			result.erase(result.begin());
			result.insert(arr[i]);
		}
	}
}

//和方法二是同样的方法,只不过这里使用简单的数组,顺带复习了下插入排序
void leastKnumbers_s3(int arr[],int len,int result[],int K)
{
    if(arr==NULL ||result==NULL|| K<=0 || len<K)
		return;

	for(int i=0;i<K;i++)
		result[i] = arr[i];
	sort(result,result+K);  //将arr前K个数放在结果中,并从小到大排序

	for(int i=K;i<len;i++)
	{
		int temp = K-1;
		while(temp>=0 && arr[i] < result[temp])
		{
			// cout<<temp<<" "<<result[temp-1]<<endl;
			result[temp] = result[temp-1];   //按理说,如果这里arr[i]小于result中最小的数(即result[0])
			temp--;                          //那么这里就会出现即result[-1]的情况,但是并不会报错,而是按照连续内存的空间
		}                                    //访问到result地址前一块的内存,但是后面还有result[temp+1] = arr[i]这句话
		result[temp+1] = arr[i];             //会把result[0]重新赋值正确,而对于其他情况不会出现问题
	}
}

int main()
{
	const int len = 10,K=3;
	int arr1[len]={3,9,2,1,5,0,4,2,2,7};
	int* result1 = new int[K];

	cout<<"leastKnumbers_s1:";
	leastKnumbers_s1(arr1,len,result1,K);
	for(int i=0;i<K;i++)
		cout<<result1[i]<<" ";
	cout<<endl;

	int arr2[len]={3,9,2,1,5,0,4,2,2,7};
	cout<<"leastKnumbers_s2:";
	multiset<int,greater<int> > result2;
	leastKnumbers_s2(arr2,len,result2,K);
	multiset<int,greater<int> >::iterator iter=result2.begin();
	for(;iter!=result2.end();iter++)
		cout<<*iter<<" ";
	cout<<endl;

	cout<<"leastKnumbers_s3:";
	int arr3[len]={3,9,2,1,5,0,4,2,2,7};
	int* result3 = new int[K];
	leastKnumbers_s3(arr3,len,result3,K);
	for(int i=0;i<K;i++)
		cout<<result3[i]<<" ";
	cout<<endl;

	return 0;
}
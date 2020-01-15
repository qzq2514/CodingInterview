#include<iostream>
using namespace std;

//如果没有重复元素,那么0~len-1这len个数字可以重排,保证在该重排下,数字num就在数组下标为num的位置
bool check_duplicate(int arr[],int len,int *duplicate_num)
{
   if(arr==NULL || len<=0)
   	return false;
   for(int i=0;i<len;i++)
   	if(arr[i]<0 || arr[i]>=len)
   		return false;

   for(int i=0;i<len;i++)
   {
   	  while(arr[i] != i)  //如果当前位置i上的数字arr[i]不是重排后应该的数字i,则不断交换
   	  {
   	  	//如果当前位置i上的元素arr[i]和重排后其本身应该在的位置arr[i]上的元素arr[arr[i]]相等,
   	  	//则找到第一个重复元素
   	  	if(arr[i] == arr[arr[i]])  
   	  	{
   	  		*duplicate_num=arr[i];
   	  		return true;
   	  	}
   	  	int temp=arr[i];
   	  	arr[i]=arr[temp];
   	  	arr[temp]=temp;
   	  	for(int j=0;j<len;j++)        //打印中间交换过程
			cout<<arr[j]<<" ";
		cout<<endl<<"i:"<<i<<endl;
   	  }
   }
   return false;
}


int main()
{
   //数组长度为n,数组中的元素为0~n-1范围
	int numbers[10]={0,2,3,4,5,5,7,8,6,9};
	int duplicate_num=-1;
	bool have_duplicate=check_duplicate(numbers,10,&duplicate_num);
	cout<<"have_duplicate:"<<have_duplicate<<"     duplicate_num:"<<duplicate_num<<endl;
	return 0;
}
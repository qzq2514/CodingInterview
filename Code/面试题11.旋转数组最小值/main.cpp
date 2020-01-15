#include<iostream>
using namespace std;

//特殊情况下可能会用到的直接从头到尾查找最小值
int min_order(int arr[],int start,int end)
{
	int min_value=arr[start];
	for (int i=start+1;i<=end;i++)
	{
		if (arr[i]<min_value)
		{
			min_value=arr[i];
		}
	}
	return min_value;
}

int Min(int arr[],int len)
{
	if(arr==NULL || len<=0)
		return -1;             //假设数组都是非负数
	int left=0;
	int right=len-1;
	int mid=left;
    
    //升序的旋转数组,左大右小,即左侧为原数组大值部分,右侧为原数组的小值部分
	if(arr[left]<=arr[right])   //如果旋转数组真的"旋转"了,才使用二分查找最小值,不然数组就是未旋转的,第一个数字就是最小的
	  return arr[0]; 
	while(right>left+1)        //保证left在大值部分,right在小值部分,最终退出时,两者又相差一个位置,那么说明left在大值最后一个,right在小值第一个,即最终要求的最小值
	{
		mid=(left+right)/2; 

		//特殊情况:{1,0,1,1,1,1,1,1,1,1}
		if(arr[mid]==arr[left] && arr[mid]==arr[right])
			return min_order(arr,left,right);

		if(arr[mid]>=arr[left])            //说明mid在大值部分
			left=mid;
		else if (arr[mid]<=arr[right])     //说明mid在小值部分
			right=mid;
	}
	return arr[right];

}

int main()
{
	// int arr[10]={5,6,7,8,9,10,1,2,3,4};    //标准的旋转数组
	// int arr[10]={1,2,3,4,5,6,7,8,9,10};    //旋转长度为0的"伪"旋转数组
    int arr[10]={1,0,1,1,1,1,1,1,1,1};        //旋转数组的特殊情况
	cout<<Min(arr,9)<<endl;
	return 0;
}
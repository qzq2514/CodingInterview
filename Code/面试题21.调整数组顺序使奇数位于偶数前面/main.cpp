#include<iostream>
using namespace std;


void print_arr(int *arr,int len)
{
	for(int i=0;i<len;i++)
	  cout<<arr[i]<<" ";
	 cout<<endl;
}
//最简单的方法:遍历数组,遇到偶数,后面的数就不断前移一位,当前偶数放到数组最后
//当然还可以继续优化,
//比如:
//1.可以记录被转到后面的数的个数num(即偶数的个数),则不用遍历到整个数组结束,
//只要遍历倒数第num个数就行(reOrder_s1就用的这个方法)
//2.每次不要只判断当前一个数,而是找到包括当前往后的连续偶数,全部放到最后
//避免出现连续的偶数,但是只能判断一个,往前移动一个
//但是即便加上这些优化,复杂度还是O(n^2)
void reOrder_s1(int *arr,int len,bool(*func)(int))
{
    int num=0;
   for(int i=0;i<len-num;i++)
   {
   	 //当前数是偶数,则开始把后面的数不断前移一位
   	 //并把放到最后
   	 int cur_num=*(arr+i);
   	 cout<<"cur_num:"<<cur_num<<endl;
   	 if(func(cur_num))
   	 {
   	 	num++;
   	 	for(int j=i;j<len-1;j++)
   	 		*(arr+j)=*(arr+j+1);
   	 	*(arr+len-1)=cur_num;
   	 }
   	 print_arr(arr,len);
   	 cout<<"----------"<<endl;
   }
}

//O(n)的方法:双指针分别从前和从后开始,第一指针和第二个指针分别指向偶数和奇数则交换

//bool(*func)(int):带有函数参数的传参形式:
//函数返回值类型 (*函数名)(函数各参数类型)
void reOrder_s2(int *arr,int len,bool(*func)(int))
{
	if(arr==NULL || len==0)
		return;

	//双指针,分别指向前半部分和后半部分
    int *p_start=arr;
    int *p_end=arr+len-1;
    while(p_start<p_end)
    {
         while(p_start<p_end && !func(*p_start))  //找到下一个偶数
         	p_start++;

         while(p_start<p_end && func(*p_end))  //找到下一个偶奇数
         	p_end--;

         if(p_start<p_end)
         {
         	int temp=*p_start;
         	*p_start=*p_end;
         	*p_end=temp;
         }
    }
}
//写成这样均具有通用性,且各模块间解耦性比较好
bool divPrinciple(int num)
{
	return (num & 1)==0; //如果是题目要求:奇数在前,偶数在后,那么这里奇数返回0,偶数返回1

    // return num >= 0; //扩展:负数在前,非负数在后
    //其他类似的,能被3整除在前,不能被3整除在后等等.都可以只改动divPrinciple,而不用修改reOrder函数
}

int main()
{
	// int arr[]={-1,-2,3,4,6,7,0};
	int arr[]={1,2,3,4,5,6,7};
	print_arr(arr,7);
    reOrder_s1(arr,7,divPrinciple);
    print_arr(arr,7);
	return 0;
}
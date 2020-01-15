#include<iostream>
#include<stdio.h>
#include <string>
#include<algorithm>
using namespace std;

//预备知识:
//strcmp:若str1=str2，则返回零；若str1<str2，则返回负数；若str1>str2
//两个字符串自左向右逐个字符相比（按ASCII值大小相比较），直到出现不同的字符或遇'\0'为止,
//若比到最后短的字符都用完了,那么就"短字符串"<"长字符串",如:
//1."A"<"B" 2."A"<"AB" 3."Apple"<"Banana" 4."A"<"a" 5."compare"<"computer"


//该方法的可行性证明见原书P248和P249
int max_number_len = 10;


char* strNumCombine1 = new char[max_number_len*2+3];
char* strNumCombine2 = new char[max_number_len*2+3];

//使用qsort方式的排序:
//1.compare函数一定要写成这种形式,返回int且两个参数都是const void*形式
//2.返回负整数则不交换strNumber1和strNumber2在原数组的顺序,返回正整数则交换顺序
int compare(const void* strNumber1,const void* strNumber2)
{
	strcpy(strNumCombine1,*(char**)strNumber1);
	strcat(strNumCombine1,*(char**)strNumber2);

	strcpy(strNumCombine2,*(char**)strNumber2);
	strcat(strNumCombine2,*(char**)strNumber1);

	//组合起来后strNumCombine1<strNumCombine2,则保证在数组中strNumber1在strNumber2前面
	return strcmp(strNumCombine1,strNumCombine2);
}

//使用sort方式的排序:
//1.参数类型和原数组元素类型一致
//1.返回bool型,true则不交换strNumber1和strNumber2在原数组的顺序,false则交换顺序
bool compare_sort(char* strNumber1,char* strNumber2)
{
	strcpy(strNumCombine1,strNumber1);
	strcat(strNumCombine1,strNumber2);

	strcpy(strNumCombine2,strNumber2);
	strcat(strNumCombine2,strNumber1);

	//组合起来后strNumCombine1<strNumCombine2,那就保证在数组中strNumber1在strNumber2前面
	return strcmp(strNumCombine1,strNumCombine2)<0;
}
//两个compare函数,返回正数,则两个参数位置不交换,负数则位置交换
//如一般返回"第一个参数">”第二个参数“的形式,那么则降序排序,反之升序排序


void printMinNumber(int* arr,int length)
{
	if(arr == NULL || length <=0)
		return;

	//定义一个二维数组,其每个元素是原arr中每个整数元素转换后的char数组
	char** strNumbers = new char*[length];
	for(int i=0;i<length;i++)
	{
		strNumbers[i] = new char[max_number_len+1];
		sprintf(strNumbers[i],"%d",arr[i]);      //将每个整型元素转为char数组形式, 如321->"321"
	}

	//一下两种排序方式可以使用任意一个
	// qsort(strNumbers,length,sizeof(char*),compare);
	sort(strNumbers,strNumbers+length,compare_sort);

	for(int i=0;i<length;i++)
	{
		printf("%s",strNumbers[i]);
	}
	printf("\n");

}

int main()
{
	const int length = 3;
	int arr[length] = {3,32,394};
	//以上如果是找最大的排列数字,那么只需要在比较函数中的strcmp交换strNumCombine1和strNumCombine2的位置
	printMinNumber(arr,length);
	return 0;
}
#include<iostream>
using namespace std;
int myAdd(int num1,int num2)
{
	int sum,carry;
	do{
		//两个数二进制各位不进位相加:eg.101^11=110
		sum = num1^num2;
		//计算各位的进位:eg.（101&11)<<1=(001)<<1=010
		carry = (num1&num2)<<1;
		//相加sum和carry,直到没有进位,即num2(carry)!=0
		num1 = sum;
		num2 = carry;
	}while(num2!=0);
	return num1;
}

//不申请临时变量交换数字
void mySwap(int num1,int num2)
{
	 cout<<"org:   "<<num1<<" "<<num2<<endl;
	 //1.加法方式
     num1 = num1+num2;
     num2 = num1-num2;
     num1 = num1-num2;
     cout<<"swap1: "<<num1<<" "<<num2<<endl;
     //2.异或方式
     num1 = num1^num2;
     num2 = num1^num2;
     num1 = num1^num2;
	cout<<"swap2: "<<num1<<" "<<num2<<endl;
}
int main()
{
	int num1 = 2;
	int num2 = 34;
	int sum = myAdd(num1,num2);
	cout<<num1<<" + "<<num2<<" = "<<sum<<endl;
	mySwap(num1,num2);
	return 0;
}
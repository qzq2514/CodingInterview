#include<iostream>
#include<math.h>
using namespace std;

bool isInvalidInput=true;

double Power_unsigned_exponent(double base,int exponent)
{
	if (exponent==0)
		return 1;
	if (exponent==1)
		return base;
    double result=Power_unsigned_exponent(base,exponent>>1);   //exponent为偶数时,base^exponent=(base^exponent/2)^2
    result*=result;
    if(exponent & 1)       ////exponent为奇数时,base^exponent=(base^exponent/2)(base^(exponent/2+1))
    	result*=base;
    return result;
}

double Power(double base,int exponent)
{
	if(fabs(base-0.0)<1e-10 && exponent<0)   //基数为0且指数为负数时,无解
	{
		isInvalidInput=false;
		return 0.0;
	}
    
    int absExponent = exponent<0?-exponent:exponent;      //注意考虑指数为负数时,要取倒数
    double result = Power_unsigned_exponent(base,absExponent);

	return exponent<0?1.0/result:result;

}

int main()
{
	double base=2.1;
	int exponent=-2;

	double res=Power(base,exponent);
	if (!isInvalidInput)
		cout<<"Not Invalid Input!!"<<endl;
	else 
		cout<<"Power("<<base<<","<<exponent<<")="<<res<<endl;

	// cout<<(unsigned int)(-10)<<endl;
	return 0;
}
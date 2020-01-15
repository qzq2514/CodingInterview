#include<iostream>
using namespace std;

//1 1 2 3 5 8

//递归方法:O(n指数)
long long Fibonacci_recursion(long long n)
{
	if (n<=0) return 0;
	if (n==1) return 1;
	return Fibonacci_recursion(n-1)+Fibonacci_recursion(n-2);
}
//循环方法:O(n)
long long Fibonacci_loop(long long n)
{
	if (n<=2) return 1;
	long long f1=1,f2=1;
	long long res=0;
	for(int i=3;i<=n;i++)
	{
		res=f1+f2;
		f1=f2;
		f2=res;
	}
	return res;
}
//线性代数方法:O(log(n))
//主要公式:
//   [f(n)   f(n-1)  = [1 1  ^(n-1)
//    f(n-1) f(n-2)]    1 0]
struct Matrix_Fib
{
	Matrix_Fib(long _v00,long _v01,long _v10,long _v11):
    v00(_v00),v01(_v01),v10(_v10),v11(_v11)
	{

	}
	long v00;long v01;
	long v10;long v11;
};
Matrix_Fib Matrix_Fib_multiply(const Matrix_Fib m1,const Matrix_Fib m2)
{
    return Matrix_Fib(
    	m1.v00*m2.v00+m1.v01*m2.v10,
    	m1.v00*m2.v01+m1.v01*m2.v11,
    	m1.v10*m2.v00+m1.v11*m2.v10,
    	m1.v10*m2.v01+m1.v11*m2.v11);
}

Matrix_Fib Matirx_power(unsigned int n)
{
	Matrix_Fib base_matrix(1,1,1,0);
	if (n==1)
		return base_matrix;
	if(n%2==0){
		Matrix_Fib matrix_half=Matirx_power(n/2);
		return Matrix_Fib_multiply(matrix_half,matrix_half);
	}
	else{
		Matrix_Fib matrix_half=Matirx_power((n-1)/2);
		return Matrix_Fib_multiply(Matrix_Fib_multiply(matrix_half,matrix_half),base_matrix);
	}
}
long long Fibonacci_Matirx(long long n)
{
  if (n<=0) return 0;
  if (n==1) return 1;

  Matrix_Fib fib_matrix=Matirx_power(n-1);
  return fib_matrix.v00;

}
int main()
{
	long long n=8;
	cout<<"Fibonacci_recursion:"<<Fibonacci_recursion(n)<<endl;
	cout<<"Fibonacci_loop:"<<Fibonacci_loop(n)<<endl;
	cout<<"Fibonacci_loop:"<<Fibonacci_Matirx(n)<<endl;

    // Matrix_Fib m(1,2,3,4);
	return 0;
}
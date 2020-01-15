#include<iostream>
using namespace std;
bool check(int * arr,int rows,int cols,int numder)
{
	if(arr==NULL || rows <=0 || cols<=0)
		return false;

	int row=0,col=cols-1;    //从左上角开始找
	while(row<rows && col>=0)
	{
		
		int cur_ind=row*cols+col;  //当前查询的下标

		// cout<<"outer   row:"<<row<<"--col:"<<col<<"-"<<arr[cur_ind]<<endl;
		if (arr[cur_ind] == numder)
		{
			cout<<"row:"<<row<<"--col:"<<col<<endl;
			return true;
		}
		else if(arr[cur_ind] > numder)  //当前元素大于要查找的元素,则向左查找
			col--;
		else                      //当前元素小于要查找的元素,则向下查找
			row++;
	}
	return false;
}
int main()
{
	//二维数组每一行从左向右递增,每一列从上到下递增
	//查找二维数组中是否存在指定元素
	//核心:确定正确的查找方向,如果从左上角开始出发,那么其右侧和下侧都比该点值大,
	// 所以如果想要找比当前值大的,可以向右或者向左,就出现不确定性,虽然是可以向右、向下都比较一下,但是会重复比较
	//但是换个角度人,如果从右上角向内部出发,其左边的值比他小,其下面的值比他大,那么这时如果想找更小的就向左走,
	//想找更大的就行向下走,不会歧义。
	//同理，从左下角向内部查找,也是类似的思路,但是从左上和右下角出发就会产生歧义。
	int arr[4][4]={1,2,8,9,2,4,9,12,4,7,10,13,6,8,11,15};
	cout<<check((int*)arr,4,4,15)<<endl;
	return 0;
}
#include<iostream>
using namespace std;

const int cols=4,rows=4;

int** init()
{
	int temp[rows][cols]={
    	{1,10,3,8},
    	{12,2,9,6},
    	{5,7,4,11},
    	{3,7,16,5}};

    int **arr=new int*[rows];
    for (int i=0;i<rows;i++)
    {
        arr[i] = new int[cols];
        for(int j=0;j<cols;j++)
        	arr[i][j] = temp[i][j];
    }
    return arr;
}
void print_arr(int** arr)
{
	for (int i=0;i<rows;i++)
    {
	    for(int j=0;j<cols;j++)
	    	cout<<arr[i][j]<<" ";
	    cout<<endl;
    }
}

//DFS:cur_sum表示dfs走到(row,col)坐标时的最大和值(包括当前值),max_sum表示
void getMaxSum_s1_core(int** arr,int row,int col,int cur_sum,int &max_sum)
{
	
	if(row>=rows || col>=cols)
		return;
	if(row==rows-1 && col==cols-1)
	{
		if(cur_sum>=max_sum)
			max_sum = cur_sum;
		return;
	}

	if(row<rows-1)
		getMaxSum_s1_core(arr,row+1,col,cur_sum+arr[row+1][col],max_sum);
	if(col<cols-1)
		getMaxSum_s1_core(arr,row,col+1,cur_sum+arr[row][col+1],max_sum);
	return;
}
int getMaxSum_s1(int** arr)
{
	if(arr==NULL || cols<=0 || rows<=0)
		return 0;
	int max_sum=0;
	getMaxSum_s1_core(arr,0,0,arr[0][0],max_sum);
	return max_sum;
}

//动态规划形式:
//dp[i][j] = max(dp[i-1][j],dp[i][j-1])+arr[i][j]
int getMaxSum_s2(int** arr)
{
	if(arr==NULL || cols<=0 || rows<=0)
		return 0;
	int **dp = new int*[rows];
	for (int i=0;i<rows;i++)
        dp[i] = new int[cols];

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			int up = i>0? dp[i-1][j]:0;
			int left= j>0? dp[i][j-1]:0;
			dp[i][j] = max(left,up)+arr[i][j];
		}
	}

	int max_sum = dp[rows-1][cols-1];
	for (int i=0;i<rows;i++)
        delete[] dp[i];
    delete[] dp;
	return max_sum;
}

int main()
{
	int **arr = init();
	print_arr(arr);
	cout<<"getMaxSum_s1: "<<getMaxSum_s1(arr)<<endl;
	cout<<"getMaxSum_s2: "<<getMaxSum_s2(arr)<<endl;
	
	return 0;
}
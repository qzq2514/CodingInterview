#include<iostream>
#include<memory.h>
using namespace std;

const int rows=2,cols=3;     //rows行cols列
bool is_visited[rows][cols];
int dir1[4]={-1,1,0,0};
int dir2[4]={0,0,-1,1};
int get_digit_sum(int number)
{
    int sum=0;
    while(number)
    {
    	sum+=number%10;
    	number/=10;
    }
    return sum;
}
bool check(int row,int col,int thresh)
{
	int digit_sum=get_digit_sum(row)+get_digit_sum(col);
	bool is_sum_over=digit_sum<=thresh;
	bool is_coord_over= row>=0 && row<rows && col>=0 && col<cols;
	return is_sum_over && is_coord_over &&!is_visited[row][col];
}

//走到坐标(cur_row,cur_col)的位置,但还未开始任何判断
int moving_count_core(int cur_row,int cur_col,int thresh)
{
	int count=0;
	
	if(check(cur_row,cur_col,thresh))
	{
		count++;         //当前位置满足,所以这里要当前位置要加1,不然moving_count函数永远返回0
		is_visited[cur_row][cur_col]=true;
		for(int dir=0;dir<4;dir++)
		{
			int next_row=cur_row+dir1[dir];
			int next_col=cur_col+dir2[dir];
			count+=moving_count_core(next_row,next_col,thresh);
		}
	}
	return count;
}

int moving_count(int thresh)
{
	if (thresh<0 || rows<=0 || cols<=0)
		return -1;
	memset(is_visited,0,sizeof(is_visited));
	// delete[] is_visited;
	return moving_count_core(0,0,thresh);
}

int main()
{
	// cout<<get_digit_sum(1887);
	int thresh=1;
	cout<<"rows:"<<rows<<" cols:"<<cols<<" threshold:"<<thresh<<endl;
	cout<<"moving_count:"<<moving_count(thresh)<<endl;
	return 0;
}
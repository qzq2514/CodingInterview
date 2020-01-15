#include<iostream>
#include <iomanip>
using namespace std;

int** init_adj(int rows,int cols)
{
	//动态生成二维数组
	int** arr=new int*[rows];
	for(int i=0;i<rows;i++)
		arr[i]=new int[cols];

	int value=0;
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
		{
			arr[i][j]=value++;
		}
	return arr;
}
void print_adj(int** arr,int rows,int cols)
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
			//输出宽度为2且左对齐
			cout<<setw(2)<<setiosflags(ios::left)<<arr[i][j]<<" ";
		cout<<endl;
	}
		
}

void print_circle(int** arr,int rows,int cols,int start)
{
    int endX=cols-1-start;
    int endY=rows-1-start;

    //打印圈上行(左->右)
    for(int i=start;i<=endX;i++)
    	cout<<arr[start][i]<<" ";

    //打印圈右列(上->下)
    for(int j=start+1;j<=endY;j++)
    	cout<<arr[j][endX]<<" ";

	//打印圈下行(左->右)
    //防止改圈是一行,以下判断防止重复输出,不然如行"3 4 5 6"会输出"3 4 5 6 5 4 3"
	if(endY>start){
		for(int i=endX-1;i>=start;i--)
    	cout<<arr[endY][i]<<" ";
	}

	//打印圈左列(下->上)
   //防止改圈是一列,以下判断防止重复输出,不然如行"3;4;5;6",同样会输出"3 4 5 6 5 4 3"
	if(endX>start){
	    for(int j=endY-1;j>=start+1;j--)
	    	cout<<arr[j][start]<<" ";
	}
}
void print_clockwise(int** arr,int rows,int cols)
{
     if(arr==NULL || rows<=0 || cols<=0)
         return;

     int start=0;    //每一圈左上角坐标为(start,start)

     //必须满足一下条件,以(start,start)为左上定点的圈才存在
     //比如5*6矩阵,只有三个圈,这三个圈左上顶点分别为(0,0)、(1,1)、(2,2)
     while(start*2<rows && start*2<cols)
     {
          print_circle(arr,rows,cols,start);
          start++;
     }
}
int main()
{
	//数组只有一行和一列时,分别当做上行和右列
	int rows=4,cols=3;
	int** arr=init_adj(rows,cols);
	print_adj(arr,rows,cols);
    cout<<"---------"<<endl<<"print_clockwise:"<<endl;
	print_clockwise(arr,rows,cols);
	cout<<endl;
	return 0;
}





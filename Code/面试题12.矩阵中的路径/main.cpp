#include<iostream>
#include<memory.h>
using namespace std;
const int N=3,M=4; 
char adj[N][M]={{'a','b','t','g'},
                {'c','f','c','s'},
                {'j','d','e','h'}};
int vertical[4]={-1,1,0,0};
int horizontal[4]={0,0,-1,1};   //上下左右四个方向
bool is_visited[N][M];

//刚走到(cur_row,cur_col)位置,还需要对比str的cur_char_index位置
bool has_path_core(int cur_row,int cur_col,int cur_char_index,char* str)
{
	// cout<<"cur_char_index:"<<cur_char_index<<"--"<<str[cur_char_index]<<endl;
	if(str[cur_char_index]=='\0')
		return true;                 //dfs找到了字符串的最后,说明全找到了
	
	if(adj[cur_row][cur_col]!=str[cur_char_index])//如果当前位置不是要比对的字符,那么“此路不通”
		return false;

    //当前位置越界,返回false
	if(!(cur_row>=0 && cur_row<N && cur_col>=0 && cur_col<M && !is_visited[cur_row][cur_col]))
		return false;

	is_visited[cur_row][cur_col]=true;
	for(int dir=0;dir<4;dir++)    //当前位置不是要比对的字符,开始向四个方向不断查找
	{
		int next_row=cur_row+vertical[dir];
		int next_col=cur_col+horizontal[dir];
	    //如果在下一个位置未越界且之前没被访问,并且从下一个位置找路径能找到,则直接返回true

	    // 方法一:在每次has_path_core前判断越界:
	    // 但是这样写有个问题就是比如"sceh"字符串,找到最后h的时候,再往h的上下左右方向直接都不能走,导致has_path_core一次也不会调用,
	    // 那么这时候就不会在for循环内返回true
		// if(next_row>=0 && next_row<N && next_col>=0 && next_col<M && !is_visited[next_row][next_col]
		// 	&& has_path_core(next_row,next_col,cur_char_index+1,str))
		// 	return true;

		//方法二:每次都直接has_path_core,在每次调用has_path_core开头进行越界判断,这样就能保证至少在每个点都会至少调用一次has_path_core函数(见23~24行)
		if(has_path_core(next_row,next_col,cur_char_index+1,str))
			return true;
	}
	//到这里,当前位置的下四个位置都无法找到正确路径,那么“此路不通”
	is_visited[cur_row][cur_col]=false;
	return false;

}

bool has_path(char* str)
{
	if(str==NULL || str[0]=='\0')
		return false;

	memset(is_visited,0,sizeof(is_visited));
	for(int row=0;row<N;row++)
		for(int col=0;col<M;col++)
		{
			//从每个位置开始dfs
			if(has_path_core(row,col,0,str))
				return true;
		}
				
	return false;
}
int main()
{
	char str[]="tgsceh";
	cout<<str<<":"<<endl<<has_path(str)<<endl;
	return 0;
}
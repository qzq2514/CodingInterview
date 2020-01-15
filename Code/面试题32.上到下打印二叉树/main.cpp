#include<iostream>
#include<stack>
#include<queue>
#include <math.h>
#include <iomanip>

using namespace std;
struct Node
{
	Node(int value,Node* left,Node* right)
	{
       this->value=value;
       this->left=left;
       this->right=right;
	}
	int value;
	Node* left;
	Node* right;

};
Node* init_tree()
{
	Node* node4 = new Node(4,NULL,NULL);
	Node* node7 = new Node(7,NULL,NULL);
	Node* node2 = new Node(2,node4,node7);
	Node* node9 = new Node(9,NULL,NULL);
	Node* node8 = new Node(8,node9,node2);
	Node* node3 = new Node(3,NULL,NULL);
	Node* node77 = new Node(7,node3,NULL);
	Node* root = new Node(8,node8,node77);
	return root;
}

//不分行打印树的节点
void tree_bfs_noLevel(Node* root)
{
	if(root==NULL)
		return ;
	queue<Node*> nodes;
	nodes.push(root);
	while(!nodes.empty())
	{
		Node* cur_node=nodes.front();
		nodes.pop();

		if(cur_node==NULL)
			continue ;

		cout<<cur_node->value<<" ";
		nodes.push(cur_node->left);
		nodes.push(cur_node->right);
	}
}

//分行地从上到下打印二叉树
void tree_bfs_withLevel(Node* root)
{
	if(root==NULL)
		return ;
	queue<Node*> nodes;
	int next_level_num=0;    //下一行要打印的节点数
	int toBePrinted_num=1;   //当前层还剩的未被打印的节点数,初始化为1即根节点
	nodes.push(root);
	while(!nodes.empty())
	{
		Node* cur_node=nodes.front();
		cout<<cur_node->value<<" ";

		if(cur_node->left!=NULL)
		{
		   nodes.push(cur_node->left);
		   next_level_num++;
		}
		if(cur_node->right!=NULL)
		{
			nodes.push(cur_node->right);
			next_level_num++;
		}
		
		nodes.pop();
		toBePrinted_num--;
		if(toBePrinted_num==0)    //当前层打印完,开始下一层
		{
			cout<<endl;
           toBePrinted_num=next_level_num;
           next_level_num=0;
		}
	}
}

//分行打印且也要打印出空节点
int get_deepth(Node* root)
{
	if(root==NULL)
		return 0;
	int left_deepth=get_deepth(root->left);
	int right_deepth=get_deepth(root->right);

	return max(left_deepth,right_deepth)+1;
}
void tree_bfs_withLevel_NULL(Node* root)
{
	if(root==NULL)
		return ;

	int deepth=get_deepth(root);

	queue<Node*> nodes;
	int toBePrinted_num=1;   //当前层还剩的未被打印的节点数,初始化为1即根节点
	int level=1;
	nodes.push(root);
	while(!nodes.empty() && level<=deepth)
	{
		Node* cur_node=nodes.front();
		nodes.pop();
		toBePrinted_num--;

		cout << setw(pow(2,deepth-level+1)) << setfill(' ');
		if(cur_node==NULL)
		{
			cout<<"N";
			nodes.push(NULL);
			nodes.push(NULL);
		}
		else
		{
			cout<<cur_node->value;
			nodes.push(cur_node->left);
			nodes.push(cur_node->right);
		}
		
		if(toBePrinted_num==0)    //当前层打印完,开始下一层
		{
		   cout<<endl;
           toBePrinted_num=pow(2,level); //下一层要被打印的节点数是2的level次方
           level++;
		}
	}
}

//栈实现树的dfs遍历, 其实就是前序遍历
void tree_dfs(Node* root)
{
	if(root==NULL)
		return ;
	stack<Node*> nodes;
	nodes.push(root);
	while(!nodes.empty())
	{
		Node* cur_node=nodes.top();
		cout<<cur_node->value<<" ";
		nodes.pop();
		// 先push右节点,再push左节点,因为栈后进先出,所以遍历的时候先遍历左子树
		// 当然这里也可以像tree_bfs一样
		if(cur_node->right!=NULL)
			nodes.push(cur_node->right);
		if(cur_node->left!=NULL)
			nodes.push(cur_node->left);
	}
}

//递归方式下的前序遍历
void preOrder(Node* root)
{
	if(root==NULL)
		return;
	cout<<root->value<<" ";   //改变这里cout的位置,就可以实现中序遍历和后序遍历
	preOrder(root->left);
	preOrder(root->right);
}

//分行且"之"字型地打印树节点
//如果栈改成队列,且184行的top变成front,并且每个queue都是先push左节点,
//那么既可以像tree_bfs_withLevel分层打印树,且每行都是从左向右打印(同理,先push右节点,则每行从右向左打印)
void tree_bfs_Level_zhi_like(Node* root)
{
	if(root==NULL)
		return ;
	stack <Node*> stacks[2];
	int cur_stack=0;       //两个栈分别存放奇数行和偶数行的数据
	int next_stack=1;
	stacks[cur_stack].push(root);
	while(!stacks[cur_stack].empty() || !stacks[next_stack].empty())
	{
		Node* cur_node=stacks[cur_stack].top();
		stacks[cur_stack].pop();
		cout<< cur_node->value<<" ";

		if(cur_stack==0)
		{
			if(cur_node->left!=NULL)
				stacks[next_stack].push(cur_node->left);       //偶数层从右向左打印,所以后push右节点
			if(cur_node->right!=NULL)
				stacks[next_stack].push(cur_node->right);
		}
		else
		{
			if(cur_node->right!=NULL)                  //奇数层从左向右打印,所以后push左节点
				stacks[next_stack].push(cur_node->right);
			if(cur_node->left!=NULL)
				stacks[next_stack].push(cur_node->left);
		}

		if(stacks[cur_stack].empty())
		{                                  //当前行打印完,交替两个栈打印下一行
			cout<<endl;
			next_stack=1-next_stack;
			cur_stack=1-cur_stack;
		}
	}
}

int main()
{
	Node* root=init_tree();
	cout<<"tree_bfs_noLevel: ";
	tree_bfs_noLevel(root);
	cout<<endl<<"tree_dfs: ";
	tree_dfs(root);
	cout<<endl<<"preOrder: ";
	preOrder(root);
    cout<<endl<<"tree_bfs_withLevel:"<<endl;
    tree_bfs_withLevel(root);
    cout<<endl<<"tree_bfs_withLevel_NULL:"<<endl;
    tree_bfs_withLevel_NULL(root);
    cout<<endl<<"tree_bfs_Level_zhi_like:"<<endl;
    tree_bfs_Level_zhi_like(root);


	return 0;
}
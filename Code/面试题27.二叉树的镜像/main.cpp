#include<iostream>
#include<stack>
#include<queue>

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
	Node* node77 = new Node(7,NULL,NULL);
	Node* root = new Node(8,node8,node77);
	return root;
}

void print_tree(Node* root)
{
	if(root==NULL)
		return;
	print_tree(root->left);
	cout<<root->value<<" ";
	print_tree(root->right);
}

//递归访问树的每个节点,交换树的左右子树就行
//其实仔细看看,下面的代码就是树的遍历
Node* MirrorTree_recurse(Node* root)
{
	if(root==NULL)
		return root;

	Node* mirror_root=new Node(root->value,NULL,NULL);

	// 原本下句意思为如果该root节点就是叶子节点了,那么直接返回new后的mirror_root就行了
	// 但其实这个if判断句话可以不要
	// if(root->left==NULL && root->right==NULL)
	// 	return mirror_root;

	//这里不会改变原树的内容,书上的方法是直接在原来的树上进行改动
	//如果是书上的方法,那么就直接交换root->left和root->right
	mirror_root->left=MirrorTree_recurse(root->right);
    mirror_root->right=MirrorTree_recurse(root->left);
    return mirror_root;
}

//其实从递归的方法可以看出,其实就是简单地遍历每个节点,然后交换左右子树就行了
//而遍历树的每个节点,可以用基于队列的层序遍历和基于栈的深度优先遍历
void MirrorTree_queue(Node* root)
{
	if(root==NULL)
		return ;
	queue<Node*> nodes;
	nodes.push(root);
	while(!nodes.empty())
	{
		Node* cur_node=nodes.front();
		nodes.pop();

		Node* temp = cur_node->left;
		cur_node->left = cur_node->right;
		cur_node->right = temp;
		if(cur_node->left!=NULL)
			nodes.push(cur_node->left);
		if(cur_node->right!=NULL)
			nodes.push(cur_node->right);
	}
	
}

void MirrorTree_stack(Node* root)
{
	if(root==NULL)
		return ;
	stack<Node*> nodes;
	nodes.push(root);
	while(!nodes.empty())
	{
		Node* cur_node=nodes.top();
		nodes.pop();

		Node* temp = cur_node->left;
		cur_node->left = cur_node->right;
		cur_node->right = temp;
		if(cur_node->left!=NULL)
			nodes.push(cur_node->left);
		if(cur_node->right!=NULL)
			nodes.push(cur_node->right);
	}
	
}



//扩展:树的深度优先遍历(DFS)
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
		if(cur_node->right!=NULL)
			nodes.push(cur_node->right);
		if(cur_node->left!=NULL)
			nodes.push(cur_node->left);
		
	}
	cout<<endl;
}

//扩展:树的广度优先遍历(DFS)
void tree_bfs(Node* root)
{
	if(root==NULL)
		return ;
	queue<Node*> nodes;
	nodes.push(root);
	while(!nodes.empty())
	{
		Node* cur_node=nodes.front();
		cout<<cur_node->value<<" ";
		nodes.pop();

		// 先push左节点,再push右节点,因为队列先进先出,所以在遍历每一层的时候从左向右遍历
		if(cur_node->left!=NULL)
			nodes.push(cur_node->left);
		if(cur_node->right!=NULL)
			nodes.push(cur_node->right);
	}
	cout<<endl;
}

int main()
{
	Node* root=init_tree();
	print_tree(root);
	cout<<endl;

	Node* mirror_root_recurse = MirrorTree_recurse(root);
	cout<<"recurse:";
	print_tree(mirror_root_recurse);

	cout<<endl<<"queue:";
	Node* root1=init_tree();
	MirrorTree_queue(root1);
	print_tree(root1);

	cout<<endl<<"stack:";
	Node* root2=init_tree();
	MirrorTree_stack(root2);
	print_tree(root2);
	cout<<endl;


    //扩展:树的深度优先遍历:
    tree_dfs(root);
    tree_bfs(root);
	return 0;
}
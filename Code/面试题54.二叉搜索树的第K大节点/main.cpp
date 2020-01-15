#include<iostream>
using namespace std;
struct Node
{
	Node(int value,Node* left,Node* right)
	{
		this->value = value;
		this->left = left;
		this->right = right;
	}
	int value;
	Node* left;
	Node* right;
};

Node* init()
{
	Node* node2 = new Node(2,NULL,NULL);
	Node* node4 = new Node(4,NULL,NULL);
	Node* node3 = new Node(3,node2,node4);
	Node* node6 = new Node(6,NULL,NULL);
	Node* node8 = new Node(8,NULL,NULL);
	Node* node7 = new Node(7,node6,node8);
	Node* root = new Node(5,node3,node7);
	return root;
}
void inOrder_print(Node* root)
{
	if(root == NULL)
		return ;
	inOrder_print(root->left);
	cout<<root->value<<" ";
	inOrder_print(root->right);
}
//因为K相当于是一个全局变量,必须要写成引用的形式,
//寻找二叉树第k大的数,其实就是中序搜索中第k个数,
//像中序搜索一样形式:1.递归遍历左子树 2.对当前根节点操作 3.递归遍历右子树
//但是需要一个全局变量控制当前已经遍历到第几个数,因为遍历左子树的时候会影响K值,进而会影响右子树的遍历
//之前dfs或者bfs函数中可能也会有某个参数控制步数,但是dfs之类每条路径上第k个节点和其他路径是不冲突,
//相互独立的,所以不用设置为全局
Node *findKthNode(Node* root,int& k)
{
	if(root==NULL)
		return NULL;
	Node* target = findKthNode(root->left,k);
	if(target!=NULL)
		return target;

	k--;
	if(k==0)
		return root;

	target = findKthNode(root->right,k);
	if(target!=NULL)
		return target;
	return NULL;
}
int main()
{
	Node* root = init();
	inOrder_print(root);
	int kth = 3;int K=kth,k=kth;
	Node* result = findKthNode(root,k);
	cout<<endl;
	if(result==NULL)
		cout<<K<<"th node is not found!"<<endl;
	else
		cout<<K<<"th node is "<<result->value<<endl;
	return 0;
}





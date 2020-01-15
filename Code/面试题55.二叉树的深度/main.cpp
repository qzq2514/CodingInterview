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
	Node* node8 = new Node(8,NULL,NULL);
	Node* node7 = new Node(7,NULL,NULL);   //可以将node8加到node7一个子树上造成不平衡
	Node* node4 = new Node(4,NULL,NULL);
	Node* node5 = new Node(5,node7,NULL);
	Node* node2 = new Node(2,node4,node5);
	Node* node6 = new Node(6,NULL,NULL);
	Node* node3 = new Node(3,NULL,node6);
	Node* root = new Node(1,node2,node3);
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

//简单的获得二叉树的深度(一个节点的树算作深度为1)
int get_tree_depth(Node* root)
{
	if(root==NULL)
		return 0;
	int left_d = get_tree_depth(root->left);
	int left_f = get_tree_depth(root->right);
	return max(left_d,left_f)+1;
}

//每个节点对应一个深度参数,且因为isBalanced已经有返回值,
//那么只能通过引用传递,将值从函数内部传回去,其实其只会改变一次,就是在74行的时候
//其并不像"面试题54.二叉搜索树的第K大节点"中的引用参数k一样会不断在递归函数中改变,
//仅仅是因为C++中只能返回一个值,如果其能够像python一样返回多个值,那么不定义成引用传递,直接返回也是可以的
bool isBalanced(Node* root,int& depth)
{
	if(root == NULL)
	{
		depth=0;
		return true;
	}

	int left_d=0,right_d=0;
	bool is_balanced = false;
	bool is_left_balanced = isBalanced(root->left,left_d);
	bool is_right_balanced = isBalanced(root->right,right_d);
	if( is_left_balanced && is_right_balanced)
	{
		int diff = left_d - right_d;
		if(diff<=1 && diff>=-1)
			is_balanced = true;
	}

	//原书中将以下这句放在if(diff<=1 && diff>=-1)判断中,这样会导致在root左右子树不平衡,
	//或者两者深度相差太大的时候,就不会更新depth,这样最后isBalanced调用完后,就无法使用depth得到准确的深度(其实这时depth=0)
	//此时,最好都显示在左右子树上调用isBalanced,因为如果像原书中用 && 连接两个isBalanced,那么如果 && 左侧的树本身就不平衡了,
	//那么久不会调用isBalanced再在另一半的树上遍历,此时如果为遍历的树其实有更深的深度,那么因为没有遍历,导致其深度为0,那么此时,
	//在执行下面这句的时候,就是导致depth仅仅是在浅的树的深度上加一,同样导致depth不准确(这时depth虽然不会等于0,但是明显偏小了)
	depth = max(left_d,right_d)+1;
	return is_balanced;
}
bool check_BBT(Node* root)
{
	int depth = 0;
	bool is_balanced = isBalanced(root,depth);
	cout<<"Depth_check_BBT: "<<depth<<endl;
	return is_balanced;
}
int main()
{
	Node* root = init();
	inOrder_print(root);
	int depth = get_tree_depth(root);
	cout<<endl<<"Depth: "<<depth<<endl;

	bool is_balanced = check_BBT(root);
	cout<<"is balanced:"<<is_balanced<<endl;
	return 0;
}
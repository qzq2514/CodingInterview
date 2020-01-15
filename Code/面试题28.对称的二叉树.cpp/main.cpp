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
Node* init_tree_notSymmetric()
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

Node* init_tree_symmetric()
{
	Node* node5 = new Node(5,NULL,NULL);
	Node* node7 = new Node(7,NULL,NULL);
	Node* node6 = new Node(6,node5,node7);
	Node* node77 = new Node(7,NULL,NULL);
	Node* node55 = new Node(5,NULL,NULL);
	Node* node66 = new Node(6,node77,node55);
	Node* root = new Node(8,node6,node66);
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

bool check_symmetric_core(Node* left_root,Node* right_root)
{
	if(left_root==NULL && right_root==NULL)
		return true;
	//如果其中一个树空了另一个没空,那么肯定不是对称的
	if(left_root==NULL || right_root==NULL)
		return false;
	//如果两个子树连根节点都不同,那么总树肯定不是对称的
	if(left_root->value!=right_root->value)
		return false;
	return check_symmetric_core(left_root->left,right_root->right)&&
			check_symmetric_core(left_root->right,right_root->left);
}

//相当于把一个树复制了一份,这份的左子树和另一份的右子树比较
//这份的右子树和另一份的左子树比较
bool check_symmetric(Node* root)
{
    return check_symmetric_core(root,root);
}

int main()
{
	//init_tree_notSymmetric init_tree_symmetric
	Node* root=init_tree_symmetric();
	print_tree(root);

	cout<<endl<<"is symmetric: "<<check_symmetric(root)<<endl;

	return 0;
}
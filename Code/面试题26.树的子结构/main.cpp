#include<iostream>
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
Node* init_father()
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

Node* init_son()
{
	Node* node2 = new Node(2,NULL,NULL);
	Node* node9 = new Node(9,NULL,NULL);
	Node* root = new Node(8,node9,node2);
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
//从root_father和root_son的根节点开始一一比较
bool check_son_tree_core(Node* root_father,Node* root_son)
{
    if(root_son==NULL)
		return true;
	if(root_father==NULL)
		return false;
	if(root_father->value!=root_son->value)
		return false;

	bool is_left_same=check_son_tree_core(root_father->left,root_son->left);
	bool is_right_same=check_son_tree_core(root_father->right,root_son->right);
	return is_left_same && is_right_same;
}

//先找到合适的根节点,再把该根节点和子树的根节点开始向下逐个节点比较
bool check_son_tree(Node* root_father,Node* root_son)
{
	//原书中在root_son为空时返回 false,我觉得返回true比较合理
	if(root_son==NULL)
		return true;
	if(root_father==NULL)
		return false;

    bool result=false;

	//在父树中找到合适的根节点开始和子树的节点一一比较
	if(root_father->value==root_son->value)
       result=check_son_tree_core(root_father,root_son);

    //当前父树根节点和子树根节点不同,那么就在左右子树中继续找合适的根节点
    //这里均使用check_son_tree函数,而不是使用check_son_tree_core
    //因为check_son_tree_core函数就已经开始逐个节点比较了,
    //而到这里还不知道左节点或右节点是不是符合条件了,不能开始逐个节点比较
    if(!result)
	   result=check_son_tree(root_father->left,root_son);
	if(!result)
	   result=check_son_tree(root_father->right,root_son);
	return result;
	
}
int main()
{
	Node* root_father=init_father();
	print_tree(root_father);
	cout<<endl;
	Node* root_son=init_son();
	print_tree(root_son);
	cout<<endl;

    bool result=check_son_tree(root_father,root_son);
    cout<<result<<endl;
	return 0;
}








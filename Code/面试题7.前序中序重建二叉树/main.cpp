#include<iostream>
#include<algorithm>
using namespace std;

struct Node{
	Node(int value){
		this->value=value;
		this->left=NULL;
		this->right=NULL;
	}
	int value;
	Node* left;
	Node* right;
};

int preOrder[]={1,2,4,7,3,5,6,8};  //前序
int inOrder[] ={4,7,2,1,5,3,8,6};  //中序
int N=8;
//当前树所有节点在前序和中序遍历中的下标起始
Node* reBuildBinaryTree(int pre_begin,int pre_end,int in_begin,int in_end)
{
	if (pre_begin>pre_end || in_begin>in_end)
		return NULL;

	//前序遍历的第一个节点是当前树的根节点
	int root_value=preOrder[pre_begin];
	Node* root=new Node(root_value);

	//找到根节点在中序数组中的位置
	int root_in_index=distance(inOrder,find(inOrder,inOrder+N,root_value));
	//中序数组中,根节点左侧为左子树,右侧为右子树,left_nodes_num为左子树节点数
	int left_nodes_num=root_in_index-in_begin;

	root->left=reBuildBinaryTree(pre_begin+1,pre_begin+left_nodes_num,in_begin,root_in_index-1);
	root->right=reBuildBinaryTree(pre_begin+1+left_nodes_num,pre_end,root_in_index+1,in_end);
	cout<<root_value<<"-";  //这里直接打印根节点数, 最后的打印顺序其实就是后序遍历的顺序
	return root;
}

void post_print(Node* root)
{
	if (root==NULL)
		return ;
	post_print(root->left);
	post_print(root->right);
	cout<<root->value<<" ";

}
int main()
{
	Node* root=reBuildBinaryTree(0,7,0,7);
	cout<<endl<<"-------------"<<endl;
	post_print(root);
	return 0;
}
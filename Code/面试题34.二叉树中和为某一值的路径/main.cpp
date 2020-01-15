#include<iostream>
#include<vector>
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
	Node* node14 = new Node(14,node3,NULL);
	Node* root = new Node(8,node8,node14);
	return root;
}

//走到当前根节点root时路径距离目标和为还差leftSum个数,路径为path
//其实就是一个dfs问题
void findPathCore(Node* root,vector<int> &path,int leftSum)
{
    if(root==NULL)
    	return;
    leftSum-=root->value;
    path.push_back(root->value);
    bool isLeaf = root->left==NULL && root->right==NULL;
    if(leftSum==0 && isLeaf)   //到达叶节点且剩余和为0(即和为指定的和expectedNum)
    {
       cout<<"A path is found:";
       vector<int>::iterator iter=path.begin();
       for(;iter!=path.end();iter++)
       	   cout<<*iter<<" ";
       cout<<endl;
    }

    findPathCore(root->left,path,leftSum);
    findPathCore(root->right,path,leftSum);
    //返回上一层之前要记得把当前根节点弹出
    path.pop_back();
}

void findPath(Node* root,int expectedNum)
{
	if(root==NULL)
		return;

	vector<int> path;
	findPathCore(root,path,expectedNum);

}

int main()
{
	Node* root=init_tree();
	findPath(root,25);
	return 0;
}
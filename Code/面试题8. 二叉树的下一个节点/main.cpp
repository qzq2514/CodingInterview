#include<iostream>
using namespace std;

struct Node{
	Node(char value,Node* left,Node* right)
	{
		this->value=value;
		this->right=right;
		this->left=left;
		if(right!= NULL)
			right->parent=this;
		if(left!= NULL)
			left->parent=this;
	}
	char value;
	Node* parent;
	Node* right;
	Node* left;
};
Node* init()
{
	Node* ni=new Node('i',NULL,NULL);Node* nh=new Node('h',NULL,NULL);
	Node* ng=new Node('g',NULL,NULL);Node* nf=new Node('f',NULL,NULL);
	Node* ne=new Node('e',nh,ni);Node* nd=new Node('d',NULL,NULL);
	Node* nc=new Node('c',nf,ng);Node* nb=new Node('b',nd,ne);
	Node* na=new Node('a',nb,nc);na->parent=NULL;
	return na;
}
void print_in_order(Node* root)
{
   if(root==NULL)
   	  return;
   print_in_order(root->left);
   cout<<root->value<<" ";
   print_in_order(root->right);

}

//直观理解版本
Node* get_next_node(Node* pNode)
{
	if (pNode==NULL)
		return NULL;
	Node* pNext=NULL;
	if(pNode->right!=NULL)   //如果当前点存在右子树,那么下一个节点就是右子树的最左边一个节点
	{
		Node* cur_node=pNode->right;
		while(cur_node->left!=NULL)
			cur_node=cur_node->left;
		pNext=cur_node;

	}
	//否则如果不存右子树,则往父节点找,此时不存在父节点则说明在根节点了,且根节点没有右子树,那么就没有下一个节点
	else if(pNode->parent!=NULL){                      
		if(pNode==pNode->parent->left)  //不存在右子树且有父节点,且该节点是其父节点的左节点,那么下一个节点就是父节点
			pNext=pNode->parent;
		else{  //不能再右子树且有父节点,但该节点是其父节点的右节点,那么从该节点往上找,找到一个节点p,使得p=p->parent->left,那么下一个节点就是p->parent
 			Node* cur_node=pNode;
 			Node* cur_parent_node=cur_node->parent;
 			while(cur_parent_node!=NULL && cur_node==cur_parent_node->right)
 			{
 				cur_node=cur_parent_node;
 				cur_parent_node=cur_node->parent;
 			}
 			pNext=cur_parent_node;
		}
	}
	return pNext;
}

//非合并版
Node* get_next_node_merge(Node* pNode)
{
	if (pNode==NULL)
		return NULL;
	Node* pNext=NULL;
	if(pNode->right!=NULL)   
	{
		Node* cur_node=pNode->right;
		while(cur_node->left!=NULL)
			cur_node=cur_node->left;
		pNext=cur_node;

	}  
	else if(pNode->parent!=NULL){              //到这里和get_next_node都是一样的
		Node* cur_node=pNode;
		Node* cur_parent_node=cur_node->parent;
		//这里如果当前节点是其父节点的左节点,那么这直接在第一次while就退出了,返回了父节点
		while(cur_parent_node!=NULL && cur_node==cur_parent_node->right)   
		{
			cur_node=cur_parent_node;
			cur_parent_node=cur_node->parent;
		}
		pNext=cur_parent_node;
	}
	return pNext;
}
void print_next(Node* cur_root)
{
	if(cur_root==NULL)
   	  return;
   print_next(cur_root->left);

   Node* next_node=get_next_node(cur_root);
   Node* next_node_merge=get_next_node_merge(cur_root);
   cout<<"cur_node:"<<cur_root->value<<"  "<<endl;
   if(next_node!=NULL)
	    cout<<"next_node : "<<next_node->value<<endl;
   else
		cout<<"next_node : NULL"<<endl;
   if(next_node_merge!=NULL)
	    cout<<"next_node_merge : "<<next_node_merge->value<<endl;
   else
		cout<<"next_node_merge : NULL"<<endl;
   cout<<"-------------"<<endl;
   print_next(cur_root->right);
}
int main()
{
	Node* root=init();

	print_in_order(root);

	//全部打印看一遍
    cout<<endl<<"----------"<<endl;
	print_next(root);


    //查看指定节点下一个节点
    Node* cur_node=root->left;
    Node* next_node=get_next_node(cur_node);
    Node* next_node_merge=get_next_node_merge(cur_node);
    cout<<"cur_node:"<<cur_node->value<<endl;
    if(next_node!=NULL)
	    cout<<"next_node : "<<next_node->value<<endl;
    else
		cout<<"next_node : NULL"<<endl;
    if(next_node_merge!=NULL)
	    cout<<"next_node_merge : "<<next_node_merge->value<<endl;
    else
		cout<<"next_node_merge : NULL"<<endl;
   cout<<"-------------"<<endl;
	
	
	return 0;
}
#include<iostream>
using namespace std;

struct BinaryNode{
	BinaryNode(int value,BinaryNode* left,BinaryNode* right)
	{
		this->value = value;
		this->left = left;
		this->right = right;
	}

	int value;
	BinaryNode* left;
	BinaryNode* right;
};

BinaryNode* init()
{
	BinaryNode* node4 = new BinaryNode(4,NULL,NULL);
	BinaryNode* node8 = new BinaryNode(8,NULL,NULL);
	BinaryNode* node6 = new BinaryNode(6,node4,node8);
	BinaryNode* node12 = new BinaryNode(12,NULL,NULL);
	BinaryNode* node16 = new BinaryNode(16,NULL,NULL);
	BinaryNode* node14 = new BinaryNode(14,node12,node16);
	BinaryNode* node10 = new BinaryNode(10,node6,node14);
	return node10;
}
void inOrder_print_tree(BinaryNode* root)
{
    if(root == NULL)
    	return;
    inOrder_print_tree(root->left);
    cout<<root->value<<" ";
    inOrder_print_tree(root->right);
}
//从左到有(小->大)打印链表
void print_list(BinaryNode* head,string type)
{
	BinaryNode* p = head;
	while(p!=NULL)
	{
		cout<<p->value<<" ";
		if(type == "FromLeft")
		   p = p->right;
		else
		   p = p->left;
	}
	cout<<endl;
}


void convertListCore(BinaryNode* root,BinaryNode** curListTail)
{
	if(root == NULL)
		return;

	//在左子树中进行转换,转换后的最大值就是链表的最后节点curListTail
	if(root->left!=NULL)
		convertListCore(root->left,curListTail);
	//因为搜索二叉树左子树节点都小于根节点,且目前最大值存放在curListTail中
	//那么在最终的双向链表中,目前最大值curListTail和根节点root是相邻的节点
	//下面两句则是对相邻节点进行连接
	root->left = *curListTail;
	if((*curListTail)!=NULL)     
		(*curListTail)->right = root;

    //再在右子树中重建双向链表(注意在重建左子树之前,当前的双向链表的最后一个节点被更新为curListTail了)
	*curListTail = root;
	if(root->right!=NULL)
		convertListCore(root->right,curListTail);
}

BinaryNode* convertList(BinaryNode* root)
{
	//BinaryNode是当前转化后链表的最后一个节点,并且自始至终只有一个申明
	BinaryNode* listTail = NULL;
	//listTail节点指针在递归的过程中不断变化,且会影响到初始值(所以这里也是传入引用的目的)
	convertListCore(root,&listTail);


	//根据最终双向链表的尾结点获得头结点
	BinaryNode* listHead = listTail;
	while(listHead!=NULL && listHead->left!=NULL)
		listHead = listHead->left;

    cout<<"FromRight: ";print_list(listTail,"FromRight");
    cout<<"FromLeft: ";print_list(listHead,"FromLeft");
    return listHead;
}

int main()
{
	BinaryNode* root = init();
	cout<<"BST in_order: ";inOrder_print_tree(root);cout<<endl;
	BinaryNode* convertListHead = convertList(root);
	cout<<"--------"<<endl;
	cout<<"Result: ";print_list(convertListHead,"FromLeft");
	return 0;
}
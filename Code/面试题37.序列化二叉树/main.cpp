#include<iostream>
#include<string.h>
using namespace std;
struct Node{
	Node(string value,Node* left,Node* right)
	{
         this->value = value;
         this->left = left;
         this->right = right;

	}
	string value;
	Node* left;
	Node* right;
};
void inorder_tree(Node* root)
{
	if(root==NULL)
		return ;
	inorder_tree(root->left);
	cout<<root->value<<"";
	inorder_tree(root->right);
}
Node* init()
{
	Node* node4 = new Node("4",NULL,NULL);
	Node* node2 = new Node("2",node4,NULL);

	Node* node5 = new Node("5",NULL,NULL);
	Node* node6 = new Node("6",NULL,NULL);
	Node* node3 = new Node("3",node5,node6);

	Node* node1 = new Node("1",node2,node3);
	return node1;
}
string Serialize(Node* root)
{
	if (root==NULL)
	   return "$";
	string retStr = root->value;
	string left_str=Serialize(root->left);
	string right_str=Serialize(root->right);
	return retStr+left_str+right_str;
}
int ind=0;
Node* unSerialize(string str)
{
	if(ind >= str.length() || str[ind]=='$')
		return NULL;
	string curStr="$";curStr[0] = str[ind];
	Node* root = new Node(curStr,NULL,NULL);
	ind++;
	root->left = unSerialize(str);
	ind++;
	root->right = unSerialize(str);
	return root;
}

int main()
{
    Node* root = init();
    string str = Serialize(root);
    cout<<"Serialize:   "<<str<<endl;
    Node* reRoot = unSerialize(str);
	cout<<"unSerialize(inorder): \n";
	inorder_tree(reRoot);
	cout<<endl;
	return 0;
}
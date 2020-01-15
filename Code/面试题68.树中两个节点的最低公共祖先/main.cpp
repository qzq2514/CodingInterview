#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Node
{
	Node(char value,vector<Node*> childers)
	{
		this->value = value;
		this->childers = childers;
	}
	char value;
	vector<Node*> childers;
};
Node* createNode(char value)
{
	vector<Node*> empty;
	return new Node(value,empty);
}
Node* createNode(char value,Node* childs[],int num)
{
	vector<Node*> childers(childs,childs+num);

	return new Node(value,childers);
}
Node* init()
{	
    Node* L = createNode('L');
    Node* M = createNode('M');
    Node* LM[] = {L,M};
    Node* E = createNode('E',LM,2);
    Node* F = createNode('F');
    Node* EF[] = {E,F};
    Node* B = createNode('B',EF,2);

    Node* G = createNode('G');
    Node* O = createNode('O');
    Node* P = createNode('P');
    Node* OP[] = {O,P};
    Node* H = createNode('H',OP,2);
    Node* GH[] = {G,H};
    Node* C = createNode('C',GH,2);

    Node* I = createNode('I');
    Node* W = createNode('W');
    Node* W_arr[] = {W};
    Node* S = createNode('S',W_arr,1);
    Node* R = createNode('R');
    Node* T = createNode('T');
    Node* RST[] = {R,S,T};
    Node* J = createNode('J',RST,2);
    Node* U = createNode('U');
    Node* V = createNode('V');
    Node* UV[] = {U,V};
    Node* K = createNode('K',UV,2);
    Node* IJK[] = {I,J,K};
    Node* D = createNode('D',IJK,3);

    Node* BCD[] = {B,C,D};
    Node* A = createNode('A',BCD,3);

    return A;
}
void level_print(Node* root)
{
	if(root==NULL)
		return ;
	queue<Node*> list;
	list.push(root);
	while(!list.empty())
	{
		Node* curNode = list.front();
		cout<<curNode->value<<" ";
		vector<Node*>::iterator childer = curNode->childers.begin();
		while(childer!=curNode->childers.end())
		{
		   list.push(*childer);
		   childer++;
		}
		list.pop();
	}
}
//寻找树中root节点到节点值为tarValue的路径(默认树中节点值不重复)
//也可以直接查找指定节点(此时树中节点可重复)
bool findPath(Node* root,char tarValue,vector<Node*> &path)
{
	if(root->value==tarValue)
		return true;
	//先把当前节点加入路径
	path.push_back(root);
	bool isFind = false;

	vector<Node*>::iterator childer = root->childers.begin();
	while(!isFind && childer!=root->childers.end())
	{
	   isFind = findPath(*childer,tarValue,path);
	   childer++;
	}
	//如果当前节点root下所有路径都到达不了tarValue,那么将root从路径中删除
	if(!isFind)
		path.pop_back();
	return isFind;
}
//eg. 路径1:A D J R, 路径2:A D J S W
//从两条路径中起始点开始找最后一个相同点
Node* commmonNode(vector<Node*> path1,vector<Node*> path2)
{	
	Node* result=NULL;
	vector<Node*>::iterator pNode1=path1.begin();
	vector<Node*>::iterator pNode2=path2.begin();
	while(pNode1!=path1.end() && pNode2!=path2.end())
	{
		if(*pNode1 == *pNode2)
			result = *pNode1;
		pNode1++;
		pNode2++;
	}
	return result;
}
Node* findLastCommon(Node* root,char value1,char value2)
{
	vector<Node*> path1;
	findPath(root,value1,path1);
	cout<<"Path("<<root->value<<"-->"<<value1<<"):";
	for(int i=0;i<path1.size();i++)
		cout<<path1[i]->value<<" ";
	cout<<value1<<endl;

	vector<Node*> path2;
	findPath(root,value2,path2);
	cout<<"Path("<<root->value<<"-->"<<value2<<"):";
	for(int i=0;i<path2.size();i++)
		cout<<path2[i]->value<<" ";
	cout<<value2<<endl;
	return commmonNode(path1,path2);
}
int main()
{
	Node* root = init();
	Node* common = findLastCommon(root,'R','W');
	cout<<"Last Common Node:"<<common->value<<endl;
	return 0;
}
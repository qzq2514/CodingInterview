#include <iostream>
#include <stack>
using namespace std;
struct Node{
	Node(int value){
		this->value=value;
	}
	int value;
	Node * next;
};

void print(Node * head)
{
	Node *pNode=head;
	while(pNode!=NULL)
	{
		cout<<pNode->value<<" ";
		pNode=pNode->next;
	}
	cout<<endl;
}
void print_stack(Node * head)
{
	stack<Node*> nodes;               //栈的方式逆序打印链表(用vector实现也是同样效果)
	Node *pNode = head;
	while(pNode!=NULL)
	{
		nodes.push(pNode);
		pNode=pNode->next;
	}

	while(!nodes.empty())
	{
		cout<<nodes.top()->value<<" "; //栈.top()方法返回栈尾元素,不弹出
		nodes.pop();				   //栈.pop()方法弹出栈尾元素,不返回
	}
	cout<<endl;
}
void print_recursively(Node *head)   //递归方式逆序打印链表,不过当链表过长时,递归的方式会因为递归层数过深而产生栈溢出
{
	if(head ==NULL)
		return;
	if(head->next!=NULL)
		print_recursively(head->next);
	cout<<head->value<<" ";
}
Node *init()
{
	Node * n1=new Node(1);Node * n2=new Node(2);
	Node * n3=new Node(3);Node * n4=new Node(4);
	n1->next=n2;n2->next=n3;n3->next=n4;n4->next=NULL;
	return n1;
}
int main()
{
	Node *head=init();
	print(head);
	print_stack(head);
	print_recursively(head);
	return 0;
}
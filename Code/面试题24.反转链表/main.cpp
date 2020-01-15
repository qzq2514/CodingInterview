#include<iostream>
using namespace std;
struct Node
{
	Node(int value,Node* preNode)
	{
      this->value=value;
      this->next=NULL;
      if(preNode!=NULL)
      	 preNode->next=this;
	}
	int value;
	Node* next;
};
void print_list(Node *head)
{
	Node* pNode=head;
	while(pNode!=NULL)
	{
        cout<<pNode->value<<" ";
        pNode=pNode->next;
	}
	cout<<endl;
}
Node* init()
{
	Node* head=new Node(1,NULL);
	Node* node2=new Node(2,head);
	Node* node3=new Node(3,node2);
	Node* node4=new Node(4,node3);
	Node* node5=new Node(5,node4);
	Node* node6=new Node(6,node5);
	return head;
}
Node* reverse_list(Node* head)
{
	Node* preNode=NULL;
	Node* pNode=head;
	
	while(pNode!=NULL)
	{
		Node* nextNode=pNode->next;
		pNode->next=preNode;   //每次只改动当前节点的next指针,
							   //而不急着让原先pNode的下一个节点的next指针指向他,这个操作在下一个while循环中做
		if(nextNode==NULL)
			return pNode;
		preNode=pNode;         //这两句是为下一次循环做准备
		pNode=nextNode;
	}
	return NULL;

}
int main()
{
	Node* head=init();
	print_list(head);

	Node* reverse_head=reverse_list(head);
	print_list(reverse_head);
	return 0;
}






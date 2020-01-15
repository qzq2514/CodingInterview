#include<iostream>
using namespace std;
struct Node{

    Node(int value,Node *preNode)
    {
    	this->value=value;
    	if(preNode!=NULL)
    		preNode->next=this;
    }
	int value;
	Node *next;
};

void print_list(Node* head)
{
	Node *p=head;
	while(p!=NULL)
	{
		cout<<p->value<<" ";
		p=p->next;
	}
	cout<<endl;
}
Node* init()
{
	Node * head=new Node(1,NULL);
	Node * node2=new Node(2,head);
	Node * node3=new Node(3,node2);
	Node * node4=new Node(4,node3);
	Node * node5=new Node(5,node4);
	Node * node6=new Node(6,node5);
	node6->next=NULL;
	return head;
}
Node* get_last_k_node(Node *head,int k)
{
	if(head==NULL || k==0)
	   return NULL; 

	Node* first_node=head;
	Node* second_node=head;

	//第一个指针先走k-1步
	for(int i=1;i<=k-1;i++)
	{
		first_node=first_node->next;

		//如果走的步数小于等于k-1步,就已经到最后一个节点的next(也就是NULL),
		//那么说明整个链表的总长度是小于k个,那这时候返回NULL
		if(first_node==NULL)
			return NULL;
	}
	
	 //两个同时走
	 while(first_node->next!=NULL)
	 {
         first_node=first_node->next;
         second_node=second_node->next;
	 }

	return second_node;
}
int main()
{
	Node* head=init();
	print_list(head);
	int k=5;
	Node *last_k_node=get_last_k_node(head,k);
	if(last_k_node!=NULL)
	     cout<<"last "<<k<<" node : "<<last_k_node->value<<endl;
	 else
	 	cout<<"last "<<k<<" node : None"<<endl;
	return 0;
}
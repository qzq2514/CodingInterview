#include<iostream>
using namespace std;
struct Node{

	Node(int value,Node *parent)
	{
		this->value=value;
		if(parent!=NULL)
			parent->next = this;
		this->next=NULL;

	}
	int value;
	Node* next;
};


Node* init()
{
    Node* head=new Node(1,NULL);Node* n2=new Node(2,head);
    Node* n3=new Node(4,n2);Node* n4=new Node(5,n3);
    return head;
}
void print(Node* head)
{
	while(head)
	{
		cout<<head->value<<" ";
		head=head->next;
	}
	cout<<endl;
	// cout<<"--------------"<<endl;
}
Node* insert_tail(Node* head,int value)
{
     Node * new_node=new Node(value,NULL);
     new_node->next=NULL;

     if (head==NULL)
     	return new_node;

     Node * pNode=head;
     while(pNode->next!=NULL)      //向尾部插入值,没必要像再申请一个头结点h_head,只需要遍历到最后就行
     	pNode=pNode->next;         //当然如果要申请也是可以的,不多做介绍
     pNode->next=new_node;

     return head;
}
Node * insert_sort(Node *head,int value)
{
	Node * new_node=new Node(value,NULL);
	new_node->next=NULL;

	// if (head==NULL)
	// 	return new_node;
	
	Node * h_head=new Node(-1,NULL);
	h_head->next=head;              //专门新建一个头指针(值无限小),这样会比较统一,不然如果插在头部,还要先比较插入值和原头结点的值

	Node *pNode=h_head;
	while(pNode->next!=NULL && pNode->next->value <=value)
	  pNode=pNode->next;

	if (pNode->next==NULL)     //遍历到最后了,那么直接将新节点插到最后就行
		pNode->next=new_node;
	else                        //插到中间
	{
		new_node->next=pNode->next;
		pNode->next=new_node;
	}

	return h_head->next;
}
Node* delete_node(Node * head,int value)
{
	if(head==NULL)
		return head;

	Node * h_head=new Node(-1,NULL);
	h_head->next = head;

	Node *pNode=h_head;
	while(pNode->next != NULL && pNode->next->value != value)
		pNode = pNode->next;
	if(pNode->next!=NULL)    //如果没有遍历到最后,那么说明pNode->next->value就要删除的值,即要删除的节点是pNode->next
	{
		  cout<<"pNode->next!=NULL "<<pNode->value<<endl;
	      pNode->next=pNode->next->next;
	}
	//遍历到最后还找不到要删除的,那么说明不存在,直接返回原链表头结点就行 
	  return h_head->next;

}
int main()
{
	Node *head=init();
	print(head);

	head=insert_tail(head,3);
	print(head);

	Node *head_null=NULL;
	head_null=insert_tail(head_null,3);
	print(head_null);

	Node* head2=init();
	head2=insert_sort(head2,3);   //尝试插入0,3,9
	print(head2);   

	Node* head3=init();
	head3=delete_node(head3,5);   
	print(head3);   

	return 0;
}
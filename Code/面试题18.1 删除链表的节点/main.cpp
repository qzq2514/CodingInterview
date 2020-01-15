#include<iostream>
using namespace std;
//根据节点删除链表中该节点,不是根据值删除节点
struct Node{
   
   Node(int value,Node* parent)
   {
   	this->value=value;
   	if(parent!=NULL )
        parent->next=this;
   }
   int value;
   Node* next;
};
void print_list(Node* head)
{
	Node * p=head;
	while(p!=NULL)
	{
		cout<<p->value<<" ";
		p=p->next;
	}
	cout<<endl;
}
//方法1:顺序法,将找到要删除节点的前一个节点,复杂度:O(n)
Node* delete_node_s1(Node *head,Node *toBeDeletedNode)
{
	  if(head==NULL || toBeDeletedNode==NULL)
	  	return head;
      Node* my_head = new Node(-1,NULL);
      my_head->next=head;
      Node* p = my_head;

      while(p->next!=NULL && p->next!=toBeDeletedNode)
      	p=p->next;
      if(p->next != NULL)       //这时,必有p->next != NULL 且p->next=toBeDeletedNode
      	p->next=p->next->next;  //那么直接指向下一个就行
                                //若退出循环时p->next = NULL,则说明找到最后了还没找到要删除的值,
                                //那么不用进行任何改动
      return my_head->next;
}

//方法2:直接就找到要删除的节点,然后将其下一个节点的值赋值给该节点
//     再将该节点指向下下个节点,复杂度为O(1)
//这里假定要删除的节点是在链表中的
Node* delete_node_s2(Node *head,Node *toBeDeletedNode)
{
	if(head==NULL || toBeDeletedNode==NULL)
	  	return head;
	
	if(toBeDeletedNode->next!=NULL)  //要删除的节点不是最后一个
	{
		Node *p_next=toBeDeletedNode->next;
		toBeDeletedNode->value =p_next->value;
		toBeDeletedNode->next =p_next->next;

		delete p_next;
		p_next=NULL;
	}
	else if (head==toBeDeletedNode)  //要删除的节点是最后一个,但是整个链表也就一个节点
    {
    	head=NULL;
    	delete toBeDeletedNode;
    	toBeDeletedNode=NULL;
    }
    else                //要删除的节点是最后一个,但是整个链表不知一个节点
    {					//如果假设toBeDeletedNode前一个节点是f,虽然f->next=toBeDeletedNode,
    	                //但是直接将toBeDeletedNode=NULL并不能改变f->next,所以这里只能按顺序找到f节点,将f-next=NULL
             Node * f=head;
             while(f->next!=toBeDeletedNode)
             	f=f->next;
             f->next=NULL;
             delete toBeDeletedNode;
             toBeDeletedNode=NULL;
    }
	return head;
}
int main()
{
	Node* head=new Node(1,NULL);
	Node* node2=new Node(2,head);
	Node* node3=new Node(3,node2);
	Node* node4=new Node(4,node3);
	Node* node5=new Node(5,node4);
	Node* node6=new Node(6,node5);
	node6->next=NULL;
	Node* node7=new Node(7,NULL);   //定义一个不相关的节点

	print_list(head);
    Node * new_head=delete_node_s2(head,node6);
	print_list(new_head);

	return 0;
}
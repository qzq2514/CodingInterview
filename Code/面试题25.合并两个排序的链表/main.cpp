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
Node* init_odd()
{
	Node* head=new Node(1,NULL);
	Node* node3=new Node(3,head);
	Node* node5=new Node(5,node3);
	Node* node7=new Node(7,node5);
	Node* node9=new Node(9,node7);
	return head;
}
Node* init_even()
{
	Node* head=new Node(2,NULL);
	Node* node4=new Node(4,head);
	Node* node6=new Node(6,node4);
	Node* node8=new Node(8,node6);
	return head;
}

//递归方式
Node* merge_lists_recurse(Node* list1,Node* list2)
{
	if(list1==NULL)
	    return list2;
	if(list2==NULL)
	    return list1;
	Node* mergedHead=NULL;
	if(list1->value < list2->value)
	{
		//如果这里直接写成mergedHead=list1,那么会修改list1链表
		//所以要使用new新建节点,后面else中的list2是同样的
		mergedHead=new Node(list1->value,NULL);
		mergedHead->next=merge_lists_recurse(list1->next,list2);
	}
	else
	{
		mergedHead=new Node(list2->value,NULL);;
		mergedHead->next=merge_lists_recurse(list1,list2->next);
	}
	return mergedHead;
}
//非递归方式
Node* merge_lists_non_recurse(Node* list1,Node* list2)
{
	Node* myHead=new Node(-1,NULL); 
	Node* p1=list1;
	Node* p2=list2;
	Node* pp=myHead;
	while(p1!=NULL && p2!=NULL)
	{
       if(p1->value < p2->value)
       {
       	   pp->next=p1;
       	   p1=p1->next;
       }
       	else
	   {
       	   pp->next=p2;
       	   p2=p2->next;
       }
       pp=pp->next;
	}

	if(p1!=NULL)
		pp->next=p1;
	else
		pp->next=p2;
	return myHead->next;
}
int main()
{
	Node* odd_list=init_odd();
	Node* even_list=init_even();
	print_list(odd_list);
    print_list(even_list);

    Node* mergeHead_s1=merge_lists_recurse(odd_list,even_list);
    cout<<"merge_lists_recurse:"<<endl;
    print_list(mergeHead_s1);

    Node* mergeHead_s2=merge_lists_non_recurse(odd_list,even_list);
    cout<<"merge_lists_non_recurse:"<<endl;
    print_list(mergeHead_s2);
	return 0;
}










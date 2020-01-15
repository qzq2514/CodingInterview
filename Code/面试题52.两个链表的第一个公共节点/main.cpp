#include<iostream>
#include<stack>
using namespace std;

//查找两条单链表的第一个公共节点:
//因为是单链表,所以从第一个公共开始两个链表是完全重合的,这时候思考,如果能够同时从两条链表的结尾开始向前找,
//找到第一个不相同的节点,该节点的next就是要求的第一个公共节点

struct Node{
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

void print_list(Node* head)
{
    Node * p = head;
    while(p!=NULL)
    {
    	cout<<p->value<<" ";
    	p=p->next;
    } 
    cout<<endl;
}


void init(Node* head1,Node* head2)
{
	//公共部分:
	Node* common1=new Node(1,NULL);
	Node* common2=new Node(2,common1);
	Node* common3=new Node(3,common2);
	Node* common4=new Node(4,common3);

	Node* head1_2 = new Node(12,head1);
	Node* head1_3 = new Node(13,head1_2);
	Node* head1_4 = new Node(14,head1_3);
	Node* head1_5 = new Node(15,head1_4);
	Node* head1_6 = new Node(16,head1_5);
	head1_6->next = common1;               //注释这句话则两个链表没有公共部分,可直接运行查看结果

	Node* head2_2 = new Node(22,head2);
	Node* head2_3 = new Node(23,head2_2);
	head2_3->next = common1;
}

//思路1:使用栈
//因为想要从后向前找,但是单链表只能从前向后,所以基于这种"先进后处"的想法,
//使用站的结构分别保存两个链表的节点,如果当前两个栈的top相等的话,不断pop,就能找到第一个公共节点
stack<Node*> getNodesStack(Node* head)
{
	stack<Node*> nodes;
	Node * p = head;
    while(p!=NULL)
    {
    	nodes.push(p);
    	p=p->next;
    } 
    return nodes;
}
Node* get_firstCommonNode_s1(Node* head1,Node* head2)
{
    stack<Node*> nodes1=getNodesStack(head1);
    stack<Node*> nodes2=getNodesStack(head2);
    // cout<<nodes1.top()->value<<" "<<nodes2.top()->value<<endl;

	Node* result=NULL;
    while(!nodes1.empty() && !nodes2.empty() && nodes1.top()==nodes2.top())
    {
    	result = nodes1.top();
    	nodes1.pop();
    	nodes2.pop();
    }

    return result;
}

//思路1需要额外使用两个栈结构,其实基本思想是把两个链表的结尾对齐进行从后向前比较
//思路2:计算两条链表的长度差diff,然后让长的长的链表头先走diff步,如果长、短链表头同时同速度next的话,
//一定会同时到达各自的尾部,其实就达到了尾对齐的目的
//这时则同时同速度next,找到第一个相同的节点就是第一个公共节点
int get_list_length(Node*head)
{
	int len=0;
	Node * p = head;
    while(p!=NULL)
    {
    	len++;
    	p=p->next;
    } 
    return len;
}
Node* get_firstCommonNode_s2(Node* head1,Node* head2)
{
     Node* result=NULL;
     int len1 = get_list_length(head1);
     int len2 = get_list_length(head2);

     // if(len1>len2)
     // 	swap(head1,head2);      //这样直接交换会修改原链表,不建议

     Node* longHead;
     Node* shortHead;
     int diff = 0;
     if(len1>len2){
     	longHead=head1;
     	shortHead=head2;
     	diff = len1-len2;
     }
     else{
		longHead=head2;
     	shortHead=head1;
     	diff = len2-len1;
     }

     for(int i=0;i<diff;i++)
     	longHead = longHead->next;

     while(longHead!=NULL && shortHead!=NULL && longHead->value!=shortHead->value)
     {
     	longHead = longHead->next;
     	shortHead = shortHead->next;
     }
     result = longHead;
     return result;
}
int main()
{
	Node* head1=new Node(11,NULL);
	Node* head2=new Node(21,NULL);
	init(head1,head2);
	cout<<"List1:";print_list(head1);
    cout<<"List2:";print_list(head2);

	Node* firstCommonNode_s1=get_firstCommonNode_s1(head1,head2);
	cout<<"First common node:";
	if(firstCommonNode_s1==NULL)
		cout<<"None"<<endl;
    else
    	cout<<firstCommonNode_s1->value<<endl;

    Node* firstCommonNode_s2=get_firstCommonNode_s2(head1,head2);
    cout<<"First common node:";
	if(firstCommonNode_s2==NULL)
		cout<<"None"<<endl;
    else
    	cout<<firstCommonNode_s2->value<<endl;

	return 0;
}





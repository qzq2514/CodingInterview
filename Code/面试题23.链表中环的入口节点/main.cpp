#include<iostream>
using namespace std;
 
struct Node{
	Node(int value,Node* parent)
	{
		this->value=value;
		this->next=NULL;
		if(parent!=NULL)
			parent->next=this;
	 } 
	Node * next;
	int value;
};

bool check_circle(Node *head)
{
	Node *fast=head;
	Node *slow=head;
	while(fast && fast->next)   //因为fast走得比slow快,所以只需要判断fast和fast-next是不是空就行 
	{                           //而不能使用while(slow->next && fast->next->next)判断,因为连用fast->next->next就跨步了
		fast=fast->next->next;
		slow=slow->next;
		if(fast==slow)
		   return true;
	}
	return false;
}
 
int get_loop_length(Node * head )
{
	if (!check_circle(head))
	   return 0;
	   
	int loop_length=0;
	Node *fast=head;
	Node *slow=head;
	bool is_first_meeted=false;
	while(fast && fast->next)  
	{                           
		fast=fast->next->next;
		slow=slow->next;
		
		if(fast==slow)
		{
			if(is_first_meeted)         //有环时,当第一次相遇后,开始计数,一直到再次相遇,快指针比慢指针夺走了一圈,走得步数s就是环的长度 
		      break;                 //因为走得步数s就是慢指针走得步数s,而快指针走了2s, 相差的步数s正好是快指针比慢指针多走的步数，就是环的一圈 
			else
		       	is_first_meeted=true;
		}
		    
		if (is_first_meeted)
		  loop_length++;
	}
	return loop_length;
}
 
//方法一:不显示获得链表环的长度.
Node * get_entrance_s1(Node *head)
{
	Node *fast=head;
	Node *slow=head;
	bool is_find_circle=false;
	//先判断链表是否有环
	while(fast && fast->next)  
	{                          
		fast=fast->next->next;
		slow=slow->next;
		if(fast==slow)
		{
			is_find_circle=true;
			break;
		}
	}
    if(!is_find_circle) return NULL;
    //存在环时,到这一步,快慢指针是在相同位置的,这时可以计算出快慢指针走的步数之差是环长度的整数倍,
    //具体为:假设起点到环入口距离为m,环长度为n
    //快指针走的步数:   2s=m+A*n+k(不一定就在环入口相遇,所以加上k),
    //慢指针走的步数为: s=m+B*n+k(在圈很大的时候,也有可能慢指针绕了好几圈才和快指针相遇),
    //所以两者走的步数差为: 2s-s=s=(A-B)*n这时候将慢指针移动到头结点位置
    //然后快慢指针同样的速度一步一步向前走,当慢指针走了m步走到环入口时,快指针从最一开始走了m+2s步,
    //因为s是环长度的整倍数,那么久可以判定此时快指针也在环入口了，即此时快指针和慢指针在环入口相遇了

    //简单点,就是快慢指针第一次相遇后,将慢指针移动到头结点,然后两个指针同速度前进,下一次相遇的地点就是入口处
    slow=head;
    while(slow!=fast)
    {
    	slow=slow->next;
    	fast=fast->next;
	}
	return slow;
}

//方法二:先获得链表环长度,再计算链表环入口
//其实这就是方法一在A-B=1时的特殊情况,即只让快指针多走一圈
Node * get_entrance_s2(Node * head)
{
	if (!check_circle(head))
	   return NULL;

	int loop_len=get_loop_length(head);
	Node *fast=head;
	Node *slow=head;

	for (int i=0;i<loop_len;i++)
       fast=fast->next;

    while(fast!=slow)
    {
    	fast=fast->next;
    	slow=slow->next;

    }
    return fast;
}

Node * init()
{
	//1->2->3->4->5->2
	Node *head=new Node(1,NULL); Node *n2=new Node(2,head);
	Node *n3=new Node(3,n2); Node *n4=new Node(4,n3);
	Node *n5=new Node(5,n4);
    n5->next=n2;
	
	return head;
}
int main()
{
	Node * head=init();
	bool have_loop=check_circle(head);
	int loop_length=get_loop_length(head);
	Node *entrance_s1=get_entrance_s1(head);
	Node *entrance_s2=get_entrance_s2(head);
	cout<<"have_loop:"<<have_loop<<"   looop_length:"<<loop_length<<endl;
	cout<<"entrance:\ns1:"<<entrance_s1->value<<"  s2:"<<entrance_s2->value<<endl;
	return 0;
 } 
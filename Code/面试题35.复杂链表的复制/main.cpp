#include<iostream>
#include<string.h>
using namespace std;
struct Node
{
	Node(string value,Node* preNode)
	{
		this->value=value;
		this->next=NULL;
		this->sibling=NULL;
		if(preNode!=NULL)
			preNode->next=this;
	}

	string value;
	Node* next;
	Node* sibling;
};

Node* init()
{
	Node* A = new Node("A",NULL);
	Node* B = new Node("B",A);
	Node* C = new Node("C",B);
	Node* D = new Node("D",C);
	Node* E = new Node("E",D);
	A->sibling=C;
	B->sibling=E;
	D->sibling=B;
	return A;
}

void print_list(Node* head)
{
	Node* p = head;
	while(p!=NULL)
	{
		string siblingStr="NULL";
		if (p->sibling!=NULL)
			siblingStr=p->sibling->value;
		cout<<p->value<<"("<<siblingStr<<")";
		if(p->next!=NULL)
			cout<<"->";
		p=p->next;
	}
	cout<<endl;
}

//在原链表的基础上,每个节点复制一份并插到该接地那后面(不复制sibling)
Node* cloneNodes(Node* head)
{
	Node* p = head;
	while(p!=NULL)
	{
		//新建和当前节点p一样的节点并插入到当前节点后面(除了sibling节点其他都一样),这里用原节点的double形式表示复制节点,用于区分(即A复制为AA)
		Node* pCloned = new Node(p->value+p->value,NULL);   
		pCloned->next = p->next;              
        p->next = pCloned;
        p = pCloned->next;     //指向链表下一个节点开始复制
	}
	return head;
}
// 对每个复制的节点的sibling属性进行赋值,这时候才相当于将原始链表完全复制了一份
// 并每个节点放在对应节点的后面,形成原链表长度两倍的长链表
Node* assignSibing(Node* head)
{
	Node* p = head;
	while(p!=NULL)
	{
		Node* clonedNode = p->next;
		if(p->sibling!=NULL)
			clonedNode->sibling = p->sibling->next;   //核心语句
		p = clonedNode->next;
	}
	return head;
}
//从长链表中抽取复制的节点(其实就是编号为偶数的节点(下标从1开始))
Node* extractClonedNodes1(Node* head)
{
    Node* p = head;
    Node* clonedHead = NULL;
    Node* pCloned = NULL; 

    if(p!=NULL)
    {
    	clonedHead = pCloned = p->next;
    	p->next =  pCloned->next;   //在抽取复制的节点时,最好也要保证原链表恢复,所以要加上这句话
    	p = pCloned->next;
    }
    while(p!=NULL)
    {
    	pCloned->next = p->next;
    	pCloned = pCloned->next;
    	p->next =  pCloned->next;  //同上理,该句保证原链表的恢复
    	p = pCloned->next;
    }
    print_list(head);      //查看原链表情况
    return clonedHead;
}
int main()
{
	Node* head=init();
	cout<<"org: ";print_list(head);
	head=cloneNodes(head);
	cout<<"cloneNodes: ";print_list(head);
	head=assignSibing(head);
	cout<<"assignSibing: ";print_list(head);
	head=extractClonedNodes1(head);
	cout<<"extractClonedNodes: ";print_list(head);
	return 0;
}
#include<iostream>
using namespace std;
//删除所有
struct Node{

	Node(int value,Node* preNode)
	{
        this->value=value;
        if(preNode!=NULL)
        	preNode->next=this;
	}
	int value;
    Node *next;
};
Node* init()
{
	Node* head=new Node(1,NULL);
	Node* node2=new Node(2,head);
	Node* node22=new Node(2,node2);
	Node* node3=new Node(3,node22);
	Node* node33=new Node(3,node3);
	Node* node333=new Node(3,node33);
	Node* node4=new Node(4,node333);
	Node* node5=new Node(5,node4);
	Node* node55=new Node(5,node5);
	node55->next=NULL;
	return head;
}
void print_list(Node* head)
{
    Node* p=head;
    while(p!=NULL)
    {
    	cout<<p->value<<" ";
    	p=p->next;
    }
    cout<<endl;
}
//会将所有重复的全部删除,不会重复的中保留一个
//eg:1 2 2 3 3 3 4 5 5 -> 1 4
Node* deleteDuplicate(Node *head)
{
	if(head==NULL)
		return NULL;
	Node* my_head = new Node(-1,NULL);
	my_head->next = head;    //因为头结点也可能被删除,所以最好定义一个初始头结点

	Node* pNode=head;
	Node* preNode=my_head;    //要记录当前遍历到的节点的前一个节点

	while(pNode!=NULL)
	{
       Node * nextNode=pNode->next;
       bool isDuplicate=false;
       if (nextNode!=NULL && nextNode->value==pNode->value)
       	isDuplicate=true;

       if(!isDuplicate) //当前节点和其后面的节点值还不重复,则继续向后遍历
       {
       	   preNode = pNode;
           pNode = pNode->next;
       }
       else           //重复了,开始删除
       {
           int duplicateValue=pNode->value;
           Node* toBeDeleteNode=pNode;   //初始指向当前重复的第一个节点

           while(toBeDeleteNode!=NULL && toBeDeleteNode->value==duplicateValue)
           {
           	 nextNode=toBeDeleteNode->next;
           	 delete toBeDeleteNode;     //这步和下一步是用于删除重复节点空间
           	 toBeDeleteNode=NULL;
           	 toBeDeleteNode=nextNode;    //指向下一个节点,继续判断继续删除
           }

           //这时候的nextNode要么指向开始不重复的节点,要么可能已经遍历到最后了(nextNode==NULL)
           
       	 //这时候就体现了preNode的作用,preNode一直指向最终保留的链表的最后一个
       	 //比如在链表“1 2 2 3 3 3 4 5 5 ”中,当pNode遍历到重复的2和3后,preNode->next一直指向的是1,这时候nextNode指向4,连起来就行
       	 //虽然在遍历完2后,preNode->next会指向第一个3,但是后面会被再覆盖掉
          preNode->next=nextNode;     
          pNode = nextNode;
       }
	}
	return my_head->next;
}

//每个重复的元素保留一个
//eg:1 2 2 3 3 3 4 5 5 -> 1 2 3 4 5
Node* deleteDuplicate_left(Node *head)
{
	if(head==NULL)
		return NULL;
	
  //即便重复,头结点肯定不会被删除,但是便于统一性,还是自定义一个头结点
  Node* my_head = new Node(-1,NULL);
  my_head->next = head;    

	Node* cur_last_node=my_head;
  Node* pNode=head;  

	while(pNode!=NULL)
	{
       Node * nextNode=pNode->next;
       bool isDuplicate=false;

       cur_last_node->next = pNode;   //每组保留第一个数(重复为一组)
       cur_last_node=pNode; 

       if (nextNode!=NULL && nextNode->value==pNode->value)//重复了,开始删除
       {
           int duplicateValue=pNode->value;
           Node* toBeDeleteNode=pNode->next;   //从重复的下一个节点开始删除
           while(toBeDeleteNode!=NULL && toBeDeleteNode->value==duplicateValue)
           {
           	 nextNode=toBeDeleteNode->next;
            	 delete toBeDeleteNode;     //这步和下一步是用于删除重复节点空间
               toBeDeleteNode=NULL;
           	 toBeDeleteNode=nextNode;    //指向下一个节点,继续判断继续删除
           }

           //注意这里一定要添加这句,因为虽然到最后这里nextNode为NULL,即下一步pNode被赋值为NULL
           //虽然之前cur_last_node->next=pNode,但是修改pNode并不会改动cur_last_node->next
           //比如最后是5 5,这时候之前cur_last_node->next=pNode(第一个5),但是pNode = nextNode后变成NULL
           //就直接退出最外层while了,就导致第二个也被保留下来了(即cur_last_node->next->next->value=5)          
           cur_last_node->next=nextNode;
       }
       pNode = nextNode;
	}
	return my_head->next;
}
int main()
{
	Node* head1=init();
	cout<<"删除前(不保留):";print_list(head1);
	head1=deleteDuplicate(head1);
	cout<<"删除后(不保留):";print_list(head1);
  head1=deleteDuplicate(head1);
  cout<<"再次删除后(不保留):";print_list(head1);

	Node* head2=init();
	cout<<"删除前(保留):";print_list(head2);
	head2=deleteDuplicate_left(head2);
	cout<<"删除后(保留):";print_list(head2);
  head2=deleteDuplicate(head2);
  cout<<"再次删除后(保留):";print_list(head2);


  cout<<"-----------------------"<<endl;
  //测试:
  Node *node1=new Node(1,NULL);
  node1->next=NULL;
  Node *node2=node1;  

  cout<<"org: node1:"<<node1->value<<endl;
  cout<<"org: node2:"<<node2->value<<endl;
  node1->value=10;   

  //node1,node2指向同一块内存,改变其中一个的属性(value或者next)会影响另一个
  cout<<"case1: node1:"<<node1->value<<endl;
  cout<<"case1: node2:"<<node2->value<<endl;

  Node *node3=new Node(3,NULL);
  node2=node3;            //将node2重新指向另一个内存

  //node1,node2不指向同一块内存,改变其中一个不会影响另一个
  cout<<"case2: node1:"<<node1->value<<endl;
  cout<<"case2: node2:"<<node2->value<<endl;

	return 0;
}
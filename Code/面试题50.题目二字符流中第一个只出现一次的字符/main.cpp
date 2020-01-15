#include<iostream>
#include<sstream>
#include<memory.h>
#include<limits.h>
using namespace std;
class charCalu{
public:charCalu(){
			index=0;     
			str<<"";
			memset(occurrence,-1,sizeof(occurrence));  
		}

		string insert(char ch)
		{
			if(occurrence[ch]==-1)   
			  occurrence[ch]=++index;
			else if(occurrence[ch]>0)
				occurrence[ch]=-2;     
			str<<ch;

			return str.str();
		}

		char firstAppearingChar()
		{
			char res='\0';
			int minIndex = numeric_limits<int>::max();
			for(int i=0;i<256;i++)
			{
				if(occurrence[i]>0 && occurrence[i]<minIndex)
				{
					minIndex=occurrence[i];
					res=char(i);
				}
			}
			return res;
		}
private:
//occurrence[i]=-1  未出现过
//occurrence[i]=-2  出现过不止一次
//occurrence[i]>0   仅出现过一次,occurrence[i]就是这一次出现的下标(从1开始)
int occurrence[256];
int index;
stringstream str;
};


//自己思考的方法二:
//使用链表的方式存放目前字符流中只出现一次的字符,每次insert时候,如果occurrence[-1]==-1那么插入链表尾部
//如果occurrence[-1]>0那么从链表中删除该字符
//最终返回链表头部即可得到第一次出现的字符,这时firstAppearingChar函数是O(1)复杂度,但是insert中可能有链表表删除操作
//所以insert的时间复杂度为O(n)
struct Node
{
	Node(char ch)
	{
		this->value=ch;
		this->next=NULL;
	}
	char value;
	Node* next;
};
class charCaluMy{
public:charCaluMy(){
			index=0;     
			str<<"";
			memset(occurrence,-1,sizeof(occurrence));  
			head = new Node('\0');
			// cout<<"charCaluMy"<<endl;
			// print_list();
			// head->next = tail;
		}

		string insert(char ch)
		{
			if(occurrence[ch]==-1)      //新字符,直接在尾部插入即可 
			{
				occurrence[ch]=1;
				Node *pNew = new Node(ch);
				Node *pNode = head;
				while(pNode->next!=NULL)
					pNode=pNode->next;
				pNode->next=pNew;
			} 
			else if(occurrence[ch]==1)  //已经出现的字符,在链表中删除
			{

				Node* pNode = head;
				while(pNode->next!=NULL && pNode->next->value != ch)
				{
					pNode=pNode->next;
				}
				if(pNode->next!=NULL)
					pNode->next=pNode->next->next;
				occurrence[ch]=2;        //这最好将occurrence[ch]置为2,防止后面再出现(第三次出现)字符ch的时候,没必要再在链表中查找删除
			}
			str<<ch;
			return str.str();
		}

		void print_list()
		{
			cout<<"print_list:"<<endl;
			Node *pNode = head;
			while(pNode != NULL)
			{
				cout<<pNode->value<<" ";
				pNode = pNode->next;
			}
			cout<<endl;
		}
		char firstAppearingChar()
		{
			if(head->next==NULL)
				return '\0';
			return head->next->value;
		}
private:
	int occurrence[256];
	int index;
	stringstream str;
	Node* head;
};

int main()
{
	charCaluMy char_calu;
	char chars[] = "google";
	char *p = chars;
	while(*p!='\0')
	{
		string str = char_calu.insert(*p);
		cout<<str<<" : "<<char_calu.firstAppearingChar()<<endl;
		p++;
	}
	return 0;
}
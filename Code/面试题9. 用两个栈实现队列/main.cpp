#include<iostream>
#include<stack>
using namespace std;


class myQueue{

public:
	 void push(int value)
	 {
        stack1.push(value);       
	 }

	 int get_head()
	 {
	 	if(stack2.empty())     //从stack2顶部弹出,如果stack2为空,则一次性将stack1全部依次弹出并压入栈stack2
	 	{
            while(!stack1.empty())
            {
            	int temp=stack1.top();
            	stack1.pop();
            	stack2.push(temp);
            }
	 	}
	 	if(stack2.empty())   
	 		return -1;       //假定栈中元素全部是非负整数,这里弹出-1表示已经空了,还要弹出,表示异常
	 	int value=stack2.top();
	 	stack2.pop();
	 	return value;
	 }
private:
     stack<int> stack1;       //stack1用于存数据
     stack<int> stack2;       //从stack1弹出数据到stack2,stack2顶部是最先入栈stack1,也是在队列中最先被弹出的

};
int main()
{
	myQueue my_queue; 
	my_queue.push(1);     //1
	my_queue.push(2);     //1,2
	my_queue.push(3);     //1,2,3
	my_queue.push(4);     //1,2,3,4
	cout<<my_queue.get_head()<<endl; //输出1,还剩2,3,4
	my_queue.push(5);     //2,3,4,5
	cout<<my_queue.get_head()<<endl; //输出2,还剩3,4,5
	cout<<my_queue.get_head()<<endl; //输出3,还剩4,5
	cout<<my_queue.get_head()<<endl; //输出4,还剩5
	cout<<my_queue.get_head()<<endl; //输出5,空
	cout<<my_queue.get_head()<<endl; //异常


	return 0;
}
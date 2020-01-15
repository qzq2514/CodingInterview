#include<iostream>
#include<queue>
using namespace std;


//用两个栈实现队列可以参考main_myQueue.cpp,因为两个栈相当于"负负得正",最后先进的可以先出
//但是两个队列相当于两个正,没办法正正得负,就不能用类似main_myQueue.cpp的那一套

//主要思想:
//保证一个队列是空,一个队列非空,插入时插到非空的队列
//弹出时,将非空队列中元素除了队尾的元素其余全部都依次添加到另一个空队列中,然后弹出那个原来非空队列最后一个元素就行

//其实就是相当于队列最后的进入的元素在队尾,而在整体的栈中是最先被弹出的.
class myStack{

public:
	 void push(int value)
	 {
	 	if(!queue1.empty())
          queue1.push(value);       
        else
          queue2.push(value);
	 }

	 int pop()
	 {
	 	int value=-1;
	 	if(queue1.empty() && queue2.empty())
	 		return value;

	 	if(!queue1.empty())
	 	{
	 		while(queue1.size()>1)
	 		{
	 			int temp=queue1.front();
	 			queue1.pop();
	 			queue2.push(temp);
	 		}
	 		value=queue1.front();
	 		queue1.pop();
	 	}
	 	else                                     //if和else内基本一致,还可以进一步简洁代码....
	 	{
	 		while(queue2.size()>1)
	 		{
	 			int temp=queue2.front();
	 			queue2.pop();
	 			queue1.push(temp);
	 		}
	 		value=queue2.front();
	 		queue2.pop();
	 	}

	 	return value;
	 }
private:
     queue<int> queue1;       
     queue<int> queue2;       

};
int main()
{
	myStack my_stack; 
	my_stack.push(1);     //1
	my_stack.push(2);     //1,2
	my_stack.push(3);     //1,2,3
	my_stack.push(4);     //1,2,3,4
	cout<<my_stack.pop()<<endl; //输出1,还剩2,3,4
	my_stack.push(5);     //2,3,4,5
	cout<<my_stack.pop()<<endl; //输出2,还剩3,4,5
	cout<<my_stack.pop()<<endl; //输出3,还剩4,5
	cout<<my_stack.pop()<<endl; //输出4,还剩5
	cout<<my_stack.pop()<<endl; //输出5,空
	cout<<my_stack.pop()<<endl; //异常


	return 0;
}
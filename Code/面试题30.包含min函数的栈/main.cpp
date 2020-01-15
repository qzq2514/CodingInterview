#include<iostream>
#include<stack>
using namespace std;

//自定义一个栈结构,在保证栈的结构(后进先出)的前提下能够以O(1)时间复杂度得到当前栈的最小值
//使用一个辅助栈和数据栈,辅助栈和数据栈同步,辅助栈中每个元素相当于记录数据栈中从栈底到当前位置的最小值

class myStack{
public:
	myStack(int* arr,int len)
	{
		for(int i=0;i<len;i++)
		{
			this->push(arr[i]);
		}
	}
   	void push(int value)
    {
		data_stack.push(value);

		if (aid_stack.empty() || value<aid_stack.top())
			aid_stack.push(value);
		else
			aid_stack.push(aid_stack.top());
    }
    void pop()
    {
    	data_stack.pop();
    	aid_stack.pop();
    }
    int top()
    {
    	return data_stack.top();
    }
    int min()
    {
    	return aid_stack.top();
    }
private:
	stack<int> data_stack;
	stack<int> aid_stack;
};
int main()
{
    int arr[]={7,4,5,3,6,1,8};
    myStack my_stack(arr,7);
    cout<<"min:"<<my_stack.min()<<endl;

    my_stack.pop();
    cout<<"min:"<<my_stack.min()<<endl;

    my_stack.pop();
    cout<<"min:"<<my_stack.min()<<endl;

    my_stack.push(2);
    cout<<"min:"<<my_stack.min()<<endl;
    cout<<"top:"<<my_stack.top()<<endl;
	return 0;
}
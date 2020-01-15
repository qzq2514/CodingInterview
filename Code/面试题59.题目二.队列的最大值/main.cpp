#include<iostream>
#include<deque>
#include<memory>
using namespace std;
class QueueWithMax{

//实现带max功能的队列:窗口机制
//复习:实现带max功能的栈:增加辅助栈,辅助中每个元素为从对应数据栈中元素到栈底的最大元素
public:
	QueueWithMax():currentIndex(0)
	{

	}
	void push_back(int number){
		while(!maximums.empty() && number>=maximums.back().number)
			maximums.pop_back();
		//相当于记录两种情况下的候选最大值:
		//1.初始化插入第一个元素到插入当前元素这一过程中的候选最大值
		//2.从上一个弹出元素到插入当前元素这一过程中的候选最大值
		//其实就是当前队列中的最大值候选集合
		InerData inerData = {number,currentIndex};
		maximums.push_back(inerData);
		data.push_back(inerData);
		currentIndex++;
	}

	void pop_front(){
		//也可以throw new exception
		if (maximums.empty())
			return ;  
		//如果当前弹出的队首元素(data.front())是当前最大值候选集合的队首元素,那么其后面肯定不
		//会成为data队列中剩下元素的候选最大值。(因为插入元素可能重复,所以用下标进行比较)
		//当前待删除的其肯定不会是maximums的非队首元素,证明:
		//假设front=data.front().number; maybeMax = maximums.front().number
		//因为front是在data队首,且那么其肯定是比maybeMax先插入data中的,所以在插入maybeMax时,肯定会清除maximums中的保存的front
		//因为由13行可知,每向maximums中插入一个元素,都会从后端开始删除小于等于该数的元素,保证maximums是按照元素的number降序保存.
		if(maximums.front().index == data.front().index)
		   maximums.pop_front();
		data.pop_front();
    }

    int front(){
		if (data.empty())
			return -1;  
		return data.front().number;
    }

	//因为在向maximums最大值候选元素时已经保证了降序(13行的while),
	//所以maximums队首就是最大值
    int max(){
    	if (maximums.empty())
			return -1; 
		return maximums.front().number;
    }

private:
	struct InerData{
		int number;   //默认都是非负数
		int index;
	};
	deque<InerData> maximums;
	deque<InerData> data;
	int currentIndex;
};

void printMyQueue(QueueWithMax myQueue)
{
	QueueWithMax temp = myQueue;   //拷贝赋值函数
	while(temp.front()!=-1)
	{
		cout<<temp.front()<<" ";
		temp.pop_front();
	}
	cout<<"  max:"<<myQueue.max()<<endl;
}
int main()
{
	QueueWithMax myQueue;
	myQueue.push_back(8);
	myQueue.push_back(5);
	printMyQueue(myQueue);
	myQueue.push_back(0);
	myQueue.push_back(3);
	myQueue.push_back(7);
	printMyQueue(myQueue);
	myQueue.pop_front();
	printMyQueue(myQueue);
	myQueue.pop_front();
	printMyQueue(myQueue);
	myQueue.push_back(9);
	myQueue.push_back(6);
	printMyQueue(myQueue);

	return 0;
}
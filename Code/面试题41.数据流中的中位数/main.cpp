# include <iostream>
# include <vector>

using namespace std;

//找数据流中的中位数基本思想:
//即最大堆中存放数据流中较小的一半元素,最大堆中存放数据流中较大的一般元素,那么最大堆堆顶和最小堆堆顶就是数据库的中位数

//基本实现:
//定义两个堆,一个最大堆,一个最小堆,保证"最大堆元素都小于等于最小堆元素"(也就是最大堆堆顶小于等于最小堆堆顶,保证1)
//然后每次从数据流中取值后,交替将值插入最小堆和最大堆,即保证"最小堆元素数目比最大堆元素数目最多不超过1个"(保证2),
//但是如果交替时本应该是插入最小堆,但是不巧的是该值小于最大堆堆顶,那么按照保证1,就应该插入最大堆,同时为了保证2,
//那么就弹出当前最大堆堆顶并将其插入最小堆,然后再将当前的值插入最大堆;
//反之如果交替时本应该是插入最大堆,但是不巧的是该值大于最小堆堆顶,亦然。

class MediumSelector
{
public:
     MediumSelector()
     {
     	//因为一开始最大堆和最小堆都是空的,所以这里不make_heap也是可以的
        // make_heap(max_heap.begin(),max_heap.end(),less<int>());
        // make_heap(min_heap.begin(),min_heap.end(),greater<int>());
     }
     void insert(int num)
     {
           if(((max_heap.size()+min_heap.size()) & 1)==0)   //目前一共处理了偶数个话,则往最小堆里添加数字
           {
                  if(max_heap.size()>0 && num<max_heap[0])
                  {
                      max_heap.push_back(num);
                      //往最大堆里面添加数字,注意第三个参数less<int>()要填上,不然默认最小堆,会出问题
                      push_heap(max_heap.begin(),max_heap.end(),less<int>());  

                      //取出最大堆堆顶,后面要插入最小堆
                      num = max_heap[0];

                      //从最大堆中弹出堆顶
                      pop_heap(max_heap.begin(),max_heap.end(),less<int>());  
                      max_heap.pop_back();
                  }
                  min_heap.push_back(num);
                  push_heap(min_heap.begin(),min_heap.end(),greater<int>());//同样最小堆要有greater<int>()参数,不然也会出问题
           }
           else
           {
                if(min_heap.size()>0 && num>min_heap[0])
                  {
                      min_heap.push_back(num);
                      push_heap(min_heap.begin(),min_heap.end(),greater<int>());  
                      num = min_heap[0];
                      pop_heap(min_heap.begin(),min_heap.end(),greater<int>());  
                      min_heap.pop_back();
                  }
                  max_heap.push_back(num);
                  push_heap(max_heap.begin(),max_heap.end(),less<int>());//同样最小堆要有greater<int>()参数,不然也会出问题
           }
     }

     float getMedium()
     {
        int sizeAll = max_heap.size()+min_heap.size();
        if(sizeAll == 0)
            return -1;

        if((sizeAll&1)==0)     //偶数个,那么取两个堆顶平均值
            return (min_heap[0]+max_heap[0])/2.0;
            
        else                //因为总个数是奇数,因为先向最小堆添加,所以这时最小堆比最大堆多一个数
            return min_heap[0];

     }
private:
    vector<int> max_heap;
    vector<int> min_heap;
};
void printVec(vector<int> nums)
{
    for (int i = 0; i < nums.size(); ++i)
        cout << nums[i] << " ";
    cout << endl;
}
int main(void)
{

    MediumSelector * s=new MediumSelector();
    s->insert(8);s->insert(3);
    s->insert(4);s->insert(7);
    s->insert(9);s->insert(2);
    s->insert(3);s->insert(4);
    s->insert(10);//s->insert(1);

    cout<<"Medium: "<<s->getMedium()<<endl;
}
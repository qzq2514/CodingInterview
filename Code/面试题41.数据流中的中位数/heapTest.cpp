# include <iostream>
# include <vector>

using namespace std;

//使用vector存放堆,但是要注意的是,最大堆(最小堆)只能保证容器的第一个元素是最大(最小)的,
//而不能说保证整个容器都是降序(升序)的,但是可以使用push_heap和pop_heap等保证在添加和删除元素后,
//最大堆(最小堆)的第一个元素一直是最大(最小)的

//插入元素时, 要先将元素push_back到容器中,然后push_heap
//删除元素时, 要先pop_heap把堆顶放在容器最后,再pop_back
void printVec(vector<int> nums)
{
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
    cout << endl;
}
int main(void)
{
    int nums_temp[] = {8, 3, 4, 8, 9, 2, 3, 4, 7};
    vector<int> nums(nums_temp, nums_temp + 9);
    cout<<"org:     ";printVec(nums);

    //make_heap默认第三个参数为less<int>,即最大堆
    //在vector不为空的时候,一定要先make_heap,不然后面的push_heap和pop_heap都无效
    make_heap(nums.begin(), nums.end());
    cout<<"max_heap:";printVec(nums);

    //显式定义最大堆
    make_heap(nums.begin(), nums.end(), less<int> ());
    cout<<"max_heap:";printVec(nums);

    //显式定义最小堆,即第三个参数为greater<int>
    make_heap(nums.begin(), nums.end(), greater<int> ());
    cout<<"min_heap:";printVec(nums);

    //向当前最小堆添加一个数,这时候只是添加到vector最后了,但此时vector中还不是最小堆的形式
    nums.push_back(3);
    //要使用push_heap函数将添加后的vector依然保证是最小堆的形式,但是要注意,因为push_heap
    //和make_heap一样默认都是最大堆,而当前nums是最小堆,所以下面的push_heap是有问题的
    push_heap(nums.begin(), nums.end());
    cout<<"push(3): ";printVec(nums);
    //要显示的告诉是向最小堆中添加数字,即push_heap第三个参数要赋值为greater<int>(),才会真正添加成功
    push_heap(nums.begin(), nums.end(), greater<int>());
    cout<<"push(3): ";printVec(nums);

    //把最小堆的堆顶弹出,注意同样要告诉当前是最大堆还是最小堆
    //pop_heap只会把最小堆的堆顶,即nums[0]放在vector的最后一个位置
    pop_heap(nums.begin(), nums.end(),greater<int>());
    cout << "pop_back(): ";printVec(nums);

    //然后再pop_back才会真正地将原堆顶弹出
    nums.pop_back();
    cout << "pop_back(): "; printVec(nums);
}
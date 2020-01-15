#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;
struct Node
{
	Node(int value,Node* left,Node* right)
	{
       this->value=value;
       this->left=left;
       this->right=right;
	}
	int value;
	Node* left;
	Node* right;

};

void preOrder(Node* root)
{
	if(root==NULL)
		return;
	   
	preOrder(root->left);
	cout<<root->value<<" ";
	preOrder(root->right);
}


//squence:当前有效序列,end:当前有效序列的最后一个元素下标(end+1是有效序列长度)
Node* reBuildBSTFromSquence(int* squence,int end,bool &isValid)
{
    if(squence==NULL || end<0)
    	return NULL;
    Node* root=new Node(squence[end],NULL,NULL);

    //在下标0~end-1范围(排除最后一个元素是根节点)找到第一个大于根节点的元素下标,
    //从此往后,都为右子树,
    //若除最后一个全小于根节点,此时ind=ind2=end,即剩下全是左子树,
    //而后面则左子树有效序列是从squence到squence+ind-1,符合,右子树从squence+ind~ind2-ind-1,最后一个下标ind2-ind-1=-1,到下一层循环会返回NULL,符合
    //若除最后一个全大于根节点,此时ind=0,ind2=end,即剩下全是右子树,
    //而后面则左子树有效序列是从squence到squence+ind-1,最后一个下标ind-1=-1,到下一层循环会返回NULL,符合,右子树从squence+0~ind2-ind-1(=end-1),符合
    //真正像此题,写代码的时候,不用考虑边界太复杂情况,在考虑好中间情况后,会自动把边界情况包括进去

    //不要用upper_bound,因为upper_bound包括lower_bound都在排序好的数组中有效
    // int ind=upper_bound(squence,squence+end,squence[end])-squence;
    int ind=0;
    for (;ind<end;ind++)
    {
    	if (squence[ind]>squence[end])
    		break;
    }

    int ind2=ind;

    //判断ind后面是不是都是大于root,不是则无法重建该BST
    for(;ind2<end;ind2++)
    	if (squence[ind2]<squence[end])
    	{
    		isValid=false;
    		return root;
    	}
    // cout<<ind<<"--"<<ind2<<endl;
    //有可能为空,默认空序列都是有效BST
    bool is_left_valid=true,is_right_valid=true;
    root->left=reBuildBSTFromSquence(squence,ind-1,is_left_valid);
    root->right=reBuildBSTFromSquence(squence+ind,ind2-ind-1,is_left_valid);
    
    isValid=is_left_valid && is_right_valid;
    return root;
}



int main()
{
	const int length=7;
	int squence[length]={5,7,6,9,11,10,8};
	// const int length=4;
	// int squence[length]={7,4,6,5};

	bool isValid=true;
	Node* root=reBuildBSTFromSquence(squence,length-1,isValid);
	cout<<"isValid:"<<isValid<<endl;
	if(isValid)
		preOrder(root);
	cout<<endl;
	return 0;
}
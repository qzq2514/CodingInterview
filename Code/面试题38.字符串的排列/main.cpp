#include<iostream>
using namespace std;

//全排列
void permutation_core(char* str,char* begin)
{
	if((*begin)=='\0')
	{
		cout<<str<<endl;
		return;
	}
	for(char* pCh=begin;*pCh!='\0';pCh++)
	{
		char temp = *pCh;
		*pCh = *begin;
		*begin = temp;

		permutation_core(str,begin+1);

		temp = *pCh;
		*pCh = *begin;
		*begin = temp;
	}
}
void permutation(char* str)
{
     if(str==NULL)
     	return ;
     permutation_core(str,str);
}
//C++自带的api-next_permutation
void permutationAPI(char* str,int len)
{
	do 
	{
      cout << str<<endl;
    } while (next_permutation(str,str+len));    
}


//全组合,对每一个字符,选择放不放入组合中
//curInd:当前遍历到的元素下标
void Combination_s1_core(int curInd,bool* is_chosen,int len,char* str)
{
	if(curInd>=len)
	{
       for(int i=0;i<len;i++)
       	 if(is_chosen[i])
       	 	cout<<str[i]<<" ";
       	cout<<endl;
       	return ;
	}
	is_chosen[curInd]=true;
	Combination_s1_core(curInd+1,is_chosen,len,str);
	is_chosen[curInd]=false;
	Combination_s1_core(curInd+1,is_chosen,len,str);

}
void Combination_s1(char* str)
{
	int len = strlen(str);
	cout<<len<<endl;

    bool *is_chosen = new bool[len];
    Combination_s1_core(0,is_chosen,len,str);
}
int main()
{
	char str[4]="ABC";

	//全排列
	// permutation(str);
	// permutationAPI(str,3);

	//全组合
	Combination_s1(str);
	// cout<<str<<endl;
	return 0;
}
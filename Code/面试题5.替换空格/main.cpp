#include<iostream>
using namespace std;
void replare_blank(char str[],char replace_str[])
{
	if(str==NULL)
		return ;

	int org_len=0,blank_num=0;
	while(str[org_len]!='\0')
	{
        if(str[org_len++]==' ')
        	blank_num++;
	}
    int replace_str_len=strlen(replace_str);
	int point_new=org_len+blank_num*(replace_str_len-1),point_org=org_len;

	while(point_org>=0 && point_new>=point_org)
	{
		if(str[point_org]==' ')
		{
			int re_ind=replace_str_len-1;
			while(re_ind>=0)
				str[point_new--]=replace_str[re_ind--];
		}
		else
			str[point_new--]=str[point_org];   //最好在一开始数组定义长一点,不然这里str[point_new--]可能会出界
		point_org--;
	}
}
int main()
{
	//将字符串中所有的空格换成"qzq2514"
	char str[100] = "We are happy!";
	char replace_str[]="qzq2514";
	replare_blank(str,replace_str);
	cout<<"str:"<<str<<endl;
	return 0;
}
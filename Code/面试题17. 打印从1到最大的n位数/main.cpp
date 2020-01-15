#include<iostream>
using namespace std;
#include<memory.h>
int N;
void print_number(char* number)
{
    int len=strlen(number);
    bool isBeginning=true;   //当前位数及之前是不是都是0

    for (int i=0;i<len;i++)
    {
    	if(isBeginning && number[i]!='0')
    		isBeginning = false;

    	if(!isBeginning)
    		printf("%c",number[i]);
    }
    cout<<endl;
}

//简单使用字符串模拟加法,返回是否溢出
bool increaseNumber(char *number)
{
     bool isOverflow=false;
     int takeOver=0;
     int len=strlen(number);
     for(int i=len-1;i>=0;i--)
     {
     	int nSum=number[i]-'0'+takeOver;  
     	if(i==len-1)
     		nSum++;      //从最低位开始加一
     	if(nSum>=10)
     	{
     		if(i==0)   //加到第一位,就是最高位,还有进位,说明溢出了
     			return true;
     		else{       //还没加到第一位,则开始进位
                  nSum-=10;
                  takeOver=1;
                  number[i]=nSum+'0';
     		}
     	}
     	else        //没有进位了,更高位的数值也不会变动了
     	{           //如果是正常两个大数相加,那么这里还需要将进位标志置为0(即takeOver=1,
     		        //但是这里是加一,所以如果到这里没有进位了,后面的也都不会变动了)
     		number[i]=nSum+'0';
     		return false;
     	}
     }
     return false;
}
void solution1(int n)
{
	if(n<=0)
		return ;

	char *number=new char[n+1];
	memset(number,'0',n);    //可使用memset将字符数字每一位设置为指定的字符
    number[n]='\0';
    while(!increaseNumber(number))
	    print_number(number);
	delete []number;

}


//使用递归的方式:每位有0-9种字符选择
//choose_num:开始选择第n位上的数字
void choose_num(char *number,int n,bool isALL0)
{
   int len=strlen(number);
   if(isALL0 && n==len)
   	   return;             //防止递归到最后全是0,这时候是不要打印的
   if(n==len)
   {
   	 print_number(number);
   	 return ;
   }

   for(int i=0;i<10;i++)
   {
   	 number[n]=i+'0';
   	 choose_num(number,n+1,isALL0 && (i==0));
   }
}
void solution2(int n)
{
	if(n<=0)
		return ;
	char *number=new char[n+1];
	memset(number,'1',n); 
	for(int i=0;i<10;i++)
    {
   	    number[0]=i+'0';
   	    choose_num(number,1,i==0);
    }
}
int main()
{
	cin>>N;
	solution2(N);
	return 0;
}
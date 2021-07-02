# 题目
Byteland had not always been a democratic country. There were also black pages in its book of history. One lovely day general Bytel − commander of the junta which had power over Byteland −− decided to finish the long−lasting time of war and released imprisoned activists of the opposition. However, he had no intention to let the leader Bytesar free. He decided to chain him to the wall with the bytish chain. It consists of joined rings and the bar fixed to the wall. Although the rings are not joined with the bar, it is hard to take them off.
'General, why have you chained me to the prison walls and did not let rejoice at freedom!' cried Bytesar.

'But Bytesar, you are not chained at all, and I am certain you are able to take off the rings from the bar by yourself.' perfidiously answered general Bytel, and he added 'But deal with that before a clock strikes the cyber hour and do not make a noise at night, otherwise I will be forced to call Civil Cyber Police.'
Help Bytesar! Number the following rings of the chain with integers 1,2,...,n. We may put on and take off these rings according to the following rules:

.only one ring can be put on or taken off from the bar in one move,

.the ring number 1 can be always put on or taken off from the bar,

.if the rings with the numbers 1,...,k−1 (for 1Write a program which:

.reads from std input the description of the bytish chain,

.computes minimal number of moves necessary to take off all rings of the bytish chain from the bar,

.writes the result to std output.

输入描述

In the first line of the input there is written one intege

输出描述

The output should contain exactly one integer equal to the minimal number of moves necessary to take off all the rings of the bytish chain from the bar.

输入例子
```
4
1 0 1 0
```
输出例子
```
6
```
# 参考答案
```c++
#include<iostream>
#include<string.h>
using namespace std;
int ko[1000];
int cun[1000][350];
int ans[1000];
int main()
{
	int length,i,j,sum;
	cin>>length;
	sum=0;
	for(i=0;i<length;i++)
	{
		cin>>ko[i];
		sum=sum+ko[i];
	}
	for(i=0;i<length;i++)
	{
		sum=sum-ko[i];
		if(sum%2==1)
			ko[i]=1-ko[i];
	}
	memset(cun,0,sizeof(cun));
	cun[0][0]=1;
	for(i=1;i<length;i++)
	{
		for(j=0;j<=349;j++)
		{
			cun[i][j]=cun[i-1][j]*2;
		}
		for(j=0;j<=349;j++)
		{
			if(cun[i][j]>10)
			{
				cun[i][j+1]=cun[i][j+1]+cun[i][j]/10;
				cun[i][j]=cun[i][j]%10;
			}
		}
	}
	memset(ans,0,sizeof(ans));
	for(i=0;i<length;i++)
	{
		if(ko[i]==0)
			continue;
		int carry=0;
		for(j=0;j<=349;j++)
		{
			ans[j]=ans[j]+cun[i][j]+carry;
			carry=ans[j]/10;
			ans[j]=ans[j]%10;
		}
	}
	int flag=-1;
	for(i=400;i>=0;i--)
		if(ans[i]!=0)
		{
			flag=i;
			break;
		}
	if(flag==-1)
		cout<<0;
	for(i=flag;i>=0;i--)
		cout<<ans[i];
	cout<<endl;
	return 0;
}




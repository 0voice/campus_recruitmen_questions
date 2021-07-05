# 题目
An equal sum partition of a sequence of numbers is a grouping of the numbers (in the same order as the original sequence) in such a way that each group has the same sum. For example, the sequence:

2 5 1 3 3 7

may be grouped as:<br>
(2 5) (1 3 3) (7)

to yield an equal sum of 7.

Note: The partition that puts all the numbers in a single group is an equal sum partition with the sum equal to the sum of all the numbers in the sequence.

For this problem, you will write a program that takes as input a sequence of positive integers and returns the smallest sum for an equal sum partition of the sequence.<br>
输入描述<br>
The first line of input contains a single integer P, (1 ≤ P ≤ 1000), which is the number of data sets that follow. The first line of each data set contains the data set number, followed by a space, followed by

a decimal integer M, (1 ≤ M ≤ 10000), giving the total number of integers in the sequence. The remaining line(s) in the dataset consist of the values, 10 per line, separated by a single space. The last line in the dataset may contain less than 10 values.

输出描述<br>
For each data set, generate one line of output with the following values: The data set number as a decimal integer, a space, and the smallest sum for an equal sum partition of the sequence.

输入例子
```
3 
1 6 
2 5 1 3 3 7 
2 6 
1 2 3 4 5 6 
3 20 
1 1 2 1 1 2 1 1 2 1 
1 2 1 1 2 1 1 2 1 1
```
输出例子
```
1 7
2 21
3 2
```
# 参考答案
```c++
#include<stdio.h>
int main()
{
int i,k,j,sum1,sum2,n,m,a[1001],flag,h,x;
scanf("%d",&x);
while(x--)
{
scanf("%d%d",&n,&m);
for(i=0;i<m;i++)
scanf("%d",&a[i]);
for(i=1;i<=m;i++)
{
sum1=sum2=k=0;
for(j=0;j<i;j++)
sum1+=a[j];//确定可能答案的数值
if(i==m)//找不到就输出全部的和
{
printf("%d %d\n",n,sum1);
break;
}
k=i;//下个数值
while(1)
{
sum2+=a[k];
k++;
   if(sum2==sum1)//找后面想等的和
{
h=k;
k=h;
sum2=0;
if(k==m)//找到
{
flag=0;
break;
}
}
if(k==m)//找不到
{
   flag=1;
break;
}
}
if(!flag)
{
printf("%d %d\n",n,sum1);
break;
}
}
}
return 0;
}




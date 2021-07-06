# 题目
Diablo II is the most famous ARPG (Act Role Playing Game) game in the world developped by Blizzard company. Diablo III is coming soon and Cannon group is reviewing Diablo II these days.

In Diablo II, there are generally two kinds of items: normal items and magic items. Normal items have no magic power, while the magic items has some magic power. Each normal item has an price P for selling, but each magic item has two prices for selling: the price before identify P1 and the price after identify P2 (Of cource, P2 is always larger than P1).

![image](https://user-images.githubusercontent.com/59190045/124579918-2c94dc00-de82-11eb-8800-4c8619e942dc.png)    ![image](https://user-images.githubusercontent.com/59190045/124579932-30c0f980-de82-11eb-93ec-1c2ceb0e6bd0.png)

To identify an magic item, you should buy an identify scroll and use it to identify the magic item. After identify an magic item, the identify scroll will disappear. Each identify scroll will cost you Pi, and you can not by an identify scroll if you have no enough money.

Now you are in a town and you have many items, some are normal items and some are magic items. You know all the prices for the items and want to sell all of them. So what is the maximum amount of money you can earn?

You can assume:

You have no money at first.<br>
All the magic items are not identified at first.<br>
You can buy as many identify scrolls as possible, as long as you have enough money.<br>
Input

There are multiple test cases. There are two parts for each case. The first part is one line with two integer N and Pi (0 N, Pi N lines. Each line gives the price (prices) for an item. For a normal item, the line will contain only a positive integer P (0 P1 and P2 (0 P1 P2

Output

For each case, print a number in one line, the maximum amount of money you can earn.

Sample Input
```
2 10
5
8
2 10
10
20 100
```
Sample Output
```
13
100
```
# 参考答案
```c++
#include <iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int mmin(int a,int b)
{
	return a<b?a:b;
}
int d[1001];
int n,pi,res;
struct node
{
 int l,r;
}p[1005];
int main()
{
 int i,j,k,p1,p2,len;
 char t[100];
 while(scanf("%d%d",&n,&pi) != EOF )
	 {
 res=k=0;
 getchar();
 for(i=0;i<n;i++) 
			 {
 gets(t);
 len=strlen(t); 
 int flag=0;
 for(j=0; j<len; j++) 
						 if(t[j]==' ') 
						 {
							 flag=1; 
							 break; 
						 }
 if(flag) 
					 {
 sscanf(t,"%d%d",&p1,&p2);
 if(p2-pi<=p1) 
							{ 
								res+=p1; 
								continue; 
							} 
 p[k].l=p1; 
							p[k++].r=p2;
 }
					 else
					 {
 sscanf(t,"%d",&p1);
 res+=p1;
 }
 }
 if(res>=pi||k==0)
			 {
 for(i=0;i<k;i++) 
						 res+=p[i].r-pi;
 printf("%d\n",res);
 continue;
 }
 int mm=pi-res;
 for(i=0; i<=mm; i++)
				 d[i]=100000000; 
			 d[0]=0;
 for(i=0; i<k; i++)
			 {
 if(p[i].l>=mm) 
						 d[mm]=mmin(d[mm],p[i].r-pi-p[i].l);
 else
					 {
 for(j=mm-p[i].l;j<=mm;j++)
								d[mm]=mmin(d[mm],d[j]+p[i].r-pi-p[i].l);
 for(j=mm; j>=p[i].l; j--)
 d[j]=mmin(d[j],d[j-p[i].l]+p[i].r-pi-p[i].l);

 }
 }
 if(d[mm]==100000000)
			 {
 for(i=0; i<k; i++) 
						 res+=p[i].l;
 }
			 else
			 {
 for(i=0; i<k; i++) 
						 res+=p[i].r-pi;
 res-=d[mm];
 }
 printf("%d\n",res);
 }
 return 0;
}

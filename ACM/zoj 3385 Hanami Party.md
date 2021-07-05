# 题目
Saigyouji Yuyuko and Konpaku Youmu are going to hold a hanami party (a Japanese traditional custom of enjoying the beauty of cherry blossoms). They decide to invite all their friends to come to the yard enjoying the feast under the flowering trees, and sometimes the party will go on until late at night.

![zoj_354desc_0](http://uploadfiles.nowcoder.com/probs/acm/zoj_354desc_0.jpg)

To prepare for the grand party, Youmu need to make as much food as possible. But soon she noticed that the "hungry ghost" Yuyuko will eat some food she made every day. If there is no enough food, the hungry Yuyuko will become angry.

They have <var>N</var> days to prepare for the party. On the first day of their preparation, Youmu has an initial cooking level <var>L</var>, which means she can make <var>L</var> units of food in one day. Everyday, Youmu can choose to do only one of the actions below:

Improve her cooking level <var>L</var> by 1.<br>
Make <var>L</var> units of food during that day.<br>
Anyway, Youmu don't want to enrage Yuyuko, so she turned to you for help. You should maximize the amount of food Youmu can present on the party, without making Yuyuko angry.

Input

There are multiple test cases (no more than 20).

The first line contains two integers <var>N</var> and <var>L</var> (1 <= <var>N</var> <= 100000, 0 <= <var>L</var> <= 10^9). The second line contains <var>N</var> integers <var>ai</var> (0 <= <var>ai</var> <= 10^9), which means on the <var>i</var>th day of their preparation, Yuyuko will eat <var>ai</var> units of food that Youmu made.

Output

If Yuyuko won't get angry during the preparation, output the maximal amount of food Youmu can present on the party. Otherwise, output a line of "Myon".

Sample Input
```
5 2
1 1 1 4 2
```
Sample Output
```
2
```
References

![zoj_354desc_1](http://uploadfiles.nowcoder.com/probs/acm/zoj_354desc_1.jpg)
# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N = 100005;
typedef long long ll;
int a[N],q[N];
ll sum[N];
int main()
{
 int n,L,i,j;
 while(~scanf("%d%d",&n,&L))
 {
 for(i=1;i<=n;i++){scanf("%d",&a[i]);sum[i]=sum[i-1]+a[i];}
 int flag=0,t=0,sL=L;
		ll ret=0,nw=0;
		for(i=1;i<=n;i++)
		{
			q[t++]=i;
			L++;
			while(nw<a[i]&&t)
			{
				nw-=(i-q[t-1]);
				L--;
				nw+=L;
				t--;
			}
			if(nw<a[i]){flag=1;break;}
			nw-=a[i];
		}
 if(flag)puts("Myon");
		else
		{
			while(t&&nw-(n-q[t-1])+L-1>nw)
			{
				nw=nw-(n-q[t-1])+L-1;
				t--;
				L--;
			}
			cout << nw << endl;;
		}
 }
 return 0;
}




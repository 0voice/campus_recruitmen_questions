# 题目
Bessy is going to school and doing well. She has taken N (1 ≤ N ≤ 5000 -- except one case where 1 ≤ N ≤ 50,000) tests and recorded the scores (T<sub>i</sub> points out of P<sub>i</sub> points for test i; 0 ≤ T<sub>i</sub> ≤ P<sub>i</sub> < 40,000; 0 < P<sub>i</sub> ) as this task's input.

Her teacher will drop the D tests with the lowest percentage ( T<sub>i</sub> ⁄ P<sub>i</sub> ) before calculating Bessie's final grade (which is the sum of the remaining test score points over the sum of the remaining total test points). Bessy is good at math and quickly realizes that this does not benefit her as much as it might.

To prove her point, Bessy wants to find all values of D for which she could have ended up with a higher grade by choosing to drop different tests than the teacher would have. Help her by finding and printing all values of D for which this is possible.

Bessy has noted that, amazingly, she has never scored the same percentage on two different tests.

输入描述
* Line 1: A single integer, N
* Lines 2..N +1: Line i +1 contains two space-separated integers: T<sub>i</sub> and P<sub>i</sub>


输出描述
* Line 1: A single integer K (0 ≤ K ≤ N ) that is the number of values of D for which Bessy could have ended up with a higher grade by dropping a different set of D tests than the teacher.
* Lines 2..K +1: The values of D for which this is true, in ascending numerical order.

输入例子
```
5
1 2
5 9
3 8
4 10
1 3
```
输出例子
```
2
1
2
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=5e4+9;
double high[maxn],low[maxn];
long long sumt[maxn],sump[maxn];
struct D
{
    long long t,p;
    bool operator <(const D & xx) const
    {
        return t*xx.p>xx.t*p;
    }
}test[maxn];
int que[maxn];

bool chk(int i,int j,int t,int s)
{
    long long a=(test[i].t-test[j].t)*(test[t].p-test[s].p);
    long long b=(test[t].t-test[s].t)*(test[i].p-test[j].p);
    return a>b;
}

bool chk2(int i,int j,long long t,long long p)
{
    long long a=(test[i].t-test[j].t)*p;
    long long b=t*(test[i].p-test[j].p);
    return a>b;
}
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1;i<=n;i++)
        scanf("%lld %lld",&test[i].t,&test[i].p);
        sort(test+1,test+1+n);

        for(int i=1;i<=n;i++)
        {
            sumt[i]=sumt[i-1]+test[i].t;
            sump[i]=sump[i-1]+test[i].p;
        }

        int front=1,end=0;
        for(int i=1;i<=n;i++)
        {
            while(end>=front&&test[i].p>=test[que[end]].p)
            end--;
            while(end>front&&chk(que[end],i,que[end-1],que[end]))
            end--;
            que[++end]=i;
            while(front<end&&chk2(que[front],que[front+1],sumt[i],sump[i])==1)
            front++;
            int u=que[front];
            low[i]=test[u].t-(double)sumt[i]/sump[i]*test[u].p;
        }
        int top=0;
        for(int i=n;i>=1;i--)
        {
            while(top>0&&test[i].p<=test[que[top]].p)
            top--;
            while(top>1&&chk(i,que[top],que[top],que[top-1]))
            top--;
            que[++top]=i;
            while(top>1&&chk2(que[top],que[top-1],sumt[i-1],sump[i-1])==0)
            top--;
            int u=que[top];
            high[i]=test[u].t-(double)sumt[i-1]/sump[i-1]*test[u].p;
        }
        int ans=0;
        for(int i=1;i<n;i++)
        if(high[i+1]>low[i])
        ans++;
        cout<<ans<<endl;
        for(int i=n-1;i>=1;i--)
        if(high[i+1]>low[i])
        printf("%d\n",n-i);
    }
    return 0;
}

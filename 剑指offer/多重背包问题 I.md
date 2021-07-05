# 题目
![NO4.png](https://img13.360buyimg.com/ddimg/jfs/t1/176148/1/18322/33955/60e2b277E7bd5de4c/c98ccf91530f4491.png)
# 参考答案
### c++代码
```c++
#include <bits/stdc++.h>
using namespace std;
int a[10005],b[10005];
int main()
{
    int t=0,n,m,dp[10005]={ },w,v,s;
    cin>>n>>m;
    while(n--)
    {
    cin>>v>>w>>s;
    while(s--)
    {a[++t]=v;
    b[t]=w;}//死拆，把多重背包拆成01背包
    }
    for(int i=1;i<=t;i++)
    for(int j=m;j>=a[i];j--)
    dp[j]=max(dp[j-a[i]]+b[i],dp[j]);//直接套01背包的板子
    cout<<dp[m]<<endl;
    return 0;
}
```


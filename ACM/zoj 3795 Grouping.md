# 题目
Suppose there are <var>N</var> people in ZJU, whose ages are unknown. We have some messages about them. The <var>i</var>-th message shows that the age of person <var>si</var> is not smaller than the age of person <var>ti</var>. Now we need to divide all these <var>N</var> people into several groups. One's age shouldn't be compared with each other in the same group, directly or indirectly. And everyone should be assigned to one and only one group. The task is to calculate the minimum number of groups that meet the requirement.

Input

There are multiple test cases. For each test case: The first line contains two integers <var>N</var>(1≤ <var>N</var>≤ 100000), <var>M</var>(1≤ <var>M</var>≤ 300000), <var>N</var> is the number of people, and <var>M</var> is is the number of messages. Then followed by <var>M</var> lines, each line contain two integers si and ti. There is a blank line between every two cases. Process to the end of input.

Output

For each the case, print the minimum number of groups that meet the requirement one line.

Sample Input
```
4 4
1 2
1 3
2 4
3 4
```
Sample Output
```
3
```
Hint

set1= {1}, set2= {2, 3}, set3= {4}
# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>
#include<stack>
using namespace std;
#define maxn 110000
vector<int>old[maxn];
vector<int>vec[maxn];
int dnf[maxn],low[maxn],instack[maxn];
int times,nums;
stack<int>st;
int pan[maxn];
int ru[maxn];
int vis[maxn];
int ans;
int res[maxn];
int val[maxn];
void init(int n)
{
    for(int i=0;i<=n+1;i++)
    {
        dnf[i]=low[i]=instack[i]
        =pan[i]=ru[i]=vis[i]=res[i]=val[i]=0;
        vec[i].clear();old[i].clear();
    }
    while(!st.empty())st.pop();
    times=nums=1;
}
void tarjan(int x)
{
    dnf[x]=low[x]=times++;
    instack[x]=1;
    st.push(x);
    for(int i=0;i<old[x].size();i++)
    {
        int y=old[x][i];
        if(!dnf[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(instack[y])
        {
            low[x]=min(low[x],dnf[y]);
        }
    }
    if(low[x]==dnf[x])
    {
        int y=-1;
        while(x!=y)
        {
            y=st.top();
            st.pop();
            instack[y]=0;
            pan[y]=nums;
            val[nums]++;
        }
        nums++;
    }
}
void dfs(int x)
{
    if(res[x])return;
    res[x]=val[x];
    for(int i=0;i<vec[x].size();i++)
    {
        int y=vec[x][i];
        dfs(y);
        res[x]=max(res[x],res[y]+val[x]);
    }
}
int main()
{
    int n,m,x,y;
    while(~scanf("%d%d",&n,&m))
    {
        init(n);
        while(m--)
        {
            scanf("%d%d",&x,&y);
            old[x].push_back(y);
        }
        for(int i=1;i<=n;i++)
            if(!dnf[i])tarjan(i);
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<old[i].size();j++)
            {
                x=pan[i];
                y=pan[old[i][j]];
                if(x==y)continue;
                vec[x].push_back(y);
                ru[y]++;
            }
        }
        ans=-1;
        for(int i=1;i<nums;i++)
        {
            if(!ru[i])
            {
                dfs(i);
                ans=max(ans,res[i]);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}




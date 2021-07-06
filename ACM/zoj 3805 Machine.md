# 题目
In a typical assembly line, machines are connected one by one. The first machine's output product will be the second machine's raw material. To simplify the problem, we put all machines into a two-dimension shelf. Every machine occupied exactly one grid and has two input ports and only one output port. One input port can get material from only one machine.

![image](https://user-images.githubusercontent.com/59190045/124593562-5efa0580-de91-11eb-8ffe-953e61f76448.png)

Pipes will be used to connect between these machines. There are two kinds of pipes : 'I' kind and 'L' kind. We should notice that the 'I' kind pipe can be linked one by one. Each pipe will also occupied one grid.

In Bob's factory, each machine will get raw materials from zero, one or two other machines. Some machines don't need any input materials, but any machine must have an output. Machines are coded by numbers from 1 to <var>n</var>. The output of the machines with greater code can be the input of the machines with less code. The machine NO.1's output product will be the final product, and will not be any other machine's input. Bob's factory has a shelf with infinite height, but finite width. He will give you the dependency relationship of these machines, and want you to arrange these machines and pipes so that he can minimize the width of the shelf.

Here's an example for you to help understand :

![image](https://user-images.githubusercontent.com/59190045/124593526-543f7080-de91-11eb-8504-9e200194a3d9.png)

Products will falling from higher machine to lower machine through the pipes. Here, machine 1 gets materials from machine 2 and machine 3. The whole width of this system is 2.

Input
For each case, the first line will be an integer <var>n</var> indicates the number of the machines (2≤ n≤ 10000). The following line will include <var>n-1</var> numbers. The <var>i</var>-th number <var>ai</var> means that the output of machine <var>i+1</var> will be the input of machine <var>ai</var> (<var>ai</var>≤ <var>i</var>). The same code will be appeared at most twice. Notice machine 1's output will be the final output, and won't be any machine's input.

Output
For each case, we need exactly one integer as output, which is the minimal width of the shelf.

Sample Input
```
3
1 1
7
1 1 2 2 3 3
```
Sample Output
```
2
3
```
Hint

Case 1 is the example. Case 2:

![image](https://user-images.githubusercontent.com/59190045/124593596-691c0400-de91-11eb-91fd-feca66faaae0.png)

This problem contains massive input and output, please use efficient IO methods.
# 参考答案
```c++
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <vector>
using namespace std;
#define up(i,x,y) for(i=x;i<=y;i++)
#define up2(i,x,y) for(i=x;y;i++)
#define down(i,x,y) for(i=x;i>=y;i--)
#define down2(i,x,y) for(i=x;y;i--)
#define pi acos(-1.0)
#define ll long long
#define s(a) scanf("%d",&a)
#define mem(a,b) memset(a,b,sizeof(a))
#define ads(a) (a<0?-a:a)
#define w(a) while(a)
int vis[100005],dp[100005],n,a[100005];
vector<int>g[100005];

int dfs(int x)
{
    if(dp[x]!=-1)
        return dp[x];
    int l=g[x].size();
    if(!l)
        dp[x]=1;
    else if(l==1)
        dp[x]=dfs(g[x][0]);
    else
        dp[x]=min(max(dfs(g[x][0])+1,dfs(g[x][1])),max(dfs(g[x][0]),dfs(g[x][1])+1));
    return dp[x];
}

int main()
{
    int i,j;
    w(~s(n))
    {
        up(i,0,n)
        {
            dp[i]=-1;
            g[i].clear();
        }
        up(i,2,n)
        {
            s(a[i]);
            g[a[i]].push_back(i);
        }
        printf("%d\n",dfs(1));
    }
}

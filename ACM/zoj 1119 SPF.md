# 题目
Consider the two networks shown below. Assuming that data moves around these networks only between directly connected nodes on a peer-to-peer basis, a failure of a single node, 3, in the network on the left would prevent some of the still available nodes from communicating with each other. Nodes 1 and 2 could still communicate with each other as could nodes 4 and 5, but communication between any other pairs of nodes would no longer be possible.

Node 3 is therefore a Single Point of Failure (SPF) for this network. Strictly, an SPF will be defined as any node that, if unavailable, would prevent at least one pair of available nodes from being able to communicate on what was previously a fully connected network. Note that the network on the right has no such node; there is no SPF in the network. At least two machines must fail before there are any pairs of available nodes which cannot communicate.

![zoj_530desc_0](http://uploadfiles.nowcoder.com/probs/acm/zoj_530desc_0.jpg)

Input

The input will contain the description of several networks. A network description will consist of pairs of integers, one pair per line, that identify connected nodes. Ordering of the pairs is irrelevant; 1 2 and 2 1 specify the same connection. All node numbers will range from 1 to 1000. A line containing a single zero ends the list of connected nodes. An empty network description flags the end of the input. Blank lines in the input file should be ignored.


Output

For each network in the input, you will output its number in the file, followed by a list of any SPF nodes that exist.

The first network in the file should be identified as ��Network #1��, the second as ��Network #2��, etc. For each SPF node, output a line, formatted as shown in the examples below, that identifies the node and the number of fully connected subnets that remain when that node fails. If the network has no SPF nodes, simply output the text ��No SPF nodes�� instead of a list of SPF nodes.


Example

Input
```
1 2
5 4
3 1
3 2
3 4
3 5
0

1 2
2 3
3 4
4 5
5 1
0

1 2
2 3
3 4
4 6
6 3
2 5
5 1
0

0
```
Output
```
Network #1
  SPF node 3 leaves 2 subnets

Network #2
  No SPF nodes

Network #3
  SPF node 2 leaves 2 subnets
  SPF node 3 leaves 2 subnets
```

# 参考答案
```c++
#include <iostream>
#include <algorithm>
#include <queue>
#include <math.h>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MOD 1000000007
#define maxn 1010
bool G[maxn][maxn];
int low[maxn],pre[maxn];
int ans[maxn];
int dfst;
int node;
int child;
void init(){
    dfst=0;
    node=0;
    child=0;
    memset(G,0,sizeof(G));
    memset(ans,0,sizeof(ans));
    memset(pre,0,sizeof(pre));
}
int dfs(int u){
   int lowu;
   lowu=pre[u]=++dfst;
   int v;
   for(v=1;v<=node;v++){
     if(G[u][v]){
          if(!pre[v]){
            int lowv=dfs(v);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u]){
                if(u!=1) ans[u]++;
                else child++;
            }
          }
          else lowu=min(lowu,pre[v]);
     }
   }
   return lowu;
}
int main()
{
    int u,v;
    int Case=0;
    while(scanf("%d",&u),u){
        init();
        scanf("%d",&v);
        node=max(u,v);
        G[u][v]=G[v][u]=1;
        while(scanf("%d",&u),u){
            scanf("%d",&v);
            node=max(node,v);
            node=max(node,u);
            G[u][v]=G[v][u]=1;
        }
        dfs(1);
        int found=0;
        if(child>1) ans[1]=child-1;
        if(Case) printf("\n");
        printf("Network #%d\n",++Case);
        for(int i=1;i<=node;i++)
          if(ans[i]){
            found=1;
            printf("  SPF node %d leaves %d subnets\n",i,ans[i]+1);
        }
        if(!found)
            printf("  No SPF nodes\n");
    }

    return 0;
}




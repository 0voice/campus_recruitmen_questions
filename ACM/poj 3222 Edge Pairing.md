# 题目
Given a simple connected undirected graph with n vertices and m edges, where m is even, your task is to find a pairing of the edges such that each pair of edges shares a vertex.

输入描述

The input contains exactly one test cases. On the first line of the test case there are two integers n and m (3 ≤ n ≤ 20,000, 2 ≤ m ≤ 100,000, m is even) which indicate the size of the graph. Next come m lines each with a pair of integers a and b representing an edge (a, b). The vertices are numbered 1 through n.

输出描述

If a pairing exists, output it in m ⁄2 lines. Each line contains three integers a, b and c in this order, indicating that the edges (a, b) and (b, c) are paired together. If no pairing exists, just output “NO” and nothing else.

输入例子
```
7 10
1 2
1 3
2 4
3 4
4 5
4 6
5 7
6 7
2 5
3 6
```
输出例子
```
1 2 4
1 3 4
4 5 2
4 6 3
5 7 6
```
Hint

Illustration of the sample test case:

![poj_2897outputs_0](http://uploadfiles.nowcoder.com/probs/acm/poj_2897outputs_0.jpg)
# 参考答案
```c++
#include <stdio.h>
#include <string.h>
#define N 20005
struct edge{
    int y,next;
}e[100005<<1];
int first[N],dfn[N],order = 0;
int n,m,top;
void add(int x,int y){
    e[top].y = y;
    e[top].next = first[x];
    first[x] = top++;
}
int dfs(int x){
    int i,y,w,v = -1;
    dfn[x] = ++order;
    for(i = first[x];i!=-1;i=e[i].next){
        y = e[i].y;
        if(!dfn[y]){
            w = dfs(y);
            if(w!=-1)
                printf("%d %d %d\n",x,y,w);
            else{
                if(v!=-1){
                    printf("%d %d %d\n",v,x,y);
                    v = -1;
                }else
                    v = y;
            }
        }else if(dfn[x] < dfn[y]){
            if(v!=-1){
                printf("%d %d %d\n",v,x,y);
                v = -1;
            }else
                v = y;
        }
    }
    return v;
}
int main(){
    int i,a,b;
    top = 0;
    memset(dfn,0,sizeof(dfn));
    memset(first,-1,sizeof(first));
    scanf("%d %d",&n,&m);
    for(i = 0;i<m;i++){
        scanf("%d %d",&a,&b);
        add(a,b);
        add(b,a);
    }
    dfs(1);
    return 0;
}





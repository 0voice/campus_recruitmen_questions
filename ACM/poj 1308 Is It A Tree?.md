# 题目
A tree is a well-known data structure that is either empty (null, void, nothing) or is a set of one or more nodes connected by directed edges between nodes satisfying the following properties.

There is exactly one node, called the root, to which no directed edges point.
Every node except the root has exactly one edge pointing to it.
There is a unique sequence of directed edges from the root to each node.
For example, consider the illustrations below, in which nodes are represented by circles and edges are represented by lines with arrowheads. The first two of these are trees, but the last is not.
![poj_3151desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_3151desc_0.jpg)

In this problem you will be given several descriptions of collections of nodes connected by directed edges. For each of these you are to determine if the collection satisfies the definition of a tree or not.

输入描述

The input will consist of a sequence of descriptions (test cases) followed by a pair of negative integers. Each test case will consist of a sequence of edge descriptions followed by a pair of zeroes Each edge description will consist of a pair of integers; the first integer identifies the node from which the edge begins, and the second integer identifies the node to which the edge is directed. Node numbers will always be greater than zero.

输出描述

For each test case display the line "Case k is a tree." or the line "Case k is not a tree.", where k corresponds to the test case number (they are sequentially numbered starting with 1).

输入例子
```
6 8  5 3  5 2  6 4
5 6  0 0

8 1  7 3  6 2  8 9  7 5
7 4  7 8  7 6  0 0

3 8  6 8  6 4
5 3  5 6  5 2  0 0
-1 -1
```
输出例子
```
Case 1 is a tree.
Case 2 is a tree.
Case 3 is not a tree.
```

# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define maxn 1006

struct Edge
{
    int v, next;
}edge[1000005];

int name[maxn];
int n, ecount, tot, root;
int in[maxn];
int head[maxn];
bool vis[maxn];
bool ok;

void addedge(int a, int b)
{
    edge[ecount].next = head[a];
    edge[ecount].v = b;
    head[a] = ecount;
    in[b]++;
    ecount++;
}

int find(int a)
{
    for (int i = 0; i < n; i++)
        if (name[i] == a)
            return i;
    name[n++] = a;
    return n - 1;
}

void dfs(int root)
{
    vis[root] = true;
    tot++;
    for (int i = head[root]; i != -1; i = edge[i].next)
    {
        if (vis[edge[i].v])
        {
            ok = false;
            return;
        }
        if (!ok)
            return;
        dfs(edge[i].v);
    }
}

int main()
{
    int t = 0;
    while (1)
    {
        t++;
        memset(in, 0, sizeof(in));
        memset(head, -1, sizeof(head));
        memset(vis, 0, sizeof(vis));
        ecount = 0;
        n = 0;
        tot = 0;
        ok = true;
        int a, b;
        scanf("%d%d", &a, &b);
        if (a < 0 && b < 0)
            return 0;
        if (a == 0 && b == 0)
        {
            printf("Case %d is a tree.\n", t);
            continue;
        }
        a = find(a);
        b = find(b);
        addedge(a, b);
        while (1)
        {
            scanf("%d%d", &a, &b);
            if (a == 0 && b == 0)
                break;
            a = find(a);
            b = find(b);
            addedge(a, b);
        }
        root = -1;
        for (int i = 0; i < n; i++)
            if (in[i] == 0)
                root = i;
        if (root >= 0)
            dfs(root);
        if (ok && tot == n && root >= 0)
            printf("Case %d is a tree.\n", t);
        else
            printf("Case %d is not a tree.\n", t);
    }
    return 0;
}

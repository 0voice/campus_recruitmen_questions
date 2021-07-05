# 题目
After a period of intensive development of the transportation infrastructure, the government of Ruritania decides to take firm steps to strengthen citizens' confidence in the national road network and sets up a compensation scheme for adventurous driving (CSAD). Those driving on a road with holes, bumps and other entertaining obstacles get compensation; those driving on a decent road pay tax. These compensations and taxes are obtained and paid in cash on entry on each road and depend on the entry point on the road. What you get and pay driving on a road from A to B may be different from what you get and pay driving on the same road from B to A. The Ruritarian authorities call fee the amount of money paid as tax or obtained as compensation on entry on a road. A positive fee is a tax; a negative fee stands for compensation.

John Doe plans to take advantage of CSAD for saving money he needs to repair his old car. When driving from A to B, John follows a path he calls optimal: a path that is rewarding and has the minimal length out of the paths with the minimal weight from A to B. In John's opinion, a path is rewarding if all the roads in the path are rewarding, and a road (X,Y) is rewarding if it has the minimal entry fee out of the roads leaving X. The weight of a path is the sum of the entry fees paid along the path. The length of a path cumulates the length of the roads in the path. The problem is helping John to compute the weight and the length of an optimal path from A to B on a given map.

For example, on the illustrated road map vertices designate cities and edges stand for roads. The label fuv[L]fvu of the road (u,v) shows the fee fuv for driving from u to v, the fee fvu for driving from v to u, and the length L of the road. The path (0,2,4,3,5) from 0 to 5 is optimal: it is rewarding, has weight 2 (-1+3+0+0) and length 50 (5+10+5+30). The path (0,1,4,3,5), although rewarding and of weight 2, has length 51. The path (0,3,5) has weight 0 and length 20 but it is not rewarding.

输入描述<br>
Write a program that reads several data sets from a text file. Each data set encodes a road map and starts with four integers: the nu<br>
输出描述<br>
For each data set, the program prints – from the beginning of a line – the weight and the length of an optimal path, according to John's oppinion, from A to B. If there is no optimal path from A to B the text VOID is printed. If the weight of the optimal path from A to B has no lower bound the text UNBOUND is printed.<br>
输入例子
```
3 3 0 2 (0,1,0[1]0) (0,2,1[1]0) (1,2,1[1]0)
3 3 0 2 (0,1,-1[1]1) (0,2,0[1]0) (1,2,0[1]1)
7 11 0 5 (0,1,-1[6]4) (0,2,-1[5]4) (0,3,0[1]0)  (1,4,3[10]1)
(2,4,3[10]1) (3,4,0[5]0)  (3,5,0[30]0) (3,5,1[20]0)
 (4,6,0[3]1)  (6,5,1[8]0)  (6,6,0[2]-1)
 ```
输出例子
```
VOID
UNBOUND
2 50
```
Hint

An input/output sample is in the table above. The first data set encodes a road map with no optimal path from 0 to 2. The second data set corresponds to a map whose optimal path from 0 to 2 has an unbound weight. The third data set encodes the road map shown in the above figure.

# 参考答案
```c++
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX_NODE_NUM 1505
#define INF 0x3f3f3f3f

struct Edge
{
    int v;
    int weight;
    int length;
    Edge()
    {}
    Edge(int v, int length, int weight):v(v), length(length), weight(weight)
    {}
}dist[MAX_NODE_NUM];

int node_num, road_num;
int origin, destination;
int least_fee[MAX_NODE_NUM];
bool vis[MAX_NODE_NUM];
int push_cnt[MAX_NODE_NUM];

vector<vector<Edge> > G;
vector<vector<Edge> > R;

void addedge(vector<vector<Edge> > &G, int u, int v, int length, int weight)
{
    G[u].push_back(Edge(v, length, weight));
}

void input()
{
    fill(least_fee, least_fee + node_num, INF);
    G.clear();
    G = vector<vector<Edge> > (node_num);
    for (int i = 0; i < road_num; i++)
    {
        int u, v, l, fuv, fvu;
        char st[50];
        scanf("%s", st);
        sscanf(st, "(%d,%d,%d[%d]%d)", &u, &v, &fuv, &l, &fvu);
        addedge(G, u, v, l, fuv);
        addedge(G, v, u, l, fvu);
        least_fee[u] = min(least_fee[u], fuv);
        least_fee[v] = min(least_fee[v], fvu);
    }
}

void clean_edge()
{
    for (int i = 0; i < node_num; i++)
    {
        int j = 0;
        for (vector<Edge>::iterator j = G[i].begin(); j != G[i].end();)
        {
            if (j->weight > least_fee[i])
                j = G[i].erase(j);
            else
                j++;
        }
    }
}

void reverse_graph()
{
    R.clear();
    R = vector<vector<Edge> > (node_num);
    for (int i = 0; i < node_num; i++)
    {
        for (vector<Edge>::iterator j = G[i].begin(); j != G[i].end(); j++)
            addedge(R, j->v, i, j->length, j->weight);
    }
}

void dfs(int id)
{
    if (vis[id])
        return;
    vis[id] = true;
    for (vector<Edge>::iterator i = R[id].begin(); i != R[id].end(); i++)
        dfs(i->v);
}

void clean_node()
{
    for (int i = 0; i < node_num; i++)
    {
        if (!vis[i])
        {
            G[i].clear();
            continue;
        }
        for (vector<Edge>::iterator j = G[i].begin(); j != G[i].end();)
        {
            if (!vis[j->v])
                j = G[i].erase(j);
            else
                j++;
        }
    }
}

bool relax(Edge &dist, int length, int weight)
{
    if (dist.weight > weight || (dist.weight == weight && dist.length > length))
    {
        dist.weight = weight;
        dist.length = length;
        return true;
    }
    return false;
}

void SPFA()
{
    fill(dist, dist + node_num, Edge(-1, INF, INF));
    memset(push_cnt, 0, sizeof(push_cnt));
    queue<Edge> q;
    q.push(Edge(origin, 0, 0));
    dist[origin] = Edge(-1, 0, 0);
    bool unbound = false;
    while (!q.empty())
    {
        Edge temp = q.front();
        q.pop();
        for (vector<Edge>::iterator i = G[temp.v].begin(); i != G[temp.v].end(); i++)
        {
            if (relax(dist[i->v], temp.length + i->length, temp.weight + i->weight))
            {
                q.push(Edge(i->v, dist[i->v].length, dist[i->v].weight));
                push_cnt[i->v]++;
                if (push_cnt[i->v] > node_num)
                {
                    puts("UNBOUND");
                    return;
                }
            }
        }
    }
    printf("%d %d\n", dist[destination].weight, dist[destination].length);
}

int main()
{
    while (scanf("%d%d%d%d", &node_num, &road_num, &origin, &destination) != EOF)
    {
        input();
        clean_edge();
        reverse_graph();
        memset(vis, 0, sizeof(vis));
        dfs(destination);
        if (!vis[origin])
        {
            puts("VOID");
            continue;
        }
        clean_node();
        SPFA();
    }
    return 0;
}





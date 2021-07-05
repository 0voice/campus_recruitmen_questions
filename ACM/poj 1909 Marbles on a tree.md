# 题目
n boxes are placed on the vertices of a rooted tree, which are numbered from 1 to n, 1 The task is to move the marbles such that each box contains exactly one marble. This is to be accomplished be a sequence of moves; each move consists of moving one marble to a box at an adjacent vertex. What is the minimum number of moves required to achieve the goal?

输入描述

The input contains a number of cases. Each case starts with the number n followed by n lines. Each line contains at least three numbers which are: v the number of a vertex, followed by the number of marbles originally placed at vertex v followed by a number d which is the number of children of v, followed by d numbers giving the identities of the children of v.

The input is terminated by a case where n = 0 and this case should not be processed.

输出描述

For each case in the input, output the smallest number of moves of marbles resulting in one marble at each vertex of the tree.

输入例子
```
9
1 2 3 2 3 4
2 1 0
3 0 2 5 6
4 1 3 7 8 9
5 3 0
6 0 0
7 0 0
8 2 0
9 0 0
9
1 0 3 2 3 4
2 0 0
3 0 2 5 6
4 9 3 7 8 9
5 0 0
6 0 0
7 0 0
8 0 0
9 0 0
9
1 0 3 2 3 4
2 9 0
3 0 2 5 6
4 0 3 7 8 9
5 0 0
6 0 0
7 0 0
8 0 0
9 0 0
0
```
输出例子
```
7
14
20
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

const int M = 10005;
vector<int>que[M];
int num[M];
int rd[M];
int n, ans;

void init() {

    for(int i = 0; i <= n; i++){

        que[i].clear();
        num[i] = 0;
        rd[i] = 0;
    }
}

void dfs(int u){

     int v;
    for(int i = 0; i < (int)que[u].size(); i++) {

        v = que[u][i];
        dfs(v);
        num[u] += num[v];
        ans += fabs(num[v]);
    }
    num[u] -= 1;
}

int main()
{
    int a, b, q;

    while(scanf("%d", &n) != EOF) {

        if(!n)
            break;
         init();
         ans = 0;
        for(int i = 0; i< n; i++){

            scanf("%d%d%d", &a, &b, &q);
            num[a] = b;
            for(int j = 0; j < q; j++){

                scanf("%d", &b);
                que[a].push_back(b);
                rd[b]++;
            }

        }
        for(int i = 1; i <= n; i++){

            if(!rd[i]){

                dfs(i);
                break;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}




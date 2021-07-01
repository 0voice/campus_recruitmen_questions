# 题目
Genghis Khan(成吉思汗)(1162-1227), also known by his birth name Temujin(铁木真) and temple name Taizu(元太祖), was the founder of the Mongol Empire and the greatest conqueror in Chinese history. After uniting many of the nomadic tribes on the Mongolian steppe, Genghis Khan founded a strong cavalry equipped by irony discipline, sabers and powder, and he became to the most fearsome conqueror in the history. He stretched the empire that resulted in the conquest of most of Eurasia. The following figure (origin: Wikipedia) shows the territory of Mongol Empire at that time.

![image](http://uploadfiles.nowcoder.com/probs/acm/poj_5601desc_0.jpg)

Our story is about Jebei Noyan(哲别), who was one of the most famous generals in Genghis Khan’s cavalry. Once his led the advance troop to invade a country named Pushtuar. The knights rolled up all the cities in Pushtuar rapidly. As Jebei Noyan’s advance troop did not have enough soldiers, the conquest was temporary and vulnerable and he was waiting for the Genghis Khan’s reinforce. At the meantime, Jebei Noyan needed to set up many guarders on the road of the country in order to guarantee that his troop in each city can send and receive messages safely and promptly through those roads.

There were N cities in Pushtuar and there were bidirectional roads connecting cities. If Jebei set up guarders on a road, it was totally safe to deliver messages between the two cities connected by the road. However setting up guarders on different road took different cost based on the distance, road condition and the residual armed power nearby. Jebei had known the cost of setting up guarders on each road. He wanted to guarantee that each two cities can safely deliver messages either directly or indirectly and the total cost was minimal.

Things will always get a little bit harder. As a sophisticated general, Jebei predicted that there would be one uprising happening in the country sooner or later which might increase the cost (setting up guarders) on exactly ONE road. Nevertheless he did not know which road would be affected, but only got the information of some suspicious road cost changes. We assumed that the probability of each suspicious case was the same. Since that after the uprising happened, the plan of guarder setting should be rearranged to achieve the minimal cost, Jebei Noyan wanted to know the new expected minimal total cost immediately based on current information.

输入描述

There are no more than 20 test cases in the input.

For each test case, the first line contains two integers N and M (1<=N<=3000, 0<=M<=N×N), demonstrating the number of cities and roads in Pushtuar. Cities are numbered from 0 to N-1. In the each of the following M lines, there are three integers xi , yi and ci (ci 7), showing that there is a bidirectional road between xi and yi , while the cost of setting up guarders on this road is ci . We guarantee that the graph is connected. The total cost of the graph is less or equal to 109 .

The next line contains an integer Q (1<=Q<=10000) representing the number of suspicious road cost changes. In the following Q lines, each line contains three integers Xi, Yi and Ci showing that the cost of road (Xi, Yi) may change to Ci (Ci

输出描述

For each test case, output a real number demonstrating the expected minimal total cost. The result should be rounded to 4 digits after decimal point.

输入例子
* 3 3
* 0 1 3
* 0 2 2
* 1 2 5
* 3
* 0 2 3
* 1 2 6
* 0 1 6
* 0 0

输出例子
* 6.0000

Hint

The initial minimal cost is 5 by connecting city 0 to 1 and city 0 to 2. In the first suspicious case, the minimal total cost is increased to 6; the second case remains 5; the third case is increased to 7. As the result, the expected cost is (5+6+7)/3 = 6.

# 参考答案
    #include<iostream>
    #include<cstdio>
    #include<string>
    #include<cstring>
    #include<algorithm>
    #include<vector>
    using namespace std;
    const int N = 3010;
    int d[N],f[N];
    bool v[N];
    int n,m,x,y,z;
    int a[N][N];
    int dfn[N];
    int curr;
    int b[N][N];
    int prim()
    {
        int tot = 0;
        memset(d,63,sizeof(d));
        memset(v,0,sizeof(v));
        memset(f,0,sizeof(f));
        v[0] = 1; d[0] = 0;
        for (int i = 1; i < n; i++)
        {
            d[i] = a[0][i];
            f[i] = 0;
        }
        for (int i = 1; i < n; i++)
        {
            int k = 0,minn = 1000000000;
            for (int j = 0; j < n; j++)
                if (!v[j] && d[j] < minn)
            {
                minn = d[j];
                k = j;
            }
            tot += d[k];

            v[k] = 1;
            for (int j = 0; j < n; j++)
                if (!v[j] && d[j] > a[k][j])
            {
                d[j] = a[k][j];
                f[j] = k;
            }
        }
        return tot;
    }
    void dfs(int x)
    {
        for (int i = 0; i < n; i++)
            if (f[i] == x && a[x][i] < 1000000000 && a[x][i] != -1)
        {
            dfs(i);
            for (int j = 0; j < n; j++) b[x][j] = min(b[x][j],b[i][j]);
        }
        for (int i = 0; i < n; i++)
        if (i != f[x]) b[x][i] = min(b[x][i],a[x][i]);
    }
    int main()
    {
        while (scanf("%d%d",&n,&m) != EOF)
        {
            if (n == 0 && m ==0) break;
            memset(a,63,sizeof(a));
            for (int i = 1; i <= m; i++)
            {
                scanf("%d%d%d",&x,&y,&z);
                if (x != y) a[x][y] =a[y][x] = z;
            }
            int ans = prim();

            memset(b,63,sizeof(b));
            for (int i = 0; i < n; i++) a[i][i] = -1;

            f[0] = -1;

            dfs(0);
            int q;
            scanf("%d",&q);
            long long sum = 0;
            //cout<<ans<<endl;
            for (int i = 0; i < q; i++)
            {
                scanf("%d%d%d",&x,&y,&z);
                if (f[x] == y)
                {
                    int minn = 1000000000;
                    sum = sum + ans;
                    sum -= a[x][y];
                    for (int j = 0; j < n; j++)
                    if (j != y && b[x][j] != -1) minn = min(minn,b[x][j]);
                    for (int j = 0; j < n; j++)
                    if (f[j] == x && b[j][y] != -1) minn = min(minn,b[j][y]);
                    minn = min(minn,z);
                    sum += minn;
                }
                else if (f[y] == x)
                {
                    int minn = 1000000000;
                    sum = sum + ans;
                    sum -= a[y][x];
                    for (int j = 0; j < n; j++)
                    if (j != x && b[y][j] != -1) minn = min(minn,b[y][j]);
                    for (int j = 0; j < n; j++)
                    if (f[j] == y && b[j][x] != -1) minn = min(minn,b[j][x]);
                    minn = min(minn,z);
                    sum += minn;
                }
                else sum += ans;
            }
            double fin = sum;
            fin = fin / q;
            printf("%.4f\n",fin);
        }
        return 0;
    }

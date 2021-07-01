# 题目
Xuanxuan has n sticks of different length. One day, she puts all her sticks in a line, represented by S1, S2, S3, ...Sn. After measuring the length of each stick Sk (1
Now given the length of S1, S2, S3, …Sn, you are required to find the maximum value j - i.

输入描述

The input contains multiple test cases. Each case contains two lines.

Line 1: a single integer n (n Line 2: n different positive integers (not larger than 100000), indicating the length of each stick in order.

输出描述

Output the maximum value j - i in a single line. If there is no such i and j, just output -1.

输入例子
* 4
* 5 4 3 6
* 4
* 6 5 4 3


输出例子
* 1
* -1

# 参考答案
    #include <cstdio>
    #include <cstring>
    #include <algorithm>
    #define MX 55555
    #define lson l,m,n<<1
    #define rson m+1,r,n<<1|1
    #define lc n<<1
    #define rc n<<1|1
    using namespace std;
    int num[MX], ma[MX << 2], mi[MX << 2];
    int L, R, N, ans;
    inline void up(int n)
    {
        ma[n] = num[ma[lc]] > num[ma[rc]] ? ma[lc] : ma[rc];
        mi[n] = num[mi[lc]] < num[mi[rc]] ? mi[lc] : mi[rc];
    }
    void B(int l = 1, int r = N, int n = 1)
    {
        if (l == r)
        {
            scanf("%d", &num[l]);
            ma[n] = mi[n] = l;
            return;
        }
        int m = l + r >> 1;
        B(lson), B(rson), up(n);
    }
    int QA(int l = 1, int r = N, int n = 1)
    {
        if (L <= l && r <= R)
            return ma[n];
        int ans = 0, m = l + r >> 1, t;
        if (L <= m)
            t = QA(lson), ans = (num[ans] > num[t]) ? ans : t;
        if (m < R)
            t = QA(rson), ans = (num[ans] > num[t]) ? ans : t;
        return ans;
    }
    int QB(int l = 1, int r = N, int n = 1)
    {
        if (L <= l && r <= R)
            return mi[n];
        int ans = N + 1, m = l + r >> 1, t;
        if (L <= m)
            t = QB(lson), ans = (num[ans] < num[t]) ? ans : t;
        if (m < R)
            t = QB(rson), ans = (num[ans] < num[t]) ? ans : t;
        return ans;
    }
    int S(int l, int r)
    {
        if (l >= r) return -1;
        L = l, R = r;
        int ans = -1, a = QA(), b = QB();
        if (a > b)
            ans = max(a - b, max(S(l, b), S(a, r)));
        else ans = max(S(a + 1, b - 1), max(S(l, a), S(b, r)));
        return ans;
    }
    int main()
    {
        while (~scanf("%d", &N))
        {
            B(), num[N + 1] = 111111;
            printf("%d\n", S(1, N));
        }
        return 0;
    }

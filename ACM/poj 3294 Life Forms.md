# 题目
You may have wondered why most extraterrestrial life forms resemble humans, differing by superficial traits such as height, colour, wrinkles, ears, eyebrows and the like. A few bear no human resemblance; these typically have geometric or amorphous shapes like cubes, oil slicks or clouds of dust.

The answer is given in the 146th episode of Star Trek - The Next Generation, titled The Chase. It turns out that in the vast majority of the quadrant's life forms ended up with a large fragment of common DNA.

Given the DNA sequences of several life forms represented as strings of letters, you are to find the longest substring that is shared by more than half of them.

输入描述

Standard input contains several test cases. Each test case begins with 1 ≤ n ≤ 100, the number of life forms. n lines follow; each contains a string of lower case letters representing the DNA sequence of a life form. Each DNA sequence contains at least one and not more than 1000 letters. A line containing 0 follows the last test case.

输出描述

For each test case, output the longest string or strings shared by more than half of the life forms. If there are many, output all of them in alphabetical order. If there is no solution with at least one letter, output "?". Leave an empty line between test cases.

输入例子
```
3
abcdefg
bcdefgh
cdefghi
3
xxx
yyy
zzz
0
```
输出例子
```
bcdefg
cdefgh

?
```
# 参考答案
#include<iostream>
#include<cstring>
using namespace std;
const int MAX = 100500;
const int nMAX = 105;
const int mMAX = 1005;

int n, sum[nMAX];
char str[nMAX][mMAX];
int m, num[MAX];
int sa[MAX], rank[MAX], height[MAX];
int wa[MAX], wb[MAX], wv[MAX], wd[MAX];

int cmp(int *r, int a, int b, int l)
{
    return r[a] == r[b] && r[a+l] == r[b+l];
}

void da(int *r, int n, int m)
{
    int i, j, p, *x = wa, *y = wb, *t;
    for(i = 0; i < m; i ++) wd[i] = 0;
    for(i = 0; i < n; i ++) wd[x[i]=r[i]] ++;
    for(i = 1; i < m; i ++) wd[i] += wd[i-1];
    for(i = n-1; i >= 0; i --) sa[-- wd[x[i]]] = i;
    for(j = 1, p = 1; p < n; j *= 2, m = p)
    {
        for(p = 0, i = n-j; i < n; i ++) y[p ++] = i;
        for(i = 0; i < n; i ++) if(sa[i] >= j) y[p ++] = sa[i] - j;
        for(i = 0; i < n; i ++) wv[i] = x[y[i]];
        for(i = 0; i < m; i ++) wd[i] = 0;
        for(i = 0; i < n; i ++) wd[wv[i]] ++;
        for(i = 1; i < m; i ++) wd[i] += wd[i-1];
        for(i = n-1; i >= 0; i --) sa[-- wd[wv[i]]] = y[i];
        for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i ++)
        {
            x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p - 1 : p ++;
        }
    }
}

void calHeight(int *r, int n)
{
    int i, j, k = 0;
    for(i = 1; i <= n; i ++) rank[sa[i]] = i;
    for(i = 0; i < n; height[rank[i ++]] = k)
    {
        for(k ? k -- : 0, j = sa[rank[i]-1]; r[i+k] == r[j+k]; k ++);
    }
}

int getId(int k)                         
{
    int low = 0, high = n - 1, mid;
    while(low < high)
    {
        mid = (low+high) / 2;
        if(sum[mid] < k) {
            low = mid + 1;
        }else {
            high = mid;
        }
    }
    return low;
}

bool valid(int len, int out = 0)
{
    int i = n + 1, j, k, id, cnt;
    bool f[nMAX];
    while(1)
    {
        while(i <= m && height[i] < len) i ++;
        if(i > m) break;
        memset(f, 0, sizeof(f));
        id = getId(sa[i-1]);
        f[id] = true;
        cnt = 1;
        while(i <= m && height[i] >= len)
        {
            id = getId(sa[i]);
            if(!f[id]) {
                f[id] = true;
                cnt ++;
            }
            i ++;
        }
        if(out == 0) {
            if(2 * cnt > n) return true;
        }else {
            if(2 * cnt > n) {
                for(k = sa[i-1], j = 0; j < len; k ++, j ++)
                {
                    printf("%c", num[k] + 'a' - 100);
                }
                printf("\n");
            }
        }
    }
    return false;
}

int main()
{
    int i, j, k;
    while(scanf("%d", &n) && n != 0)
    {
        scanf("%s", str[0]);
        if(n == 1) {
            printf("%s\n\n", str[0]);
            continue;
        }
        sum[0] = strlen(str[0]);
        for(i = 1; i < n; i ++)
        {
            scanf("%s", str[i]);
            sum[i] = sum[i-1] + strlen(str[i]) + 1;
        }
        for(k = i = 0; i < n; i ++)
        {
            for(j = 0; j < strlen(str[i]); j ++)
            {
                num[k ++] = str[i][j] - 'a' + 100;
            }
            num[k ++] = i;
        }
        m = k - 1;
        da(num, m + 1, 130);
        calHeight(num, m);
        int low = 0, high = m, mid;
        while(low < high)                
        {
            mid = (low+high+1) / 2;
            if(valid(mid)) {
                low = mid;
            }else {
                high = mid - 1;
            }
        }
        if(low == 0) {
            printf("?\n\n");
        }else {                          
            valid(low, 1);
            printf("\n");
        }
    }
    return 0;

}

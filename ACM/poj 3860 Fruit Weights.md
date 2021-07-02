# 题目
Have you ever thought about comparing the weight of fruits? That’s what you should do in this problem! Given a series of fruit weight comparisons, you should anticipate the result of another comparison. In this problem, all fruits of the same kind are identical and have the same weights. Each fruit weight comparison is something like “a X ≤ b Y” in which a and b are positive integers, and X and Y are fruit names. Such a comparison means that the weight of a fruits of type X is less than or equal to the weight of b fruits of type Y.

输入描述

The input contains multiple test cases. Each test case starts with a line containing n, which is the number of given comparisons. Each of the next n lines gives a comparison in the form of “a X b Y” meaning that “a X ≤ b Y”. The last line of each test case contains the comparison query in the same form of “a X b Y” inquiring the comparison of “a X” and “b Y”.

A case of n = 0 shows the end of input and should not be processed. All integers in the input (except the last n which is 0) are positive and are not greater than 100. Fruit names are case-sensitive strings of (lowercase and uppercase) letters with length no more than 50.

输出描述

For each test case, write one line with your result for that test case. Your result can be one of the followings (assume the comparison query was “a X b Y”):<br>
““>=”: meaning you are sure that “a X ≥ b Y”.<br>
“==”: meaning you are sure that “a X = b Y” (i.e. you have reached both of the above results).<br>
“UNAVAILABLE”: meaning that you can say nothing for sure in comparing “a X” and “b Y” (i.e. you have reached none of the above results).<br>
“INCONSISTENT”: meaning that there is an inconsistency in the given comparisons (i.e. you are sure that all the given comparisons for that test case cannot hold at the same time).

输入例子
```
2
2 Orange 3 Apple
1 Apple 1 Peach
2 Orange 3 Peach
1
2 Orange 3 Apple
2 Orange 2 Apple
2
3 a 2 A
2 A 3 a
5 A 5 a
2
3 B 2 A
2 A 3 B
2 A 3 B
3
2 b 2 A
2 A 2 C
3 C 2 b
1 A 1 b
0
```
输出例子
```
=
==
INCONSISTENT
```
# 参考答案
```c++
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 220;
const double EPS = 1e-8;

map<string, int> mp;
string a, b;
int m, n;

double x, y;
int aid, bid;
double mat[MAXN][MAXN];

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

bool floyd() {
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i) if(mat[i][k] > 0)
            for(int j = 1; j <= n; ++j) if(mat[k][j] > 0)
                if(mat[i][j] < 0 || mat[i][k] * mat[k][j] < mat[i][j]) mat[i][j] = mat[i][k] * mat[k][j];
    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j) {
            if(mat[i][j] < 0 || mat[j][i] < 0) continue;
            if(sgn(mat[i][j] * mat[j][i] - 1) < 0) return false;
        }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    while(cin>>m) {
        if(m == 0) break;
        n = 0;
        mp.clear();
        for(int i = 1; i < MAXN; ++i) {
            for(int j = 1; j < MAXN; ++j) mat[i][j] = -1;
            mat[i][i] = 1;
        }
        for(int i = 0; i < m; ++i) {
            cin>>x>>a>>y>>b;
            if(mp.find(a) != mp.end()) aid = mp[a];
            else mp[a] = aid = ++n;
            if(mp.find(b) != mp.end()) bid = mp[b];
            else mp[b] = bid = ++n;
            if(aid == bid) continue;
            //if(mat[aid][bid] < double(x, y)) mat[aid][bid] = double(x, y);
            if(mat[bid][aid] < 0 || mat[bid][aid] > y / x) mat[bid][aid] = y / x;
        }
        cin>>x>>a>>y>>b;
        if(!floyd()) {
            puts("INCONSISTENT");
            continue;
        }
        if(mp.find(a) == mp.end() || mp.find(b) == mp.end()) {
            puts("UNAVAILABLE");
            continue;
        }
        aid = mp[a];
        bid = mp[b];
        if(sgn(mat[aid][bid] - x / y) == 0  && sgn(mat[bid][aid] - y / x) == 0) {
            puts("==");
            continue;
        }
        if(mat[bid][aid] > 0 && sgn(mat[bid][aid] - y / x) <= 0) {
            puts("<=");
            continue;
        }
        if(mat[aid][bid] > 0 && sgn(mat[aid][bid] - x / y) <= 0) {
            puts(">=");
            continue;
        }
        puts("UNAVAILABLE");
    }
}





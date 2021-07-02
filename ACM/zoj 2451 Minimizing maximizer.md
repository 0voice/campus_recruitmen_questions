# 题目
The company Chris Ltd. is preparing a new sorting hardware called Maximizer. Maximizer has N inputs numbered from 1 to N. Each input represents one integer. Maximizer has one output which represents the maximum value present on Maximizer's inputs.

Maximizer is implemented as a pipeline of sorters Sorter(i[1], j[1]), ..., Sorter(i[k], j[k]). Each sorter has N inputs and N outputs. Sorter(i, j) sorts values on inputs i, i+1, ..., j in non-decreasing order and lets the other inputs pass through unchanged. The N-th output of the last sorter is the output of the Maximizer.

An intern (a former ACM contestant) observed that some sorters could be excluded from the pipeline and Maximizer would still produce the correct result. What is the length of the shortest subsequence of the given sequence of sorters in the pipeline still producing correct results for all possible combinations of input values?

Task

Write a program that:

reads the description of a Maximizer, i.e. the initial sequence of sorters in the pipeline,<br>
computes the length of the shortest subsequence of the initial sequence of sorters still producing correct results for all possible input data,<br>
writes the result.<br>
Input Specification<br>
The input consists of several test cases.<br>
For each case, the first line contains two integers N and M (2 &lt= N &lt= 50 000, 1 &lt= M &lt= 500 000) separated by a single space. Integer N is the number of inputs and integer M is the number of sorters in the pipeline. The initial sequence of sorters is described in the next M lines. The k-th of these lines contains the parameters of the k-th sorter: two integers i[k] and j[k] (1 &lt= i[k] &lt j[k] &lt= N) separated by a single space.

Output Specification<br>
For each test case, print in one line the length of the shortest subsequence of the initial sequence of sorters still producing correct results for all possible data.

Sample Input
```
40 6
20 30
1 10
10 20
20 30
15 25
30 40
```
Output for the Sample Input
```
4
```

# 参考答案
```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <stack>
#include <string>
#include <list>
#include <queue>
#include <map>
#include <vector>
#include <deque>
#include <set>
using namespace std;

#ifdef WIN32
#define INT64 "%I64d"
#define UINT64 "%I64u"
#else
#define INT64 "%lld"
#define UINT64 "%llu"
#endif

#define INF 0x3f3f3f3f
#define eps 1e-8
#define PI acos(-1.)
#define PI2 asin (1.);
typedef long long LL;
typedef unsigned int ui;
typedef unsigned long long ui64;
#define MP make_pair
typedef vector<int> VI;
typedef pair<int, int> PII;
#define pb push_back
#define mp make_pair

#define CL(a,b) memset (a, b, sizeof (a))
#define sqr(a,b) sqrt ((double)(a)*(a) + (double)(b)*(b))
#define sqr3(a,b,c) sqrt((double)(a)*(a) + (double)(b)*(b) + (double)(c)*(c))

template <typename T> double DIS(T va, T vb) { return sqr(va.x - vb.x, va.y - vb.y); }
template <class T> inline T INTEGER_LEN(T v) { int len = 1; while (v /= 10) ++len; return len; }
template <typename T> inline T square(T va, T vb) { return va * va + vb * vb; }

// aply for the memory of the stack
//#pragma comment (linker, "/STACK:1024000000,1024000000")
//end

#define MAXN 50005
#define CY 4 * MAXN

int L[CY], R[CY], seg[CY];
int n, M;

void build(int id, int lt, int rt) {
	L[id] = lt; R[id] = rt;
	seg[id] = M + 1;
	if (lt == rt) return ;
	int mid = (lt + rt) >> 1;
	int lc = id << 1, rc = lc + 1;
	build(lc, lt, mid);
	build(rc, mid + 1, rt);
}

void update(int id, int p, int val) {
	seg[id] = min(seg[id], val);
	if (L[id] == R[id]) return ;
	int mid = (L[id] + R[id]) >> 1;
	int lc = id << 1, rc = lc | 1;
	if (p <= mid) update(lc, p, val);
	else update(rc, p, val);
}

int query(int id, int lt, int rt) {
	if (L[id] == lt && R[id] == rt) {
		return seg[id];
	}
	int mid = (L[id] + R[id]) >> 1;
	int lc = id << 1, rc = lc | 1;
	if (rt <= mid) return query(lc, lt, rt);
	else if (lt > mid) return query(rc, lt, rt);
	else {
		return min(query(lc, lt, mid), query(rc, mid + 1, rt));
	}
}

int main(void) {
	while (2 == scanf("%d%d", &n, &M)) {
		build(1, 1, n);
		update(1, 1, 0);
		int a, b;
		while (M--) {
			scanf("%d%d", &a, &b);
			int value = query(1, a, b - 1);
			update(1, b, value + 1);
		}
		printf("%d\n", query(1,n, n));
	}
	return 0;
}





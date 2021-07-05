# 题目
There are <var>n</var> people standing in a row. And There are <var>m</var> numbers, 1.2...m. Every one should choose a number. But if two persons standing adjacent to each other choose the same number, the number shouldn't equal or less than <var>k</var>. Apart from this rule, there are no more limiting conditions.

And you need to calculate how many ways they can choose the numbers obeying the rule.

Input
There are multiple test cases. Each case contain a line, containing three integer n (2 ≤ n ≤ 10<sup>8</sup>), m (2 ≤ m ≤ 30000), k(0 ≤ k ≤ m).

Output
One line for each case. The number of ways module 1000000007.

Sample Input
```
4 4 1
```
Sample Output
```
216
```
# 参考答案
```c++
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <cmath>
#include <ctime>

using namespace std;

typedef long long LL;
const LL MOD = 1000000007;
struct Mat {
	LL val[2][2];
	void init(LL v = 0) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) val[i][j] = 0;
			val[i][i] = v;
		}
	}
	void print() {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) cout << val[i][j] << ' ';
			cout << endl;
		}
	}
} base, op;

Mat operator * (Mat a, Mat b) {
	Mat ret;
	ret.init();
	for (int i = 0; i < 2; i++) {
		for (int k = 0; k < 2; k++) {
			if (a.val[i][k]) {
				for (int j = 0; j < 2; j++) ret.val[i][j] += a.val[i][k] * b.val[k][j] % MOD, ret.val[i][j] %= MOD;
			}
		}
	}
	return ret;
}

Mat operator ^ (Mat a, int p) {
	Mat ret;
	ret.init(1);
	while (p > 0) {
		if (p & 1) ret = ret * a;
		a = a * a, p >>= 1;
	}
	return ret;
}

void cal(LL n, LL m, LL k) {
	LL dp[10][2];
	k = m - k;
	dp[1][0] = k, dp[1][1] = m - k;
	for (int i = 2; i <= n; i++) {
		dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) * k;
		dp[i][1] = dp[i - 1][0] * (m - k) + dp[i - 1][1] * (m - k - 1);
	}
	for (int i = 0; i < 2; i++) cout << dp[n][i] << endl;
	cout << dp[n][0] + dp[n][1] << endl;
}

int main() {
	LL n, m, k;
	while (cin >> n >> m >> k) {
		k = m - k;
		op.val[0][0] = op.val[1][0] = k;
		op.val[0][1] = m - k, op.val[1][1] = m - k - 1;
		base.init();
		base.val[0][0] = k, base.val[0][1] = m - k;
		base = base * (op ^ (n - 1));
		cout << (base.val[0][0] + base.val[0][1]) % MOD << endl;
	}
	return 0;
}




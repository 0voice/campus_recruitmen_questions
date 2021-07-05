# 题目
Jack helps his mentor build a simple distributed storage system. He uses several servers and connects them as the following topology:

![](http://uploadfiles.nowcoder.com/probs/acm/poj_5283desc_0.jpg)

This distributed storage system contains a group of backend servers and a master server. The backend servers are different from each other while they store identical data, and all of them are invisible to client. When a client machine needs a file, it sends request to a master server. The master server collects different part of the file from some of backend servers. The strategy of the master is like follows.

Each backend server has its own processing throughput and transmission bandwidth. The master server knows that i<sup>th</sup>backend server’s throughput is p<sub>i</sub> (MB/s) and bandwidth is b<sub>i</sub> (MB/s). As the result, omitted the propagation time, handling size of f<sub>i</sub> MB data and sending to master machine needs time:

Total time = Processing time + Transmission time = f<sub>i</sub> / p<sub>i</sub> + f<sub>i</sub> / b<sub>i<sub>

In addition, handling 1 MB data on ith server costs c<sub>i</sub>. (Including electricity consumption and maintenance cost, etc.) In order to minimize the total cost, the master server should carefully decide which backends should be used and how much load they should process. At the same time, because of some consistency consideration, every time the master should choose exactly K backend servers to extract file, and each of them should take exactly the same time to finish the job.

Your task is to write a scheduling program for the master server. Assuming the size of the file is F MB, and the file can be infinitely divided.

输入描述

The first line contains two integers N and K (K≤ N ≤ 20000), and a real number F. The master should choose exactly K machines among total N backend servers. The F is the size of the file.

The following N lines describe the details of each backend servers. Each line contains three real numbers, p<sub>i</sub>, b<sub>i</sub> and c<sub>i</sub>, representing the processing throughput, bandwidth and unit cost.

输出描述

The output file contains only one real number, the minimum cost. The answer is less than 10000000000 and should be rounded to four digits

输入例子
```
3 2 2
1 1 2
1 1 1
2 2 10
```
输出例子
```
3.0000
```
Hint

In the sample case, the master should choose the first two backend machines. Each of them should handle 1 MB part of the file (total is 2 MB) in order to make the finishing time identically (2 second). The total cost is 1*2+1*1 = 3.0000
# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn = 211111;
const double eps = 1e-6;
typedef long long LL;
struct node {
	double w, v, val;
	node() {
	}
	node(double w, double v) :
			w(w), v(v) {
		val = 0;
	}
	bool operator<(const node& t) const {
		return val < t.val;
	}
} f[maxn];
double F;
int main() {
	int n, k, i;
	double w, p, b, v, c;
	scanf("%d%d%lf", &n, &k, &F);
	for (i = 0; i < n; ++i) {
		scanf("%lf%lf%lf", &p, &b, &c);
		v = (p * b) / (p + b);
		f[i] = node(v * c * F, v);
	}
	double rate = 0, pre = -100;
	rate = f[0].w / f[0].v;
	for (i = 0; i < n; ++i)
		f[i].val = f[i].w - f[i].v * rate;
	while (fabs(rate - pre) > eps) {
		pre = rate;
		w = v = 0;
		sort(f, f + n);
		for (i = 0; i < k; ++i)
			w += f[i].w, v += f[i].v;
		rate = w / v;
		for (i = 0; i < n; ++i)
			f[i].val = f[i].w - f[i].v * rate;
	}
	printf("%.4f\n", rate);
	return 0;
}




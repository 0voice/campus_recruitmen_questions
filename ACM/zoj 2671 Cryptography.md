# 题目
Young cryptoanalyst Georgie is planning to break the new cipher invented by his friend Andie. To do this, he must make some linear transformations over the ring Z<sub>r</sub> = Z/rZ.

Each linear transformation is defined by 2×2 matrix. Georgie has a sequence of matrices A<sub>1</sub> , A<sub>2</sub> ,..., A<sub>n</sub> . As a step of his algorithm he must take some segment A<sub>i</sub> , A<sub>i+1</sub> , ..., A<sub>j</sub> of the sequence and multiply some vector by a product P<sub>i</sub>,j=A<sub>i</sub> × A<sub>i</sub>+1 × ... × A<sub>j</sub> of the segment. He must do it for m various segments.

Help Georgie to determine the products he needs.

Input

There are several test cases in the input. The first line of each case contains r (1 <= r <= 10,000 ), n (1 <= n <= 30,000 ) and m (1 <= m <= 30,000 ). Next n blocks of two lines, containing two integer numbers ranging from 0 to r - 1 each, describe matrices. Blocks are separated with blank lines. They are followed by m pairs of integer numbers ranging from 1 to n each that describe segments, products for which are to be calculated.
There is an empty line between cases.

Output

Print m blocks containing two lines each. Each line should contain two integer numbers ranging from 0 to r - 1 and define the corresponding product matrix.
There should be an empty line between cases.

Separate blocks with an empty line.

Sample

Input
```
3 4 4
0 1
0 0

2 1
1 2

0 0
0 2

1 0
0 2

1 4
2 3
1 3
2 2
```

Output
```
0 2
0 0

0 2
0 1

0 1
0 0

2 1
1 2
```
# 参考答案
```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

#define maxn 111111
#define lson l, m, rt << 1
#define rson m+1, r, rt << 1 | 1

int mod;

struct Matrix {
 int d[2][2];
 void clearit() {
 d[0][0] = d[1][1] = 1;
 d[1][0] = d[0][1] = 0;
 }
 Matrix() {
 clearit();
 }
 Matrix operator + (const Matrix & _m) const {
 Matrix ans;
 for(int i=0; i<2; i++) {
 for(int j=0; j<2; j++) {
 ans.d[i][j] = 0;
 for(int k=0; k<2; k++) {
 ans.d[i][j] = (ans.d[i][j] + d[i][k] * _m.d[k][j]) % mod;
 }
 }
 }
 return ans;
 }
 void printit() {
 for(int i=0; i<2; i++) {
 for(int j=0; j<2; j++) {
 printf("%d%c", d[i][j], j==1?'\n':' ');
 }
 }
 }
};

Matrix tree[maxn<<2];

void PushUp(int rt) {
 tree[rt] = tree[rt<<1] + tree[rt<<1|1];
}

void build(int l, int r, int rt) {
 tree[rt].clearit();
 if(l == r) {
 for(int i=0; i<2; i++) {
 for(int j=0; j<2; j++) {
 scanf("%d", &tree[rt].d[i][j]);
 }
 }
 return ;
 }
 int m = (l + r) >> 1;
 build(lson);
 build(rson);
 PushUp(rt);
}

Matrix query(int L, int R, int l, int r, int rt) {
 if(L <= l && r <= R) {
 return tree[rt];
 }
 int m = (l + r) >> 1;
 Matrix ret;
 if(L <= m) ret = ret + query(L, R, lson);
 if(m < R) ret = ret + query(L, R, rson);
 return ret;
}

void scanfit(Matrix &m) {
 for(int i=0; i<2; i++) {
 for(int j=0; j<2; j++) {
 scanf("%d", &m.d[i][j]);
 }
 }
}

int main()
{
 int n, q;
 int flag = 1;
 while(scanf("%d%d%d", &mod, &n, &q) == 3){
 if(flag == 0) printf("\n");
 flag = 0;
 build(1, n, 1);
 int l, r;
 for(int i=0; i<q; i++) {
 scanf("%d%d", &l, &r);
 Matrix ans = query(l, r, 1, n, 1);
 ans.printit();
 if(i != q-1) printf("\n");
 }
 }
 return 0;
}

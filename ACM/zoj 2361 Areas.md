# 题目
Consider N different lines on the plane. They divide it to several parts, some of which are finite, some infinite.

Your task in this problem is for each finite part to find its area.


This problem contains multiple test cases!

The first line of a multiple input is an integer N, then a blank line followed by N input blocks. Each input block is in the format indicated in the problem description. There is a blank line between input blocks.

The output format consists of N output blocks. There is a blank line between output blocks.


Input

The first line of the input file contains N �� the number of lines (1 1, y1, x2 and y2 - the coordinates of two different points of the line.

All coordinates do not exceed 102 by their absolute value.

No two lines coincide.

Output

First output K - the number of finite parts among those the lines divide the plane to.

Next K lines of the output file must contain area parts sorted in non-decreasing order. You answer must be accurate up to 10-4.

Due to floating point precision losses possible, do not consider parts with area not exceeding 10-8.

Sample Input
```
1

5
0 0 1 0
1 0 1 1
1 1 0 1
0 1 0 0
0 0 1 1
```
Sample Output
```
2
0.5000
0.5000
```
# 参考答案
```c++
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;

#define sfll(x) scanf("%I64d",&x)
#define sfint(x) scanf("%d",&x)
#define sfstr(c) scanf("%s",c)
#define fr(i,s,n) for(int i=s;i<n;++i)
#define cl(a) memset(a,0,sizeof(a))

#define SIZE(x) ( (int)(x.size()))
#define PB push_back
#define MP make_pair

typedef pair<double,double > point;
#define X first
#define Y second

const double eps = 1e-8;
const double pi = acos(-1.);
const int maxm = 200000;
const int maxp = 20000;
const int maxn = 90;

int e[maxm],prev[maxm],mark[maxm],tote;
int info[maxp];

int N,P;
point a[maxn],b[maxn];
point p[maxp];

bool zero(double x){
 return fabs(x) < eps;
}
point operator - (const point &a ,const point &b){
 return MP(a.X - b.X ,a.Y - b.Y);
}

point operator * ( const point &a, double k) {
 return point(a.X * k ,a.Y * k);
}

point operator / (const point &a,double k){
 return point(a.X / k,a.Y/k);
}
double getAngle(const point &a){
 return atan2(a.Y , a.X);
}
double det(const point &a,const point &b){
 return a.X * b.Y - a.Y * b.X;
}
bool operator == ( const point &a,const point &b){
 return zero(a.X - b.X) && zero(a.Y - b.Y);
}
bool intersect(const point &a , const point &b ,const point &c,const point &d,point &res){
 double k1 = det(b-a , c-a) , k2 = det(b - a, d - a);
 if( zero(k1 - k2)) return false;
 res = (d * k1 - c * k2) / (k1 - k2);
 return true;
}
void addedge(int x,int y){
 e[tote] = y;prev[tote] = info[x];info[x] = tote++;
 e[tote] = x;prev[tote] = info[y];info[y] = tote++;
}
vector<double > Devide(){
 P = 0;
 fr(i , 0 ,N){
 fr(j ,i+1,N){
 if(intersect(a[i] , b[i], a[j], b[j], p[P])) ++P;
 }
 }
 sort(p , p +P);
 int tot = 1;
 for(int i = 1; i < P;++i){
 if(!(p[i] == p[tot-1])) p[tot++] = p[i];
 }
 P = tot;
 cl(info);
 tote = 2;
 fr(i , 0 ,N){
 int last = -1;
 fr(j , 0 ,P){
 if( zero(det(b[i] - a[i],p[j] - a[i]))){
 if(last != -1) addedge(last,j);
 last = j;
 }
 }
 }
 cl(mark);
 vector<double> area;
 fr(i ,2, tote){
 if( !mark[i]){
 int laste = i^1;
 int lastp = e[i];
 int head = e[laste];
 mark[i] = true;
 double ans ;
 for(ans = det(p[head], p[lastp]) ; lastp != head; ) {
 double best = 1E20;
 int cur = -1;
 double base = getAngle(p[e[laste]] - p[lastp]);
 for(int k = info[lastp] ; k ; k = prev[k]) {
 if(k != laste){
 double tmp = getAngle(p[e[k]] - p[lastp]) - base;
 if(tmp < 0) tmp += pi*2;
 if(tmp >= pi * 2) tmp -= pi*2;
 if( tmp < best){
 best = tmp;
 cur = k;
 }
 }
 }
 ans += det(p[lastp] , p[e[cur]]);
 lastp = e[cur];
 laste = cur ^ 1;
 mark[cur] = true;
 }
 area.PB(fabs(ans) * .5);
 }

 }
 sort(area.begin(),area.end());
 if( SIZE(area) ) area.erase(area.end() - 1);
 return area;
}

namespace Sol{
 void sol(){
 int t;
 sfint(t);
 while(t--){
 int n;
 sfint(n);
 N = n;
 fr(i , 0 ,n){
 scanf("%lf %lf %lf %lf",&a[i].X,&a[i].Y,&b[i].X,&b[i].Y);
 }
 vector<double> ans = Devide();
 printf("%d\n",ans.size());
 fr(i , 0 ,ans.size()){
 printf("%.5f\n",ans[i]);
 }
 }
 }
}
int main(){
 Sol::sol();
	return 0;
}




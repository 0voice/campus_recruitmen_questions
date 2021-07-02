# 题目
Tom is good at making stean, he can make steans of various color and shape. Now he want to know how many water it can contain, and how many material he need to making a stean.

![zoj_1717desc_0](http://uploadfiles.nowcoder.com/probs/acm/zoj_1717desc_0.jpg)

The shape of the stean follows rules below:

1. The horizontal projection is a circle. The front projection contains two cosine curve. Tom can pour water from the top of stean.

2.To describe it more clearly, Tom constructs a cylindrical coordinate system. Tom is a strange person, because if there no stean at all when <var>Z1</var> is equal to <var>Z2</var>, he still asks you. Tom tells you origin of coordinates is on the axis of cylinder , <var>Z</var>-axis is the axis of cylinder. And he measures that the height of undersurface <var>Z1</var> and the height of upsurface of the stean <var>Z2</var>. And he find the formula of cosine curve is <var>R</var> = 2 + cos(<var>Z</var>).Here <var>R</var> is the inner circle's radius.

Now you need to tell him the capacity and the area of internal surface, which are in direct proportional to water tank capacity and material needed. You need to be precise to two digits after float point.

Input

The first line of the input contains a single integer <var>T</var> (1 <= <var>T</var> <= 300), which denotes the number of test cases. Then each line contains a case, consisted by a pair of integer numbers <var>Z1</var> and <var>Z2</var> (|<var>Z1</var>| <= 1000.00, |<var>Z2</var>| <= 1000.00). They are separated by a space.

Output

There are <var>T</var> lines, each line contains a floating point number, the capacity and the area of internal surface. An answer with absolute error less than 10-2 or with relative error less than 10-5 will be accepted.

Sample Input
```
2
0 3.14159
-0.0001 0.0
```
Sample Output
```
44.41 76.28
0.00 28.27
```
# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<set>
#include<map>
#include<stack>
#include<vector>
#include<queue>
#include<string>
#include<sstream>
#define eps 1e-9
#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define MAXN 20005
#define MAXM 40005
#define INF 0x3fffffff
#define PB push_back
#define MP make_pair
#define X first
#define Y second
#define clr(x,y) memset(x,y,sizeof(x));
using namespace std;
typedef long long LL;
int i,j,k,n,m,x,y,T,ans,big,cas,num,len;
bool flag;
const double pi=acos(-1.0);
double l,r;

double f(double u)
{
    return cos(u)+2.0;
}

double df(double u)
{
    return (2.0+cos(u))*sqrt(1.0+sin(u)*sin(u));
}

double xps(double l,double r)
{
    return (r-l)*(df(r)+4.0*df((l+r)/2)+df(l))/6.0;
}

double f2(double u)
{
    return 4.0*sin(u)+sin(u*2.0)/4.0+9.0*u/2.0;
}

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%lf%lf",&l,&r);
        double ans=0;
        double g=l;
        double h=(r-l)/5001;
        for (i=1;i<=5001;i++)
        {
            ans+=xps(g,g+h);
            g+=h;
        }
        printf("%.2lf ",pi*(f2(r)-f2(l)));
        printf("%.2lf\n",2.0*pi*ans+pi*f(l)*f(l));
    }
}





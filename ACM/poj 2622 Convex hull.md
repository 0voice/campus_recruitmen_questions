# 题目
et a finite set of points M be defined on plane. The plane has a usual Cartesian coordinates. Well-formed convex hull of set M is minimal (relative to inclusion) set, containing M, and bounded by closed broken line. All sections of this broken line should be parrallel to axes or inclined by 45°.
Your task is to find a well-formed convex hull for a given set M.

输入描述

In the first line an numbe

输出描述

Your program should print the sequence of broken line's vertexes. Vertexes should be enumretated in the counter clock-wise order. As a first vertex any of them can be taken. In every line exactly one vertex's coordinates (two numbers, separated by spaces) should be put out. Every vertex of broken line should be mentioned in the file only once.

No three consecutive vertexes of broken line should lie on a straight line.

输入例子
```
4
3 3
3 1
2 2
4 2
```
输出例子
```
3 1
4 2
3 3
2 2
```
# 参考答案
```c++
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#define MAXN 200020
#define INF 999999
#define eps 1e-8
using namespace std;
struct pt
{
	double x, y;
	pt operator - (const pt &p1){return (pt){x - p1.x, y - p1.y};}
	pt operator + (const pt &p1){return (pt){x + p1.x, y + p1.y};}
	pt operator / (double r){return (pt){x / r, y / r};}
	pt operator * (double r){return (pt){x * r, y * r};}
	bool operator < (const pt &p1)const{return y < p1.y - eps || fabs(y-p1.y)<eps && x < p1.x;}
	bool operator == (const pt &p1)const{return x == p1.x && y == p1.y;}

	bool operator != (const pt &p1)const{return x != p1.x || y != p1.y;}
};

int dcmp (double x) {return x < -eps ? -1 : x > eps;}

double cpr(const pt &a,const pt &b,const pt &c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}
double dpr(const pt &a,const pt &b,const pt &c){return (b.x-a.x)*(c.x-a.x)+(b.y-a.y)*(c.y-a.y);}

double cpr(const pt &a,const pt &b){return a.x*b.y-a.y*b.x;}
double dpr(const pt &a,const pt &b){return a.x*b.x+a.y*b.y;}

double vlen(const pt &a){return sqrt(a.x*a.x+a.y*a.y);}
double dis(const pt &a, const pt &b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}

void make_ch(pt *p, pt *f, int n, int &top)
{
	top = 0;
	sort(p, p + n);
	for (int i = 0; i < 2*n-1; i++)
	{
		int j = (i < n) ? i : 2*(n-1)-i;
		while (top > 1 && cpr(f[top-2], f[top-1], p[j]) < -eps)
			top--;
		f[top++] = p[j];
	}
	top--;
}

pt its(const pt &a, const pt &b, const pt &c, const pt &d)
{
	pt ret = a;
	double t =((c.x - a.x)*(d.y - c.y) - (c.y - a.y)*(d.x - c.x))/
	   			((b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x));
	ret.x += (b.x - a.x) * t;
	ret.y += (b.y - a.y) * t;
	return ret;
}

pt ori[MAXN];
pt dest[MAXN];
int n, num;
double tp = -INF, dn = INF, lf = INF, rt = -INF;
pt left_top, left_down, right_top, right_down;

void init()
{
	int i;
	tp = rt = -INF;
	dn = lf = INF;
	memset (ori, 0, sizeof ori);
	memset (dest, 0, sizeof dest);
	for (i = 0; i < n; i++)
		scanf ("%lf%lf", &ori[i].x, &ori[i].y);
	make_ch(ori, dest, n, num);

	for (i = 0; i < num; i++)
	{
		if (dcmp(dest[i].y - tp) == 1) {tp = dest[i].y;}
		if (dcmp(dn - dest[i].y) == 1) {dn = dest[i].y;}
		if (dcmp(dest[i].x - rt) == 1) {rt = dest[i].x;}
		if (dcmp(lf - dest[i].x) == 1) {lf = dest[i].x;}
	}
	left_top.x = lf; left_top.y = tp;
	left_down.x = lf; left_down.y = dn;
	right_top.x = rt; right_top.y = tp;
	right_down.x = rt; right_down.y = dn;

}

void Solve()
{
	double plt, pld, prt, prd, ptl, ptr, pdl, pdr;
	pt cross, a, b;
	pt res[10];
	int i;
	memset (res, 0, sizeof res);

	plt = prt = dn;
	pld = prd = tp;
	ptl = pdl = rt;
	ptr = pdr = lf;
	for (i = 0; i < num; i++)
	{
		a = dest[i];
		b = a + (pt){-1, 1};	//鍙充笅绾�	
		cross = its(a, b, left_top, left_down);

		if (dcmp(pld - cross.y) == 1) {pld = cross.y;}
		cross = its(a, b, left_down, right_down);

		if (dcmp(pdl - cross.x) == 1) {pdl = cross.x;}
		cross = its(a, b, left_top, right_top);

		if (dcmp(cross.x - ptr) == 1) {ptr = cross.x;}
		cross = its(a, b, right_top, right_down);

		if (dcmp(cross.y - prt) == 1) {prt = cross.y;}
		b = a + (pt){1, 1};	//鍙充笂绾�	
		cross = its(a, b, left_top, left_down);

		if (dcmp(cross.y - plt) == 1) {plt = cross.y;}
		cross = its(a, b, left_top, right_top);

		if (dcmp(ptl - cross.x) == 1) {ptl = cross.x;}
		cross = its(a, b, left_down, right_down);

		if (dcmp(cross.x - pdr) == 1) {pdr = cross.x;}
		cross = its(a, b, right_top, right_down);

		if (dcmp(prd - cross.y) == 1) {prd = cross.y;}

	}
	res[0] = (pt){lf, plt}; res[1] = (pt){lf, pld};
	res[2] = (pt){pdl, dn};	res[3] = (pt){pdr, dn};
	res[4] = (pt){rt, prd}; res[5] = (pt){rt, prt};
	res[6] = (pt){ptr, tp}; res[7] = (pt){ptl, tp};
	for (i = 0; i < 8; i++)
		if (dcmp(dis(res[i], res[(i + 1) % 8])) > 0)
			printf("%.6f %.6f\n", res[i].x, res[i].y);

}

int main()
{

		scanf ("%d", &n);
		init();
		if (n != 1) {Solve();}
		else {printf("%.6f %.6f\n", ori[0].x, ori[0].y);}

	return 0;
}




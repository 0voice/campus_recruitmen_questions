# 题目
Just when you thought we had run out of model rocket height problems...

Yet another method used to determine the height achieved by a model rocket is the vertical line method. Two observers A and B are spaced D feet apart along a base line along one edge of the flat test field. The launch platform is equidistant from observers A and B and L feet from the base line. Each observer has a theodolite or some other device for measuring angle above the horizontal (elevation angle) of a distant object and the azimuth angle (the angle the vertical plane of the sight line makes with the line from A through B measured counter-clockwise). Each measuring device is on a stand. A's device is HA feet above the level of the launch platform and B's device is HB feet above the level of the launch platform. When a rocket is fired, near the top of its flight, it deploys a parachute and emits a puff of smoke. Each observer measures the elevation angle and azimuth angle of the puff of smoke from their location. If the peak location is on the wrong side of the baseline or outside the lines determined by A and B perpendicular to the base line, it is out of bounds and disqualified. From this information, the height of the rocket may be determined as follows:

Each sight line determines a vertical plane. These two planes intersect in a vertical line (thus the name of the method). Each sight line intersects this vertical line in a point. If these points are more than ERRDIST feet apart, an error is assumed and the flight is rejected. Otherwise, the point halfway between the two points where a sight line intersects the vertical line is computed. The rocket height is the distance of this midpoint above the launch platform.

You must write a program which, given the parameters D (the distance in feet between observers A and B), L (the distance in feet from the base line to the launch platform), HA (the distance of the measuring device A above the launch platform in feet), HB (the distance of the measuring device B above the launch platform in feet), ERRDIST (the maximum distance between the intersection points of a sight line with the vertical line), a1(the elevation angle of the rocket in degrees measured by the left observer A),a2 (the elevation angle of the rocket in degrees observed by the right observer B), a3(the azimuth angle in degrees measured by the left observer A) and a4(the azimuth angle in degrees measured by the right observer B), computes the height of the rocket above the launch platform in feet to the nearest foot.

Input

The first line of input contains a single integer N, (1 <= N <= 1000) which is the number of datasets that follow.

The second line contains the parameters D, L, HA, HB and ERRDIST in that order as (floating point) decimal values. These values would be measured once at the beginning of the day and remain fixed through all rocket shots.

Each succeeding line of input represents a single dataset. Each dataset will contain the angles a1, a2, a3 and a4 in that order (measured in degrees) as (floating point) decimal values for a rocket shot.

Output

For each dataset of four angles, the output consists of a single line . If angles a1, a2 and a3 are not strictly between 0 and 90 degrees or a4 is not strictly between 90 degrees and 180 degrees, the line should contain the dataset number, a space and the word "DISQUALIFIED" (without the quotes). Otherwise, if the distance between the intersection points of a sight line with the vertical line is more that ERRDIST feet, the line should contain the dataset number, a space and the word "ERROR" (without the quotes). Otherwise, the line should contain the dataset number, a space and the height above the launch platform in feet to the nearest foot.

Sample Input
```
4
100.0 300.0 5.25 2.92 5.00
40.1 36.2 35.3 151.6
64.9 71.1 15.7 160.1
44.9 41.2 33.1 152.5
44.9 41.2 33.1 52.5
```
Sample Output
```
1 50
2 ERROR
3 58
4 DISQUALIFIED
```
# 参考答案
```c++
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#include <time.h>
#include <queue>
#include <set>
#include <stack>
#include <string>
#pragma comment(linker, "/STACK:1024000000,1024000000")

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define MP make_pair
#define PB push_back

typedef double TYPE;

#define Abs(x) (((x)>0)?(x):(-(x)))
#define Sgn(x) (((x)<0)?(-1):(1))
#define Max(a,b) (((a)>(b))?(a):(b))
#define Min(a,b) (((a)<(b))?(a):(b))

#define EPS 1e-6
#define Infinity 1e+6
const double Pi = acos(-1.0);

TYPE Deg2Rad(TYPE deg)
{
	return (deg * Pi / 180.0);
}

TYPE Rad2Deg(TYPE rad)
{
	return (rad * 180.0 / Pi);
}

TYPE Sin(TYPE deg)
{
	return sin(Deg2Rad(deg));
}

TYPE Cos(TYPE deg)
{
	return cos(Deg2Rad(deg));
}

TYPE ArcSin(TYPE val)
{
	return Rad2Deg(asin(val));
}

TYPE ArcCos(TYPE val)
{
	return Rad2Deg(acos(val));
}

TYPE Sqrt(TYPE val)
{
	return sqrt(val);
}

struct POINT
{
	TYPE x;
	TYPE y;
	TYPE z;
	POINT() : x(0), y(0), z(0) {};
	POINT(TYPE _x_, TYPE _y_, TYPE _z_ = 0) : x(_x_), y(_y_), z(_z_) {};
};

TYPE Cross(const POINT & a, const POINT & b, const POINT & o)
{
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

TYPE Cross(const POINT & a, const POINT &b)
{
	return a.x * b.y - a.y * b.x;
}

bool IsZero(TYPE a)
{
	return fabs(a) < EPS;
}
TYPE Distance(const POINT & a, const POINT & b)
{
	return Sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) +
		(a.z - b.z) * (a.z - b.z));
}

struct LINE
{
	POINT a;
	POINT b;
	LINE() {};
	LINE(POINT _a_, POINT _b_) : a(_a_), b(_b_) {};
};
void Coefficient(const LINE & L, TYPE & A, TYPE & B, TYPE & C)
{
	A = L.b.y - L.a.y;
	B = L.a.x - L.b.x;
	C = L.b.x * L.a.y - L.a.x * L.b.y;
}

void Coefficient(const POINT & p,const TYPE a,TYPE & A,TYPE & B,TYPE & C)
{
	A = Cos(a);
	B = Sin(a);
	C = - (p.y * B + p.x * A);
}
struct SEG
{
	POINT a;
	POINT b;
	SEG() {};
	SEG(POINT _a_, POINT _b_):a(_a_),b(_b_) {};
};

bool IsEqual(TYPE a, TYPE b)
{
	return (Abs(a - b) < EPS);
}

bool IsEqual(const POINT & a, const POINT & b)
{
	return (IsEqual(a.x, b.x) && IsEqual(a.y, b.y));
}

bool IsEqual(const LINE & A, const LINE & B)
{
	TYPE A1, B1, C1;
	TYPE A2, B2, C2;

	Coefficient(A, A1, B1, C1);
	Coefficient(B, A2, B2, C2);

	return IsEqual(A1 * B2, A2 * B1) &&
		IsEqual(A1 * C2, A2 * C1) &&
		IsEqual(B1 * C2, B2 * C1);
}
bool IsOnSeg(const SEG & seg, const POINT & p)
{
	return (IsEqual(p, seg.a) || IsEqual(p, seg.b)) ||
		(((p.x - seg.a.x) * (p.x - seg.b.x) < 0 ||
		(p.y - seg.a.y) * (p.y - seg.b.y) < 0) &&
		(IsEqual(Cross(seg.b, p, seg.a), 0)));
}
bool IsIntersect(const SEG & u, const SEG & v)
{
	return (Cross(v.a, u.b, u.a) * Cross(u.b, v.b, u.a) >= 0) &&
		(Cross(u.a, v.b, v.a) * Cross(v.b, u.b, v.a) >= 0) &&
		(Max(u.a.x, u.b.x) >= Min(v.a.x, v.b.x)) &&
		(Max(v.a.x, v.b.x) >= Min(u.a.x, u.b.x)) &&
		(Max(u.a.y, u.b.y) >= Min(v.a.y, v.b.y)) &&
		(Max(v.a.y, v.b.y) >= Min(u.a.y, u.b.y));
}
bool IsParallel(const LINE & A, const LINE & B)
{
	TYPE A1, B1, C1;
	TYPE A2, B2, C2;

	Coefficient(A, A1, B1, C1);
	Coefficient(B, A2, B2, C2);

	return (A1 * B2 == A2 * B1) &&
		((A1 * C2 != A2 * C1) || (B1 * C2 != B2 * C1));
}
bool IsIntersect(const LINE & A, const LINE & B)
{
	return !IsParallel(A, B);
}
POINT Intersection(const LINE & A, const LINE & B)
{
	TYPE A1, B1, C1;
	TYPE A2, B2, C2;

	Coefficient(A, A1, B1, C1);
	Coefficient(B, A2, B2, C2);
	POINT I(0, 0);
	I.x = - (B2 * C1 - B1 * C2) / (A1 * B2 - A2 * B1);
	I.y = (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);

	return I;
}

void Solve()
{
	int n;
	double D, L, HA, HB, ERRDIST;
	double a1, a2, a3, a4;
	scanf ("%d", &n);
	scanf ("%lf %lf %lf %lf %lf", &D, &L, &HA, &HB, &ERRDIST);
	double deg2rad = atan2(1.0, 1.0) / 45.0;
	double xb = D * 0.5;
	double xa = -xb;
	double yb = 0.0, ya = 0.0;
	for (int i = 1; i <= n; i++)
	{
		scanf ("%lf %lf %lf %lf", &a1, &a2, &a3, &a4);
		if ((a1 <= 0.0) || (a1 >= 90.0) || (a2 <= 0.0) || (a2 >= 90.0) ||
			(a3 <= 0.0) || (a3 >= 90.0) || (a4 <= 90.0) || (a4 >= 180.0))
		{
			printf("%d DISQUALIFIED\n", i);
			continue;
		}
		double dxa = cos(deg2rad * a1) * cos(deg2rad * a3);
		double dya = cos(deg2rad * a1) * sin(deg2rad * a3);
		double dza = sin(deg2rad * a1);
		double dxb = cos(deg2rad * a2) * cos(deg2rad * a4);
		double dyb = cos(deg2rad * a2) * sin(deg2rad * a4);
		double dzb = sin(deg2rad * a2);

		double R = xa * dya - ya * dxa;
		double S = xb * dyb - yb * dxb;
		double denom = dyb * dxa - dya * dxb;

		double x = (S * dxa - R * dxb) / denom;
		double y = (S * dya - R * dyb) / denom;
		double ta = fabs(dxa) >= fabs(dya) ? (x - xa) / dxa : (y - ya) / dya;
		double tb = fabs(dxb) >= fabs(dyb) ? (x - xb) / dxb : (y - yb) / dyb;

		double rza = HA + ta * dza;
		double rzb = HB + tb * dzb;
		if (fabs(rza - rzb) > ERRDIST)
			printf ("%d ERROR\n", i);
		else
			printf ("%d %d\n", i, (int)((rza + rzb) * 0.5 + 0.5));
	}
}

int main()
{
	Solve();
	return 0;
}




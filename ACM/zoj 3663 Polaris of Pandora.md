# 题目
Polaris is a star, it is the most magnificent scene in the sky, and the most important navigation star of planet Pandora <sup>[1]</sup>. People live in Pandora call themselves as "Na'vi" <sup>[2]</sup>, and they all love to fly in the sky with their ikran <sup>[3]</sup>. When they are flying in the sky, they use Polaris to navigate. Polaris could be used to navigate because that it is always staying in the straight line linking the North pole and the South pole of Pandora. That straight line could also be called as "axis of Pandora", and Polaris stays on the North pole side.

Polaris is too far away from Pandora, so in every place near Pandora, light from Polaris could be regarded as parallel to axis of Pandora. Now several Na'vi ikran riders are flying in the sky of Pandora, they want to know the percentage of their whole flying distance that Polaris is visible. Polaris's light is quite bright, so Polaris is visible even when it is just on the skyline.

To simplify the problem, Na'vi riders assume that Pandora is a perfect sphere, which have a <var>R</var> radius. A rider starts flying from a point on the Pandora's surface and lands at another point, the flying height is given as <var>H</var>. Ikran is so powerful that flying time between the surface of Pandora and the flying height could be ignored, and ikran will always fly straight up and down between surface and flying height. Both the starting point and the landing point could be described using latitude and longitude <sup>[4]</sup> of Pandora. And riders will always choose the shortest path to fly.

Input<br>
There are several test cases. Process to the end of file.

The only line of each test case contains 6 real numbers <var>R</var> (1000 ≤ <var>R</var> ≤ 10000), <var>H</var> (1 ≤ <var>H</var> ≤ <var>R</var>), <var>lat0</var> (-π/2 < <var>lat0</var> < π/2), <var>lng0</var> (-π < <var>lng0</var> < π), <var>lat1</var> (-π/2 < <var>lat1</var> < π/2), <var>lng1</var> (-π < <var>lng1</var> < π). <var>R</var> is radius of planet Pandora, <var>H</var> is Na'vi ikran rider's flying height, <var>lat0</var> and <var>lng0</var> are latitude and longitude of starting point, <var>lat1</var> and <var>lng1</var> are latitude and longitude of landing point.

We guarantee that starting point and landing point will not be the same, and they also will not be "opposite" (Starting point, landing point and Pandora's center will not be in the same line.)

Output<br>
For each test case, output one line with the percentage of the flying distance that Polaris is visible. Round to 3 decimal places.

Sample Input
```
1000 10 0 0 0 0.5
4000 1000 0 0.618 1.0 0.618
```
Sample Output
```
100.000
64.350
```
Reference
[1]:
Pandora is the fifth moon of the gas giant Polyphemus (both are figures in Greek mythology), which orbits the closest star to the sun, Alpha Centauri A.

[2]:
The Na'vi (English: The People) are a race of sentient extraterrestrial humanoids who inhabit the lush jungle moon of Pandora.

[3]:
Ikran (English: Mountain banshees) are large, bird-like aerial predators that are native to Pandora. They are used by the Na'vi for hunting from the air and traveling larger distances.

[4]:
To define latitude and longitude of Pandora, we need to know equator of the planet. The equator is the intersection of Pandora's surface with the plane perpendicular to axis of Pandora and containing the planet's center. Latitude is a geographic coordinate that specifies the north-south position of a point on the Pandora's surface, it is the angle between the equator and the line connected point on the surface with the planet's center. Latitude is an angle which ranges from -π/2 at the North pole to π/2 at the South pole. Longitude is a geographic coordinate that specifies the east-west position of a point on the Earth's surface. Points with the same longitude lie in lines running from the North Pole to the South Pole. The longitude of a point on the surface is measured as an angle east or west from the Hometree <sup>[5]</sup> , ranging from 0 at the Hometree to π eastward and -π westward. Specifically, it is the angle between a plane containing the Hometree and a plane containing the North Pole, South Pole and the point on the surface.

[5]:
Hometrees (Na'vi name: Kelutral) are massive trees that can be found throughout Pandora. Many Na'vi clans make these enormous plants their home.
# 参考答案
```c++
#include <iomanip>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const double PI = acos(-1.0);

inline int sgn(double d) {
    if (fabs(d)<EPS) return 0;
    return d>0?1:-1;
}

struct sp {
    double x, y, z;
    sp() {}
    sp(double a, double b, double c): x(a), y(b), z(c) {}
    void write() {
        printf("%f %f %f\n", x, y, z);
    }
};

sp operator-(const sp &u, const sp &v) {
    return sp(u.x-v.x, u.y-v.y, u.z-v.z);
}

double dot(const sp &u, const sp &v) {
    return u.x*v.x+u.y*v.y+u.z*v.z;
}

sp det(const sp &u, const sp &v) {
    return sp(u.y*v.z-v.y*u.z,
            u.z*v.x-u.x*v.z,
            u.x*v.y-u.y*v.x);
}

double nrm(const sp &u) {
    return sqrt(u.x*u.x+u.y*u.y+u.z*u.z);
}

double dis(const sp &u, const sp &v) {
    double dx = u.x-v.x;
    double dy = u.y-v.y;
    double dz = u.z-v.z;
    return sqrt(dx*dx+dy*dy+dz*dz);
}

double ang(const sp &u, const sp &v) {
    double d = dot(u, v);
    return acos(d/(nrm(u)*nrm(v)));
}

double r, h, as, ns, at, nt, R;
sp s, t, hmr, mdk;
double a, b, c, tmp;

bool quad(double a, double b, double c, double &x1, double &x2) {
    double delta = b*b-4*a*c;
    if (sgn(delta)<=0) return 0;
    x1 = (-b+sqrt(delta))/(2*a);
    x2 = (-b-sqrt(delta))/(2*a);
    return 1;
}

bool coplane(const sp &a, const sp &b, const sp &c, const sp &d) {
    return sgn(dot(det(c-a, b-a), d-a))==0;
}

bool inside(const sp &s, const sp &p, const sp &t) {
    return sgn(dot(det(s,p),det(s,t)))>=0 && sgn(dot(det(p,t),det(s,t)))>=0;
}

int main() {
    while (cin>>r>>h>>as>>ns>>at>>nt) {
        if (sgn(as)==0 && sgn(at)==0) {
            puts("100.000");
            continue;
        }
        as += PI/2; at += PI/2;
        ns += PI; nt += PI;
        R = r+h;
        s = sp(R*sin(as)*cos(ns), R*sin(as)*sin(ns), R*cos(as));
        t = sp(R*sin(at)*cos(nt), R*sin(at)*sin(nt), R*cos(at));
        a = s.y*t.z-s.z*t.y; b = s.z*t.x-s.x*t.z; c = s.x*t.y-s.y*t.x;
        tmp = -sqrt(R*R-r*r);
        hmr.z = mdk.z = tmp;
        assert(sgn(a)!=0 || sgn(b)!=0);
        if (sgn(b)) {
            if (quad(a*a+b*b, 2*a*c*tmp, c*c*(R*R-r*r)-b*b*r*r, hmr.x, mdk.x)) {
                hmr.y = (-c*tmp-a*hmr.x)/b;
                mdk.y = (-c*tmp-a*mdk.x)/b;
            }
            else {
                puts("100.000");
                continue;
            }
        }
        else {
            if (quad(a*a+b*b, 2*b*c*tmp, c*c*(R*R-r*r)-a*a*r*r, hmr.y, mdk.y)) {
                hmr.x = (-c*tmp-b*hmr.y)/a;
                mdk.x = (-c*tmp-b*mdk.y)/a;
            }
            else {
                puts("100.000");
                continue;
            }
        }
        int cnt = 0;
        if (inside(s, hmr, t)) ++cnt;
        if (inside(s, mdk, t)) ++cnt;
        double tot=ang(s, t), dark;
        if (cnt==0) {
            if (inside(hmr, s, mdk) && inside(hmr, t, mdk)) dark = tot;
            else dark = 0;
        }
        else if (cnt==1) {
            if (inside(s, mdk, t)) swap(hmr, mdk);
            assert(inside(s, hmr, t)&&!inside(s, mdk, t));
            if (inside(hmr, s, mdk)) dark = ang(hmr, s);
            else dark = ang(hmr, t);
        }
        else dark = ang(hmr, mdk);
        double ans = (1-dark/tot)*100;
        printf("%.3f\n", ans);
    }
    return 0;
}

# 题目
A closed polygon is a figure bounded by a finite number of line segments. The intersections of the bounding line segments are called the vertices of the polygon. When one starts at any vertex of a closed polygon and traverses each bounding line segment exactly once, one comes back to the starting vertex.

A closed polygon is called convex if the line segment joining any two points of the polygon lies in the polygon. Figure 1 shows a closed polygon which is convex and one which is not convex. (Informally, a closed polygon is convex if its border doesn't have any "dents".)

![poj_5836desc_2](http://uploadfiles.nowcoder.com/probs/acm/poj_5836desc_2.jpg)

The subject of this problem is a closed convex polygon in the coordinate plane, one of whose vertices is the origin (x = 0, y = 0). Figure 2 shows an example. Such a polygon will have two properties significant for this problem.

The first property is that the vertices of the polygon will be confined to three or fewer of the four quadrants of the coordinate plane. In the example shown in Figure 2, none of the vertices are in the second quadrant (where x 0).

To describe the second property, suppose you "take a trip" around the polygon: start at (0, 0), visit all other vertices exactly once, and arrive at (0, 0). As you visit each vertex (other than (0, 0)), draw the diagonal that connects the current vertex with (0, 0), and calculate the slope of this diagonal. Then, within each quadrant, the slopes of these diagonals will form a decreasing or increasing sequence of numbers, i.e., they will be sorted. Figure 3 illustrates this point.

![poj_5836desc_1](http://uploadfiles.nowcoder.com/probs/acm/poj_5836desc_1.jpg)

![poj_5836desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_5836desc_0.jpg)

输入描述

The input lists the vertices of a closed convex polygon in the plane. The number of lines in the input will be at least three but no more than 50. Each line contains the x and y coordinates of one vertex. Each x and y coordinate is an integer in the range -999..999. The vertex on the first line of the input file will be the origin, i.e., x = 0 and y = 0. Otherwise, the vertices may be in a scrambled order. Except for the origin, no vertex will be on the x-axis or the y-axis. No three vertices are colinear.

输出描述

The output lists the vertices of the given polygon, one vertex per line. Each vertex from the input appears exactly once in the output. The origin (0,0) is the vertex on the first line of the output. The order of vertices in the output will determine a trip taken along the polygon's border, in the counterclockwise direction. The output format for each vertex is (x,y) as shown below.
输入例子
```
0 0
70 -50
60 30
-30 -50
80 20
50 -60
90 -20
-30 -40
-10 -60
90 10
```
输出例子
```
(0,0)
(-30,-40)
(-30,-50)
(-10,-60)
(50,-60)
(70,-50)
(90,-20)
(90,10)
(80,20)
(60,30)
```
# 参考答案
```c++
#include<iostream>
#include<cmath>
#include<complex>
#include<algorithm>
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#define EPS 1e-8
using namespace std;
struct point {
    double x,y;    
};
point convex[50];

double cross(const point &p1, const point &p2, const point &q1, const point &q2)
{
    return (q2.y - q1.y)*(p2.x - p1.x) - (q2.x - q1.x)*(p2.y - p1.y);    
}

bool cmp(const point &a, const point &b)
{
    point origin;
    origin.x = origin.y = 0;
    return cross(origin,b,origin,a) < 0;
}

int main()
{
    int cnt = 0;
    while (scanf("%lf%lf",&convex[cnt].x,&convex[cnt].y) != EOF) {
        ++cnt;
    }
    sort(convex+1,convex+cnt,cmp);
    for (int i(0); i<cnt; ++i) {
        cout<<"("<<convex[i].x<<","<<convex[i].y<<")"<<endl;    
    }
    return 0;    
}




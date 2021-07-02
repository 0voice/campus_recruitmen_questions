# 题目
While creating a customer logo, ACM uses graphical utilities to draw a picture that can later be cut into special fluorescent materials. To ensure proper processing, the shapes in the picture cannot intersect. However, some logos contain such intersecting shapes. It is necessary to detect them and decide how to change the picture.

Given a set of geometric shapes, you are to determine all of their intersections. Only outlines are considered, if a shape is completely inside another one, it is not counted as an intersection.

![poj_5485desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_5485desc_0.jpg)

输入描述
Input contains several pictures. Each picture describes at most 26 shapes, each specified on a separate line. The line begins with an uppercase letter that uniquely identifies the shape inside the corresponding picture. Then there is a kind of the shape and two or more points, everything separated by at least one space. Possible shape kinds are:

• square: Followed by two distinct points giving the opposite corners of the square.<br>
• rectangle: Three points are given, there will always be a right angle between the lines connecting the first point with the second and the second with the third.<br>
• line: Specifies a line segment, two distinct end points are given.<br>
• triangle: Three points are given, they are guaranteed not to be co-linear.<br>
• polygon: Followed by an integer number N (3 ≤ N ≤ 20) and N points specifying vertices of the polygon in either clockwise or anti-clockwise order. The polygon will never intersect itself and its sides will have non-zero length.

All points are always given as two integer coordinates X and Y separated with a comma and enclosed in parentheses. You may assume that |X|, |Y | ≤ 10000.

The picture description is terminated by a line containing a single dash (“-”). After the last picture, there is a line with one dot (“.”).

输出描述

For each picture, output one line for each of the shapes, sorted alphabetically by its identifier (X). The line must be one of the following:

• “X has no intersections”, if X does not intersect with any other shapes.<br>
• “X intersects with A”, if X intersects with exactly 1 other shape.<br>
• “X intersects with A and B”, if X intersects with exactly 2 other shapes.<br>
• “X intersects with A, B, . . ., and Z”, if X intersects with more than 2 other shapes.<br>

Please note that there is an additional comma for more than two intersections. A, B, etc. are all intersecting shapes, sorted alphabetically.

Print one empty line after each picture, including the last one.

输入例子
```
A square (1,2) (3,2)
F line (1,3) (4,4)
W triangle (3,5) (5,5) (4,3)
X triangle (7,2) (7,4) (5,3)
S polygon 6 (9,3) (10,3) (10,4) (8,4) (8,1) (10,2)
B rectangle (3,3) (7,5) (8,3)
-
B square (1,1) (2,2)
A square (3,3) (4,4)
-
.
```
输出例子
```
A has no intersections
B intersects with S, W, and X
F intersects with W
S intersects with B
W intersects with B and F
X intersects with B

A has no intersections
B has no intersections
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<math.h>
using namespace std;
#define eps 10e-8

struct point
{
    double x, y;
};

int num, n;
vector<int>v[27];

 //以下是汝的黑书求两线段模板 （极少部分名称被我修改过）
double crossdet(double x1, double y1, double x2, double y2)
{
    return x1 * y2 - x2 * y1;
}
double cross(point o, point a, point b)
{
    return crossdet(a.x - o.x, a.y - o.y, b.x - o.x, b.y - o.y);
}
double dotdet(double x1, double y1, double x2, double y2)
{
    return x1 * x2 + y1 * y2;
}
double dot(point o, point a, point b)
{
    return dotdet(a.x - o.x, a.y - o.y, b.x - o.x, b.y - o.y);
}
int dblcmp(double d)
{
    if( fabs(d) < eps)return 0;
    return d > 0 ? 1 : -1;
}
int between(point a, point b, point c)
{
    return dblcmp( dot(a, b, c));
}
int seg_cross(point a, point b, point c, point d)
{
    double s1, s2, s3, s4;
    int d1, d2, d3, d4;
    d1 = dblcmp (s1 = cross(a, b, c));
    d2 = dblcmp (s2 = cross(a, b, d));
    d3 = dblcmp (s3 = cross(c, d, a));
    d4 = dblcmp (s4 = cross(c, d, b));
    if( (d1 ^ d2) == -2 && (d3 ^ d4) == -2)return 1;
    if( d1 == 0 && between(c, a, b) <= 0
     || d2 == 0 && between(d, a, b) <= 0
     || d3 == 0 && between(a, c, d) <= 0
     || d4 == 0 && between(b, c, d) <= 0)return 1;
    return 0;
}

struct node
{
    char no[4], kind[15], cnt;
    point p[22];
}a[27];

bool cmp(node a, node b)
{
    return a.no[0] < b.no[0];
}

void input()
{
    char c;
    int i, j;
    scanf("%s",a[num].kind);
    c = a[num].kind[0];
    if(c == 'p')
    {
        scanf("%d", &n);
        a[num].cnt = n + 1;
        for(i = 1; i <= n; i++)
            scanf(" (%lf,%lf)", &a[num].p[i].x, &a[num].p[i].y);
        a[num].p[n + 1].x = a[num].p[1].x;
        a[num].p[n + 1].y = a[num].p[1].y;
    }
    else if(c == 'l')
    {
        a[num].cnt = 2;
        for(i = 1; i <= 2; i++)
            scanf(" (%lf,%lf)", &a[num].p[i].x, &a[num].p[i].y);
    }
    else if(c == 't')
    {
        a[num].cnt = 4;
        for(i = 1; i <= 3; i++)
            scanf(" (%lf,%lf)", &a[num].p[i].x, &a[num].p[i].y);
        a[num].p[4].x = a[num].p[1].x;
        a[num].p[4].y = a[num].p[1].y;
    }
    else if(c == 's')
    {
        a[num].cnt = 5;
        for(i = 1; i <= 3; i += 2)
            scanf(" (%lf,%lf)", &a[num].p[i].x, &a[num].p[i].y);
        a[num].p[2].x = ( a[num].p[1].x + a[num].p[3].x + a[num].p[3].y - a[num].p[1].y) / 2.0;
        a[num].p[4].x = ( a[num].p[1].x + a[num].p[3].x - a[num].p[3].y + a[num].p[1].y) / 2.0;
        a[num].p[2].y = ( a[num].p[1].x - a[num].p[3].x + a[num].p[1].y + a[num].p[3].y) / 2.0;
        a[num].p[4].y = ( a[num].p[3].x - a[num].p[1].x + a[num].p[1].y + a[num].p[3].y) / 2.0;
        a[num].p[5].x = a[num].p[1].x;
        a[num].p[5].y = a[num].p[1].y;
    }
    else if(c == 'r')
    {
        a[num].cnt = 5;
        for(i = 1; i <= 3; i++)
            scanf(" (%lf,%lf)", &a[num].p[i].x, &a[num].p[i].y);
        a[num].p[4].x = a[num].p[1].x + a[num].p[3].x - a[num].p[2].x;
        a[num].p[4].y = a[num].p[1].y + a[num].p[3].y - a[num].p[2].y;
        a[num].p[5].x = a[num].p[1].x;
        a[num].p[5].y = a[num].p[1].y;
    }
    num++;
}

int main()
{
    int i, j, k, x;
    num = 0;
    while( scanf("%s", a[num].no ) != EOF )
    {
        if(a[num].no[0] == '.')break;
        input();
        while( scanf("%s", a[num].no ) != EOF && a[num].no[0] != '-')
        {
            input();
        }
        sort(a, a+num,cmp);
        for(i = 0; i <= 26; i++)
            v[i].clear();
        bool flag = 0;
        for(i = 0; i < num; i++)
            for(j = i + 1; j < num; j++)
            {
                for(x = 1; x < a[i].cnt; x++)
                {
                    for(k = 1; k < a[j].cnt; k++)
                    {
                        if(seg_cross(a[i].p[x], a[i].p[x+1], a[j].p[k], a[j].p[k+1]))
                        {
                            flag = 1;v[i].push_back(j);v[j].push_back(i);break;
                        }
                    }
                    if( k != a[j].cnt)break;
                }
            }    
        for(i = 0; i < num; i++)
        {
            printf("%c ",a[i].no[0]);
            int len = v[i].size();
            if(len == 0)printf("has no intersections\n");
            else if(len == 1)printf("intersects with %c\n", a[ v[i][0] ].no[0]);
            else if(len == 2)printf("intersects with %c and %c\n", a[ v[i][0] ].no[0], a[ v[i][1] ].no[0]);
            else
            {
                printf("intersects with ");
                for(j = 0; j < len - 1; j++)
                    printf("%c, ", a[ v[i][j] ].no[0]);
                printf("and %c\n",a[ v[i][len - 1] ].no[0]);
            }
        }
        puts("");
        num = 0;
    }
    return 0;
}



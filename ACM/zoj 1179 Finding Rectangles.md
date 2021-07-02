# 题目
Consider the point sets in figures 1a, 2a, and 3a. Using only those points as vertices, figures 1b, 2b, and 3b show all the rectangles that can be formed with horizontal and vertical sides. No rectangles can be formed from the points in figure 4.

  ![zoj_610desc_0](http://uploadfiles.nowcoder.com/probs/acm/zoj_610desc_0.jpg)
                   
Your task is to write a program that can find all rectangles that can be formed from a given set of points. The example input and output given below correspond to the figures above.


Input

The input contains one or more point sets, followed by a line containing the number 0 that signals the end of the file. Each point set begins with a line containing n, the number of points, and is followed by n lines that describe the points. Each point description contains a capital letter that is the label of the point, then a space, the horizontal coordinate, a space, and the vertical coordinate. Within each set, points labels occur in alphabetical order.

Note that since each point is labelled with a capital letter there can be at most 26 points. All coordinates are nonnegative integers less than 50. Points within a set are unique.


Output

The output for each point set starts with ``Point set ", followed by the number of the point set and a colon. If there are no rectangles, `` No rectangles" appears after the colon. If there are rectangles, they are listed starting on the next line. A blank precedes each rectangle. Each rectangle is given by its vertex labels, in clockwise order from the upper left, so the order is upper left, upper right, lower right, lower left. The rectangles are listed ten per line, except for the last line, where there may be as few as one. The rectangles are listed in alphabetical order.

Sample Input
```
7
A 1 1
B 2 1
C 3 1
D 2 3
E 3 3
F 1 4
G 3 4
8
B 1 1
D 2 1
F 4 1
J 4 4
L 2 4
M 2 3
N 4 3
P 1 2
12
A 1 5
B 2 5
C 1 4
D 2 4
E 1 3
F 2 3
G 1 2
H 2 2
I 1 1
J 2 1
K 1 0
L 2 0
5
B 1 1
D 2 1
L 2 4
N 2 3
P 1 2
0
```

Sample Output
```
Point set 1:
 DECB FGCA
Point set 2:
 LJFD LJNM MNFD
Point set 3:
 ABDC ABFE ABHG ABJI ABLK CDFE CDHG CDJI CDLK EFHG
 EFJI EFLK GHJI GHLK IJLK
Point set 4: No rectangles
```
# 参考答案
```c++
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

namespace
{
	struct Point
	{
			char c;
			int x, y;
	};

	bool cmp(const Point *p1, const Point *p2)
	{
		if (p1->x != p2->x)
			return p1->x < p2->x;
		else
			return p1->y < p2->y;
	}

	bool valid(Point *p1, Point *p2, Point *p3, Point *p4)
	{
		return p1->x == p2->x && p3->x == p4->x && p1->y == p3->y
				&& p2->y == p4->y;
	}
}

int main()
{
	int n, x, y, count = 0;
	vector<Point*> V;
	vector<string> res;
	char s[2];
	while (scanf("%d", &n), n)
	{
		getchar();
		V.clear();
		res.clear();
		for (int i = 0; i < n; i++)
		{
			scanf("%s %d %d", s, &x, &y);
			Point *p = new Point();
			p->c = s[0];
			p->x = x;
			p->y = y;
			V.push_back(p);
		}
		sort(V.begin(), V.end(), cmp);
		for (size_t i = 0; i < V.size(); i++)
			for (size_t j = i + 1; j < V.size(); j++)
				for (size_t k = j + 1; k < V.size(); k++)
					for (size_t l = k + 1; l < V.size(); l++)
						if (valid(V[i], V[j], V[k], V[l]))
						{
							string str;
							str.push_back(V[j]->c);
							str.push_back(V[l]->c);
							str.push_back(V[k]->c);
							str.push_back(V[i]->c);
							res.push_back(str);
						}
		sort(res.begin(), res.end());
		printf("Point set %d:", ++count);
		if (res.size())
		{
			for (size_t i = 0; i < res.size(); i++)
			{
				if (i % 10 == 0)
					putchar('\n');
				cout << ' ' << res[i];
			}
			putchar('\n');
		}
		else
			puts(" No rectangles");
	}
	return 0;
}





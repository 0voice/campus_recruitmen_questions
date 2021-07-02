# 题目
Farmer John's pastoral neighborhood has N farms (2
```
           F1 --- (13) ---- F6 --- (9) ----- F3

            |                                 |

           (3)                                |

            |                                (7)

           F4 --- (20) -------- F2            |

            |                                 |

           (2)                               F5

            | 

           F7 
```

Being an ASCII diagram, it is not precisely to scale, of course.

Each farm can connect directly to at most four other farms via roads that lead exactly north, south, east, and/or west. Moreover, farms are only located at the endpoints of roads, and some farm can be found at every endpoint of every road. No two roads cross, and precisely one path
(sequence of roads) links every pair of farms.

FJ lost his paper copy of the farm map and he wants to reconstruct it from backup information on his computer. This data contains lines like the following, one for every road:

There is a road of length 10 running north from Farm #23 to Farm #17<br>
There is a road of length 7 running east from Farm #1 to Farm #17<br>
...

As FJ is retrieving this data, he is occasionally interrupted by questions such as the following that he receives from his navigationally-challenged neighbor, farmer Bob:

What is the Manhattan distance between farms #1 and #23?

FJ answers Bob, when he can (sometimes he doesn't yet have enough data yet). In the example above, the answer would be 17, since Bob wants to know the "Manhattan" distance between the pair of farms.
The Manhattan distance between two points (x1,y1) and (x2,y2) is just |x1-x2| + |y1-y2| (which is the distance a taxicab in a large city must travel over city streets in a perfect grid to connect two x,y points).

When Bob asks about a particular pair of farms, FJ might not yet have enough information to deduce the distance between them; in this case, FJ apologizes profusely and replies with "-1".
输入描述
```
* Line 1: Two space-separated integers: N and M

* Lines 2..M+1: Each line contains four space-separated entities, F1,

        F2, L, and D that describe a road. F1 and F2 are numbers of

        two farms connected by a road, L is its length, and D is a

        character that is either 'N', 'E', 'S', or 'W' giving the

        direction of the road from F1 to F2.

* Line M+2: A single integer, K (1         queries


* Lines M+3..M+K+2: Each line corresponds to a query from Farmer Bob

        and contains three space-separated integers: F1, F2, and I. F1

        and F2 are numbers of the two farms in the query and I is the

        index (1         query. Data index 1 is on line 2 of the input data, and so on.
```
输出描述
```
* Lines 1..K: One integer per line, the response to each of Bob's

        queries.  Each line should contain either a distance

        measurement or -1, if it is impossible to determine the

        appropriate distance.
```
输入例子
```
7 6
1 6 13 E
6 3 9 E
3 5 7 S
4 1 3 N
2 4 20 W
4 7 2 S
3
1 6 1
1 4 3
2 6 6
```
输出例子
```
13
-1
10
```
Hint

At time 1, FJ knows the distance between 1 and 6 is 13.<br>
At time 3, the distance between 1 and 4 is still unknown.<br>
At the end, location 6 is 3 units west and 7 north of 2, so the distance is 10.<br>

# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
using namespace std;
const int maxn=40100;
struct node
{
    int x;
    int y;
}a[maxn];
struct Edge 
{
    int u;
    int v;
    int l;
    char dir[5];
}e[maxn];
int n,m,p[maxn];
int find(int x)
{
    if(p[x]==-1)
	return x;
    int y=p[x];
    p[x]=find(p[x]);
    a[x].x+=a[y].x;
    a[x].y+=a[y].y;
    return p[x];
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
	memset(p,-1,sizeof(p));
	memset(a,0,sizeof(a));
	for(int i=0;i<m;i++)
	    scanf("%d%d%d%s",&e[i].u,&e[i].v,&e[i].l,&e[i].dir);
	int q,now=0;
	scanf("%d",&q);
	while(q--)
	{
	    int sa,sb,t;
	    scanf("%d%d%d",&sa,&sb,&t);
	    while(now<t)
	    {
		int u=e[now].u;
		int v=e[now].v;
		int x=find(e[now].u);
		int y=find(e[now].v);
		if(x==y)
		    continue;
		int x1=a[v].x;
		int y1=a[v].y;
		if(e[now].dir[0]=='E')
		{
		    a[y].x=a[u].x+e[now].l-a[v].x;
		    a[y].y=a[u].y-a[v].y;
		}
		else if(e[now].dir[0]=='W')
		{
		    a[y].x=a[u].x-e[now].l-a[v].x;
		    a[y].y=a[u].y-a[v].y;
		}
		else if(e[now].dir[0]=='S')
		{
		    a[y].x=a[u].x-a[v].x;
		    a[y].y=a[u].y-e[now].l-a[v].y;
		}
		else
		{
		    a[y].x=a[u].x-a[v].x;
		    a[y].y=a[u].y+e[now].l-a[v].y;
		}
		if(x!=y)
		    p[y]=x;
		now++;
	    }
	    int x=find(sa);
	    int y=find(sb);
	    if(x==y)
		printf("%d\n",abs(a[sa].x-a[sb].x)+abs(a[sa].y-a[sb].y));
	    else
		printf("-1\n");
	}
    }
    return 0;
}





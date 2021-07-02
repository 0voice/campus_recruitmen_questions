# 题目
Ants are quite diligent. They sometimes build their nests beneath flagstones.<br>
Here, an ant is walking in a rectangular area tiled with square flagstones, seeking the only hole leading to her nest.

![zoj_149desc_0](http://uploadfiles.nowcoder.com/probs/acm/zoj_149desc_0.jpg)

The ant takes exactly one second to move from one flagstone to another. That is, if the ant is on the flagstone with coordinates (x,y) at time t, she will be on one of the five flagstones with the following coordinates at time t+1:

(x, y), (x+1, y), (x-1, y), (x, y+1), (x, y-1).

The ant cannot go out of the rectangular area. The ant can visit the same flagstone more than once.

Insects are easy to starve. The ant has to go back to her nest without starving. Physical strength of the ant is expressed by the unit "HP". Initially, the ant has the strength of 6 HP. Every second, she loses 1 HP. When the ant arrives at a flagstone with some food on it, she eats a small piece of the food there, and recovers her strength to the maximum value, i.e., 6 HP, without taking any time. The food is plenty enough, and she can eat it as many times as she wants.

When the ant's strength gets down to 0 HP, she dies and will not move anymore. If the ant's strength gets down to 0 HP at the moment she moves to a flagstone, she does not effectively reach the flagstone: even if some food is on it, she cannot eat it; even if the hole is on that stone, she has to die at the entrance of her home.

If there is a puddle on a flagstone, the ant cannot move there.

Your job is to write a program which computes the minimum possible time for the ant to reach the hole with positive strength from her start position, if ever possible.


Input

The input consists of multiple maps, each representing the size and the arrangement of the rectangular area. A map is given in the following format.

w h<br>
d11 d12 d13 ... d1w<br>
d21 d22 d23 ... d2w<br>
...<br>
dh1 dh2 dh3 ... dhw

The integers w and h are the numbers of flagstones in the x- and y-directions, respectively. w and h are less than or equal to 8. The integer dyx represents the state of the flagstone with coordinates (x, y) as follows.

0: There is a puddle on the flagstone, and the ant cannot move there.<br>
1, 2: Nothing exists on the flagstone, and the ant can move there. "2" indicates where the ant initially stands.<br>
3: The hole to the nest is on the flagstone.<br>
4: Some food is on the flagstone.

There is one and only one flagstone with a hole. Not more than five flagstones have food on them.

The end of the input is indicated by a line with two zeros.

Integer numbers in an input line are separated by at least one space character.


Output

For each map in the input, your program should output one line containing one integer representing the minimum time. If the ant cannot return to her nest, your program should output -1 instead of the minimum time.


Sample Input
```
3 3
2 1 1
1 1 0
1 1 3
8 4
2 1 1 0 1 1 1 0
1 0 4 1 1 0 4 1
1 0 0 0 0 0 0 1
1 1 1 4 1 1 1 3
8 5
1 2 1 1 1 1 1 4
1 0 0 0 1 0 0 1
1 4 1 0 1 1 0 1
1 0 0 0 0 3 0 1
1 1 4 1 1 1 1 1
8 7
1 2 1 1 1 1 1 1
1 1 1 1 1 1 1 4
1 1 1 1 1 1 1 1
1 1 1 1 4 1 1 1
4 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 3
8 8
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 4 4 1 1 1 1 1
1 4 4 2 1 1 0 0
1 1 0 0 0 0 0 3
1 1 0 4 1 1 1 1
1 1 1 1 1 1 1 1
8 8
1 1 1 1 1 1 1 1
1 1 2 1 1 1 1 1
1 1 4 4 4 1 1 1
1 1 1 4 4 1 0 1
1 1 1 1 1 1 0 1
1 1 1 1 1 1 0 3
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
0 0
```

Sample Output
```
4
-1
13
20
-1
-1
```
# 参考答案
```c++
#include<cstdio>
#include<queue>
#include<cstring>
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int nx,ny,m,n,ex,ey,vis[10][10],a[10][10];
using namespace std;
struct node
{
	int x,y,v,time;
	friend bool operator < (node a,node b)
	{
		return a.v>b.v;
	}
}p,temp;
void bfs(int c,int y)
{
	p.x=c;
	p.y=y;
	p.time=0;
	p.v=6;
	queue<node>q;
	q.push(p);
	while(!q.empty())
	{
		p=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			temp.y=p.y+dy[i];
			temp.x=p.x+dx[i];
			temp.time=p.time+1;
			temp.v=p.v-1;
			if(temp.x<m&&temp.x>=0&&temp.y<n&&temp.y>=0&&!vis[temp.x][temp.y]&&temp.v>=1)
			{
				if(temp.x==ex&&temp.y==ey)
				{
					printf("%d\n",temp.time);
					return;
				}	
				if(a[temp.x][temp.y]==4)
				{
					temp.v=6;
					vis[temp.x][temp.y]=1;	
				}
				if(temp.v==1)
					continue;
				q.push(temp);
			}	
		}
	}
	printf("-1\n");
}
int main()
{
	int sx,sy,i,j;
	while(scanf("%d%d",&n,&m),m||n)
	{
		memset(vis,0,sizeof(vis));
		for(i=0;i<m;i++)
			for(j=0;j<n;j++)
			{
				scanf("%d",&a[i][j]);
				if(a[i][j]==2)
				{
					sx=i;
					sy=j;
				}
				else if(a[i][j]==3)
				{
					ex=i;
					ey=j;
				}
				else if(a[i][j]==0)
					vis[i][j]=1;
			}
		bfs(sx,sy);
	}
	return 0;
}




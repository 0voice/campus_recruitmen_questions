# 题目
One day Leon finds a very classic game called Wumpus.The game is as follow.

Once an agent fell into a cave. The legend said that in this cave lived a kind of monster called Wumpus, and there were horrible pits which could lead to death everywhere. However, there were also a huge amount of gold in the cave. The agent must be careful and sensitive so that he could grab all of the gold and climb out of the cave safely.

The cave can be regarded as a n*n board. In each square there could be a Wumpus, a pit, a brick of gold, or nothing. The agent would be at position (0,0) at first and headed right.(As the picture below)

![zoj_1702desc_0](http://uploadfiles.nowcoder.com/probs/acm/zoj_1702desc_0.jpg)

For each step, there are six possible movements including going forward, turning left, turning right, shooting, grabbing the gold, and climbing out of the cave. If the agent steps into a square containing a pit or Wumpus, he will die. When the agent shoots, the Wumpus in front of him will die. The goal of the agent is to grab all of the gold and return to the starting position and climb out(it's OK if any Wumpus is still living).When a brick of gold is grabbed successfully, you will gain 1000 points. For each step you take, you will lose 10 points.

Your job is to help him compute the highest point he can possibly get.

For the purpose of simplification, we suppose that there is only one brick of gold and the agent cannot shoot the Wumpus.

If there is a pit at (0, 0), the agent dies immediately. There will not be a Wumpus at (0, 0).

Input

There are multiple cases. The first line will contain one integer <var>k</var> that indicates the number of cases.

For each case:

The first line will contain one integer <var>n</var> (n <= 20).

The following lines will contain three integers, each line shows a position of an object. The first one indicates the type of the object. 1 for Wumpus, 2 for pit and 3 for gold. Then the next two integers show the x and y coordinates of the object.

The input end with -1 -1 -1. (It is guaranteed that no two things appear in one position.)

Output

The output contains one line with one integer, which is the highest point Leon could possibly get. If he cannot finish the game with a non-negative score, print "-1".

Sample Input
```
2
3
1 1 1
2 2 0
3 2 2
-1 -1 -1
3
1 1 1
3 2 2
-1 -1 -1
```
Sample Output
```
850
870
```
Hint

For the sample 1, the following steps are taken:

turn left, forward, forward, turn right, forward, forward, grab, turn left, turn left, forward, forward, turn left, forward, forward, climb.

There are in all 15 steps, so the final score is 840. For the sample 2 , the path is as follow:

![zoj_1702desc_1](http://uploadfiles.nowcoder.com/probs/acm/zoj_1702desc_1.jpg)

# 参考答案
```c++
#include<cstdio>
#include<cmath>
#include<queue>
#include<vector>
#include<stack>
#include<map>
#include<string>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
const ll maxn = 25;
int T, n, flag, x, y;
int mp[maxn][maxn];
int f[maxn][maxn][4][2];

struct point
{
	int x, y, d, v;
	point(int x, int y, int d, int v) :x(x), y(y), d(d), v(v){}
};

int bfs()
{
	queue<point> p;
	p.push(point(0, 0, 0, 0));
	if (mp[0][0] == 1) return -1;
	f[0][0][0][0] = 0;
	int x, y, d, v;
	while (!p.empty())
	{
		point q = p.front();	p.pop();
		if (f[q.x][q.y][q.d][q.v] > 98) continue;
		x = q.x;	y = q.y;	v = q.v;
		if (mp[x][y] == 3 && f[x][y][q.d][1] > f[x][y][q.d][0])
		{
			f[x][y][q.d][1] = f[x][y][q.d][0];
			p.push(point(x, y, q.d, 1));
		}
		d = (q.d + 1) % 4;
		if (f[x][y][d][v] > f[x][y][q.d][v] + 1)
		{
			f[x][y][d][v] = f[x][y][q.d][v] + 1;
			p.push(point(x, y, d, v));
		}
		d = (q.d + 3) % 4;
		if (f[x][y][d][v] > f[x][y][q.d][v] + 1)
		{
			f[x][y][d][v] = f[x][y][q.d][v] + 1;
			p.push(point(x, y, d, v));
		}
		d = q.d;
		if (d == 0) ++x;
		if (d == 1) --y;
		if (d == 2) --x;
		if (d == 3) ++y;
		if (x >= 0 && x < n&&y >= 0 && y<n)
		if (mp[x][y] != 1 && mp[x][y] != 2)
		if (f[x][y][d][v] > f[q.x][q.y][d][v] + 1)
		{
			f[x][y][d][v] = f[q.x][q.y][d][v] + 1;
			p.push(point(x, y, d, v));
		}
	}
	int ans = f[0][0][0][1];
	for (int i = 1; i < 4; i++) ans = min(ans, f[0][0][i][1]);
	ans = 980 - ans * 10;
	if (ans < 0) return -1;
	return ans;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		memset(mp, 0, sizeof(mp));
		while (scanf("%d%d%d", &flag, &x, &y) == 3)
		{
			if (x == -1 && y == -1 && flag == -1) break;
			mp[x][y] = flag;
		}
		memset(f, 1, sizeof(f));
		printf("%d\n", bfs());
	}
	return 0;
}





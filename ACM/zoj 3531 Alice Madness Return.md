# 题目
Recently there is a new game called <<Alice Madness Return>>. In this game, Alice was trapped in the wonderland by some evil spirits and she also lost her memory. The player need to help Alice find her memory and escape from wonderland.

  ![zoj_1205desc_0](http://uploadfiles.nowcoder.com/probs/acm/zoj_1205desc_0.jpg)
	
  Now Alice is facing a big door which is locked. If she wants to open the door, she must pass a strange maze on a chess board with size m*n. There is a pawn controlled by Alice, and there is a mirror pawn indirectly controlled by Alice. In each turn, Alice can move her own pawn 1 step to one of the four direction (north, south, west, east). At the same time, the mirror pawn will also move 1 step in opposite direction. Since there are 2 exits, Alice must find a way to make her pawn and the mirror pawn reach both the 2 exits simultaneously so that she can open the door.
  
  This game is not easy because there are 2 kinds of chess pieces on the chess board which are listed below:
  
  Rook: You can consider the Rook as a heavy stone so that nobody can step into the grid occupied by a Rook. The Rook itself will never move.
  
  Knight: There is only one Knight on the chess board. Since the Knight is very dangerous, both Alice's pawn and the mirror pawn cannot be caught by the Knight (it means they meet in the same grid), or they will be killed. At first the Knight stands in a grid, facing one of the four direction. In each turn, after Alice and the mirror pawn has moved, the Knight will also move 1 step to the direction he is facing. If he is blocked by a Rook or he is on the boundary of the board, he will turn around (i.e turn to north if he is facing south) instead of moving.
Besides, there are some memory pieces of Alice on the chess board. Alice must control her own pawn to collect all the memory pieces before she leave the maze. There are at most 5 memory pieces on the chess board.
Now it's your job to help Alice find a way to collect all her memory and open the door as soon as possible.

Notice:

  Any two chess pieces cannot occupy the same grid but the Knight can move into grid occupied by Alice or the mirror and in that situation he will kill them. You can consider the exit as empty grid so that Knight can pass the exit.
In each turn, Alice must move her own pawn and cannot move out of the chess board. If she cannot move, she will die.
After Alice's move, the mirror will move, but if the mirror is blocked by any chess piece(i.e the mirror is blocked by a Rook) or it is forced to move out of the chess board, then the mirror will stay unmoved.
Once Alice and the mirror reach the 2 exits, the door will open and the Knight cannot catch them after that. Of course, if the door has been open, Alice cannot get back to the chessboard to collect her memory any more.

  Input
The input contains multiple test cases.
In each test case, fisrt there are two integers, <var>m</var> and <var>n</var> ( 1 <= <var>m</var>, <var>n</var> <=10 ) , which is the size of the chess board.
Then there are <var>m</var> lines each containing <var>n</var> characters. In these characters, '*' means empty grid, 'R' means Rook, 'K' means Kight, 'A' means Alice's pawn, 'B' means the mirror pawn, 'E' means exit, 'M' means memory piece.
Finally there is a line containing one character describing the initial direction the Knight is facing. 'N' means north, 'S' means south, 'W' means west, 'E' means east.
We guarantee that there are exactly 1 Knight, 2 exits, no more than 5 memory pieces on the chess board.

Output

For each test case, output one line with an integer which is the minimum number of turns Alice needed to collect all her memory pieces and open the door. If she cannot finish the task, output -1 instead.

Sample Input
```
6 6
*BR*E*
******
**R***
***K**
**R***
E**R*A
E
```
Sample Output
```
8
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<queue>
using namespace std;
typedef long long lld;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define inf 0xfffffff
int n,m;
char g[110][110];
bool inside(int x,int y)
{
	if(x < 0 || x >= n || y < 0 || y >= m)
		return false;
	return true;
}
struct Node
{
	int a,b,c,mask;
	Node(){}
	Node(int a0,int b0,int c0,int mask0)
	{
		a=a0;
		b=b0;
		c=c0;
		mask=mask0;
	}
};
char str[110];
queue<Node>Q;
int dis[10][10][10][10][2][10][1<<5];
int tx[4]={1,-1,0,0};
int ty[4]={0,0,1,-1};
int af,sf;
int id[110][110];
int T;
int bfs()
{
	while(!Q.empty())
	{
		Node o=Q.front();
		Q.pop();
		int ax,ay,bx,by,cx,cy,ck,mask;
		ax=o.a/10;
		ay=o.a%10;
		bx=o.b/10;
		by=o.b%10;
		if(af == 0)
		{
			cx=o.c%10;
			cy=sf;
		}
		else
		{
			cx=sf;
			cy=o.c%10;
		}
		int c01=o.c/10;
		int cat=o.c%10;
		mask=o.mask;
		ck=o.c/10+af;
		for(int k=0;k<4;k++)
		{
			int x1=ax+tx[k];
			int y1=ay+ty[k];
			if(!inside(x1,y1) || g[x1][y1] == 'R' ||
					(x1 == bx && y1 == by) || (x1 == cx && y1 == cy))
				continue;
			int tk=k^1;
			int x2=bx+tx[tk];
			int y2=by+ty[tk];
			if(!inside(x2,y2) || g[x2][y2] == 'R' ||
					(x2 == x1 && y2 == y1) || (x2 == cx && y2 == cy))
			{
				x2=bx;
				y2=by;
			}
			int next=mask;
			if(id[x1][y1] != -1)
				next|=(1<<id[x1][y1]);
			if(g[x1][y1] == 'E' && g[x2][y2] == 'E' && (x1 != x2 || y1 != y2))
			{
				if(next == ((1<<T)-1))
					return dis[ax][ay][bx][by][c01][cat][mask]+1;
				continue;
			}
			int x3=cx+tx[ck];
			int y3=cy+ty[ck];
			int nc01=c01;
			if(!inside(x3,y3) || g[x3][y3] == 'R')
			{
				x3=cx;
				y3=cy;
				nc01^=1;
			}
			else
			{
				if((x3 == x1 && y3 == y1) || (x3 == x2 && y3 == y2))
					continue;
			}
			int ncat;
			if(af == 0)
				ncat=x3;
			else
				ncat=y3;
			if(dis[x1][y1][x2][y2][nc01][ncat][next] == -1)
			{
				dis[x1][y1][x2][y2][nc01][ncat][next]=dis[ax][ay][bx][by][c01][cat][mask]+1;
				Q.push(Node(x1*10+y1,x2*10+y2,nc01*10+ncat,next));
			}
		}
	}
	return -1;
}
int main()
{
	while(scanf("%d %d",&n,&m)!=EOF)
	{
		for(int i=0;i<n;i++)
			scanf("%s",g[i]);
		int ax,ay,bx,by,c,cx,cy,f;
		T=0;
		memset(id,-1,sizeof(id));
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				if(g[i][j] == 'A')
				{
					ax=i;
					ay=j;
				}
				if(g[i][j] == 'B')
				{
					bx=i;
					by=j;
				}
				if(g[i][j] == 'K')
				{
					cx=i;
					cy=j;
				}
				if(g[i][j] == 'M')
					id[i][j]=T++;
			}
		scanf("%s",str);
		if(str[0] == 'N' || str[0] == 'S')
			c=cx,sf=cy;
		else
			c=cy,sf=cx;
		if(str[0] == 'S')
			f=0,af=0;
		if(str[0] == 'N')
			f=1,af=0;
		if(str[0] == 'E')
			f=0,af=2;
		if(str[0] == 'W')
			f=1,af=2;
		memset(dis,-1,sizeof(dis));
		dis[ax][ay][bx][by][f][c][0]=0;
		while(!Q.empty())
			Q.pop();
		Q.push(Node(ax*10+ay,bx*10+by,f*10+c,0));
		printf("%d\n",bfs());
	}
	return 0;
}

# 题目
"Never End" is a flash game. Here, we consider a simplified version of it. A world is represented by a board of N by M, where each grid may be empty or a block. The world is surrounded by blocks with one empty grid being the exit. The player can use the following four operations to escape from the world (get to the exit).

Step Left one grid.<br>
Step Right one grid.<br>
Rotate Left the world.<br>
Rotate Right the world.<br>
However, the player can not get into the blocks. After one operation, the player will fall off until he reaches a block or gets to the exit. Refer to the figure for a more intuitive understanding of the four operations.

![image](https://user-images.githubusercontent.com/59190045/124579633-e3448c80-de81-11eb-9df6-3e45bf4a4eb9.png)

input

There are no more than 50 cases. Each case begins with a line with two integers N (3 <= N <= 500) and M (3 <= M <= 500), the height and width of the world respectively. The next N lines describe the world. Each of the N lines contains exactly M characters. A '#' denotes a block. The 'E' denotes the exit, which is guaranteed to be at one edge of the world excluding the corners. The '|' represents the player. You can assume that the player stands on a block at first.

Process to the end of the file.

Output

For each case, print a line with the minimal number of operations that the player can escape from the world. If it is impossible for the player to escape, print "Can not escape!" instead.

Sample Input
```
9 9
#########
# #     #
# # ### #
# #  #  #
E ## #  #
# #  ####
#   ##  #
#   |   #
#########
7 7
#######
###|  #
####  #
E     #
####  #
###   #
#######
```
Sample Output
```
4
Can not escape!
```
# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
using namespace std;

int sx, sy, ex, ey;
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};
struct nod{
	int cnt, dir, x, y;
}u, temp;
int vis[500][500][4];
char er[501][501];
queue<nod> q;
int n, m;

nod gao(nod a){
	if(a.dir == 0){
		while(a.x > 0 && er[a.x-1][a.y] != '#') a.x --;
	}else if(a.dir == 1){
		while(a.x < n-1 && er[a.x+1][a.y] != '#') a.x ++;
	}else if(a.dir == 2){
		while(a.y > 0 && er[a.x][a.y-1] != '#') a.y --;
	}else if(a.dir == 3){
		while(a.y < m-1 && er[a.x][a.y+1] != '#') a.y ++;
	}
	return a;
}	
nod solve(nod a, int kind){
	if(kind == 0){
		if(a.dir == 0) a.dir = 3;
		else if(a.dir == 3) a.dir = 1;
		else if(a.dir == 1) a.dir = 2;
		else a.dir = 0;
		return gao(a);
	}else if(kind == 1){
		if(a.dir == 0) a.dir = 2;
		else if(a.dir == 2) a.dir = 1;
		else if(a.dir == 1) a.dir = 3;
		else a.dir = 0;
		return gao(a);
	}else if(kind == 2){
		if(a.dir == 1){
			if(a.y > 0 && er[a.x][a.y-1] != '#') {
				a.y -= 1;
				return gao(a);
			}
		}else if(a.dir == 0){
			if(a.y < m-1 && er[a.x][a.y+1] != '#'){
				a.y += 1;
				return gao(a);
			}
		}else if(a.dir == 2){
			if(a.x > 0 && er[a.x-1][a.y] != '#'){
				a.x -= 1;
				return gao(a);
			}
		}else if(a.dir == 3){
			if(a.x < n-1 && er[a.x+1][a.y] != '#'){
				a.x += 1;
				return gao(a);
			}
		}
	}else {
		if(a.dir == 1){
			if(a.y < m-1 && er[a.x][a.y+1] != '#'){
				a.y += 1;
				return gao(a);
			}
		}else if(a.dir == 0){
			if(a.y > 0 && er[a.x][a.y-1] != '#') {
				a.y -= 1;
				return gao(a);
			}
		}else if(a.dir == 2){
			if(a.x < n-1 && er[a.x+1][a.y] != '#'){
				a.x += 1;
				return gao(a);
			}
		}else if(a.dir == 3){
			if(a.x > 0 && er[a.x-1][a.y] != '#'){
				a.x -= 1;
				return gao(a);
			}
		}
	}
	return a;
}

int bfs(){
	while(!q.empty()) q.pop();
	memset(vis, 0, sizeof(vis));
	temp.x = sx;
	temp.y = sy;
	temp.cnt = 0;
	temp.dir = 1;
	temp = gao(temp);
	vis[temp.x][temp.y][temp.dir] = 1;
	q.push(temp);
	while(!q.empty()){
		u = q.front();
		q.pop();
		if(er[u.x][u.y] == 'E') return u.cnt;
		u.cnt ++;
		for(int i = 0; i < 4; i ++){
			temp = solve(u, i);
			if(vis[temp.x][temp.y][temp.dir]) continue;
			vis[temp.x][temp.y][temp.dir] = 1;
			q.push(temp);
		}
	}
	return -1;
}	

int main(){
	while(scanf("%d%d", &n, &m) != EOF){
		int i, j;
		getchar();
		for(i = 0; i < n; i ++){
			gets(er[i]);
			for(j = 0; j < m; j ++){
				if(er[i][j] == '|'){
					sx = i;
					sy = j;
				}if(er[i][j] == 'E'){
					ex = i;
					ey = j;
				}
			}
		}
		int k = bfs();
		if(k != -1)
		printf("%d\n", k);
		else printf("Can not escape!\n");
	}
	return 0;
}

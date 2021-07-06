# 题目
When the scientists explore the sea base, they use a kind of auto mobile robot, which has the mission to collect the swatches of resource of the sea base. The collections of the resource are taken to the research ship and classified, and then the research ship goes back to the mainland -- the research centre where scientists can do further research.

The robots have equipments to collect and store the resource, but the equipments have limited capability. Only a small quantity of each kind of recourse is enough for scientific research. So, once the robot has collected one kind of resource, it needs not to collect more. The capability of the robot is fixed and the same as the number of kinds of resource the scientists have already known. So, the robot will collect a list of resource and come back with fruitful results. The resource is buried beneath the surface of the sea base, and the quantity is always enough for the robot to collect if the map indicates that there are some. If the robot doesn't want to collect the resource underneath its location, it can leave it ignored and pass the square freely.

The robot needs a unit electric power to move from a square to another when its container is vacant and only can it move to a square adjacent to it. It needs Ai units to dig and collect the resource marked i. Each of the resource has its weight, so the robot costs Bi units of power per move after it has collected resource i.

During the sea base walk, the robot carries a battery with a certain units(P) of electric power, and the power of it need to be economized, the scientists ask you to calculate the minimal quantity of power the robot will use to collect all kinds of resource and back to the ship.

输入描述
The first line of the input is an integer T which indicates the number of test cases.

Each of the cases tells the map of the sea base you will explore, The first line will be the M, N, K, P. M (1 ≤ M ≤ 20) is the width of the area, N (1 ≤ N ≤ 20) is the length of the area, and K (1 ≤ K ≤ 10) is the number of kinds of resource, P is the certain capacity of the battery.

Then follows M lines characters indicating the map, each line contains N characters.

There are four kinds of characters, '.', '*', '#' and capital letters.

The symbol '.' indicate that free space. The '*' indicates where the research ship located, notice that once the robot moves back to this area, it will be fetched back to the main ship automatically. You can assume there is only one '*' on one map.The '#' indicates that the space is blocked of some reason, the capital letters indicate K kinds of resource, and you can assume that there are always K kinds of capital letters (alphabetically from A).

The next K lines follows two integers each line, A<sub>i</sub> and B<sub>i</sub>  .

输出描述

For each input set output a number of the minimal quantity of power on one single line. Print a warning 'Impossible' if the minimal quantity of power needed exceeds the capacity of the battery or it's impossible for the robot to accomplish the mission. 　

输入例子
```
1
5 5 1 50
*....
##.##
A#.#A
.#.#.
.....
1 0
```
输出例子
```
21
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
#define N 25
#define M 15
#define NS 2510
const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};

char map[N][N];
int row,col,kind,power,sx,sy,tot;
int A[M],B[M],per[NS];
bool vis[N][N][NS];
struct node  //bfs搜索时的状态
{
    int x,y;    //当前所在的坐标
    int s;     //携带的物品的状态，压缩回来的十进制数
    int cost;  //花费了多少电量
    void func(int xx ,int yy ,int ss ,int cc)
    { x=xx; y=yy; s=ss; cost=cc; }
    bool operator<(const struct node &a) const{ 
        return cost > a.cost; }
};
priority_queue<struct node>que;

void input()
{
    cin >> row >> col >> kind >> power;
    for(int r=0; r<row; r++) cin >> map[r];
    for(int i=0; i<kind; i++) cin >> A[i] >> B[i];
    for(int r=0; r<row; r++)
        for(int c=0; c<col; c++)
            if(map[r][c] == '*')
            { sx=r; sy=c; break; }
}

void cal_per()
{
    tot = (1<<kind);
    for(int s=0; s<tot; s++)
    {
        per[s] = 1;
        for(int k=0; k<kind; k++)
            if( s & (1<<k) )
                per[s] += B[k];
    }
}

int solve()
{
    struct node a,b;
    memset(vis,0,sizeof(vis));
    while(!que.empty()) que.pop();
    a.func(sx,sy,0,0);
    que.push(a);
    vis[sx][sy][0] = true;

    while(!que.empty())
    {
        a = que.top(); que.pop();
        if(a.cost + per[a.s] > power) continue; 
        for(int k=0; k<4; k++) 
        {
            int xx = a.x + dx[k];
            int yy = a.y + dy[k];
            int ss = a.s;
            int cc = a.cost + per[a.s];
            if(xx<0 || xx>=row || yy<0 || yy>=col || map[xx][yy]=='#') continue; 

            if(xx==sx && yy==sy) 
                if(ss == tot-1) return cc;
                else            continue; 

            if(!vis[xx][yy][ss]) 
            {
                b.func(xx,yy,ss,cc);
                que.push(b);
                vis[xx][yy][ss] = true;
            }

            if(map[xx][yy]>='A' && map[xx][yy]<='Z')
            {
                int index = map[xx][yy] - 'A';
                if( !(ss & (1<<index)) ) 
                {
                    ss |= (1<<index); 
                    cc += A[index];  
                    if(cc+A[index] > power)  continue; 
                    if(xx==sx && yy==sy && ss==tot-1) return cc; 
                    if(!vis[xx][yy][ss])
                    {
                        b.func(xx,yy,ss,cc);
                        que.push(b);
                        vis[xx][yy][ss] = true;
                    }
                }
            }
        }
    }
    return -1;
}

int main()
{
    int cas;
    cin >> cas;
    while(cas--)
    {
        input();
        cal_per();
        int res = solve();
        if(res == -1) cout << "Impossible" << endl;
        else          cout << res << endl;
    }
    return 0;
}

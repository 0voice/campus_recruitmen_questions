# 题目

Let’s play a puzzle using eight cubes placed on a 3 × 3 board leaving one empty square.

Faces of cubes are painted with three colors. As a puzzle step, you can roll one of the cubes to a adjacent empty square. Your goal is to make the specified color pattern visible from above by a number of such steps.

The rules of this puzzle are as follows.

Coloring of Cubes: All the cubes area colored in the same way as shown in Figure 1. The opposite faces have the same color.

![image](https://user-images.githubusercontent.com/59190045/124566123-585d9500-de75-11eb-8cd7-c75a9a4c6fd8.png)

Initial Board State: Eight cubes are placed on the 3 × 3 board leaving one empty square. All the cubes have the same orientation as shown in Figure 2. As shown in the figure, squares on the board are given x and y coordinates, (1, 1), (1, 2), …, and (3, 3). The position of the initially empty square may vary.

![image](https://user-images.githubusercontent.com/59190045/124566152-601d3980-de75-11eb-8ff6-1cda8be19a59.png)

Rolling Cubes: At each step, we can choose one of the cubes adjacent to the empty square and roll it into the empty square, leaving the original position empty. Figure 3 shows an example.

![image](https://user-images.githubusercontent.com/59190045/124566185-67dcde00-de75-11eb-8ae5-7ee2c1bf075e.png)

Figure 3: Rolling a cube

Goal: The goal of this puzzle is to arrange the cubes so that their top faces form the specified color pattern by a number of cube rolling steps described above.

Your task is to write a program that finds the minimum number of steps required to make the specified color pattern from the given initial state.

输入描述

The input is a sequence of datasets. The end of the input is indicated by a line containing two zeros separated by a space. The number of datasets is less than 16. Each dataset is formatted as follows.

x |	y | -
--------------- | --------------- | ---------------
F <sub>11</sub> |	F <sub>21</sub> |	F <sub>31</sub>
F <sub>12</sub> |	F <sub>22</sub> |	F <sub>32</sub>
F <sub>13</sub> |	F <sub>23</sub> |	F <sub>33</sub>

The first line contains two integers x and y separated by a space, indicating the position (x, y) of the initially empty square. The values of x and y are 1, 2, or 3.

The following three lines specify the color pattern to make. Each line contains three characters F 1<sub>j</sub> , F 2<sub>j</sub> , and F 3<sub>j</sub> , separated by a space. Character F<sub>ij</sub> indicates the top color of the cube, if any, at the position (i, j) as follows:
```
B: Blue,

W: White,

R: Red,

E: the square is Empty.
```
There is exactly one ‘E’ character in each dataset.

输出描述

For each dataset, output the minimum number of steps to achieve the goal, when the goal can be reached within 30 steps. Otherwise, output “-1” for the dataset.

输入例子
```
1 2 
W W W 
E W W 
W W W 
2 1 
R B W 
R W W 
E W W 
3 3 
W B W 
B R E 
R B R 
3 3 
B W R 
B W R 
B E R 
2 1 
B B B 
B R B 
B R E 
1 1 
R R R 
W W W 
R R E 
2 1 
R R R 
B W B 
R R E 
3 2 
R R R 
W E W 
R R R
0 0
```
输出例子
```
0 
3 
13 
23 
29 
30 
-1 
-1
```
# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;            // 0WRB, 1WBR, 2RWB, 3RBW, 4BRW, 5BWR

int base[]={1,6,36,216,1296,7776,46656,279936,1679616};
int state[6][4]={{2,2,4,4},{5,5,3,3},{0,0,5,5},{4,4,1,1},{3,3,0,0},{1,1,2,2}};
char hash1[1680000][9];
char hash2[1680000][9];
char b[10];
struct node
{
    int s[9];
    int dis;
    int space;
    int value;
}st;
queue<node> q;
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};      //下，上，右，左，和前面相反

inline bool isok(int &x,int &y)
{
    return x>=0&&x<3&&y>=0&&y<3;
}
inline int cal(node &t)     //计算初始的hash值
{
    int value=0;
    int top=0;
    for(int i=0;i<9;i++)
    {
        if(i==t.space) continue;
        value+=t.s[i]*base[top++];
    }
    return value;
}
 int cal(node &t,node &f,int d)     //因为每次移动只会改变几个hash值，所以可以特判
{
    if(d==2)
    {
        t.value-=f.s[t.space]*base[f.space];
        t.value+=t.s[f.space]*base[f.space];
        return t.value;
    }
    else if(d==3)
    {
        t.value-=f.s[t.space]*base[t.space];
        t.value+=t.s[f.space]*base[t.space];
        return t.value;
    }
    else if(d==0)
    {
        for(int i=f.space;i<=f.space+2;i++)
        {
            t.value-=f.s[i+1]*base[i];
            t.value+=t.s[i]*base[i];
        }
        return t.value;
    }
    else if(d==1)
    {
        for(int i=t.space;i<=t.space+2;i++)
        {
            t.value-=f.s[i]*base[i];
            t.value+=t.s[i+1]*base[i];
        }
        return t.value;
    }
}
bool bfs(node st)
{
    node t1,t2,f;
    queue<node> Q;
    st.dis=0;
    Q.push(st);
    t2.dis=0;
    int k;
    int k1=1,kk1=0,k2=256,kk2=0;
    while(!Q.empty()&&!q.empty())
    {
        while(k1--){
        st=Q.front();Q.pop();
        if(st.dis+1+t2.dis>30) {printf("-1\n");return false;}
        for(int d=0;d<4;d++)
        {
            t1=st;
            int sx=t1.space/3;
            int sy=t1.space%3;
            int nx=sx+dir[d][0];
            int ny=sy+dir[d][1];
            if(isok(nx,ny))
            {
                t1.space=nx*3+ny;
                t1.s[sx*3+sy]=state[t1.s[nx*3+ny]][d];
                t1.s[nx*3+ny]=6;
                t1.dis=st.dis+1;
                t1.value=cal(t1,st,d);
                if(hash1[t1.value][t1.space]) continue;
                if(hash2[t1.value][t1.space]) {printf("%d\n",t1.dis+t2.dis);return true;}

                hash1[t1.value][t1.space]=t1.dis;
                Q.push(t1);
                kk1++;
            }
        }
        }
        k1=kk1;
        kk1=0;
        while(k2--){
        f=q.front();
        if(f.dis==9) break;
        q.pop();
        for(int d=0;d<4;d++)
        {
            t2=f;
            int sx=t2.space/3;
            int sy=t2.space%3;
            int nx=sx+dir[d][0];
            int ny=sy+dir[d][1];
            t2.dis=f.dis+1;
            if(isok(nx,ny))
            {
                t2.space=nx*3+ny;
                t2.s[sx*3+sy]=state[t2.s[nx*3+ny]][d];
                t2.s[nx*3+ny]=6;
                t2.value=cal(t2,f,d);
                if(hash2[t2.value][t2.space]) continue;
                if(hash1[t2.value][t2.space])
                {
                    printf("%d\n",t2.dis+st.dis+1);
                    return true;
                }
                hash2[t2.value][t2.space]=t2.dis;
                q.push(t2);
                kk2++;
            }
        }
        }
        t1.dis=f.dis+1;
        k2=kk2;
        kk2=0;
    }
    printf("-1\n");
}
void dfs(node &end,int k)
{
    if(k==9)
    {
        end.dis=0;
        end.value=cal(end);
        q.push(end);
        hash2[end.value][end.space]=1;
        return;
    }
    if(b[k]=='W')
    {
        end.s[k]=0;
        dfs(end,k+1);
        end.s[k]=1;
        dfs(end,k+1);
    }
    else if(b[k]=='R')
    {
        end.s[k]=2;
        dfs(end,k+1);
        end.s[k]=3;
        dfs(end,k+1);
    }
    else if(b[k]=='B')
    {
        end.s[k]=4;
        dfs(end,k+1);
        end.s[k]=5;
        dfs(end,k+1);
    }
    else
    {
        end.s[k]=6;
        dfs(end,k+1);
    }
}
int main()
{
    int x,y;
    char a;
    node end;
    while(scanf("%d%d",&y,&x)!=EOF)
    {
        if(!x&&!y) break;
        while(!q.empty()) q.pop();
        memset(hash1,0,sizeof(hash1));
        memset(hash2,0,sizeof(hash2));

        x--;y--;
        for(int i=0;i<9;i++)
        {
            if(x==i/3&&y==i%3) {st.s[i]=6;st.space=i;}
            else st.s[i]=0;
        }
        for(int i=0;i<9;i++)
        {
            scanf(" %c",&a);
            if(a=='E') end.space=i;
            b[i]=a;
        }
        dfs(end,0);     //得到所有的终点状态，全部加入队列。

        int k;          //一开始就是答案
        st.value=cal(st);
        hash1[st.value][st.space]=-1;
        if(hash2[st.value][st.space]) {printf("0\n");continue;}
        bfs(st);
    }
    return 0;
}

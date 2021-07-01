# 题目
Due to recent rains, water has pooled in various places in Farmer John's field, which is represented by a rectangle of N x M (1
Given a diagram of Farmer John's field, determine how many ponds he has.

输入描述

*Line 1: Two space-separated integers: N and M

*Lines 2..N+1: M characters per line representing one row of Farmer John's field. Each character is either 'W' or '.'. The characters do not have spaces between them.

输出描述

*Line 1: The number of ponds in Farmer John's field.

输入例子

    10 12
    W........WW.
    .WWW.....WWW
    ....WW...WW.
    .........WW.
    .........W..
    ..W......W..
    .W.W.....WW.
    W.W.W.....W.
    .W.W......W.
    ..W.......W.
输出例子
* 3

Hint

OUTPUT DETAILS:

There are three ponds: one in the upper left, one in the lower left,and one along the right side.
# 参考答案
    #include<iostream>
    #include<queue>
    using namespace std;

    struct Node
    {
      int x;
      int y;
    };

    int dir[8][2]={{0,1},{0,-1},{1,0},{-1,0},{1,-1},{-1,1},{1,1},{-1,-1}};
    char map[105][105];
    int num;
    int n,m;

    void BFS(int x,int y)
    {
      queue<Node>q;
      int tx,ty;
      int i,j;
      Node t,p;
      t.x=x;
      t.y=y;
      q.push(t);
      while(!q.empty())
      {
        p=q.front();
        q.pop();
        for(i=0;i<8;i++)
        {
          tx=p.x+dir[i][0];
          ty=p.y+dir[i][1];
          if(tx>=0&&tx<n&&ty>=0&&ty<m&&map[tx][ty]=='W')
          {
            t.x=tx;
            t.y=ty;
            q.push(t);
            map[tx][ty]='.';
          }
        }
      }
    }

    int main()
    {
      int i,j;
      while(scanf("%d%d",&n,&m)!=EOF)
      {
        num=0;
        for(i=0;i<n;i++)
        {
          scanf("%s",map[i]);
        }
        for(i=0;i<n;i++)
        {
          for(j=0;j<m;j++)
          {
            if(map[i][j]=='W')
            {
              num++;
              BFS(i,j);
            }
          }
        }
        printf("%d\n",num);
      }
      return 0;
    }

# 题目
H.L. is preparing a circuit for the next coming physical experiment. His circuit consists of N nodes, numbered 1 to N, which are connected by wires with certain resistance. H.L is curious about the equivalent resistance between Node 1 and Node N.

输入描述

The first line contains two positive integers N and M, the number of nodes and wires in the circuit.( N, M ≤ 100)

The next M lines, each describe a wire connection by three integers X, Y, R which indicates that between Node X and Node Y, there is a wire with resistance of R ohm.

输出描述

The equivalent resistance rounded after the second decimal place.

输入例子
```
2 2
1 2 1
1 2 1
```
输出例子
```
0.50
```
# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define INF 1000.0
#define V 105
using namespace std;
int num[V][V],n,N,m,i,x,y,j,p,k,zz;
double R[V][V],map[V][V][V],ans[V],s[V],f[V][V],max,z,A,Max,temp;
int main()
{
  while (scanf("%d%d",&n,&m)!=EOF)
  {
    memset(R,0,sizeof(R));
    memset(s,0,sizeof(s));
    memset(ans,0,sizeof(ans));
    memset(num,0,sizeof(num));
    memset(map,0,sizeof(map));
    memset(f,0,sizeof(f));
    A=0;
    for (i=1;i<=m;i++)
      scanf("%d%d%d",&x,&y,&zz),z=(double)zz,x--,y--,map[x][y][++num[x][y]]=z,map[y][x][++num[y][x]]=z;
    for (i=0;i<n;i++)
      for (j=0;j<n;j++)
        if (num[i][j])
        {
          for (k=1;k<=num[i][j];k++)
            R[i][j]+=(double)1.0/map[i][j][k];
          R[i][j]=1.0/R[i][j];
        }
    ans[0]=INF;ans[n-1]=0;N=n-2;
    for (i=1;i<=N;i++)
    {
      if (R[i][0]) f[i][i]-=1.0/R[i][0],s[i]-=ans[0]/R[i][0];
      if (R[i][n-1]) f[i][i]-=1.0/R[i][n-1];
      for (j=1;j<=N;j++)
        if (R[i][j]&&i!=j) f[i][j]=1.0/R[i][j],f[i][i]-=1.0/R[i][j];
    }
    for (i=1;i<N;i++)  
    {  
      for (j=i+1;j<=N;j++)  
      {  
        temp=f[j][i]/f[i][i];  
        for (k=i;k<=N;k++)  
          f[j][k]-=f[i][k]*temp;  
        s[j]-=s[i]*temp;  
      }  
    } 
    for (i=N;i;i--)  
    {  
      for (j=i+1;j<=N;j++)  
        s[i]-=ans[j]*f[i][j];  
      ans[i]=s[i]/f[i][i];  
    }
    for (i=0;i<=N;i++) if (R[i][n-1]) A+=ans[i]/R[i][n-1];
    printf("%.2lf\n",(INF/A+1e-4));
  }
  return 0;
}





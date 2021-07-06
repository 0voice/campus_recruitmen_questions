# 题目
The USA Computer Security Office claims that the terrorist attack on 11th of September could not be scheduled without the help of scheduler programs that minimize the period of hijacking 4 plan es and tower crashing. To check this claim, Information Ministry decided to write such a program and check if the result of the program is the same as the hijacking plan on September 11th. Terrorist's plan is to hijack some planes, immediately after take o ff and redirect them in order to hit the target towers. Each hijacked plane can be used for hitting at most one tower. The program input is the scheduling of the flights, and the position of main US towers. It's supposed that terrorists want to damage at least d towers and they want to minimize the period between the first and the last tower crash.

输入描述<br>
The input consists of several test cases. In the first line of each test case there are 4 numbers n, k, p, d which are the number of airports, towers, planes and minimum expected number of towers to be damaged, respectively. In the I'th line of the next n lines there are two integers x and y indicating the position of the I'th airport. Then, in the I'th line of the next k lines the re are two integers x and y indicating the position of the I'th tower and finally in the I'th line of the next p lines there are 5 integers h, m, f, t, s indicating that the I'th plane leaves the airport f to airport t at time h:m(hour and minute of the flight) with speed s kilometers per second. The test case with n=k=p=d=0 represent the end of input file. All coordinates are in kilomete

输出描述<br>
In the output, for each test case except the one with n=k=p=d=0 in a separate line write the minimum time (in the format of h:m) which is the period between the first and the last crash when at least d towers are damaged. If the period has seconds, round it to the nearest minute. If there is no such interval write "Impossible!" in the output file.

输入例子
```
2 2 2 2
17 97
25 47
72 7
43 78
18 41 1 2 4
7 17 1 2 8
2 1 1 1
89 85
57 45
2 25
14 5 2 1 7
0 0 0 0
```
输出例子
```
11:24
0:0
```
# 参考答案
```c++
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<stdio.h>
#include<cstring>
using namespace std;
double ans;
int n,k,p,d,cnt,adj[51][91],num[51],to[150];
bool visit[51];
struct edge
{
   int id1,id2;
   double w;
   bool operator <(const edge &temp)const
   {
        return w<temp.w;
   }
};
edge edges[5000];
struct airport
{
    double x,y;
};
airport airports[60];
struct tower
{
    double x,y;
};
tower towers[60];
struct plane
{
    double h,m,s;
    int f,t;
};
plane planes[100];
double dist(double x1,double y1,double x2,double y2)
{
       return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
bool dfs(int id)
{
     int i,j,s,q,ip; 
     for(i=0;i<num[id];i++)
     {
        ip=adj[id][i];
        if(to[ip]==ip)
        {
            to[id]=ip;
            to[ip]=id;
            return true;
        }
        else
        {
            if(!visit[to[ip]])
            {
               visit[to[ip]]=true;
               if(dfs(to[ip]))
               {
                  to[id]=ip;
                  to[ip]=id;
                  return true;
               }
            }
        }
     }
     return false;
}
double kk()
{
       int i,j,s,q,temp;
       double res=1000000000;
       for(i=0;i<cnt;i++)
       {
          for(j=0;j<k;j++) 
             num[j]=visit[j]=0;
          for(j=0;j<k+p;j++) 
             to[j]=j;
          temp=0;
          for(j=i+1;j<cnt;j++)
          {
              int id1=edges[j].id1,id2=edges[j].id2;
              if(id1==edges[i].id1||id2==edges[i].id2)
                  continue;
              adj[id1][num[id1]++]=id2;
              visit[id1]=true;
              temp+=dfs(id1); 
              if(temp>=d-1) 
                 break;
          }
          if(j<cnt)
          {
             if(res>edges[j].w-edges[i].w)
                res=edges[j].w-edges[i].w;
          }
          else
             break;
       }
       return res;
}
int main()
{
    int i,j,s,q,id;
    while(scanf("%d%d%d%d",&n,&k,&p,&d)&&n+k+p+d)
    {
          for(i=0;i<n;i++)
            scanf("%lf%lf",&airports[i].x,&airports[i].y);
          for(i=0;i<k;i++)           
            scanf("%lf%lf",&towers[i].x,&towers[i].y);
           for(i=0;i<p;i++)
           {
              scanf("%lf%lf%d%d%lf",&planes[i].h,&planes[i].m,&planes[i].f,&planes[i].t,&planes[i].s);                          
              planes[i].f--;
           }
           if(d>min(k,p))
           { 
                puts("Impossible!");
                continue;
           }
           if(d<=1)
           {
              printf("0:0\n");
              continue;
           }
           cnt=0;
           for(i=0;i<k;i++)
             for(j=0;j<p;j++)
             {
                edges[cnt].id1=i;
                edges[cnt].id2=j+k;
                id=planes[j].f;
                edges[cnt].w=dist(airports[id].x,airports[id].y,towers[i].x,towers[i].y)/planes[j].s;
                edges[cnt].w+=(planes[j].h*60.00+planes[j].m)*60.00;
                edges[cnt].w/=60.00;
                cnt++;
             }
          sort(edges,edges+cnt);
          ans=kk();
          if(ans<1000000000)
            printf("%d:%d\n",((int)(ans+0.5))/60,((int)(ans+0.5))%60);
          else
            puts("Impossible!");
    }
    return 0;
}

# 题目
You must have heard of the literature "Alice's Adventures in Wonderland"! The 3D film "Alice in Wonderland" published by Disney Company becomes the most popular film in 2010! Today, Alice starts her new adventure in Wonderland again!

In Wonderland, there are n cities, numbered from 1 to n. The capital is city 1. Cities are connected by bi-directional roads. The road system is constructed so that from every city, there is exactly one way to reach any other.

Alice hopes that she could make a tour in which she visits each city exactly once then return to the capital. Furthermore, she doesn't want to traverse any road more than once. Obviously, it is impossible to make such tour with current road system.

However, in Wonderland, we can use magic spells! The Cheshire Cat, with his magic power, plans to construct more roads to make Alice's dream come true. Sadly, if he used too many magic spells, he would be weaken. "What is the minimum number of roads I have to construct?" - The poor cat wonders. Could you help him answer this question?

输入描述

The first line of input contains the number n --- the number of cities in Wonderland (3 ≤ n ≤ 100 000). The following n-1 lines describe the roads. Each road is represented by two integers --- the indexes of two cities it connects.

输出描述

The minimum number of roads to construct.

输入例子
```
5
1 2
2 3
2 4
1 5
```
输出例子
```
2
```
Hint

In this example, we can construct 2 roads: 3-4 and 4-5, then Alice will be able to take a tour 1-2-3-4-5-1
# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std ;
const int N = 100001 ;
const int Inf = 100000000 ;
struct Node
{
       int vdx ;
       Node *next ;   
}*map[N],nome[2*N] ; 
int n,en;
void  add(int from,int to)
{
      Node *ptr = &nome[en++] ;
      ptr ->vdx = to ;
      ptr ->next = map[from] ;
      map[from] = ptr ;    
}   
int   son[N],dp[N][2],sug[N];
bool  used[N] ;
int   cmp(int a,int b)
{
      return  dp[a][0]-dp[a][1] < dp[b][0]-dp[b][1] ;   
}
void  dfs(int u,int f)
{
      int v , tot = 0 ;  
      used[u] = true ;
      dp[u][0] = dp[u][1] = Inf ;
      for(Node *ptr=map[u];ptr;ptr=ptr->next)
      {
              v = ptr -> vdx ;  
              if(!used[v])
              {
                      son[u] ++ ;
                      dfs(v,u) ;   
                      tot += dp[v][1] ; 
              }   
      }           
      if(son[u] == 0)
      { 
         dp[u][0] = dp[u][1] = 0 ;
         return ; 
      } 
      int j = 0 ;  
      for(Node *ptr=map[u];ptr;ptr=ptr->next)
      {
              int v = ptr -> vdx ;
              if(v != f)  {
                   dp[u][0] = min(dp[u][0],tot-dp[v][1]+dp[v][0]+son[u]-1) ; 
                   sug[j++] = v ; 
              }
      } 
      sort(sug,sug+j,cmp) ;
      if(j==1) {
           dp[u][1] = dp[u][0] ;
      }else {
          int x = sug[0] , y = sug[1] ;
          dp[u][1] = tot - dp[x][1] - dp[y][1] + dp[x][0] + dp[y][0] + son[u]-2 ;     
          dp[u][1] = min(dp[u][0],dp[u][1]) ;
      }            
} 
int readT()
{
      char c;int ret;
      while(c=getchar(),c<'0'||c>'9');
      ret=c-'0';
      while(c=getchar(),c>='0'&&c<='9')ret=ret*10+c-'0';
      return ret;
}
int   main()
{
      while(~scanf("%d",&n))
      {
            int a,b ;
            en=0; 
            for(int i=1;i<=n;i++)  map[i] = NULL ; 
            for(int i=1;i<n;i++)
            {
                a = readT() ;
                b = readT() ;  
                add(a,b) ;
                add(b,a) ; 
            }
            memset(son,0,sizeof(son)) ;
            memset(used,false,sizeof(used)) ;   
            dfs(1,-1) ;
            printf("%d\n",dp[1][1]+1) ;            
      }
      return 0 ; 
}




# 题目
There is a group of N bakers in the town of Utopia. These bakers hold a monthly celebration in which they award a prize to some of the luckier among themselves. These lucky guys are chosen as follows:

In the beginning there are some chalk marks on some of the bakers' houses. Each baker has a list of his/her favorite bakers. After each celebration each of the winners puts a chalk mark on the house of all the bakers in his/her favorite list. Before each celebration those bakers with an odd number of chalk marks on their house will be chosen as winners. As there will be a great prize for the winners of the tth celebration, you are asked to find the number of its winners.

输入描述

The first line of the input contains a single integer X (1 The first line of each instance contains two integers n (the number of bakers) and t (the number of the celebration we want the winners of).

1 1 The next n lines of the instance each describe a baker. In each of these lines first comes the name of the baker (names are lower case strings of no more than 20 characters without spaces), then comes the number of chalk marks initially on the baker's house, then comes the number of bakers in this baker's favorite list, and after that come the names of the bakers in this baker's list.

输出描述

There should be one line per test case. For each test case write a line containing a single integer, the number of the winners of the t-th celebration.

输入例子
```
2
3 2
bessie 2 3 bessie linda mary
mary 1 1 linda
linda 0 1 bessie
2 2	
siavosh 1 2 siavosh mohammad 
mohammad 1 0
```
输出例子
```
2
0
```
# 参考答案
```c++
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN 110
typedef int M[MAXN][MAXN];

struct person
{
    char name[25],fav[MAXN][25];
    int nfav;
    int ori;
};

person P[MAXN];
int n,baker[MAXN],matrix[MAXN][MAXN],O[MAXN][MAXN],cse,t,res;

void copy(M x,M y)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            x[i][j]=y[i][j];
        }
    }
    return ;
}

void mu(M x,M y)
{
    int i,j,k,t;
    M c;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            t=0;
            for(k=0;k<n;k++)
            {
                if(x[i][k] && y[k][j])
                {
                    t=(t+x[i][k]*y[k][j])%2;
                }
            }
            c[i][j]=t;
        }
    }
    copy(x,c);
    return ;
}

void Cal(M a,int k)
{
    if(k==1)
    {
        copy(a,O);
        return ;
    }
    Cal(a,k/2);
    mu(a,a);
    if(k & 1)
    {
        mu(a,O);
    }
}

int main()
{
    int i,j,k;
    scanf("%d",&cse);
    while(cse--)
    {
        scanf("%d %d",&n,&t);
        for(i=0;i<n;i++)
        {
            getchar();
            scanf("%s",P[i].name);
            scanf("%d %d",&P[i].ori,&P[i].nfav);
            baker[i]=P[i].ori%2;
            for(j=0;j<P[i].nfav;j++)
            {
                getchar();
                scanf("%s",&P[i].fav[j]);
            }
        }
        memset(O,0,sizeof(O));
        for(i=0;i<n;i++)
        {
            O[i][i]=1;
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<P[i].nfav;j++)
            {
                for(k=0;k<n;k++)
                {
                    if(strcmp(P[i].fav[j],P[k].name)==0)
                    {
                        break;
                    }
                }
                O[i][k]=(O[i][k]+1)%2;
            }
        }        
        Cal(matrix,t-1);     
        res=0;
        for(i=0;i<n;i++)
        {
            int tmp=0 ;
            for(j=0;j<n;j++)
            {
                tmp=(tmp+baker[j]*matrix[j][i])%2;
            }
            if(tmp)res++;              
        }           
        printf("%d\n",res);
    }
    return 0;
}

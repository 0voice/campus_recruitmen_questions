# 题目
FJ is about to take his N (1 ≤ N ≤ 30,000) cows to the annual"Farmer of the Year" competition. In this contest every farmer arranges his cows in a line and herds them past the judges.

The contest organizers adopted a new registration scheme this year: simply register the initial letter of every cow in the order they will appear (i.e., If FJ takes Bessie, Sylvia, and Dora in that order he just registers BSD). After the registration phase ends, every group is judged in increasing lexicographic order according to the string of the initials of the cows' names.

FJ is very busy this year and has to hurry back to his farm, so he wants to be judged as early as possible. He decides to rearrange his cows, who have already lined up, before registering them.

FJ marks a location for a new line of the competing cows. He then proceeds to marshal the cows from the old line to the new one by repeatedly sending either the first or last cow in the (remainder of the) original line to the end of the new line. When he's finished, FJ takes his cows for registration in this new order.

Given the initial order of his cows, determine the least lexicographic string of initials he can make this way.

输入描述
* Line 1: A single integer: N
* Lines 2..N+1: Line i+1 contains a single initial ('A'..'Z') of the cow in the ith position in the original line

输出描述

The least lexicographic string he can make. Every line (except perhaps the last one) contains the initials of 80 cows ('A'..'Z') in the new line.

输入例子
```
6
A
C
D
B
C
B
```
输出例子
```
ABCBCD
```
# 参考答案
```c++
#include <iostream>
using namespace std;
const int maxn=60010;

int wa[maxn],wb[maxn],sa[maxn],rk[maxn],w[maxn],v[maxn];
char s[maxn],ans[maxn];
int n;
int cmp(int* r,int a,int b,int l)  
{  
    return r[a]==r[b] && r[a+l]==r[b+l];  
}  

void da(char* s,int* sa,int n,int m)  
{  
     int *x=wa,*y=wb,*t,i,j,p;  
     for (i=0;i<m;i++) w[i]=0;  
     for (i=0;i<n;i++) w[x[i]=s[i]]++;  
     for (i=1;i<m;i++) w[i]+=w[i-1];  
     for (i=n-1;i>=0;i--) sa[--w[x[i]]]=i;  
     for (j=1,p=1;p<n;j*=2,m=p)  
     {  
         for (p=0,i=n-j;i<n;i++) y[p++]=i;  
         for (i=0;i<n;i++) if (sa[i]>=j) y[p++]=sa[i]-j;  
         for (i=0;i<n;i++) v[i]=x[y[i]];  
         for (i=0;i<m;i++) w[i]=0;  
         for (i=0;i<n;i++) w[v[i]]++;  
         for (i=1;i<m;i++) w[i]+=w[i-1];  
         for (i=n-1;i>=0;i--) sa[--w[v[i]]]=y[i];  
         for (t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)  
             x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;  
     }  
     for (i=1;i<n;i++) rk[sa[i]]=i; 
}  

void calheight()  
{  
     int i,j,k=0;  

}

int main()
{
    int i,j,tot;
    scanf("%d\n",&n);
    for (i=0;i<n;i++)
        scanf("%c\n",&s[i]);
    s[n]='$';
    for (i=n+1;i<n+n+1;i++)
        s[i]=s[n+n-i];
    s[n+n+1]=0;
    da(s,sa,strlen(s)+1,128);
    tot=0;
    for (i=0,j=n+1;i<n && j<n+n+1;)
    {
        if (rk[i]<rk[j]) ans[tot++]=s[i++];
        else ans[tot++]=s[j++];
        if (tot==n) break;
    }
    for (i=0;i<tot;i++)
    {
        cout << ans[i];
        if (i%80==79) cout << endl;
    }
    return 0;
}

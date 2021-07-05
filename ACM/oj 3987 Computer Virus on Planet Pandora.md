# 题目
Aliens on planet Pandora also write computer programs like us. Their programs only consist of capital letters (‘A’ to ‘Z’) which they learned from the Earth. On planet Pandora, hackers make computer virus, so they also have anti-virus software. Of course they learned virus scanning algorithm from the Earth. Every virus has a pattern string which consists of only capital letters. If a virus’s pattern string is a substring of a program, or the pattern string is a substring of the reverse of that program, they can say the program is infected by that virus. Give you a program and a list of virus pattern strings, please write a program to figure out how many viruses the program is infected by.

输入描述

There are multiple test cases. The first line in the input is an integer T ( T

For each test case:

The first line is a integer n( 0

Then n lines follows, each represents a virus pattern string. Every pattern string stands for a virus. It’s guaranteed that those n pattern strings are all different so there are n different viruses. The length of pattern string is no more than 1,000 and a pattern string at least consists of one letter.

The last line of a test case is the program. The program may be described in a compressed format. A compressed program consists of capital letters and “compressors”. A “compressor” is in the following format:

[qx]

q is a number( 0<br>
AB[2D]E[7K]G

It actually is ABDDEKKKKKKKG after decompressed to original format.<br>
The length of the program is at least 1 and at most 5,100,000, no matter in the compressed format or after it is decompressed to original format.<br>
输出描述<br>
For each test case, print an integer K in a line meaning that the program is infected by K viruses.<br>
输入例子
```
3
2
AB
DCB
DACB
3
ABC
CDE
GHI
ABCCDEFIHG
4
ABB
ACDEE
BBB
FEEE
A[2B]CD[4E]F
```
输出例子
```
0
3
2
```
Hint

In the second case in the sample input, the reverse of the program is ‘GHIFEDCCBA’, and ‘GHI’ is a substring of the reverse, so the program is infected by virus ‘GHI’.
# 参考答案
```c++
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int MAXN=251;
const int MAXL=5100001;

struct node
{
    int id,fail;
    int next[26];
}ac[500000];
char P1[MAXL],word[MAXN][1001];
int N,test,len,tn,ans;
queue<int> q;

void Insert(char *s)
{
    int len=strlen(s);
    int p=0;
    for (int i=0;i<len;i++)
    {
        int index=s[i]-'A';
        if (!ac[p].next[index])  ac[p].next[index]=++tn;
        p=ac[p].next[index];
    }
    ac[p].id=1;
}

void Build()
{
    ac[0].fail=-1;
    q.push(0);
    while (!q.empty())
    {
        int u=q.front();
        q.pop();
        for (int i=0;i<26;i++)
        {
            int temp=ac[u].next[i],p;
            if (temp)
            {
                for (p=ac[u].fail;p!=-1;p=ac[p].fail)
                    if (ac[p].next[i]) {ac[temp].fail=ac[p].next[i];break;}
                if (p==-1) ac[temp].fail=0;
                q.push(temp);
            }
        }
    }
}

void Init()
{
    scanf("%d",&N);
    for (int i=1;i<=N;i++) 
    {
        scanf("%s",word[i]);
        Insert(word[i]);
    }
    int a;
    char ch;
    scanf("\n");
    for(scanf("%c",&ch);ch!='\n';scanf("%c",&ch))
    {
        if (ch=='[')
        {            
            scanf("%d",&a);
            scanf("%c",&ch);
            for (int i=1;i<=a;i++) P1[len++]=ch;
            scanf("%c",&ch);
        }
        else  P1[len++]=ch;
    }
    P1[len]='\0';
    Build();
}

void Solve(char *s)
{
    int len=strlen(s),p=0;
    for (int i=0;i<len;i++)
    {
        int index=s[i]-'A';
        while (!ac[p].next[index]&&p) p=ac[p].fail;
        p=ac[p].next[index];
        int temp=p;
        while (temp&&ac[temp].id!=-1)
        {
            ans+=ac[temp].id;
            ac[temp].id=-1;
            temp=ac[temp].fail;
        }
    }
}

void Prepare()
{
    len=tn=ans=0;
    memset(ac,0,sizeof(ac));
    memset(P1,0,sizeof(P1));
}

int main()
{
    scanf("%d",&test);
    while (test--)
    {
        Prepare();
        Init();
        Solve(P1);
        for (int i=0;i<len/2;i++) swap(P1[i],P1[len-1-i]);
        Solve(P1);
        printf("%d\n",ans);
    }
    return 0;
}




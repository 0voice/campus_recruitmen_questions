# 题目
KEY Inc., the leading company in security hardware, has developed a new kind of safe. To unlock it, you don't need a key but you are required to enter the correct n-digit code on a keypad (as if this were something new!). There are several models available, from toy safes for children (with a 2-digit code) to the military version (with a 6-digit code).

The safe will open as soon as the last digit of the correct code is entered. There is no "enter" key. When you enter more than n digits, only the last n digits are significant. For example (in the 4-digit version), if the correct code is 4567, and you plan to enter the digit sequence 1234567890, the door will open as soon as you press the 7 key.

The software to create this effect is rather simple. In the n-digit version the safe is always in one of 10<sup>n-1</sup> internal states. The current state of the safe simply represents the last n-1 digits that have been entered. One of these states (in the example above, state 456) is marked as the unlocked state. If the safe is in the unlocked state and then the right key (in the example above, 7) is pressed, the door opens. Otherwise the safe shifts to the corresponding new state. For example, if the safe is in state 456 and then you press 8, the safe goes into state 568.

A trivial strategy to open the safe is to enter all possible codes one after the other. In the worst case, however, this will require n * 10<sup>n</sup> keystrokes. By choosing a good digit sequence it is possible to open the safe in at most 10<sup>n</sup> + n - 1 keystrokes. All you have to do is to find a digit sequence that contains all n-digit sequences exactly once. KEY Inc. claims that for the military version (n=6) the fastest computers available today would need billions of years to find such a sequence - but apparently they don't know what some programmers are capable of...

输入描述
The input contains several test cases. Every test case is specified by an integer n. You may assume

输出描述
For each test case specified by n output a line containing a sequence of 10<sup>n</sup> + n - 1> digits that contains each n-digit sequence exactly once.

输入例子
```
1
2
0
```
输出例子
```
0123456789
00102030405060708091121314151617181922324252627282933435363738394454647484955657585966768697787988990
```
# 参考答案
```c++
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define M 1001000
using namespace std;
int to[M],head[M],len[M],next[M],top,cnt,n,dk,ans[M];
bool vis[M];
int fc[8]={1,10,100,1000,10000,100000,1000000};
struct STACK
{
    int x,p;
}stack[M];
void add(int u,int v,int w)
{
    to[cnt]=v; len[cnt]=w; next[cnt]=head[u]; head[u]=cnt++;
}
void create()
{
    memset(head,-1,sizeof head);
    memset(vis,0,sizeof vis);
    cnt=0;
    for(int i=0,tmp;i<fc[n-1];i++)
    {
        tmp=i%fc[n-2];
        for(int j=9;j>=0;j--)//字典序最小
            add(i,tmp*10+j,i*10+j);
    }
}
void euler()
{
    int u,pos;
    top=2; dk=0;
    stack[1].x=0; stack[1].p=head[0];
    while(top)
    {
        u=stack[top-1].x; pos=stack[top-1].p;
        for(;~pos;pos=next[pos])
            if(!vis[pos])
            {
                stack[top-1].p=pos;
                vis[pos]=true;
                stack[top].p=head[to[pos]]; stack[top].x=to[pos];  ++top;
                break;
            }
        if(pos==-1)//扫完u了，相当于递归完毕 
        {
            ans[++dk]=stack[top-1].p;
            top--;
        } 
    }
}
void prt()
{
    for(int i=1;i<n;i++) printf("0");
    for(int i=dk-1;i>=2;i--) printf("%d",len[ans[i]]%10);
    printf("\n");
}
void go()
{
    create();
    euler();
    prt();
}
int main()
{
    while(scanf("%d",&n),n)
    {
        if(n==1) printf("0123456789\n");
        else go();
    }
    return 0;
}

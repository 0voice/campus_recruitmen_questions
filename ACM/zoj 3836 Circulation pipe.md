# 题目
Darkgy is a transport pipe master. One day, due to some strange redstone signal, an Iron pipe changed its direction and make a part of the pipe system become a circulation pipe.

The circulation pipe consists of L unit pipe numbered from 0 to <var>L</var>-1. Every <var>K</var> ticks, an item will input into pipe 0, and it will be transported in pipes with 1 unit pipe length per tick speed from pipe 0 to pipe <var>L</var>-1. When it was transported into pipe <var>L</var>-1, its direction will reversed and will be transported from <var>L</var>-1 to 0. When it reached pipe 0, its direction will be reversed again.

This process will repeat until the moment when there are more than <var>C</var> items in one of the <var>L</var> pipes, <var>C</var> is the capacity of each pipe.

For example, if <var>L</var>=5, <var>K</var>=3, <var>C</var>=1.

In tick 0, the first item will input into pipe 0.

In tick 3, it will be transported into pipe 3 and the second item will input into pipe 0.

In tick 4, the first item reached pipe 4 and its direction reversed, at the same time, the second item moved into pipe 1.

In tick 6, the third item appeared in pipe 0, the first item moved into pipe 2 while the second item was in pipe 3. Though the first item and the second item crossed, but......it does not matter XD.

In tick 7, the first item and the third item meet in pipe 1, and pipe 1 blast.

Darkgy want to know in which tick, the circulation pipe will blast.

Input

There are large amount of test cases, for each test case, there will be only one line with 3 integers 1 ≤ <var>L</var>, <var>K</var>, <var>C</var> ≤ 104 which was mentioned in the description.

Output

For each test case, you should output only one line with an integer <var>T</var> which means the tick when circulation pipe was blast.

Sample Input
```
5 3 1
1 1 1
1 1 2
1 1 3
```
Sample Output
```
7
1
2
3
```
# 参考答案
```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#define ll long long
using namespace std;

ll a,b,x,y,q;
ll l,k,c;
ll myabs(ll x){
    return x>0?x:-x;
}
void extend_gcd(ll a,ll b,ll &x,ll &y,ll &q){
    if(b==0){x=1;y=0;q=a;}
    else{
        extend_gcd(b,a%b,x,y,q);
        ll tmp=x;x=y;y=tmp-a/b*y;
    }
}
ll forward(int i){
    ll ans=0;
    a=2*(l-1),b=-k;
    extend_gcd(a,b,x,y,q);
    ll t=k/myabs(q)*a;
    if(i==0||i==l-1) return (c-1)*t+i;
    if(2*i%q) ans=(c-1)*t+i;
    else{
        x*=-2*i/q;
        ll tmp=x/(k/q),res;
        res=x-k/q*tmp;
        if(res<0) res+=myabs(k/q);
        if(c&1) ans=c/2*t+i;
        else ans=(c-1)/2*t+res*a+2*i+a-i;
    }
    return ans;
}
ll backward(int i){
    ll ans=0;
    a=2*(l-1),b=-k;
    extend_gcd(a,b,x,y,q);
    ll t=k/myabs(q)*a;
    if(i==0||i==l-1) return (c-1)*t+i;
    if(2*(l-i-1)%q) ans=(c-1)*t+a-i;
    else{
        x*=-2*(l-i-1)/q;
        ll tmp=x/(k/q),res;
        res=x-k/q*tmp;
        if(res<0) res+=myabs(k/q);
        if(c&1) ans=c/2*t+a-i;
        else ans=(c-1)/2*t+res*a+2*(l-i-1)+i;
    }
    return ans;
}
int main()
{
    ll res;
    while(~scanf("%lld%lld%lld",&l,&k,&c)){
        if(l==1) {printf("%lld\n",c*k);continue;}
        c+=1;
        res=min(forward(0),backward(l-1));
        for(int i=1;i<l-1;i++){
            res=min(res,forward(i));
            res=min(res,backward(i));
        }
        printf("%lld\n",res);
    }
	return 0;
}




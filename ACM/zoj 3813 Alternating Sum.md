# 题目
There is a digit string <var>S</var> with infinite length. In addition, <var>S</var> is periodic and it can be formed by concatenating infinite repetitions of a base string <var>P</var>. For example, if <var>P</var> = 3423537, then <var>S</var> = 3423537342353734235373423537...

Let's define the alternating sum on substrings of <var>S</var>. Assume <var>S</var><var>l</var>..<var>r</var> is a substring of <var>S</var> from index <var>l</var> to index <var>r</var> (all indexes are 1-based), then the alternating sum of <var>S</var><var>l</var>..<var>r</var> is:

<var>G</var>(<var>l</var>, <var>r</var>) = <var>S</var><var>l</var> - <var>S</var><var>l+1</var> + <var>S</var><var>l+2</var> - ... + (-1)<var>r-l</var><var>S</var><var>r</var>

For example, <var>S</var>2..10 = 423537342, then <var>G</var>(2, 10) = 4 - 2 + 3 - 5 + 3 - 7 + 3 - 4 + 2 = -3.

Now, you are given the base string <var>P</var> and you have to do many operations. There are only two kinds of operations:

1 <var>x d</var>: set <var>P</var><var>x</var> to <var>d</var>, <var>d</var> is a single digit.<br>
2 <var>l r</var>: find the sum of <var>G</var>(<var>i</var>, <var>j</var>) that <var>l</var> <= <var>i</var> <= <var>j</var> <= <var>r</var>.

For each second operation, you should output the sum modulo 10<sup>9</sup> + 7.

Input<br>
There are multiple test cases. The first line of input contains an integer <var>T</var> indicating the number of test cases. For each test case:

The first line contains a digit string <var>P</var> (1 <= length(<var>P</var>) <= 100000).

The second line contains an integer <var>Q</var> (1 <= <var>Q</var> <= 100000) indicating the number of operations. Each of the following <var>Q</var> lines is an operation in such format:

1 <var>x d</var> (1 <= <var>x</var> <= length(<var>P</var>), 0 <= <var>d</var> <= 9)<br>
2 <var>l r</var> (1 <= <var>l</var> <= <var>r</var> <= 1018)<br>

Output<br>
For each "2 l r" operation, output an integer, indicating the sum modulo 109 + 7.

Sample Input
```2
324242
4
2 1 1
2 1 4
1 3 7
2 3 4
324242
6
2 1 1
1 3 7
2 2 4
1 3 4
2 7 10
2 1 30
```
Sample Output
```
3
20
14
3
8
20
870
```
# 参考答案
```c++
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#define maxn 200010
#define mid ((t[p].l+t[p].r)>>1)
#define ls (p<<1)
#define rs (ls|1)
#define ll long long
#define mod 1000000007
using namespace std;
char st[maxn];
struct tree
{
    ll l,r;
    ll sum[2],tsum[2];
}t[maxn<<2];
void pushup(int p)
{
    ll l=t[ls].r-t[ls].l+1;
    ll r=t[rs].r-t[rs].l+1;
    if(l%2)
    {
        t[p].sum[0]=(t[ls].sum[0]+t[rs].sum[1])%mod;
        t[p].sum[1]=(t[ls].sum[1]+t[rs].sum[0])%mod;
        t[p].tsum[0]=(t[ls].tsum[0]+r*t[ls].sum[0]%mod+t[rs].tsum[1])%mod;
        t[p].tsum[1]=(t[ls].tsum[1]+r*t[ls].sum[1]%mod+t[rs].tsum[0])%mod;
    }
    else
    {
        t[p].sum[0]=(t[ls].sum[0]+t[rs].sum[0])%mod;
        t[p].sum[1]=(t[ls].sum[1]+t[rs].sum[1])%mod;
        t[p].tsum[0]=(t[ls].tsum[0]+r*t[ls].sum[0]%mod+t[rs].tsum[0])%mod;
        t[p].tsum[1]=(t[ls].tsum[1]+r*t[ls].sum[1]%mod+t[rs].tsum[1])%mod;
    }
}
void build(int p,int l,int r)
{
    t[p].l=l,t[p].r=r;
    t[p].sum[0]=t[p].sum[1]=t[p].tsum[0]=t[p].tsum[1]=0;
    if(l==r)
    {
        t[p].sum[0]=t[p].tsum[0]=0;
        t[p].sum[1]=t[p].tsum[1]=st[l]-'0';
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}
void modify(int p,int po,ll d)
{
    if(t[p].l==t[p].r)
    {
        t[p].sum[1]=t[p].tsum[1]=d;
        return;
    }
    if(po>mid)
    modify(rs,po,d);
    else
    modify(ls,po,d);
    pushup(p);
}
tree query(int p,ll l,ll r)
{
    tree tmp;
    if(t[p].l==l&&t[p].r==r)
    {
        return t[p];
    }
    if(l>mid)
    return query(rs,l,r);
    else if(r<=mid)
    return query(ls,l,r);
    else
    {
        tree t1=query(ls,l,mid);
        tree t2=query(rs,mid+1,r);
        tmp.l=t1.l,tmp.r=t2.r;
        ll l=t1.r-t1.l+1;
        ll r=t2.r-t2.l+1;
        if(l%2){
            tmp.sum[0]=(t1.sum[0]+t2.sum[1])%mod;
            tmp.sum[1]=(t1.sum[1]+t2.sum[0])%mod;
            tmp.tsum[0]=(t1.tsum[0]+r*t1.sum[0]%mod+t2.tsum[1])%mod;
            tmp.tsum[1]=(t1.tsum[1]+r*t1.sum[1]%mod+t2.tsum[0])%mod;
        }
        else{
            tmp.sum[0]=(t1.sum[0]+t2.sum[0])%mod;
            tmp.sum[1]=(t1.sum[1]+t2.sum[1])%mod;
            tmp.tsum[0]=(t1.tsum[0]+r*t1.sum[0]%mod+t2.tsum[0])%mod;
            tmp.tsum[1]=(t1.tsum[1]+r*t1.sum[1]%mod+t2.tsum[1])%mod;
        }
        return tmp;
    }
}
ll getsum(ll num,ll len,ll left,int typ)
{
    if(num==0)
    return 0;
    ll sum=0;
    sum=num%mod*t[1].tsum[typ]%mod;
    ll tt;
    if(num%2)
    tt=((num-1)/2)%mod*(num%mod);
    else
    tt=((num-1)%mod)*((num/2)%mod);
    tt%=mod;
    ll tmp=(num%mod*left%mod+tt*len%mod)%mod;
    sum=(sum+tmp*t[1].sum[typ]%mod)%mod;
    return sum;
}
int main()
{
  // freopen("dd.txt","r",stdin);
    int ncase;
    scanf("%d",&ncase);
    while(ncase--)
    {
        scanf("%s",st);
        int len=strlen(st);
        for(int i=0;i<len;i++)
        {
            st[i+len]=st[i];
        }
        len*=2;
        build(1,0,len-1);
        int q;
        scanf("%d",&q);
        while(q--){
            int typ;
            ll ans=0,l,r;
            scanf("%d",&typ);
            if(typ==1)
            {
                int x,d;
                scanf("%d%d",&x,&d);
                modify(1,x-1,d);
                modify(1,x-1+(len/2),d);
            }
            else
            {
                scanf("%lld%lld",&l,&r);
                l--,r--;
                ll lpo=l/len,rpo=r/len;
                ll L=l%len,R=r%len;
                if(lpo==rpo)
                {
                    ans=query(1,L,R).tsum[1];
                }
                else
                {
                    ll Len=((r-l+1)-(len-L))%mod;
                    tree t1=query(1,L,len-1);
                    tree t2=query(1,0,R);
                    ans=(ans+t1.tsum[1]+Len*t1.sum[1]%mod)%mod;
                    if((len-L)%2)
                    ans=(ans+t2.tsum[0])%mod;
                    else
                    ans=(ans+t2.tsum[1])%mod;
                    if((len-L)%2)
                    ans=(ans+getsum(rpo-lpo-1,len,R+1,0))%mod;
                    else
                    ans=(ans+getsum(rpo-lpo-1,len,R+1,1))%mod;
                }
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}

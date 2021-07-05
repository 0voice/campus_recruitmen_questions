# 题目
"Let it Bead" company is located upstairs at 700 Cannery Row in Monterey, CA. As you can deduce from the company name, their business is beads. Their PR department found out that customers are interested in buying colored bracelets. However, over 90 percent of the target audience insists that the bracelets be unique. (Just imagine what happened if two women showed up at the same party wearing identical bracelets!) It's a good thing that bracelets can have different lengths and need not be made of beads of one color. Help the boss estimating maximum profit by calculating how many different bracelets can be produced.

A bracelet is a ring-like sequence of s beads each of which can have one of c distinct colors. The ring is closed, i.e. has no beginning or end, and has no direction. Assume an unlimited supply of beads of each color. For different values of s and c, calculate the number of different bracelets that can be made.

输入描述<br>
Every line of the input file defines a test case and contains two integers: the number of available colors c followed by the length of the bracelets s. Input is terminated by c=s=0. Otherwise, both are positive, and, due to technical difficulties in the bracelet-fabrication-machi

![poj_3492output_0](http://uploadfiles.nowcoder.com/probs/acm/poj_3492output_0.jpg)

输出描述<br>
For each test case output on a single line the number of unique bracelets. The figure below shows the 8 different bracelets that can be made with 2 colors and 5 beads.
输入例子<br>
```
1 1
2 1
2 2
5 1
2 5
2 6
6 2
0 0
```
输出例子
```
1
2
3
5
8
13
21
```

# 参考答案
```c++
#include<cstdio>
#include<iostream>
using namespace  std;
int ans;
int fun(int x,int n)
{
    if(n==0)
    {
        ans=1;
        return ans;
    }
    if(n==1)
    {
        ans=x;
        return ans;
    }
    fun(x,n>>1); //浜屽垎
    ans=ans*ans;
    if(n&1)
    {
        ans=ans*x;
        return ans;
    }
    return ans;
}
int euler(int n){
     int res=n,a=n;
     for(int i=2;i*i<=a;i++){
         if(a%i==0){
             res=res/i*(i-1);
             while(a%i==0) a/=i;
         }
     }
     if(a>1) res=res/a*(a-1);
     return res;
}
void solve(int n,int c)
{
    int ans = 0;
    for (int i = 1; i <= n; i++) if (n % i == 0)
        {
            ans += fun(c, i) * euler(n / i);
        }
    if (n & 1) ans += n * fun(c, n / 2 + 1);
    else ans += n / 2 * (fun(c, n / 2) + fun(c, n / 2 + 1));
    cout << ans / (2 * n) << endl;
}
int main()
{
    int n,c;
    while(~scanf("%d%d",&c,&n)&&n&&c)
    {
            solve(n,c);
    }
    return 0;
}


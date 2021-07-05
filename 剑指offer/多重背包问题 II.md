# 题目
![NO5.png](https://img10.360buyimg.com/ddimg/jfs/t1/192353/5/11582/38381/60e2b331E4fe9865a/622255978780c5d0.png)
# 参考答案
### c++代码
```c++
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 2010;
int f[N],n,m;
struct good
{
    int w,v;
};

int main()
{
    cin>>n>>m;
    vector<good> Good;
    good tmp;

    //二进制处理
    for(int i = 1 ; i <= n ; i++ )
    {
        int v,w,s;
        cin>>v>>w>>s;
        //坑,k <= s
        for(int k = 1 ; k <= s ; k*=2 )
        {
            s-=k;
            Good.push_back({k*w,k*v});
        }
        if(s>0) Good.push_back({s*w,s*v});
    }

    //01背包优化+二进制
    for(auto t : Good)
        for(int j = m ; j >= t.v ; j--)
            f[j] = max(f[j] , f[j-t.v]+t.w ); //这里就是f[j]


    cout<<f[m]<<endl;
    return 0;

}

```

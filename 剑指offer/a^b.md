# 题目
求 a 的 b 次方对 p 取模的值。

输入格式<br>
三个整数 a,b,p ,在同一行用空格隔开。

输出格式<br>
输出一个整数，表示a^b mod p的值。

数据范围<br>
0≤a,b≤109<br>
1≤p≤109<br>

输入样例：
```
3 2 7
```
输出样例：
```
2
```
# 参考答案
```c++
#include<iostream>
using namespace std;

int main()
{
    long long  a,b,p,res=1;
    scanf("%ld%ld%ld",&a,&b,&p);
    while(b)
    {
        if(b&1) res=res*a%p;
        b>>=1;//b右移了一位后,a也需要更新
        a=a*a%p;
    }
    printf("%ld\n",res%p);
}

# 题目
Data-mining huge data sets can be a painful and long lasting process if we are not aware of tiny patterns existing within those data sets.

One reputable company has recently discovered a tiny bug in their hardware video processing solution and they are trying to create software workaround. To achieve maximum performance they use their chips in pairs and all data objects in memory should have even number of references. Under certain circumstances this rule became violated and exactly one data object is referred by odd number of references. They are ready to launch product and this is the only showstopper they have. They need YOU to help them resolve this critical issue in most efficient way.

Can you help them?

输入描述

Input file consists from multiple data sets separated by one or more empty lines.

Each data set represents a sequence of 32-bit (positive) integers (references) which are stored in compressed way.

Each line of input set consists from three single space separated 32-bit (positive) integers X Y Z and they represent following sequence of references: X, X+Z, X+2*Z, X+3*Z, …, X+K*Z, …(while (X+K*Z)<=Y).

Your task is to data-mine input data and for each set determine weather data were corrupted, which reference is occurring odd number of times, and count that reference.

输出描述

For each input data set you should print to standard output new line of text with either “no corruption” (low case) or two integers separated by single space (first one is reference that occurs odd number of times and second one is count of that reference).

输入例子
```
1 10 1
2 10 1

1 10 1
1 10 1

1 10 1
4 4 1
1 5 1
6 10 1
```
输出例子
```
1 1
no corruption
4 3
```
# 参考答案
```c++
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
#define N 500005
typedef long long LL;
using namespace std;
int n ;
LL X[N] , Y[N] , Z[N];
char str[55];

LL cal(LL k)
{
  LL sum = 0 , x;
  for (int i = 1 ; i <= n; ++ i)
  {
    if (k < X[i]) continue;
    x = min(k , Y[i]);
    sum += (x - X[i]) / Z[i] + 1;
  }
  return sum;
}

void work()
{
  n = 1;
  X[n] = 0;
  sscanf(str , "%I64d %I64d %I64d" , &X[n] , &Y[n] , &Z[n]);
  if (!X[n]) return;
  memset(str , 0 , sizeof(str));
  while (gets(str) , *str)
    ++ n , sscanf(str , "%I64d %I64d %I64d" , &X[n] , &Y[n] , &Z[n]) , memset(str , 0 , sizeof(str));
  LL l = 1 , r = 1LL << 33 , m;
  while (l < r)
  {
    m = (l + r) >> 1;
    if (cal(m) & 1)
      r = m;
    else l = m + 1;
  }
  if (l == 1LL << 33)
    puts("no corruption");
  else printf("%I64d %I64d\n" , l , (cal(l) - cal(l - 1)));
}

int main()
{
  while(gets(str))
    work();
  return 0;
}

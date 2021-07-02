# 题目
Count the number of permutations that have a specific number of inversions.
Given a permutation a1, a2, a3,..., an of the n integers 1, 2, 3, ..., n, an inversion is a pair (ai, aj) where i aj. The number of inversions in a permutation gives an indication on how "unsorted" a permutation is. If we wish to analyze the average running time of a sorting algorithm, it is often useful to know how many permutations of n objects will have a certain number of inversions.

In this problem you are asked to compute the number of permutations of n values that have exactly k inversions.

For example, if n = 3, there are 6 permutations with the indicated inversions as follows:
```
123			0 inversions


132			1 inversion (3 > 2)


213			1 inversion (2 > 1)


231			2 inversions (2 > 1, 3 > 1)


312			2 inversions (3 > 1, 3 > 2)


321			3 inversions (3 > 2, 3 > 1, 2 > 1)
```
Therefore, for the permutations of 3 things
1 of them has 0 inversions
2 of them have 1 inversion
2 of them have 2 inversions
1 of them has 3 inversions
0 of them have 4 inversions
0 of them have 5 inversions
etc.

输入描述

The input consists one or more problems. The input for each problem is specified on a single line, giving the intege

输出描述

For each problem, output the number of permutations of {1, ..., n}with exactly k inversions.

输入例子
```
3 0
3 1
3 2
3 3
4 2
4 10
13 23
18 80
0 0
```
输出例子
```
1
2
2
1
5
0
46936280
184348859235088
```
# 参考答案
```c++
#include<iostream>
using namespace std;
int main()
{
    long long dp[19][200]= {0};
    dp[1][0]=1;
    for(int i=1; i<18; i++)
        for(int j=0; dp[i][j]; j++)
            for(int k=0; k<=i; k++)
                dp[i+1][j+k]+=dp[i][j];
    int x,y;
    while(cin>>x>>y,x)
    cout<<dp[x][y]<<endl;
}

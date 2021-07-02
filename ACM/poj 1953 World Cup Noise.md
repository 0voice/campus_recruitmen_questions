# 题目
Background

"KO-RE-A, KO-RE-A" shout 54.000 happy football fans after their team has reached the semifinals of the FIFA World Cup in their home country. But although their excitement is real, the Korean people are still very organized by nature. For example, they have organized huge trumpets (that sound like blowing a ship's horn) to support their team playing on the field. The fans want to keep the level of noise constant throughout the match.

The trumpets are operated by compressed gas. However, if you blow the trumpet for 2 seconds without stopping it will break. So when the trumpet makes noise, everything is okay, but in a pause of the trumpet,the fans must chant "KO-RE-A"!
Before the match, a group of fans gathers and decides on a chanting pattern. The pattern is a sequence of 0's and 1's which is interpreted in the following way: If the pattern shows a 1, the trumpet is blown. If it shows a 0, the fans chant "KO-RE-A". To ensure that the trumpet will not break, the pattern is not allowed to have two consecutive 1's in it.
Problem

Given a positive integer n, determine the number of different chanting patterns of this length, i.e., determine the number of n-bit sequences that contain no adjacent 1's. For example, for n = 3 the answer is 5 (sequences 000, 001, 010, 100, 101 are acceptable while 011, 110, 111 are not).

输入描述

The first line contains the number of scenarios.

For each scenario, you are given a single positive integer less than 45 on a line by itself.

输出描述

The output for every scenario begins with a line containing "Scenario #i:", where i is the number of the scenario starting at 1. Then print a single line containing the number of n-bit sequences which have no adjacent 1's. Terminate the output for the scenario with a blank line.

输入例子
```
2
3
1
```
输出例子
```
Scenario #1:
5

Scenario #2:
2
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define maxn 45

int f[maxn];

int main()
{
    f[1] = 2;
    f[2] = 3;
    for (int i = 3; i < maxn; i++)
        f[i] = f[i - 1] + f[i - 2];
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        int a;
        scanf("%d", &a);
        printf("Scenario #%d:\n%d\n\n", i, f[a]);
    }
    return 0;
}

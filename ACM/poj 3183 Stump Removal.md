# 题目
Always thinking of the cows' grazing experience, FJ has found that he must remove N (1

FJ will use the traditional high explosives to destroy the stumps. These high explosives are formulated to destroy adjacent stumps as long as those adjacent stumps are strictly shorter than the nearest stump being destroyed. The blast can continue past the closest adjacent stump to the next adjacent stump if it is even shorter than the nearest stump just destroyed. As soon as a stump encountered by the blast wave is not shorter, though, no more destruction occurs on that side of the target stump (the other side follows the same rules with whatever stumps might appear there).

Consider a line of nine stumps with these heights:
```
              1 2 5 4 3 3 6 6 2
```
If FJ blows up the third stump (with height 5), then the second stump will also be destroyed (height 2) and the first stump (height 1) will also be destroyed. Likewise, the fourth stump (height 4) and fifth stump (height 3) will be destroyed since they are successively shorter, leaving the line like this:
```
              * * * * * 3 6 6 2
```
Two more explosives (at stumps 7 and 8) will destroy the rest.

Help FJ determine the minimum number of explosive charges he needs to destroy the stumps.

输入描述

Line 1: A single integer, N

Lines 2..N+1: Line i+1 contains H_i

输出描述

Lines 1..?: Each line contains one integer which is the index of a stump to blow up. The indices must be listed in increasing order.

输入例子
```
9
1
2
5
4
3
3
6
6
2
```
输出例子
```
3
7
8
```
# 参考答案
```c++
#include <iostream>
using namespace std;

int h[50050];

int main()
{
    int n, i;
    cin >> n;
    for (i = 1; i <= n; i++){
        cin >> h[i];
    }
    if (h[1] >= h[2])//边界的处理 
       cout << 1 << endl;
    for (i = 2; i <= n; i++){
        if (i == n){
              if (h[i] >= h[i-1])
                   cout << i << endl;
        }
        else{ 
              if (h[i] >= h[i-1] && h[i] >= h[i+1])
                  cout << i << endl;
           }
    }
    return 0;
}




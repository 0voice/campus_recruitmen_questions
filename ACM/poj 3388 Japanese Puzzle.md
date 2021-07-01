# 题目
A brand-new Japanese puzzle is coming from the East to strike the world-popular Sudoku game and become an international hit. The rules of this puzzle are kept in secret yet, but the goal is already advertised: given a square grid n × n, where each square contains a block with one of k types of pictures, the player has to rearrange it to get the maximal possible number of equal first rows (two rows are considered equal if both of them are filled with the same pictures in the same order). An unnamed insider of the game production company told the press that the game is about moving blocks of pictures according to some rules, while the overall set of pictures isn’t changed (no pictures removed, no new pictures added). She also mentioned that the puzzle is so exciting because there are thousands of ways to swap two arbitrary pictures on a grid leaving the rest of the grid intact.

Andy works at the puzzles review magazine, and of course he got interest in this Japanese news. He realized that the information known so far is enough to find the number of equal first rows in a puzzle winning position. Now Andy wants to write a computer program for calculating this number for any given starting configuration.

For example, if you are given a puzzle which looks this way:
≡ |	≡	| +
-------------|-------------|-------------
≡ |	∗ |	∗
∆ |	∗ |	∆

one of the optimal rearrangements could look like
≡	|∗	|∆
-------------|-------------|-------------
≡|	∗	|∆
+|	≡|	∗

输入描述

The first line of the input file contains two integers n (1 ≤ n ≤ <nobr>40 000</nobr>) and k (1 ≤ k ≤ <nobr>50 000</nobr>). Each of the next k lines contains the number of blocks with the corresponding type of picture li (li > 0, sum of all li is exactly n 2).

输出描述

Output the maximal possible number of equal first rows at the first line of the output file. The following n lines must contain contents of the row which gives the maximum. Each line shows a single number of picture, in order they must appear. If there are many optimal solutions, any is acceptable.

输入例子
* 3 4
* 3
* 3
* 2
* 1

输出例子
* 2
* 1
* 2
* 3

# 参考答案
    #include <stdlib.h>
    #include <stdio.h>
    #include <vector>
    #include <queue>
    #include <stack>
    #include <string>
    #include <set>
    #include <map>
    #include <algorithm>
    #include <cmath>
    #include <utility>
    #include <set>
    #include <functional>
    #include <string.h>
    #include <iostream>
    #include <numeric>
    #include <list>

    using namespace std;

    int main() {
      int n, k;
      scanf("%d %d", &n, &k);
      vector<int> data(k);
      for (int i = 0; i < k; ++i) {
        scanf("%d", &data[i]);
      }
      int low = 1; 
      int high = n + 1;
      while (high - low > 1) {
        int mid = (high + low) / 2;
        int cols = 0;
        for (int i = 0; i < k; ++i) {
          cols += data[i] / mid;
        }
        if (cols >= n) {
          low = mid;
        } else {
          high = mid;
        }
      }
      printf("%d\n", low);
      for (int i = 0; i < k; ++i) {
        for (int j = data[i] / low; j > 0; --j) {
          if (n-- > 0) {
            printf("%d\n", i + 1);
          } else {
            break;
          }
        }
      }
    }

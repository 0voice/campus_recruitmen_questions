# 题目
The puzzle game of Sudoku is played on a board of N 2 × N 2 cells. The cells are grouped in N × N squares of N × N cells each. Each cell is either empty or contains a number between 1 and N 2.

The sudoku position is correct when numbers in each row, each column and each square are different. The goal of the game is, starting from some correct position, fill all empty cells so that the final position is still correct.

This game is fairly popular in the Internet, and there are many sites which allow visitors to solve puzzles online. Such sites always have a subroutine to determine a correctness of a given position.

You are to write such a routin.

输入描述

Input file contains integer N, followed by N 4 integers — sudoku position. Empty cells are denoted by zeroes.

Constraints

1 ≤ N ≤ 10.

输出描述

Output file must contain a single string 'CORRECT' or 'INCORRECT'.
　

输入例子
```
Sample input 1
2
0 0 0 0
0 0 0 0
0 0 2 0
0 0 0 1
Sample input 2
2
2 1 3 0
3 2 4 0
1 3 2 4
0 0 0 1
```
输出例子
```
Sample output 1
CORRECT
Sample output 2
INCORRECT
```
Hint

Bold texts appearing in the sample sections are informative and do not form part of the actual data.

# 参考答案
```c++
#include<cstdio>
#include<cstring>
#define MAXN 105
int N, arr[MAXN][MAXN];
int x_used[MAXN][11], y_used[MAXN][11], n_used[MAXN][11];

int main() {
    while(scanf("%d", &N) != EOF) {
        memset(x_used, 0, sizeof(x_used));
        memset(y_used, 0, sizeof(y_used));
        memset(n_used, 0, sizeof(n_used));
        bool flag = true;
        for(int i = 0; i < N * N; ++ i) {
            for(int j = 0; j < N * N; ++ j) {
                scanf("%d", &arr[i][j]);
                if(arr[i][j] > 0 && flag) {
                    if(x_used[i][arr[i][j]] == 1) {
                        flag = false;
                    } else {
                        x_used[i][arr[i][j]] = 1;
                    }
                    if(y_used[j][arr[i][j]] == 1) {
                        flag = false;
                    } else {
                        y_used[j][arr[i][j]] = 1;
                    }
                    if(n_used[i / N * N + j / N + 1][arr[i][j]] == 1) {
                        flag = false;
                    } else {
                        n_used[i / N * N + j / N + 1][arr[i][j]] = 1;
                    }
                }
            }
        }
        if(flag) {
            printf("CORRECT\n");
        } else {
            printf("INCORRECT\n");
        }
    }
    return 0;
}





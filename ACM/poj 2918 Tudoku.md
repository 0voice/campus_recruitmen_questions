# 题目
Tom is a master in several mathematical-theoretical disciplines. He recently founded a research-lab at our university and teaches newcomers like Jim. In the first lesson he explained the game of Tudoku to Jim. Tudoku is a straight-forward variant of Sudoku, because it consists of a board where almost all the numbers are already in place. Such a board is left over when Tom stops solving an ordinary Sudoku because of being too lazy to fill out the last few straight-forward cells. Now, you should help Jim solve all Tudokus Tom left for him.

Sudoku is played on a 9 × 9 board that is divided into nine different 3 × 3 blocks. Initially, it contains only a few numbers and the goal is to fill the remaining cells so that each row, column, and 3 × 3 block contains every number from 1 to 9. This can be quite hard but remember that Tom already filled most cells. A resulting Tudoku board can be solved using the following rule repeatedly: if some row, column or 3 × 3 block contains exactly eight numbers, fill in the remaining one.

In the following example, three cells are still missing. The upper left one cannot be determined directly because neither in its row, column, or block, there are eight numbers present. The missing number for the right cell can be determined using the above rule, however, because its column contains exactly eight numbers. Similarly, the number for the lower-most free cell can be determined by examining its row. Finally, the last free cell can be filled by either looking at its row, column or block.

7	| 5 |	3 |	2	| 8 | 4	| 6	| 9	| 1
-|-|-|-|-|-|-|-|-|
4	|	8	|	2	|	9	|	1	|	6	|	5	|	3	|	7
1	|	9	| 6	| 7	| 5	| 3	|	8	| 4	|	2
9	|3	|1	|6	|4	|2	|5
2|	7	|5	|4	|9	|1	|3	|8	|6
6	|4	|8	|3	|2	|1	|7	|9
5	|6	|7	|3	|4	|9	|2	|1	|8
8	|2	|4	|1	|7	|5	|9	|6	|3
3	|1	|9	|6	|2	|8	|7	|5	|4

输入描述

The first line contains the number of scenarios. For each scenario the input contains nine lines of nine digits each. Zeros indicate the cells that have not been filled by Tom and need to be filled by you. Each scenario is terminated by an empty line.

输出描述

The output for every scenario begins with a line containing “<tt>Scenario #</tt>i<tt>:</tt>”, where i is the number of the scenario starting at 1. Then, print the solved Tudoku board in the same format that was used for the input, except that zeroes are replaced with the correct digits. Terminate the output for the scenario with a blank line.

输入例子
```
2
000000000
817965430
652743190
175439820
308102950
294856370
581697240
903504610
746321580

781654392
962837154
543219786
439182675
158976423
627543918
316728549
895461237
274395861
```
输出例子
```
Scenario #1:
439218765
817965432
652743198
175439826
368172954
294856371
581697243
923584617
746321589

Scenario #2:
781654392
962837154
543219786
439182675
158976423
627543918
316728549
895461237
274395861
```
# 参考答案
```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstdlib>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
const int maxd=10+5;
typedef long long ll;
int dx[]= {0,0,1,-1};
int dy[]= {1,-1,0,0};

int mz[maxd][maxd],visr[maxd][maxd],visc[maxd][maxd],grid[maxd][maxd];
char m[maxd][maxd];
int row[maxd],col[maxd];
void init()
{
    mem(visr,0),mem(visc,0),mem(grid,0);
    mem(row,0),mem(col,0);
    for(int i=0; i<9; ++i)
    {
        scanf("%s",m[i]);
        for(int j=0; j<9; ++j)
        {
            mz[i][j]=m[i][j]-'0';
            visr[i][mz[i][j]]=1;
            visc[j][mz[i][j]]=1;
            if(mz[i][j]!=0) row[i]++,col[j]++;
            int tmp=i/3*3+j/3;
            grid[tmp][mz[i][j]]=1;
        }
    }
    for(int i=0; i<9; ++i)
        if(row[i]==8)
        {
            int j;
            for(j=0; j<9; ++j)
                if(mz[i][j]==0) break;

            for(int k=1; k<=9; ++k)
                if(visr[i][k]==0)
                {
                    mz[i][j]=k;
                    visr[i][k]=1;
                    visc[j][k]=1;
                    int tmp=i/3*3+j/3;
                    grid[tmp][k]=1;
                    break;
                }
        }

    for(int j=0; j<9; ++j)
        if(col[j]==8)
        {
            int i;
            for(i=0; i<9; ++i)
                if(mz[i][j]==0) break;

            for(int k=1; k<=9; ++k)
                if(visc[j][k]==0)
                {
                    mz[i][j]=k;
                    visc[j][k]=1;
                    visr[i][k]=1;
                    int tmp=i/3*3+j/3;
                    grid[tmp][k]=1;
                    break;
                }
        }
}

bool dfs(int x,int y)
{
    // if(!setnum(x,y)) return;
    if(x==9) return true;
    bool flag=false;
    if(mz[x][y]==0)
    {
        int tmp=x/3*3+y/3;
        for(int i=1; i<=9; ++i)
            if(visr[x][i]==0 && visc[y][i]==0 && grid[tmp][i]==0)
            {
                mz[x][y]=i;
                visr[x][i]=1;
                visc[y][i]=1;
                grid[tmp][i]=1;
                if(y==8)
                    flag=dfs(x+1,0);
                else
                    flag=dfs(x,y+1);

                if(flag) return true;
                else
                {
                    mz[x][y]=0;
                    visr[x][i]=0;
                    visc[y][i]=0;
                    grid[tmp][i]=0;
                }
            }
    }
    else
    {
        if(y==8)
            flag=dfs(x+1,0);
        else
            flag=dfs(x,y+1);

        if(flag) return true;
        else return false;
    }
    return false;
}

void print(int k)
{
    printf("Scenario #%d:\n",k);
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j)
            printf("%d",mz[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int kase;
    scanf("%d",&kase);
    for(int k=1; k<=kase; ++k)
    {
        init();
        dfs(0,0);
        print(k);
    }
    return 0;
}

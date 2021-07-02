# 题目
The 15-puzzle has been around for over 100 years; even if you don't know it by that name, you've seen it. It is constructed with 15 sliding tiles, each with a number from 1 to 15 on it, and all packed into a 4 by 4 frame with one tile missing. Let's call the missing tile 'x'; the object of the puzzle is to arrange the tiles so that they are ordered as:
 ```
 1  2  3  4 

 5  6  7  8 

 9 10 11 12 

13 14 15  x 
```
where the only legal operation is to exchange 'x' with one of the tiles with which it shares an edge. As an example, the following sequence of moves solves a slightly scrambled puzzle:
``` 
 1  2  3  4    1  2  3  4    1  2  3  4    1  2  3  4 

 5  6  7  8    5  6  7  8    5  6  7  8    5  6  7  8 

 9  x 10 12    9 10  x 12    9 10 11 12    9 10 11 12 

13 14 11 15   13 14 11 15   13 14  x 15   13 14 15  x 

           r->           d->           r-> 
```
The letters in the previous row indicate which neighbor of the 'x' tile is swapped with the 'x' tile at each step; legal values are 'r','l','u' and 'd', for right, left, up, and down, respectively.

Not all puzzles can be solved; in 1870, a man named Sam Loyd was famous for distributing an unsolvable version of the puzzle, and
frustrating many people. In fact, all you have to do to make a regular puzzle into an unsolvable one is to swap two tiles (not counting the missing 'x' tile, of course).

In this problem, you will write a program for solving the less well-known 8-puzzle, composed of tiles on a three by three
arrangement.

输入描述

You will receive a description of a configuration of the 8 puzzle. The description is just a list of the tiles in their initial positions, with the rows listed from top to bottom, and the tiles listed from left to right within a row, where the tiles are represented by numbers 1 to 8, plus 'x'. For example, this puzzle
 ```
 1  2  3 

 x  4  6 

 7  5  8 
```
is described by this list:
```
 1 2 3 x 4 6 7 5 8 
 ```
输出描述

You will print to standard output either the word unsolvable, if the puzzle has no solution, or a string consisting entirely of the letters 'r', 'l', 'u' and 'd' that describes a series of moves that produce a solution. The string should include no spaces and start at the beginning of the line.

输入例子
```
2  3  4  1  5  x  7  6  8 
```
输出例子
```
ullddrurdllurdruldr
```
# 参考答案

```c++
#include <iostream>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

const    int        maxn = 10;

char    ans[100];
int        tot, dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

struct Node
{
    char    map[maxn];
    int        g, move, xpos;
}starts;

void init()
{
    for (int i = 0; i < 9; i++)
    {
        starts.map[i] = ' ';
        while (starts.map[i] == ' ')
            scanf("%c",&starts.map[i]);
        if (starts.map[i] == 'x')
        {
            starts.map[i] = 9;
            starts.xpos = i;
        } else
            starts.map[i] -= '0';
    }
}

int h(Node &a)
{
    int        x1, x2, y1, y2, i, r = 0;

    for (i = 0; i < 9; i++)
    {
        x1 = i / 3;
        y1 = i % 3;
        x2 = (a.map[i] - 1) / 3;
        y2 = (a.map[i] - 1) % 3;
        r += abs(x1 - x2) + abs(y1 - y2);
    }
    return r;
}

Node getchild(int a, Node ¤ts)
{
    int        x, y, pos, i;
    Node    r;

    x = currents.xpos / 3 + dir[a][0];
    y = currents.xpos % 3 + dir[a][1];
    r.xpos = -1;
    if (x < 0 || y < 0 || x > 2 || y > 2)
        return r;
    pos = x * 3 + y;
    r.xpos = pos;
    r.g = currents.g + 1;
    r.move = a;
    for (i = 0; i < 9; i++)
        r.map[i] = currents.map[i];
    r.map[pos] = 9;
    r.map[currents.xpos] = currents.map[pos];
    return r;
}

bool ida()
{
    int        pathlimit, i, temp, next;
    bool    success = 0;
    Node    currents, child;

    next = h(starts)/2;
    stack<Node> stk;
    do
    {
        pathlimit = next;
        if (pathlimit > 100)
            return false;
        tot = 0;
        starts.g = 0;
        starts.move = -1;
        next = 200;
        stk.push(starts);
        do
        {
            currents = stk.top();
            ans[currents.g] = currents.move;
            stk.pop();
            temp = h(currents);
            if (temp == 0)
            {
                tot = currents.g;
                success = true;
            }
            else if (pathlimit >= currents.g + temp / 2)
            {
                for (i = 0; i < 4; i++)
                {
                    child = getchild(i, currents);
                    if (child.xpos != -1 && abs(child.move - currents.move) != 2)
                        stk.push(child);
                }
            }else if (next > currents.g + temp / 2)
                next = currents.g + temp / 2;
        }while (!success && !stk.empty());
    }while (!success);
    return true;
}

void print()
{
    int        i;

    for (i = 1; i <= tot; i++)
        switch(ans[i])
        {
            case 0: printf("u"); break;
            case 1: printf("r"); break;
            case 2: printf("d"); break;
            case 3: printf("l"); break;
        }
    printf("\n");
}

int main()
{
    init();
    if (ida())
        print();
    else
        printf("unsolvable\n");
    return 0;
}



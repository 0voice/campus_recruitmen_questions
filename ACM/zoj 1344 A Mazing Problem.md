# 题目
In a maze of size M by N, there is a savage hound named "Fatdog". Fatdog keeps moving around, and will have a good bite at his victim as soon as anyone moves into his sightline. You are supposed to compute the minimum time taken to cross this maze alive, and Fatdog must be for sure avoided.

In every time unit, you may move one block to one of the upper, lower, left and right neighboring blocks, or you may stay where you are. Of course you must not move into the wall, neither must you walk right into Fatdog, and you must not fall into Fatdog's sightline as well. The entrance given is guaranteed to avoid Fatdog's sight.

At the mean time, Fatdog is not as smart as you are -- in every time unit, he either moves forward by one block, or stays and turns 90 degrees to the left or to the right.

Assume that in every time unit you and Fatdog are taking actions simultaneously.

Input

There are several test cases. For each test case:

The first line of input contains 2 integers M and N (0 < M,N <= 50) which indicating the size of a maze, provided that the origin is at the upper-left corner.

The second line contains 7 numbers: x1,y1,x2,y2,x3,y3,D where x1 and y1 are the coordinates of your starting position, x2 and y2 are your exit coordinates, x3 and y3 are the coordinates of the initial position of Fatdog (assuming that he is facing North at every beginning)

The next line contains D(0 < D <= 50) characters, representing Fatdog's actions. When he finishes these D actions, he will be back to his starting position and facing North, and then he will repeat these actions again and again forever (poor Fatdog...). These characters are:

'G' means moving one block forward

'L' means turning 90 degrees to the left

'R' means turning 90 degrees to the right

Then there will be M lines followed, with N characters in each line, describing the maze:

'.' represents an empty block, meaning there is a path.

'*' represents a block of wall.

The input is finished by a pair of 0's as M and N.


Output

For each test case, the first line of output must be in the form "Case d:" where d is the case number (start counting from 1). The second line must be either "Minimal time is: d" where d is the minimum crossing time, or "No way out" meaning that it is impossible to cross the maze alive.

Two test cases must be separated by a blank line.


Sample Input
```
5 3
3 1 3 3 4 2 8
GGRRGGRR
***
*.*
...
*.*
***
5 3
3 1 3 3 2 2 2
LR
***
*.*
...
*.*
***
3 3
2 1 2 3 2 2 4
RRRR
***
...
***
0 0
```
Sample Output
```
Case 1:
Minimal time is: 3

Case 2:
Minimal time is: 2

Case 3:
No way out
```
# 参考答案
```c++
#include<iostream>
#include<queue>
#include<cstdio>
#include<cctype>
#include<string.h> 
using namespace std;
enum {
    SIZ = 54,
};
struct Pnt{
    unsigned x,y;
    int m;
};
int move[5][2] = {
    {-1,0},{0,1},{1,0},{0,-1},{0,0}
};
int M, N, D;
int stat[SIZ][SIZ][SIZ];
int mat[SIZ][SIZ];
Pnt st, ex, dog;

int fun(){
    Pnt one, nex;
    queue<Pnt> q;
    st.m = 0;
    stat[0][st.x][st.y] = 1;
    q.push(st);
    while(!q.empty()){
        one = q.front(); q.pop();
        if(one.x == ex.x && one.y == ex.y){
            return stat[one.m][one.x][one.y]-1;
        }
        nex.m = (one.m + 1)%D ;
        for(int i=0; i<5; i++){
            nex.x = one.x + move[i][0];
            nex.y = one.y + move[i][1];
            if(nex.x>=M||nex.y>=N
                ||mat[nex.x][nex.y]
                ||stat[nex.m][nex.x][nex.y] != 0) 
                continue;
            stat[nex.m][nex.x][nex.y] = stat[one.m][one.x][one.y] + 1;
            q.push(nex);
        }
    }
    return -1;
}

void forbid(int s, const Pnt &p){
    unsigned x, y, d;
    x = p.x; y = p.y; d = p.m;
    while(x<M && y<N && mat[x][y] ==0){
        stat[s][x][y] = -1;
        x += move[d][0];
        y += move[d][1];
    }
}
int readIn(){
    static char buf[SIZ];
    scanf("%d%d",&M,&N);
    if(M + N ==0) return 0;
    memset(stat, 0, sizeof(stat));
    int x, y;
    scanf("%d%d",&x,&y);
    st.x = x-1, st.y = y-1;
    scanf("%d%d",&x,&y);
    ex.x = x-1, ex.y = y-1;
    scanf("%d%d",&x,&y);
    dog.x = x-1, dog.y = y-1; dog.m = 0;
    scanf("%d %s ", &D, buf);
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            scanf(" %c ", &mat[i][j]);
            mat[i][j] = (mat[i][j]=='*');
        }
    }
    x = dog.x, y = dog.y;
    forbid(0, dog);
    for(int i=0; i<D; i++){
        switch(buf[i]){
        case 'G':
            dog.x += move[dog.m][0];
            dog.y += move[dog.m][1];
            break;
        case 'L':
            dog.m = (dog.m + 3) % 4;
            break;
        case 'R':
            dog.m = (dog.m + 1) % 4;
            break;
        }
        forbid(i+1, dog);
    }
    if(x == dog.x && y==dog.y && dog.m == 0){
        ;
    } else {
        D++;
    }
    return 1;
}
int main(){
    int tst = 0, t;

    while(readIn() > 0){
        if(tst++) printf("\n");
        printf("Case %d:\n", tst);
        t = fun();
        if(t < 0){
            printf("No way out\n");
        } else {
            printf("Minimal time is: %d\n", t);
        }
    }
    return 0;
}





# 题目
Tomy's fond of a game called 'Fans and Gems' (also known as Gravnic). In the game, he can use fans to collect gems, but he's satisfied with his play only if all the gems are collected with minimal number of steps. The game is played as following:

![image](https://user-images.githubusercontent.com/59190045/124577443-d9ba2500-de7f-11eb-8331-fa751c4ff5a6.png)

There are three kinds of gems, one colored red, one colored green and one colored blue. There are walls in the space, as you see. There are also virtual fans everywhere in the game, but you cannot see them. What you can do each time is to select a DIRECTION to which the fans should blow. There are only four directions possible: UP, DOWN, LEFT and RIGHT. Then, the fans will work, pushing all the gems to fly to the selected direction at the same speed, until they cannot move further(blocked by the wall, other gems or a flyer). Then, if there are some gems touching some same-colored gem(touching means adjacent in one of the four directions), they disappear simultaneously. Note that the fans are still working, so some gems may go on moving in that direction after some gems disappeared. The fans stop working when all the gems cannot move any more, and none of them should disappear. There may be some flyers that can be moved by the fans, but they can NEVER disappear.

You are to write a program that finds the minimal number of operations to make all the gems disappear.

Input

The input file begins with an integer T, indicating the number of test cases. (1<=T<=50) Each test case begins with two integers N, M, indicating the height and width of the map. (1<=N<=12,1<=M<=20) In the following N lines, each line contains M characters describing the map. There is one line after each map, ignore them. Spaces denotes empty square, '#' denotes a wall, '1' denotes a red gem, '2' denotes a green gem, '3' denotes a blue gem, and '@' denotes a flyer. It's guaranteed that the four sides of the map are all walls. There is at least one gem in the map, and no two same-colored gems will touch each other at the beginning of the game.


Output

You should print a single line for each case. If there is a solution, write the shortest operation sequence in a string. The ith character must be from the set {'U','D','L','R'}, describing ith operation. The four characters represent UP, DOWM, LEFT, RIGHT respectively. If there are more than one solution, choose the lexicographical smallest one, if there are no solution, output -1 on the line. When a solution exists, you need only 18 or fewer steps to carry it out.


Sample Input
```
2
9 8
########
##   1##
##  2  #
#  1  ##
##2   ##
#   1@##
###   ##
#### ###
########

7 8
########
#212121#
#      #
# # # ##
# #    #
#     ##
########
```

Sample Output
```
LURD
DL
```
# 参考答案
```c++
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
typedef char State[13][21];
State map;
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
char dir_name[] = {'D', 'L', 'R', 'U'};
int N,M;

inline void swap(char &ch1, char &ch2){ char t=ch1; ch1=ch2; ch2=t; }

inline bool is_gem_fly(char ch){
    if(ch=='1'||ch=='2'||ch=='3'||ch=='@') return true;
    return false;
}

inline bool move(State &s, int dir){
    bool flag=false;
    if(dir==0){ // 下
        for(int i=1; i<M-1; ++i){
            for(int j=N-1; j>0; --j)if(s[j][i]==' '){
                int k = j-1;
                while(s[k][i]==' ') --k;
                if(is_gem_fly(s[k][i])){
                    swap(s[j][i], s[k][i]); flag=true;
                }
                else
                    j=k;
            }
        }
    }
    else if(dir==1){ // 左
        for(int i=1; i<N-1; ++i){
            for(int j=1; j<M-1; ++j)if(s[i][j]==' '){
                int k = j+1;
                while(s[i][k]==' ') ++k;
                if(is_gem_fly(s[i][k])){
                    swap(s[i][j], s[i][k]); flag=true;
                }
                else
                    j=k;
            }
        }
    }
    else if(dir==2){ // 右
        for(int i=1; i<N-1; ++i){
            for(int j=M-1; j>1; --j)if(s[i][j]==' '){
                int k = j-1;
                while(s[i][k]==' ') --k;
                if(is_gem_fly(s[i][k])){
                    swap(s[i][j], s[i][k]); flag=true;
                }
                else 
                    j=k;
            }
        }
    }
    else if(dir==3){ // 上
        for(int i=1; i<M-1; ++i){
            for(int j=1; j<N-1; ++j)if(s[j][i]==' '){
                int k = j+1;
                while(s[k][i]==' ')++k;
                if(is_gem_fly(s[k][i])){
                    swap(s[j][i], s[k][i]); flag=true;
                }
                else
                    j=k;
            }
        }
    }
    if(flag)return true;
    return false;
}

void dfs(State &s, char ch, int x, int y){ // 消除相同的宝石
    s[x][y] = ' ';
    for(int i=0; i<4; ++i){
        int dx=x+dir[i][0], dy=y+dir[i][1];
        if(s[dx][dy]==ch)
            dfs(s, ch, dx, dy);
    }
}

inline bool remove(State &s){
    bool ok=false;
    for(int i=1; i<N-1; ++i){
        for(int j=1; j<M-1; ++j)if(is_gem_fly(s[i][j]) && s[i][j]!='@'){
            bool flag=false;
            for(int k=0; k<4; ++k){
                int dx=i+dir[k][0], dy=j+dir[k][1];
                if(dx>=0 && dx<N && dy>=0 && dy<M && s[i][j]==s[dx][dy]){
                    flag=true; 
                    break;
                }
            }
            if(flag){
                ok = true; 
                dfs(s,s[i][j],i,j);
            }
        }
    }
    if(ok) return true;
    return false;
}

inline void run(State &s, int dir){  // 往哪个方向的步骤
    while(move(s, dir)){
        remove(s);
    }
}

const int MAXN = 100000;
const int HashSize = 1000003;
State que[MAXN];
int head[HashSize], next[MAXN], father[MAXN], step[MAXN], ans;
char path[MAXN];

inline void init_lookup_table(){ 
    ans = -1;
    father[0]=0; 
    step[0] = 0;
    memset(head, 0, sizeof(head)); 
    memset(que, 0, sizeof(que));
}
inline int hash(State &s){
    int seed=131, v=0;
    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j)
            v = (v*seed+s[i][j]) & 0x7FFFFFFF;
    }
    return v%HashSize;
}
bool try_to_insert(int s){
    int h = hash(que[s]);
    int u = head[h];
    while(u){
        if(memcmp(que[u], que[s], sizeof(que[s]))==0)return false;
        u = next[u];
    }
    next[s] = head[h];
    head[h] = s;
    return true;
}

inline bool is_ok(State &s){
    for(int i=1; i<N-1; ++i){
        for(int j=1; j<M-1; ++j)
            if(s[i][j]=='1'||s[i][j]=='2'||s[i][j]=='3')return false;
    }
    return true;
}

bool bfs(){
    init_lookup_table();
    int front=0, rear=1;
    memcpy(que[0], map, sizeof(map));
    try_to_insert(0);

    while(front < rear){
        State &s = que[front];
        if(step[front] > 18){
            ++front; continue;
        }
        if(is_ok(s)){
            ans = front;
            return true;
        }
        for(int i=0; i<4; ++i){
            State &t = que[rear];
            memcpy(t, s, sizeof(s));
            run(t, i);
            if(try_to_insert(rear)){
                step[rear] = step[front]+1;
                father[rear] = front;
                path[rear] = dir_name[i];
                ++rear;
            }
        }
        ++front;
    }
    return false;
}

void print_path(int cur){
    if(cur){
        print_path(father[cur]);
        printf("%c", path[cur]);
    }
}

int main(){
    int T;
    char str[1000];
    scanf("%d%*c",&T);
    while(T--){
        scanf("%d%d%*c",&N,&M);
        for(int i=0; i<N; ++i)
            gets(map[i]); 
        gets(str);
        if(!bfs())
            printf("-1\n");
        else{
            print_path(ans);
            printf("\n");
        }
    }
    return 0;
}

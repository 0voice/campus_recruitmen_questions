# 题目
Painting some colored segments on a line, some previously painted segments may be covered by some the subsequent ones.
Your task is counting the segments of different colors you can see at last.

Input

The first line of each data set contains exactly one integer n, 1 <= n <= 8000, equal to the number of colored segments.

Each of the following n lines consists of exactly 3 nonnegative integers separated by single spaces:

x1 x2 c

x1 and x2 indicate the left endpoint and right endpoint of the segment, c indicates the color of the segment.

All the numbers are in the range [0, 8000], and they are all integers.

Input may contain several data set, process to the end of file.


Output

Each line of the output should contain a color index that can be seen from the top, following the count of the segments of this color, they should be printed according to the color index.

If some color can't be seen, you shouldn't print it.

Print a blank line after every dataset.


Sample Input
```
5
0 4 4
0 3 1
3 4 2
0 2 2
0 2 3
4
0 1 1
3 4 1
1 3 2
1 3 1
6
0 1 0
1 2 1
2 3 1
1 2 0
2 3 0
1 2 1
```

Sample Output
```
1 1
2 1
3 1

1 1

0 2
1 1
```
# 参考答案
```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#define mem(str,x) memset(str,(x),sizeof(str))
#define FOR(i,s,t) for(int i=(s); i<(t); ++i)
#define FF(i,n) for(int i=0; i<(n); ++i)
#define mid ((left+right)>>1)
#define len (right-left+1)
#define lson rt<<1, left, m
#define rson rt<<1|1, m+1, right
#define STOP puts("Stop Here~");
using namespace std;
const int MAXN = 8005;
int n,col[MAXN<<2],vis[MAXN<<2],ans[MAXN<<2];

inline void push_down(int rt){
    if(col[rt] != -1){
        col[rt<<1] = col[rt<<1|1] = col[rt];
        col[rt] = -1;
    }
}
void update(int rt,int left,int right,int l,int r,int data){
    if(l<=left && right<=r){
        col[rt] = data;
        return;
    }
    if(col[rt] == data) return;
    if(col[rt]!=-1)push_down(rt);
    int m = mid;
    if(l <= m)update(lson,l,r,data);
    if(r > m)update(rson,l,r,data);
}
void query(int rt,int left,int right){
    if(col[rt]>=0){
        for(int i=left; i<=right; ++i)
            vis[i] = col[rt];
        return;
    }
    if(left!=right && col[rt] == -1){
        int m = mid;
        query(lson);
        query(rson);
    }
}

int main(){
    int a,b,c;
    while(~scanf("%d",&n)){
        memset(col,-1,sizeof(col));
        for(int i=0; i<n; ++i){
            scanf("%d%d%d",&a,&b,&c);
            if(a>=b)continue;
            update(1,1,8000,a+1,b,c);
        }

        mem(vis,-1); 
        query(1,1,8000);
        int i = 1;

        mem(ans,0);
        while(i<MAXN){
            int color=vis[i], j=i+1;
            if(color==-1){++i; continue;}
            while(vis[j]!=-1 && vis[j]==color && j<MAXN) ++j;
            ++ans[color];
            i=j;
        }
        for(int i=0; i<MAXN; ++i)if(ans[i])
            printf("%d %d\n",i,ans[i]);
        puts(""); 
    }
    return 0;
}



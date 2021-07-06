# 题目

Introduction

You've been a treasure hunter for a long time. You're pretty good at disarming traps, sneaking past the natives, and generally getting the goods while leaving your skin intact. That stuff doesn't really worry you, but what really raises a sweat is after each expedition there are always very tense arguments about how to split up the loot. You've worked with all kinds of characters and nobody ever agrees on what each piece of treasure is actually worth. You need to come up with a way of splitting the booty as fairly as possible.

Input

Input to this problem will consist of a (non-empty) series of up to 100 data sets. Each data set will be formatted according to the following description, and there will be no blank lines separating data sets.

A single data set has 5 components:

Start line - A single line, "START"

Number of Treasures - A single line with a single integer, t, where 1 <= t <= 8, indicating the number of treasures.

Number of Hunters - A single line with a single integer, h, where 1 <= h <= 6, indicating the number of treasure hunters.

Treasure Value List - A series of h lines, one for each hunter in sequence (line 1 for hunter 1, line 2 for hunter 2, etc.). Each line contains a space-separated list of estimated treasure values for that hunter. The first estimate on each line is for treasure 1, the second is for treasure 2, etc., and an estimate for each treasure will appear for every hunter. Each estimate will be a positive integer strictly less than 10000.

End line - A single line, "END"


Output

For each input data set, there will be exactly one output set, and there will be exactly one blank line separating output sets.

Each output set consists of multiple lines, where each line represents a hunter (listed in the same order as the corresponding input data set). Each line contains a list of the treasures given to that hunter followed by the total perceived cash value (by that hunter), of all the treasures they receive. Treasures will be listed in ascending order by treasure number, and all values on each line will be space-separated.

Treasures will be divided among the hunters in the fairest way possible. The "fairest" way to divide the treasure is defined to be the distribution with the minimum difference between the highest perceived total value and the lowest perceived total value of treasures received by any hunter. In other words, find the distribution that minimizes the difference between the hunter that gets the "most" and the hunter that gets the "least."

There will not be multiple "fair" distributions.


Sample Input
```
START
5
3
42 500 350 700 100
250 200 500 1000 75
150 400 800 800 150
END
START
5
3
42 500 350 200 100
250 200 500 1000 75
150 400 800 800 150
END
START
5
3
500 500 350 200 100
250 200 500 1000 75
150 400 800 800 150
END
```

Sample Output
```
4 700
3 5 575
1 2 550

1 4 5 342
3 500
2 400

1 2 1000
4 1000
3 5 950
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;

const int Max = 0x7fffffff;
struct Node{
    int val[ 10 ];
}a[ 10 ];
struct Node2{
    int num[ 10 ];
    int cnt ,sum ;
}ans[ 10 ],dfs_ans[ 10 ];
int vis[ 10 ];
int diff;
bool flag[ 10 ];

void init(){
    diff = Max;
    memset( flag,false,sizeof( flag ) );
    for( int i=0;i<10;i++ ){
        for( int j=0;j<10;j++ ){
            ans[ i ].num[ j ] = dfs_ans[ i ].num[ j ] = 0;
        }
        ans[ i ].cnt = ans[ i ].sum = dfs_ans[ i ].cnt = dfs_ans[ i ].sum = 0;
    }
}

void init_vis( int n ){
    int N = (1<<n);
    for( int i=0;i<N;i++ ){
        for( int j=0;j<n;j++ ){
            if( i&(1<<j) ) vis[ j ] = 0;
            else vis[ j ] = 1;
        }
    }
}

void dfs( int cur_hunter,int cur_treasure,int num_treasure,int hunter ){
    if( cur_hunter==hunter&&cur_treasure==num_treasure ){
        int t_max = dfs_ans[0].sum;
        int t_min = dfs_ans[0].sum;
        for( int i=1;i<hunter;i++ ){
            t_max = max( t_max,dfs_ans[i].sum );
            t_min = min( t_min,dfs_ans[i].sum );
        }
        if( t_max-t_min<diff ){
            diff = t_max-t_min;
            for( int i=0;i<hunter;i++ )
                ans[i] = dfs_ans[i];
        }
        return ;
    }
    if( cur_hunter>=hunter ) return ;
    int N = (1<<num_treasure);
    for( int i=0;i<N;i++ ){
        int t_cnt = 0;
        bool p_flag = true;
        for( int j=0;j<num_treasure;j++ ){
            if( i&(1<<j) ) vis[ j ] = 0;
            else {
                vis[ j ] = 1;
                t_cnt++;
                if( flag[j]==true ) {
                    p_flag = false;
                    break;
                }
            }
        }
        if( p_flag==true&&( t_cnt+cur_treasure+hunter-cur_hunter-1 )<=num_treasure ){
            int tt = 0;
            dfs_ans[ cur_hunter ].sum = 0;
            dfs_ans[ cur_hunter ].cnt = t_cnt;
            for( int j=0;j<num_treasure;j++ ){
                if( vis[j] == 1 ){
                    dfs_ans[ cur_hunter ].num[ tt++ ] = j;
                    flag[ j ] = true;
                    dfs_ans[ cur_hunter ].sum += a[ cur_hunter ].val[j];
                }
            }
            dfs( cur_hunter+1,cur_treasure+t_cnt,num_treasure,hunter);
            for( int j=0;j<tt;j++ ){
                flag[ dfs_ans[ cur_hunter ].num[j] ] = false;
            }
        }
    }
    return ;
}

int main(){
    int num_treasure,hunter;
    char s[ 12 ];
    int ca = 1;
    while( scanf("%s",s)!=EOF ){
        init();
        scanf("%d%d",&num_treasure,&hunter);
        for( int i=0;i<hunter;i++ ){
            for( int j=0;j<num_treasure;j++ ){
                scanf("%d",&a[i].val[j]);
            }
        }
        scanf("%s",s);
        if( num_treasure==1 ){
            int m_min = a[0].val[0];
            int m_num = 0;
            for( int i=1;i<hunter;i++ ){
                if( m_min>a[i].val[0] ){
                    m_min = a[ i ].val[0];
                    m_num = i;
                }
            }
            if( ca!=1 ) printf("\n");
            ca++;
            for( int i=0;i<hunter;i++ ){
                if( i==m_num ){
                    printf("1 %d\n",m_min);
                }
                else
                    printf("0\n");
            }
            continue;
        }
        dfs( 0,0,num_treasure,hunter );
        if( ca!=1 ) printf("\n");
        ca++;
        for( int i=0;i<hunter;i++ ){
            for( int j=0;j<ans[i].cnt;j++ ){
                if( j==0 )
                    printf("%d",ans[i].num[j]+1);
                else 
                    printf(" %d",ans[i].num[j]+1);
            }
            if( ans[i].cnt>0 ) printf(" %d\n",ans[i].sum);
            else printf("%d\n",ans[i].sum);
        }
    }
    return 0;
}

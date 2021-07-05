# 题目
The Happy Worm lives in an m*n rectangular field. There are k stones placed in certain locations of the field. (Each square of the field is either empty, or contains a stone.) Whenever the worm sleeps, it lies either horizontally or vertically, and stretches so that its length increases as much as possible. The worm will not go in a square with a stone or out of the field. The happy worm can not be shorter than 2 squares.

The question you are to answer is how many different positions this worm could be in while sleeping.

Input Specification

The first line of the input file contains a single integer t (1 <= t <= 11), the number of test cases, followed by the input data for each test case. The first line of each test case contains three integers m, n, and k (0 <= m,n,k <= 200000). The input for this test case will be followed by k lines. Each line contains two integers which specify the row and column of a stone. No stone will be given twice.

Output Specification

There should be one line per test case containing the number of positions the happy worm can be in.

Sample Input
```
1
5 5 6
1 5
2 3
2 4
4 2
4 3
5 1
```
Sample Output
```
9
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int T,n,m,k,x[1000005],y[1000005],b[1000005];
int dealrow(){
    int cnt=0,Trow=0;
    int mark[1000005];
    int ans=0;
    memset(mark,0,sizeof(mark));
    for(int i=0;i<k;i++){
        if(mark[x[i]]==1) continue;
        mark[x[i]]=1;
        Trow++;
        cnt=0;
        b[cnt++]=y[i];
        for(int j=i+1;j<k;j++){
            if(x[j]==x[i]){
                b[cnt++]=y[j];    
            }
        }
        sort(b,b+cnt);
        for(int j=0;j<cnt-1;j++){
            if(b[j+1]-b[j]>2) {ans++;}
        }
        if(b[0]>2) {ans++;}
        if(b[cnt-1]<=n-2&&n>=3){ans++;}
    }
    if(n>=2) ans+=(m-Trow);
    return ans;
}

int dealcolumn(){
    int cnt=0,Tcolumn=0;
    int mark[1000005];
    int ans=0;
    memset(mark,0,sizeof(mark));
    for(int i=0;i<k;i++){
        if(mark[y[i]]==1) continue;
        Tcolumn++;
        cnt=0;
        b[cnt++]=x[i];
        mark[y[i]]=1;
        for(int j=i+1;j<k;j++){
            if(y[j]==y[i]){
                b[cnt++]=x[j];
            }
        }
        sort(b,b+cnt);
        for(int j=0;j<cnt-1;j++){
            if(b[j+1]-b[j]>2) ans++;
        }
        if(b[0]>2) {ans++;}
        if(b[cnt-1]<=m-2&&m>=3) {ans++;}
    }
    if(m>=2) ans+=(n-Tcolumn);
    return ans;
}

int main(){
    while(~scanf("%d",&T)){
        while(T--){
            scanf("%d %d %d",&m,&n,&k);
            for(int i=0;i<k;i++){
                scanf("%d %d",&x[i],&y[i]);
            }
            int Tans=0;
            Tans+=dealrow();
            Tans+=dealcolumn();
            printf("%d\n",Tans);
        }
    }
return 0;
}




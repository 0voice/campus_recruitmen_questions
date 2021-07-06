# 题目

Alice has invented an Auto-Calculation Machine (ACM) that operates on very large integer arrays. The machine is so simple that only one operation of the format sum(i, j) can be performed on it. An operation sum(i, j) means to calculate the sum of all integers between the i-th and j-th ones (inclusive) in the array. Despite its simplicity, the machine is not carefully designed. From time to time, it makes mistakes.

Alice has recorded a list of operations on a certain integer array of the ACM. Your task is to check whether it has made any mistakes not given any information about the array. For any record in the list, it is considered mistaken if it conflicts with the former ones, otherwise it is all right.

输入描述

The input consists of multiple lines. The first line contains a single positive integer M ≤ 10,000 indicating the number of records in the list. Each of the next M lines contain a record i j v (1 ≤ i, j ≤ 10<sup>9</sup>, −20,000 ≤ v ≤ 20,000) in the list meaning that the result of an operation sum(i, j) is v.

输出描述

Output one line for each record in the list. If the operation referred to by the record is all right, output a single word “Accept”; otherwise output the phrase “Bug Detected” followed by and separated from by a single space the correct result of the operation.

输入例子
```
6
1 2 1
1 2 2
5 6 3
1 6 7
3 4 50
7 10 10
```
输出例子
```
Accept
Bug Detected 1
Accept
Accept
Bug Detected 3
Accept
```
# 参考答案
```c++
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<climits>
#include<cmath>
#include<queue>
#include<vector>
#include<stack>
#include<set>
#include<map>
#define INF 0x3f3f3f3f
#define eps 1e-8
using namespace std;

const int MAXN=110000;
int a[MAXN],b[MAXN],p[MAXN];
long long c[MAXN],d[MAXN];
vector<int> hash;

long long findp(int x) {
    if(p[x]==-1) {
        return x;
    }
    int ret=findp(p[x]);
    d[x]+=d[p[x]];
    return p[x]=ret;
}

int main() {
    int m;
    while(scanf("%d",&m)==1) {
        hash.clear();
        memset(p,-1,sizeof(p));
        memset(d,0,sizeof(d));
        for(int i=0; i<m; i++) {
            scanf("%d%d%lld",&a[i],&b[i],&c[i]);
            if(a[i]>b[i]) {
                swap(a[i],b[i]);
            }
            hash.push_back(a[i]-1);
            hash.push_back(b[i]);
        }
        sort(hash.begin(),hash.end());
        hash.erase(unique(hash.begin(),hash.end()),hash.end());
        for(int i=0; i<m; i++) {
            a[i]=lower_bound(hash.begin(),hash.end(),a[i]-1)-hash.begin();
            b[i]=lower_bound(hash.begin(),hash.end(),b[i])-hash.begin();
            int px=findp(a[i]);
            int py=findp(b[i]);
            if(px==py) {
                if(d[b[i]]-d[a[i]]==c[i]) {
                    puts("Accept");
                } else {
                    printf("Bug Detected %lld\n",d[b[i]]-d[a[i]]);
                }
            } else {
                if(px>py) {
                    swap(a[i],b[i]);
                    swap(px,py);
                    c[i]=-c[i];
                }
                d[py]=d[a[i]]+c[i]-d[b[i]];
                p[py]=px;
                puts("Accept");
            }
        }
    }
    return 0;
}

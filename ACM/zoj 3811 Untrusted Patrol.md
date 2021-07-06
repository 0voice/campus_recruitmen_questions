# 题目
Edward is a rich man. He owns a large factory for health drink production. As a matter of course, there is a large warehouse in the factory.

To ensure the safety of drinks, Edward hired a security man to patrol the warehouse. The warehouse has <var>N</var> piles of drinks and <var>M</var> passageways connected them (warehouse is not big enough). When the evening comes, the security man will start to patrol the warehouse following a path to check all piles of drinks.

Unfortunately, Edward is a suspicious man, so he sets sensors on <var>K</var> piles of the drinks. When the security man comes to check the drinks, the sensor will record a message. Because of the memory limit, the sensors can only record for the first time of the security man's visit.

After a peaceful evening, Edward gathered all messages ordered by recording time. He wants to know whether is possible that the security man has checked all piles of drinks. Can you help him?

The security man may start to patrol at any piles of drinks. It is guaranteed that the sensors work properly. However, Edward thinks the security man may not works as expected. For example, he may digs through walls, climb over piles, use some black magic to teleport to anywhere and so on.

Input
There are multiple test cases. The first line of input is an integer <var>T</var> indicates the number of test cases. For each test case:

The first line contains three integers <var>N</var> (1 <= <var>N</var> <= 100000), <var>M</var> (1 <= <var>M</var> <= 200000) and <var>K</var> (1 <= <var>K</var> <= <var>N</var>).

The next line contains <var>K</var> distinct integers indicating the indexes of piles (1-based) that have sensors installed. The following <var>M</var> lines, each line contains two integers <var>Ai</var> and <var>Bi</var> (1 <= <var>Ai</var>, <var>Bi</var> <= <var>N</var>) which indicates a bidirectional passageway connects piles <var>Ai</var> and <var>Bi</var>.

Then, there is an integer <var>L</var> (1 <= <var>L</var> <= <var>K</var>) indicating the number of messages gathered from all sensors. The next line contains <var>L</var> distinct integers. These are the indexes of piles where the messages came from (each is among the <var>K</var> integers above), ordered by recording time.

Output
For each test case, output "Yes" if the security man worked normally and has checked all piles of drinks, or "No" if not.

Sample Input
```
2
5 5 3
1 2 4
1 2
2 3
3 1
1 4
4 5
3
4 2 1
5 5 3
1 2 4
1 2
2 3
3 1
1 4
4 5
3
4 1 2
```
Sample Output
```
No
Yes
```
# 参考答案
```c++
  #include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<cstdlib>

#define mt(a,b) memset(a,b,sizeof(a))
#define LL long long
using namespace std;

const int M = 200020;

struct G {
    struct E {
        int u,v,next;
    } e[M*2];
    int head[M],le;

    void init() {
        le = 0;
        mt(head,-1);
    }

    void add(int u,int v) {
        e[le].u = u;
        e[le].v = v;
        e[le].next = head[u];
        head[u] = le++;
    }
} g;

class UnionFindSet { 
    int par[M];
public:
    void init() {
        mt(par,-1);
    }
    int getroot(int x) {
        int i=x,j=x,temp;
        while(par[i]>=0) i=par[i];
        while(j!=i) {
            temp=par[j];
            par[j]=i;
            j=temp;
        }
        return i;
    }
    bool unite(int x,int y) {
        int p=getroot(x);
        int q=getroot(y);
        if(p==q)return false;
        if(par[p]>par[q]) {
            par[q]+=par[p];
            par[p]=q;
        } else {
            par[p]+=par[q];
            par[q]=p;
        }
        return true;
    }
} ts;

bool mark[100020];
int viwer[100020];

int main() {
    int _;
    scanf("%d",&_);
    int n,m,k,l;
    while(_--) {
        scanf("%d%d%d",&n,&m,&k);
        mt(mark,false);
        int tmp;
        for(int i=0; i<k; i++) {
            scanf("%d",&tmp);
            mark[tmp] = true;
        }

        g.init();
        for(int i=0; i<m; i++) {
            int u,v;
            scanf("%d%d",&u,&v);
            g.add(u,v);
            g.add(v,u);
        }

        scanf("%d",&l);
        for(int i=0;i<l;i++){
            scanf("%d",&viwer[i]);
        }

        if(k!=l) {
            puts("No");
            continue;
        }

        ts.init();
        for(int x=1; x<=n; x++) {
            if(!mark[x]) {
                for(int i=g.head[x]; ~i; i=g.e[i].next) {
                    int u = g.e[i].u;
                    int v = g.e[i].v;
                    ts.unite(u,v);
                }
            }
        }

        bool ans = true;
        for(int x=0; x<k; x++) {
            int u = viwer[x];
            mark[u] = false;
            for(int i=g.head[u]; ~i; i=g.e[i].next) {
                int v = g.e[i].v;
                if(!mark[v]) ts.unite(u,v);
            }
            if(x>0){
                if(ts.getroot(viwer[x-1]) != ts.getroot(u)){
                    ans = false;
                    break;
                }
            }
        }

        if(ans){
            int num = 0;
            for(int i=1;i<=n;i++){
                if(ts.getroot(i)==i) num++;
            }
            if(num>1){
                ans = false;
            }
        }

        if(ans) puts("Yes");
        else    puts("No");

    }

    return 0;
}

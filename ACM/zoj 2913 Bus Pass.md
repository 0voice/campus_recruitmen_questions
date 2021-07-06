# 题目
You travel a lot by bus and the costs of all the seperate tickets are starting to add up.

Therefore you want to see if it might be advantageous for you to buy a bus pass.

The way the bus system works in your country (and also in the Netherlands) is as follows:

when you buy a bus pass, you have to indicate a center zone and a star value. You are allowed to travel freely in any zone which has a distance to your center zone which is less than your star value. For example, if you have a star value of one, you can only travel in your center zone. If you have a star value of two, you can also travel in all adjacent zones, et cetera.

You have a list of all bus trips you frequently make, and would like to determine the minimum star value you need to make all these trips using your buss pass. But this is not always an easy task. For example look at the following figure:

![image](https://user-images.githubusercontent.com/59190045/124562223-5b568680-de71-11eb-8ac0-7f09a9e7bd09.png)

 Here you want to be able to travel from A to B and from B to D. The best center zone is 7400, for which you only need a star value of 4. Note that you do not even visit this zone on your trips!
 
 Input

On the first line an integert(1 <=t<= 100): the number of test cases. Then for each test case:

One line with two integersnz(2 <=nz<= 9 999) andnr(1 <=nr<= 10): the number of zones and the number of bus trips, respectively.

nz lines starting with two integers id<sub>i</sub> (1 <= id<sub>i</sub> <= 9 999) and mzi (1 <= mz<sub>i</sub> <= 10), a number identifying the i-th zone and the number of zones adjacent to it, followed by mz<sub>i</sub> integers: the numbers of the adjacent zones.

nr lines starting with one integer mr<sub>i</sub> (1 <= mr<sub>i</sub> <= 20), indicating the number of zones the ith bus trip visits, followed by mr<sub>i</sub> integers: the numbers of the zones through which the bus passes in the order in which they are visited.

All zones are connected, either directly or via other zones.

Output

For each test case:

One line with two integers, the minimum star value and the id of a center zone which achieves this minimum star value. If there are multiple possibilities, choose the zone with the lowest number.

Sample Input
```
1
17 2
7400 6 7401 7402 7403 7404 7405 7406
7401 6 7412 7402 7400 7406 7410 7411
7402 5 7412 7403 7400 7401 7411
7403 6 7413 7414 7404 7400 7402 7412
7404 5 7403 7414 7415 7405 7400
7405 6 7404 7415 7407 7408 7406 7400
7406 7 7400 7405 7407 7408 7409 7410 7401
7407 4 7408 7406 7405 7415
7408 4 7409 7406 7405 7407
7409 3 7410 7406 7408
7410 4 7411 7401 7406 7409
7411 5 7416 7412 7402 7401 7410
7412 6 7416 7411 7401 7402 7403 7413
7413 3 7412 7403 7414
7414 3 7413 7403 7404
7415 3 7404 7405 7407
7416 2 7411 7412
5 7409 7408 7407 7405 7415
6 7415 7404 7414 7413 7412 7416
```
Sample Output
```
4 7400
```
# 参考答案
```c++
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <queue>
#define rep(i,n) for(int i=0;i<n;i++)
#define F first
#define S second
#define mp make_pair
#define LL long long
#define pb push_back
#define inf 0x3fffffff
using namespace std;

int T;
int n,m;
vector <int> p[10005];
vector <int> pas;
int dis[10005],vis[10005],ma[10005];

queue <int> q;
void bfs(int st)
{
 while(!q.empty())q.pop();
 memset(vis,0,sizeof(vis));
 rep(i,10005)dis[i]=inf;
 dis[st] = 0;
 vis[st] = 1;
 q.push(st);
 while(!q.empty())
 {
 int st = q.front();
 q.pop();
 for(int i=0;i<p[st].size();i++)
 {
 int en = p[st][i];
 if(!vis[en])
 {
 dis[en] = dis[st] + 1;
 vis[en] = 1;
 q.push(en);
 }
 }
 }
}
int main()
{
 scanf("%d",&T);
 while(T--)
 {
 scanf("%d%d",&n,&m);
 rep(i,10005)p[i].clear();
 int st,en,num;
 rep(i,n)
 {
 scanf("%d%d",&st,&num);
 rep(j,num)
 {
 scanf("%d",&en);
 p[st].pb(en);
 }
 }
 pas.clear();
 rep(i,m)
 {
 scanf("%d",&num);
 rep(j,num)
 {
 scanf("%d",&st);
 pas.pb(st);
 }
 }
 rep(i,10005)ma[i] = 0;
 rep(i,pas.size())
 {
 bfs(pas[i]);
 rep(j,10005)
 ma[j] = max(ma[j],dis[j]);
 }
 int ret = inf , id = -1;
 rep(i,10005)
 {
 if(ma[i]<ret)
 {
 ret = ma[i];
 id = i;
 }
 }
 printf("%d %d\n",ret+1,id);
 }
}

# 题目
Bounty hunter is a hero who always moves along cities to earn money by his power. One day he decides to <var>N</var> cities one by one

At the beginning ,Bounty hunter has <var>X</var> money and <var>Y</var> points of Attack force. At day 1, he will goes to city 1, then city 2 at day 2, city 3 at day 3, ... At last ,he goes to city <var>N</var> at day <var>N</var> and leaves it at day <var>N+1</var>. In each city, he can increase his attack force by money and earn some money by accepting a task. In the city <var>i</var>, it costs him <var>ai</var> money to increase one point of attack force. And he can gets <var>bi</var>*<var>yi</var> money after finishing the task in city <var>i</var> while <var>yi</var> is his attack force after his increasing at city <var>i</var>.

As it's known to all that money is the life of Bounty hunter, he wants to own as much money as he can after leaving city <var>N</var>. Please find out the maximal moeny he can get.

PS1: when Bounty hunter leaves a city he won't come back.

PS2: Bounty hunter can increases his attack force by any real numbers he wants, if the money is enough. For example, if he has 7 money and the unit price of attack force at the city he stays now is 2, he can spend 3 money to increase attack force by 1.5.

PS3: After Bounty hunter finishes the task he will leave the city at once. It means he can and only can increase his attack force before he finishes the task and gets the money at the same city.

Input

The first line of the input is three integers <var>N</var>,<var>X</var>,<var>Y</var>, (0≤<var>N</var>,<var>X</var>,<var>Y</var>≤100000) following is <var>N</var> lines. In the <var>i</var>-th line has two real number <var>ai</var> and <var>bi</var>.(0≤<var>bi</var>≤1,0ai≤100000)

Output

Output the maximal money he can get.Two decimal places reserved. We promise that the answer is less than 1e15

Sample Input
```
1 10 0
1.0 1.0

3 13 5
7.0 1.0
1.1 0.6
1.0 0.6
```
Sample Output
```
10.00
25.64
```
# 参考答案
```c++
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;
#define inf 2147480000
struct hammer
{
 double val;
 double cost;
}map[100010];
double final[100010][2];
int n;
double x,y;
int main(int argc, char *argv[])
{
 while(scanf("%d",&n)!=EOF)
 {
 cin>>x>>y;
 for(int i=1;i<=n;i++)
 cin>>map[i].cost>>map[i].val;
 final[n][0]=map[n].val;
 final[n][1]=max(1.0,map[n].val/map[n].cost);
 for(int i=n-1;i>=1;i--)
 {
 final[i][0]=final[i+1][0]+map[i].val*final[i+1][1];
 final[i][1]=max(final[i+1][1],final[i][0]/map[i].cost);
 }
 double ans=x*final[1][1]+y*final[1][0];
 printf("%.2lf\n",ans);
 }
 return 0;
}




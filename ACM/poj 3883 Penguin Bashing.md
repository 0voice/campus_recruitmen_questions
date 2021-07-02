# 题目
In a well-known online game you play a yeti whose goal it is to hit a cute and cuddly penguin in such a way that it flies as far as possible. The game is set in sunny Antarctica, where the ground is littered with obstacles left by human and robotic expeditions. The most dangerous obstacles are sharp, pointy, metal objects, known as spikes. These spikes are most definitely not safe for penguins and children under three years of age.
Besides the occasional expedition, there have also been many wars in Antarctica. The result is that besides spikes, penguins (and yetis), one is also likely to encounter mines on the Antarctic surface. While they are not good for the health of a penguin, the explosions do improve the distance he will travel.
The best way to get a high score in this game is by guring out the optimal strategy in advance. To be able to do this you need to know the following facts:

The yeti always bats at an integral angle between -90 and +90 degrees, -90° is straight down, 0° is to the right and +90° is straight up.<br>
The penguin gets a total velocity of 25m/s regardless of the angle.<br>
The yeti hits the 3kg penguin at exactly one meter above the ground.<br>
Upon hitting the ground the penguin will slide along the ground, while undergoing friction. This will slow it down by 5m/s for every meter traveled.<br>
Upon hitting a mine the penguin will be flung 2m forward through the air, and also undergo an instant increase in velocity of 4m/s forward.<br>
If the penguin hits a spike, the game ends immediately with a score of -100. Otherwise the score will be the horizontal distance traveled in centimeters, rounded to the nearest integer.
Standard Earth gravity (9.81m/s2) is used and drag is ignored.<br>
输入描述
On the first line of the input is a positive integer, the number of test cases. Then for each test case:<br>
A line with a single integer n 5, the number of obstacles.<br>
n lines, each containing:<br>
- A single floating point number xi, the position of the obstacle in meters from the start.<br>
- A string describing the obstacle, either "mine" or "spike".<br>
输出描述<br>
For each test case:<br>
One line containing two integers, the highest possible score, and the angle in degrees at which the yeti needs to hit the penguin to achieve that score. In case of a tie output the lowest angle.

输入例子
```
3
0
1
64.7 spike
2
63.9 mine
64.7 spike
```
输出例子
```
6829 44
6466 34
7022 39
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <numeric>
#include <sstream>
#include <string>
using namespace std;
#define out(X) cerr << #X << ": " << (X) << endl
#define SZ(X) ((int)(X.size()))
#define LENGTH(X) ((int)(X.length()))
#define REP(I,N) for (int I = 0; I < (N); ++I)
#define FOR(I,L,H) for (int I = (L); I < (H); ++I)
#define MP(X,Y) make_pair((X),(Y))
#define PB push_back
#define ALL(X) X.begin(), X.end()
template <typename T> inline bool checkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template <typename T> inline bool checkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
typedef long long lint;

const int MAXN = 100000 + 100;
const int MAXINT = -1u >> 1;
const double PI = acos(-1.0);
const double g = 9.81;
const double a = 5.00;
const double vbegin = 25.00;
const double EPS = 1e-6;

int sgn(const double &x) {return (int)((x > EPS) - (x < -EPS));}

struct Node {
 double dis;
 bool mine;
 void input() {
 char buff[10];
 scanf("%lf %s",&dis,buff);
 mine = (buff[0] == 'm' ? true : false);
 }
 bool operator < (const Node &A) const {
 return sgn(dis - A.dis) == -1;
 }
}e[MAXN];

bool stop(const double &y,const double &vx,const double &vy) {
 if (sgn(y) == 0 && sgn(vx) == 0 && sgn(vy) == 0) {
 return true;
 }
 return false;
}

lint getScore(const int &tmp,const int &N) {
 int cntE = 0;
 double ang = tmp;
 ang = ang / 180.0 * PI;
 double y = 1.0,x = 0.0;
 double vy = sin(ang) * vbegin;
 double vx = cos(ang) * vbegin;
 double S,t,Smax;
 while(!stop(y,vx,vy)) {
 if (sgn(y) > 0) {
 S = y;
 t = (vy + sqrt(vy * vy + 2.0 * S * g)) / g;
 y = 0.0;
 x += vx * t;
 vy = 0.0;
 }
 while(cntE < N && sgn(e[cntE].dis - x) < 0) {
 cntE++;
 }
 S = e[cntE].dis - x;
 Smax = vx / a;
 if (sgn(Smax - S) >= 0) {
 vx -= S * a;
 x += S;
 if (e[cntE].mine) {
 vx += 4.0;
 x += 2.0;
 }
 else return -100;
 }
 else {
 vx = 0.0;
 x += Smax;
 }
 }
 return lint(x * 100 + 0.5);
}

int main() {
 int T,N;
 scanf("%d",&T);
 while(scanf("%d",&N) == 1) {
 for(int i = 0 ; i < N ; i++) {
 e[i].input();
 }
 e[N].dis = 1e100;
 e[N].mine = false;
 N++;
 sort(e , e + N);
 lint res = -100,optAng = -90;
 for(int ang = -90 ; ang < 90 + 1 ; ang++) {
 lint tmp;
 tmp = getScore(ang,N);
 if (tmp > res) {
 res = tmp;
 optAng = ang;
 }
 }
 cout << res << ' ' << optAng << endl;
 }
 return 0;
}




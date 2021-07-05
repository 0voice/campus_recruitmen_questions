# 题目
One of the traps we will encounter in the Pyramid is located in the Large Room. A lot of small holes are drilled into the floor. They look completely harmless at the first sight. But when activated, they start to throw out very hot java, uh ... pardon, lava. Unfortunately, all known paths to the Center Room (where the Sarcophagus is) contain a trigger that activates the trap. The ACM were not able to avoid that. But they have carefully monitored the positions of all the holes. So it is important to find the place in the Large Room that has the maximal distance from all the holes. This place is the safest in the entire room and the archaeologist has to hide there.

Input

The input consists of T test cases. The number of them (T) is given on the first line of the input file. Each test case begins with a line containing three integers X, Y, M separated by space. The numbers satisfy conditions: 1 <= X,Y <=10000, 1 <= M <= 1000. The numbers X and Yindicate the dimensions of the Large Room which has a rectangular shape. The number M stands for the number of holes. Then exactly M lines follow, each containing two integer numbers Ui and Vi (0 <= Ui <= X, 0 <= Vi <= Y) indicating the coordinates of one hole. There may be several holes at the same position.


Output

Print exactly one line for each test case. The line should contain the sentence "The safest point is (P, Q)." where P and Qare the coordinates of the point in the room that has the maximum distance from the nearest hole, rounded to the nearest number with exactly one digit after the decimal point (0.05 rounds up to 0.1).


Sample Input
```
3
1000 50 1
10 10
100 100 4
10 10
10 90
90 10
90 90
3000 3000 4
1200 85
63 2500
2700 2650
2990 100
```

Sample Output
```
The safest point is (1000.0, 50.0).
The safest point is (50.0, 50.0).
The safest point is (1433.0, 1669.8).
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <set>
#include<map>
#include<ctime>
using namespace std;
const int NUM=20;
const int RAD=1000;
struct point
{
	double x,y,val;
	point(){}
	point(double _x,double _y):x(_x),y(_y){}
}p[10001],May[NUM],e1,e2;
int n;
double X,Y;
double dis(point a,point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double judge(point t)
{
	double len;
	len=1LL<<45;
	for(int i=0;i<n;i++)
	len=min(len,dis(t,p[i]));
	return len;
}
double Rand(){return rand()%(RAD+1)/(1.0*RAD);}
point Rand_point(point a,point b)
{
	double xx=a.x+(b.x-a.x)*Rand();
	double  yy=a.y+(b.y-a.y)*Rand();
	point tmp=point(xx,yy);
	tmp.val=judge(tmp);
	return tmp;
}
void solve(double D)
{
	May[0]=point(0,0);
	May[1]=point(X,Y);
	May[2]=point(0,Y);
	May[3]=point(X,0);
	for(int i=4;i<NUM;i++)
	May[i]=Rand_point(May[0],May[1]);
	while(D>0.01)
	{
		for(int i=0;i<NUM;i++)
		for(int j=0;j<NUM;j++)
		{
			point tmp=Rand_point(point(max(0.0,May[i].x-D),max(0.0,May[i].y-D)),point(min(X,May[i].x+D),min(Y,May[i].y+D)));
			if(tmp.val>May[i].val)
			{
				May[i]=tmp;
			}
		}
		D*=0.9;
	}
	point ans;
	ans.val=0;
	for(int i=0;i<NUM;i++)
	if(May[i].val>ans.val)
	ans=May[i];
	printf("The safest point is (%.1f, %.1f).\n",ans.x,ans.y);
}
int main()
{
	srand(time(0));
	e2=point(0,0);
	int Case;
	scanf("%d",&Case);
	while(Case--)
	{
		scanf("%lf%lf%d",&X,&Y,&n);
		for(int i=0;i<n;i++)
		{
		scanf("%lf%lf",&p[i].x,&p[i].y);
		}
		solve(max(Y,X));
	}
}




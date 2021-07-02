# 题目
A multiple-geared bicycle typically has a gear in the front with two or three cogs, and a set of gears in the back, with five to nine cogs. In this problem, we will assume three cogs in the front and nine cogs in the back. The cyclist chooses a cog in the back and one in the front. The ratio (number of front teeth)/(number of back teeth) gives the relative diffculty for the gears. (The larger the ratio, the bigger the gear.) The gear setup is usually given in the form of a ratio. For example 42/21 indicates a 42-tooth cog in the front and a 21-tooth cog in the rear. How diffcult it is to turn that gear also depends on the size of the rear wheel. When the ratio is multiplied by the rear wheel circumference, we get a measure of the size of the gear on that particular bike.

For example, a 27-inch diameter wheel has a circumference of 84.82293 inches (if we use the approximation of 3.14159 for PI). A cyclist using a 52/15 setup would be riding a (52/15) * 84.82293 = 294.052824 inch gear. You'll be given the set of cogs on a bicycle and the diameter of the rear wheel. You'll also be given a target gear size and must then find the closest setup to that target.

Input

There will be multiple problem instances. The first line is a positive integer n indicating the number of problem instances to follow. Each of the next n lines will contain input for one problem instance. This line will consist of 14 positive integers in the form:

f1 f2 f3 r1 ... r9 diameter target

where f1 < f2 < f3 are the three front cogs and r1 < r2 < .. < r9 are the nine rear cogs, diameter is the diameter of the wheel and target is the target gear size.


Output

You should generate one line of output for each problem instance. This line should be of the form:

A gear selection of ff/rr produces a gear size of size.

where size is the closest computed gear size, rounded and displayed to three places, and ff/rr is the front cog/rear cog setup used for that gear size. (Use the approximation PI = 3.14159 in your calculations.) If there is a tie for the closest size, use the one that uses the smallest front cog.

Separate outputs for problem instances with a blank line.

Sample Input
```
3
32 42 52 12 13 14 15 16 17 21 24 27 27 294
30 40 50 15 16 17 18 19 21 23 27 29 26 141
28 39 48 15 17 18 19 21 24 25 27 31 24 259
```

Sample Output
```
A gear selection of 52/15 produces a gear size of 294.053.

A gear selection of 50/29 produces a gear size of 140.830.

A gear selection of 48/15 produces a gear size of 241.274.
```
# 参考答案
```c++
#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

#define PI 3.14159
float f[4],r[10];

int main()
{
 int n,j,k;
 float res,target,dia,ma,mb,mc;
 scanf("%d",&n);
 for(int i=0;i<n;i++)
 {
  for(j=0;j<3;j++)scanf("%f",&f[j]);
  for(j=0;j<9;j++)scanf("%f",&r[j]);
  scanf("%f %f",&dia,&target);
  double sub,min=10000.0;
  for(j=0;j<3;j++)
   for(k=0;k<9;k++)
   {
    res=(f[j]/r[k])*PI*dia;
    sub=fabs(double(target-res));
    if(sub<min){min=sub;ma=f[j];mb=r[k];mc=res;}
   }
  printf("A gear selection of %.0f/%.0f produces a gear size of %.3f.\n",ma,mb,mc);
  if(i!=n-1)printf("\n");
 }
 return 0;
}




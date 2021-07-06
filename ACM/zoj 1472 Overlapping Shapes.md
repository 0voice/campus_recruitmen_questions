# 题目
There are problems easy to human brain, but hard to computers. For example, a man can tell whether two shapes overlap by a single glimpse, but a computer will have to check this and that before giving a correct answer.

In this problem, you are asked to write a program that checks whether two shapes overlap. Two shapes are said to overlap if and only if the two shapes touch on at least one point. Notice that the case in which one shape lies completely inside the other shape is NOT considered as "overlap". For simplicity, only two special kinds of shapes are taken into account: circle and rectangle.


Input

The first line of input contains an integer n which is the number of tests. Each test consists of two lines, specifying the characteristics of the two shapes. A shape specification begins with a string which is either "circle" or "rectangle". If it is a circle, then three integers follow: r, x, and y where x and y are the coordinates of the center of the circle and r is the radius. Otherwise four integers follow: x1, y1, x2, and y2, specifying the coordinates of the top-left corner and the right-bottom corner. All the coordinates will be within the range [-50000, 50000], and 0 < r < 50000.


Output

For each test, if the two shapes overlap, print "yes" in a single line; otherwise print "no".


Sample Input
```
3
circle 1 0 0
circle 2 0 0
rectangle 0 10 10 0
rectangle 0 20 20 0
circle 10 0 0
rectangle 100 200 200 100
```

Sample Output
```
no
yes
no
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#include<math.h>
#define eps 1e-8
struct point{
	double x,y;
};
struct tr{
	point a,b,c,d;
}u,v;
struct circle{
	point o;
	double r;
}cu,cv;
double chaji(point a,point b,point c){
	return (c.x-a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x);
}
int dianji(point a,point b,point c){
	double t;
	t=(c.x-a.x)*(b.x-a.x)+(c.y-a.y)*(b.y-a.y);
	if(t<-eps)return -1;
	if(t>eps)return 1;
	return 0;
}
double dis(point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double disl(point a,point b,point c){
	if(dianji(b,c,a)*dianji(c,b,a)<0)
		return fmin(dis(a,b),dis(a,c));
	else
	    return fabs(chaji(a,b,c))/dis(b,c);
}
bool tin(tr u,point v){
	if(v.x>u.a.x-eps&&v.x<u.c.x+eps&&v.y>u.c.y-eps&&v.y<u.a.y+eps)
	    return 1;
	return 0;
}
void solve(circle u,tr v){
	if(disl(u.o,v.a,v.b)<u.r+eps||
	   disl(u.o,v.b,v.c)<u.r+eps||
	   disl(u.o,v.c,v.d)<u.r+eps||
	   disl(u.o,v.d,v.a)<u.r+eps)
		puts("yes");
	else
	    puts("no");
}
int main(){
	char name1[50],name2[50];
	int cs,f1,f2;
	double dr;
	scanf("%d",&cs);
	while(cs--){
		scanf("%s",name1);
		if(!strcmp(name1,"circle"))
		    scanf("%lf%lf%lf",&cu.r,&cu.o.x,&cu.o.y),f1=0;
		else{
		    scanf("%lf%lf%lf%lf",&u.a.x,&u.a.y,&u.c.x,&u.c.y);
			u.b.x=u.a.x;u.b.y=u.c.y;
			u.d.x=u.c.x;u.d.y=u.a.y;
			f1=1;
		}
        scanf("%s",name2);
		if(!strcmp(name2,"circle"))
		    scanf("%lf%lf%lf",&cv.r,&cv.o.x,&cv.o.y),f2=0;
		else{
		    scanf("%lf%lf%lf%lf",&v.a.x,&v.a.y,&v.c.x,&v.c.y);
			v.b.x=v.a.x;
			v.b.y=v.c.y;
			v.d.x=v.c.x;
			v.d.y=v.a.y;
			f2=1;
		}
	if(!f1&&!f2){
		dr=dis(cu.o,cv.o);
		if((dr-eps<cu.r+cv.r)&&(dr+eps>fabs(cu.r-cv.r)))
			puts("yes");
		else
		    puts("no");
	}
	if(f1&&f2){
		if(tin(u,v.a)||tin(u,v.b)||tin(u,v.c)||tin(u,v.d)||
		   tin(v,u.a)||tin(v,u.b)||tin(v,u.c)||tin(v,u.d))
			puts("yes");
		else
		    puts("no");
	}
	if(!f1&&f2)solve(cu,v);
	if(f1&&!f2)solve(cv,u);
	}
	return 0;
}

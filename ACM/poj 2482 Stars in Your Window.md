# 题目
Fleeting time does not blur my memory of you. Can it really be 4 years since I first saw you? I still remember, vividly, on the beautiful Zhuhai Campus, 4 years ago, from the moment I saw you smile, as you were walking out of the classroom and turned your head back, with the soft sunset glow shining on your rosy cheek, I knew, I knew that I was already drunk on you. Then, after several months’ observation and prying, your grace and your wisdom, your attitude to life and your aspiration for future were all strongly impressed on my memory. You were the glamorous and sunny girl whom I always dream of to share the rest of my life with. Alas, actually you were far beyond my wildest dreams and I had no idea about how to bridge that gulf between you and me. So I schemed nothing but to wait, to wait for an appropriate opportunity. Till now — the arrival of graduation, I realize I am such an idiot that one should create the opportunity and seize it instead of just waiting.

These days, having parted with friends, roommates and classmates one after another, I still cannot believe the fact that after waving hands, these familiar faces will soon vanish from our life and become no more than a memory. I will move out from school tomorrow. And you are planning to fly far far away, to pursue your future and fulfill your dreams. Perhaps we will not meet each other any more if without fate and luck. So tonight, I was wandering around your dormitory building hoping to meet you there by chance. But contradictorily, your appearance must quicken my heartbeat and my clumsy tongue might be not able to belch out a word. I cannot remember how many times I have passed your dormitory building both in Zhuhai and Guangzhou, and each time aspired to see you appear in the balcony or your silhouette that cast on the window. I cannot remember how many times this idea comes to my mind: call her out to have dinner or at least a conversation. But each time, thinking of your excellence and my commonness, the predominance of timidity over courage drove me leave silently.

Graduation, means the end of life in university, the end of these glorious, romantic years. Your lovely smile which is my original incentive to work hard and this unrequited love will be both sealed as a memory in the deep of my heart and my mind. Graduation, also means a start of new life, a footprint on the way to bright prospect. I truly hope you will be happy everyday abroad and everything goes well. Meanwhile, I will try to get out from puerility and become more sophisticated. To pursue my own love and happiness here in reality will be my ideal I never desert.

Farewell, my princess!

If someday, somewhere, we have a chance to gather, even as gray-haired man and woman, at that time, I hope we can be good friends to share this memory proudly to relight the youthful and joyful emotions. If this chance never comes, I wish I were the stars in the sky and twinkling in your window, to bless you far away, as friends, to accompany you every night, sharing the sweet dreams or going through the nightmares together.
![poj_3489desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_3489desc_0.jpg)

Here comes the problem: Assume the sky is a flat plane. All the stars lie on it with a location (x, y). for each star, there is a grade ranging from 1 to 100, representing its brightness, where 100 is the brightest and 1 is the weakest. The window is a rectangle whose edges are parallel to the x-axis or y-axis. Your task is to tell where I should put the window in order to maximize the sum of the brightness of the stars within the window. Note, the stars which are right on the edge of the window does not count. The window can be translated but rotation is not allowed.

输入描述

There are several test cases in the input. The first line of each case contains 3 integers: n, W, H, indicating the number of stars, the horizontal length and the vertical height of the rectangle-shaped window. Then n lines follow, with 3 integers each: x, y, c, telling the location (x, y) and the brightness of each star. No two stars are on the same point.

There are at least 1 and at most 10000 stars in the sky. 1

输出描述

For each test case, output the maximum brightness in a single line.

输入例子
```
3 5 4
1 2 3
2 3 2
6 3 1
3 5 4
1 2 3
2 3 2
5 3 1
```
输出例子
```
5
6
```
# 参考答案
```c++
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=40005;
long long r[N*12];
int n;
long long w,h;
int tot,cnt;
long long mx=0;
long long maxl(long long a,long long b)
{return a>b?a:b;}
struct line
{
	long long x,y1,y2,c;
}pos[N*6];
bool cmp(line a,line b)
{
	if(a.x==b.x)return a.c<b.c;
	return a.x<b.x;
}
struct sgtr
{
	int l,r;
	long long dat;
	long long add;
}tr[N*6];
void build(int p,int l,int r)
{
	tr[p].l=l,tr[p].r=r,tr[p].dat=tr[p].add=0;
	if(l==r)return;
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
}
void spread(int p)
{
	if(tr[p].l==tr[p].r)return;
	if(tr[p].add)
	{
		tr[p*2].dat+=tr[p].add;
		tr[p*2+1].dat+=tr[p].add;
		tr[p*2].add+=tr[p].add;
		tr[p*2+1].add+=tr[p].add;
	}
	tr[p].add=0;
}
void change(int p,int l,int r,long long x)
{
	if(l<=tr[p].l&&r>=tr[p].r)
	{
		tr[p].dat+=x;
		tr[p].add+=x;
		return;
	}
	spread(p);
	int mid=(tr[p].l+tr[p].r)/2;
	if(l<=mid)change(p*2,l,r,x);
	if(r>mid)change(p*2+1,l,r,x);
	tr[p].dat=maxl(tr[p*2].dat,tr[p*2+1].dat);
}
void make()
{
	sort(r+1,r+tot+1);
	for(int i=1;i<=cnt;i++)
	{
		//pos[i].x=lower_bound(r+1,r+tot+1,pos[i].x)-r;
		pos[i].y1=lower_bound(r+1,r+tot+1,pos[i].y1)-r;
		pos[i].y2=lower_bound(r+1,r+tot+1,pos[i].y2)-r;
		mx=maxl(mx,maxl(pos[i].y2,pos[i].y1));
	}
	sort(pos+1,pos+cnt+1,cmp);
}
void init()
{
	memset(&tr,0,sizeof tr);
	memset(&pos,0,sizeof pos);
	memset(r,0,sizeof r);
	mx=tot=cnt=0;
}
int main()
{
	while(scanf("%d%I64d%I64d",&n,&w,&h)!=EOF)
	{
		init();
		for(int i=1;i<=n;i++)
		{
			long long a,b,c;
			scanf("%I64d%I64d%I64d",&a,&b,&c);
			pos[++cnt].x=a,pos[cnt].y1=b,pos[cnt].y2=b+h-1,pos[cnt].c=c;
			pos[++cnt].x=a+w,pos[cnt].y1=b,pos[cnt].y2=b+h-1,pos[cnt].c=-c;
			r[++tot]=b,r[++tot]=b-1,r[++tot]=b+1,r[++tot]=b+h-1,r[++tot]=b+h,r[++tot]=b+h+1;
		}
		make();
		build(1,1,mx+10);
		unsigned long long ans=0;
		for(int i=1;i<=cnt;i++)
		{
			//cout<<"push "<<pos[i].y1<<" "<<pos[i].y2<<" "<<pos[i].c<<endl;
			change(1,pos[i].y1,pos[i].y2,pos[i].c);
			ans=maxl(ans,tr[1].dat);
			//cout<<ans<<endl;
		}
		printf("%I64d\n",ans);
	}
}

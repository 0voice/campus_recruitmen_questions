# 题目
John and Brus are playing a military strategic game on a PC. The game is played on the flat world map. At the beginning of the game Brus places his army. Then John has to choose strategic points for his army according to the following rules:

each strategic point must be a lattice point (x, y) (a lattice point is a point with integer coordinates) such that |x| + |y| John can choose any positive number of strategic points;<br>
all the strategic points must be distinct;<br>
each of the strategic points must be free (i.e. not occupied by Brus’s army);<br>
each pair of different strategic points must be connected (possibly via some other strategic points).

Here two different lattice points (x1, y1) and (x2, y2) are connected if |x1 – x2| + |y1 – y2| = 1. If A, B and C are strategic points, A and B are connected, B and C are connected, then A and C are also connected.<br>
Your task is to find the number of ways for John to choose strategic points for his army.<br>
输入描述

The first line contains single integer T – the number of test cases. Each test case starts with a line containing two integers N and M separated by a single space. N is the number mentioned in the first rule. M is the number of lattice points on the world map already occupied by Brus’s army. Each of the following M lines contains two integers Xk and Yk separated by a single space. Each lattice point (Xk, Yk) is occupied by Brus’s army.

输出描述
For each test case print a single line containing the number of ways for John to choose strategic points for his army.<br>
输入例子
```
2 
2 1 
7 7 
2 3 
0 0 
4 -7 
7 -4
```
输出例子
```
20 
4
```
Hint
```
Constraints:
1 ≤ T ≤ 74,
1 ≤ N ≤ 7,
1 ≤ M ≤ 225,
-7 ≤ Xk, Yk ≤ 7,
all (Xk, Yk) will be distinct.
```
# 参考答案
```c++
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<queue>
#include<vector>

using namespace std;

typedef long long LL;
const LL bit=(LL)(1000000000)*(LL)(1000000000);
const int MAXD=15;
const int HASH=30007;
const int STATE=1000010;
const int MAXN=3;
int N,M,n,m;
int maze[MAXD][MAXD];
int code[MAXD];
int ch[MAXD];
int ex,ey;

struct HP
{
	int len;
	LL s[MAXN];
	HP()
	{
		memset(s,0,sizeof(s));
		len=1;
	}
	HP operator =(const char *num)
	{
		int k=0,j=0;
		LL mul=1,tmp=0;
		for(int i=strlen(num)-1;i>=0;i--)
        {
            tmp=tmp*mul+(LL)(num[i]-'0');
            j++,mul*=10;
            if(j==8)
            {
                s[k++]=tmp;
                j=0;
                mul=1;
                tmp=0;
            }
        }
        if(tmp!=0)
            s[k++]=tmp;
        len=k;
		return *this;
	}
	HP operator =(int num)
	{
		char s[MAXN];
		sprintf(s,"%d",num);
		*this=s;
		return *this;
	}
	HP(int num) { *this=num;}
	HP(const char*num) {*this=num;}
	string str()const
	{
		string res="";
		for(int i=0;i<len-1;i++)
        {
            LL tmp=s[i];
            for(int j=0;j<8;j++)
            {
                res=(char)(tmp%10+'0')+res;
                tmp/=10;
            }
        }
        LL tmp=s[len-1];
        while(tmp!=0)
        {
            res=(char)(tmp%10+'0')+res;
            tmp/=10;
        }
		if(res=="") res="0";
		return res;
	}
	HP operator +(const HP& b) const
    {
        HP c;
        c.len=0;
        LL g=0;
        for(int i=0;g!=0||i<max(len,b.len);i++)
        {
            LL x=g;
            if(i<len) x+=s[i];
            if(i<b.len) x+=b.s[i];
            c.s[c.len++]=x%bit;
            g=x/bit;
        }
        return c;
    }
    void clean(){ while(len > 1 && !s[len-1]) len--;}
    void output()
    {
        printf("%lld",s[len-1]);
        for(int i=len-2;i>=0;i--) printf("%.18lld",s[i]);
        printf("\n");
    }
}ans,tmp;

struct HASHMAP
{
    int head[HASH],next[STATE],size;
    LL state[STATE];
    HP f[STATE];
    void init()
    {
        size=0;
        memset(head,-1,sizeof(head));
    }
    void push(LL st,HP ans)
    {
        int h=st%HASH;
        for(int i=head[h];i!=-1;i=next[i])
          if(state[i]==st)
          {
              f[i]=f[i]+ans;
              return;
          }
        state[size]=st;
        f[size]=ans;
        next[size]=head[h];
        head[h]=size++;
    }
}hm[2];

void decode(int *code,int m,LL  st)
{
    for(int i=m;i>=0;i--)
    {
        code[i]=st&7;
        st>>=3;
    }
}
LL encode(int *code,int m)
{
    int cnt=1;
    memset(ch,-1,sizeof(ch));
    ch[0]=0;
    LL st=0;
    for(int i=0;i<=m;i++)
    {
        if(ch[code[i]]==-1)ch[code[i]]=cnt++;
        code[i]=ch[code[i]];
        st<<=3;
        st|=code[i];
    }
    return st;
}
void shift(int *code,int m)
{
    for(int i=m;i>0;i--)code[i]=code[i-1];
    code[0]=0;
}

bool jud(int *code,int m)
{
    int cnt=1;
    memset(ch,-1,sizeof(ch));
    ch[0]=0;
    for(int i=0;i<=m&&cnt<3;i++)
        if(ch[code[i]]==-1)ch[code[i]]=cnt++;
    return cnt==2;
}

//12 34567
//  |-----
//--|
//01234567
bool con(int *code,int x,int y)
{
    memset(ch,0,sizeof(ch));
    for(int i=1;i<=M;i++)
    {
        if(i==y)continue;
        if(i<y&&maze[x+1][i])  ch[code[i-1]]=1;
        else if(i>y&&maze[x][i])  ch[code[i]]=1;
    }
    for(int i=0;i<=M;i++) if(code[i]!=0&&ch[code[i]]==0) return false;
    return true;
}

void dpblank(int i,int j,int cur)
{
    int left,up;
    for(int k=0;k<hm[cur].size;k++)
    {
        int cod[MAXD];
        decode(code,M,hm[cur].state[k]);
        memcpy(cod,code,sizeof(code));
        left=code[j-1];
        up=code[j];
        tmp=hm[cur].f[k];
        if(left&&up)
        {
            if(left==up)
            {
                if(j==M)shift(code,M);
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
                if(jud(code,M)) ans=ans+tmp;
            }
            else
            {
                code[j-1]=code[j]=left;
                for(int t=0;t<=M;t++) if(code[t]==up)code[t]=left;
                if(j==M)shift(code,M);
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
                if(jud(code,M)) ans=ans+tmp;
            }
        }
        else if((left&&(!up))||((!left)&&up))
        {
            int t;
            if(!left)t=up;
            else t=left;
            code[j-1]=code[j]=t;
            if(j==M)shift(code,M);
            hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            if(jud(code,M)) ans=ans+tmp;
        }
        else
        {
            code[j-1]=code[j]=13;
            if(j==M)shift(code,M);
            hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            if(jud(code,M))ans=ans+tmp;
        }
        memcpy(code,cod,sizeof(cod));
        maze[i][j]=0;
        if(!con(code,i,j))  continue;
        code[j]=code[j-1]=0;
        if(j==M)shift(code,M);
        hm[cur^1].push(encode(code,M),hm[cur].f[k]);
    }
}

void dpblock(int i,int j,int cur)
{
    for(int k=0;k<hm[cur].size;k++)
    {
        decode(code,M,hm[cur].state[k]);
        if(!con(code,i,j))  continue;
        code[j-1]=code[j]=0;
        if(j==M)shift(code,M);
        hm[cur^1].push(encode(code,M),hm[cur].f[k]);
    }
}

void dp()
{
    int cur=0;
    ans=0;
    hm[cur].init();
    hm[cur].push(0,1);
    for(int i=1;i<=N;i++)
      for(int j=1;j<=M;j++)
      {
          hm[cur^1].init();
          if(maze[i][j])dpblank(i,j,cur);
          else  dpblock(i,j,cur);
          cur^=1;
      }
}

int main()
{
    int cs;
    cin>>cs;
    while(cs--)
    {
        scanf("%d%d",&n,&m);
        memset(maze,0,sizeof(maze));
        for(int i=-(n-1);i<=n-1;i++)
            for(int j=-(n-1);j<=n-1;j++)
                if(abs(i)+abs(j)<n) maze[i+n][j+n]=1;
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            if(abs(x)+abs(y)<n) maze[x+n][y+n]=0;
        }
        N=n*2-1;M=N; // -(n-1) --- n-1    ->  1 --- 2*n-1
        int sig=0;
        for(int i=1;i<=N;i++) for(int j=1;j<=N;j++)
            sig+=maze[i][j]?1:0;
        if(sig<2) printf("%d\n",sig);
        else
        {
            dp();
            ans.output();
        }
    }
    return 0;
}

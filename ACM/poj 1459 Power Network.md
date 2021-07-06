# 题目
A power network consists of nodes (power stations, consumers and dispatchers) connected by power transport lines. A node u may be supplied with an amount s(u) >= 0 of power, may produce an amount 0 max(u) of power, may consume an amount 0 max(u)) of power, and may deliver an amount d(u)=s(u)+p(u)-c(u) of power. The following restrictions apply: c(u)=0 for any power station, p(u)=0 for any consumer, and p(u)=c(u)=0 for any dispatcher. There is at most one power transport line (u,v) from a node u to a node v in the net; it transports an amount 0 max(u,v) of power delivered by u to v. Let Con=Σu c(u) be the power consumed in the net. The problem is to compute the maximum value of Con.

![image](https://user-images.githubusercontent.com/59190045/124560563-87710800-de6f-11eb-905e-ba42a334879d.png)

An example is in figure 1. The label x/y of power station u shows that p(u)=x and p<sub>max</sub> (u)=y. The label x/y of consumer u shows that c(u)=x and c<sub>max</sub> (u)=y. The label x/y of power transport line (u,v) shows that l(u,v)=x and l<sub>max</sub> (u,v)=y. The power consumed is Con=6. Notice that there are other possible states of the network but the value of Con cannot exceed 6.

输入描述

There are several data sets in the input. Each data set encodes a power network. It starts with four integers: 0 max(u,v). Follow np doublets (u)z, where u is the identifier of a power station and 0 max(u). The data set ends with nc doublets (u)z, where u is the identifier of a consumer and 0 max(u). All input numbers are integers. Except the (u,v)z triplets and the (u)z doublets, which do not contain white spaces, white spaces can occur freely in input. Input data terminate with an end of file and are correct.

输出描述

For each data set from the input, the program prints on the standard output the maximum amount of power that can be consumed in the corresponding network. Each result has an integral value and is printed from the beginning of a separate line.

输入例子
```
2 1 1 2 (0,1)20 (1,0)10 (0)15 (1)20
7 2 3 13 (0,0)1 (0,1)2 (0,2)5 (1,0)1 (1,2)8 (2,3)1 (2,4)7
         (3,5)2 (3,6)5 (4,2)7 (4,3)5 (4,5)1 (6,0)5
         (0)5 (1)2 (3)2 (4)1 (5)4
```
输出例子
```
15
6
```
Hint

The sample input contains two data sets. The first data set encodes a network with 2 nodes, power station 0 with pmax(0)=15 and consumer 1 with cmax(1)=20, and 2 power transport lines with lmax(0,1)=20 and lmax(1,0)=10. The maximum value of Con is 15. The second data set encodes the network from figure 1.
# 参考答案
```c++
#include<iostream>
using namespace std;

const int inf=10001;

int n;  //总节点数
int np; //电站数
int nc; //用户数
int line;  //线路数
int cap[102][102];  //弧(u,v)的容量
int flow[102][102];  //弧(u,v)的流量
bool vist[102];   //标记点v是否已标号
int s,t;  //超级源，超级汇

class info   //当前点v的标记信息
{
public:
    int pre;  //当前点v的前驱u
    int lv;  //l(v)
    int nei[101];  //当前结点直接指向的邻居结点
    int pn;  //邻居结点的指针
}node[102];

int min(int a,int b)
{
    return a<b?a:b;
}

void back(void)
{
    int x=t;
    while(x!=s)
    {
        flow[ node[x].pre ][x] += node[t].lv;  //改进增广路
        x=node[x].pre;

    }
    return;
}

bool bfs(void)
{
    memset(vist,false,sizeof(vist));
    node[s].pre=-1;
    node[s].lv=inf;
    vist[s]=true;

    int queue[102];
    int head=0;
    int tail=0;
    queue[tail++]=s;

    while(head<=tail-1)  //注意，这是再也找不到增广路的结束条件
    {
        int x=queue[head];
        int y;
        for(int i=0;i<node[x].pn;i++)
        {
            y=node[x].nei[i];
            if(!vist[y] && flow[x][y]<cap[x][y])   //搜索的目标要求是 未标记 & 非饱和弧
            {
                queue[tail++]=y;

                vist[y]=true;
                node[y].pre=x;
                node[y].lv=min( node[x].lv , cap[x][y]-flow[x][y] );
            }
            if(vist[t])  //当超级汇被标记
                break;
        }
        if(!vist[t])
            head++;
        else
            return true;  //搜索到一条增广路
    }
    return false;
}

int main(int i,int j,int u,int v,int z,char temp)
{
    while(cin>>n>>np>>nc>>line)
    {
        /*Initial*/

        s=n;
        t=n+1;
        for(i=0;i<n+1;i++)
            node[i].pn=0;

        /*Input & Structure Maps*/

        for(i=1;i<=line;i++)
        {
            cin>>temp>>u>>temp>>v>>temp>>z;
            if(u==v)
                continue;   //不需要环
            cap[u][v]=z;
            flow[u][v]=0;   //每条边的流量都初始化为0
            node[u].nei[ node[u].pn++ ]=v;
        }
        for(i=1;i<=np;i++)
        {
            cin>>temp>>v>>temp>>z;
            cap[s][v]=z;     //建立超级源，指向所有电站
            flow[s][v]=0;
            node[s].nei[ node[s].pn++ ]=v;
        }
        for(i=1;i<=nc;i++)
        {
            cin>>temp>>u>>temp>>z;
            cap[u][t]=z;     //建立超级汇，被所有用户指向
            flow[u][t]=0;
            node[u].nei[ node[u].pn++ ]=t;
        }

        /*标号法找增广轨*/

        while(true)
        {
            if(bfs())  //如果能搜到到增广路
                back();  //从超级汇开始回溯,改进增广路
            else
            {
                int max=0;        //输出最大流
                for(i=0;i<node[s].pn;i++)
                    max+=flow[s][ node[s].nei[i] ];
                cout<<max<<endl;
                break;
            }
        }
    }
    return 0;
}

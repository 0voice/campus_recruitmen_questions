# 题目
Consider the two networks shown below. Assuming that data moves around these networks only between directly connected nodes on a peer-to-peer basis, a failure of a single node, 3, in the network on the left would prevent some of the still available nodes from communicating with each other. Nodes 1 and 2 could still communicate with each other as could nodes 4 and 5, but communication between any other pairs of nodes would no longer be possible.

Node 3 is therefore a Single Point of Failure (SPF) for this network. Strictly, an SPF will be defined as any node that, if unavailable, would prevent at least one pair of available nodes from being able to communicate on what was previously a fully connected network. Note that the network on the right has no such node; there is no SPF in the network. At least two machines must fail before there are any pairs of available nodes which cannot communicate.

![poj_4694desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_4694desc_0.jpg)

输入描述

The input will contain the description of several networks. A network description will consist of pairs of integers, one pair per line, that identify connected nodes. Ordering of the pairs is irrelevant; 1 2 and 2 1 specify the same connection. All node numbers will range from 1 to 1000. A line containing a single zero ends the list of connected nodes. An empty network description flags the end of the input. Blank lines in the input file should be ignored.

输出描述

For each network in the input, you will output its number in the file, followed by a list of any SPF nodes that exist.

The first network in the file should be identified as "Network #1", the second as "Network #2", etc. For each SPF node, output a line, formatted as shown in the examples below, that identifies the node and the number of fully connected subnets that remain when that node fails. If the network has no SPF nodes, simply output the text "No SPF nodes" instead of a list of SPF nodes.

输入例子
```
1 2
5 4
3 1
3 2
3 4
3 5
0

1 2
2 3
3 4
4 5
5 1
0

1 2
2 3
3 4
4 6
6 3
2 5
5 1
0

0
```
输出例子
```
Network #1
  SPF node 3 leaves 2 subnets

Network #2
  No SPF nodes

Network #3
  SPF node 2 leaves 2 subnets
  SPF node 3 leaves 2 subnets
```
# 参考答案
```c++
    #include<iostream>
    #include<string.h>

    using namespace std;

    const int size=1001;

    struct Node
    {
      int id;				//结点编号
      struct Node* next;
    };

    class solve
    {
    public:
      solve():cases(0)
      {
        for(int i=0;i<size;i++)		//初始化邻接链表链头
          ListTable_Head[i]=0;

        DFS();
      }
      ~solve()
      {
        delete[] *ListTable_Head;
      }

      int min(int a,int b) const{return a<b?a:b;}

      bool Input(void);							//返回0: 等待下一组输入。 返回1:程序结束
      void Insert(int x,int y);					//把无向边(x,y)插入邻接表

      void DFS(void);								//搜索割点及其对应的连通分量数
      void DFS_SPF(int k,int father,int depth);	//搜索割点。k:当前结点。father:k的父亲结点。depth:搜索深度(时间戳)
      void DFS_Subnet(int i);						//i为从割点出发的分支,搜索并标记该从该分支出发所能到达的所有node
                            //（这些node就是一个连通分量）

      void Empty(void);							//清空邻接表(保留链头并使其指向NULL)
      void Del(Node* p);							//删除以结点p为链头的整条链(保留链头并使其指向NULL)

    protected:

      int cases;						//案例数
      Node* ListTable_Head[size];		//邻接链表链头

      int Root;						//深搜树的根(搜索起点)
      int deep[size];					//结点k的搜索深度deep[k]
      int AnceDeep[size];				//结点k及其子孙辈分最高(深度最浅)的祖先的深度AnceDeep[k]
      int color[size];				//结点k的颜色color[k]。0:未访问未检查；1:已访问未检查；2:已访问已检查
      bool cut[size];					//标记结点是否为割点
      bool SPF;						//标记网络是否出现割点

      int Subnet_Num;					//被割点的划分的连通分量的个数
      bool vist[size];				//标记访问过的node
    };

    bool solve::Input(void)
    {
      int x,y;
      for(int i=0;;i++)
      {
        cin>>x;
        if(x==0 && i==0)		//程序结束
          break;
        else if(x==0 && i!=0)	//当前case的数据输入完毕
          return true;

        cin>>y;
        Insert(x,y);
      }
      return false;
    }

    void solve::Insert(int x,int y)
    {
      if(!ListTable_Head[x])		//链头不存在，则创建
      {
        ListTable_Head[x]=new Node;
        ListTable_Head[x]->next=0;
      }
      if(!ListTable_Head[y])
      {
        ListTable_Head[y]=new Node;
        ListTable_Head[y]->next=0;
      }

      Node* px=ListTable_Head[x];
      Node* py=ListTable_Head[y];
      Node* tmp;

      tmp=px->next;		//头插入法
      px->next=new Node;
      px->next->id=y;
      px->next->next=tmp;

      tmp=py->next;		//头插入法
      py->next=new Node;
      py->next->id=x;
      py->next->next=tmp;

      return;
    }

    void solve::DFS(void)
    {
      while(Input())
      {
        SPF=false;
        memset(deep,0,sizeof(deep));
        memset(AnceDeep,0,sizeof(AnceDeep));
        memset(color,0,sizeof(color));
        memset(cut,false,sizeof(cut));

        /*搜索编号最小的node作为深搜树树的根*/
        for(int k=1;k<size;k++)
          if(ListTable_Head[k])
          {
            Root=k;
            break;
          }

        /*寻找所有割点*/
        DFS_SPF(Root,Root,1);

        cout<<"Network #"<<++cases<<endl;
        if(!SPF)
          cout<<"  No SPF nodes"<<endl;
        else
        {
          for(int i=Root;i<size;i++)
            if(cut[i])
            {
              Subnet_Num=0;
              memset(vist,false,sizeof(vist));
              vist[i]=true;

              /*枚举割点i的所有分支，其中没有访问过的分支则对其逐一深搜*/
              /*找出被割点i划分的所有连通分量*/
              for(Node* p=ListTable_Head[i]->next;p;p=p->next)
              {
                if(!vist[p->id])		//分支p->id没有被访问
                {						//说明当前分支与前面搜索的连通分量 不连通
                  Subnet_Num++;		//则连通分量数+1
                  DFS_Subnet(p->id);	//搜索并标记该连通分量下的所有node
                }
              }
              cout<<"  SPF node "<<i<<" leaves "<<Subnet_Num<<" subnets"<<endl;
            }
        }
        cout<<endl;

        Empty();
      }
      return;
    }

    void solve::DFS_SPF(int k,int father,int depth)
    {
      color[k]=1;				//染色，结点k已访问未检查
      deep[k]=depth;			//记录k的搜索深度
      AnceDeep[k]=depth;		//初始化,k最浅的祖先的深度就是k本身的深度
      int son=0;				//k的儿子数

      for(Node* p=ListTable_Head[k]->next;p;p=p->next)
      {
        int i=p->id;

        if(color[i]==0)		//未访问未检查的node
        {
          son++;			//k的分支中，所有未访问未检查的node都是其儿子
          DFS_SPF(i,k,depth+1);
          AnceDeep[k]=min(AnceDeep[k],AnceDeep[i]);	//由于k和其儿子i必然同宗
        }												//若在i中出现后向边使得i的祖先辈分更高（深度更浅）
                                //那么k的祖先辈分应该被更新

        if(i!=father && color[i]==1)	//k的分支中，所有已访问未检查的node都是其祖先
          AnceDeep[k]=min(AnceDeep[k],deep[i]);	//直接检查祖先辈分（深度）并更新

        if((k==Root && son>1) ||			/*根结点的儿子数(分支数) >1时，则Root必定是割点*/
          (k!=Root && AnceDeep[i]>=deep[k])) 	/*k的儿子i的最大祖先的深度比k的深度要深，则删除k后i与k的father必然断开*/
        {
          cut[k]=true;
          SPF=true;
        }
      }
      color[k]=2;
      return;
    }

    void solve::DFS_Subnet(int cp)
    {
      for(Node* p=ListTable_Head[cp]->next;p;p=p->next)
      {
        int i=p->id;
        if(!vist[i])
        {
          vist[i]=true;
          DFS_Subnet(i);
        }
      }
      return;
    }

    void solve::Empty(void)
    {
      for(int i=1;i<size;i++)
      {
        if(ListTable_Head[i])
          Del(ListTable_Head[i]);
        ListTable_Head[i]=0;		//保留链表表头并初始化
      }
      return;
    }

    void solve::Del(Node* p)
    {
      if(p->next)
        Del(p->next);
      delete p;
      return;
    }

    int main(void)
    {
      solve poj1523;
      return 0;
    }

# 题目
Let us consider a special type of a binary search tree, called a cartesian tree. Recall that a binary search tree is a rooted ordered binary tree, such that for its every node x the following condition is satisfied: each node in its left subtree has the key less then the key of x, and each node in its right subtree has the key greater then the key of x.
That is, if we denote left subtree of the node x by L(x), its right subtree by R(x) and its key by kx then for each node x we have<br>
if y ∈ L(x) then ky<br>
if z ∈ R(x) then kz > kx<br>

The binary search tree is called cartesian if its every node x in addition to the main key kx also has an auxiliary key that we will denote by ax, and for these keys the heap condition is satisfied, that is<br>
if y is the parent of x then ay<br>
Thus a cartesian tree is a binary rooted ordered tree, such that each of its nodes has a pair of two keys (k, a) and three conditions described are satisfied.<br>
Given a set of pairs, construct a cartesian tree out of them, or detect that it is not possible.<br>
输入描述<br>
The first line of the input file contains an integer number N -- the number of pairs you should build cartesian tree out<br>
输出描述<br>
On the first line of the output file print YES if it is possible to build a cartesian tree out of given pairs or NO if it is not. If the answer is positive, on the following N lines output the tree. Let nodes be numbered from 1 to N corresponding to pairs they contain as they are given in the input file. For each node output three numbers -- its parent, its left child and its right child. If the node has no parent or no corresponding child, output 0 instead.
The input ensure these is only one possible tree.<br>
输入例子
```
7
5 4
2 2
3 9
0 5
1 3
6 6
4 11
```
输出例子
```
YES
2 3 6
0 5 1
1 0 7
5 0 0
2 4 0
1 0 0
3 0 0
```
# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int N=50005;
struct Treap_Node
{
    int left,right;
    int value,pri,id;
}Tnode[N];
int ans[N][3];
void dfs(int now)
{
    if(now==-1)
        return;
    int id=Tnode[now].id,ll=Tnode[now].left,rr=Tnode[now].right;
    if(ll!=-1)
    {
        ans[id][1]=Tnode[ll].id;
        ans[Tnode[ll].id][0]=id;
        dfs(ll);
    }
    if(rr!=-1)
    {
        ans[id][2]=Tnode[rr].id;
        ans[Tnode[rr].id][0]=id;
        dfs(rr);
    }
}
struct data
{
    int v,p,id;
    bool operator<(const data &ne)const
    {
        return v<ne.v;
    }
}po[N];
int stk[N],top;
int main()
{
    int n;
    scanf("%d",&n);
    memset(ans,0,sizeof(ans));
    for(int i=1; i<=n; i++)
    {
        scanf("%d%d",&po[i].v,&po[i].p);
        po[i].id=i;
    }
    sort(po+1,po+n+1);
    Tnode[0].left=Tnode[0].right=-1;
    Tnode[0].pri=-10000000;
    top=1;
    stk[0]=0;
    for(int i=1;i<=n;i++)
    {
        int v=po[i].v,p=po[i].p,d=po[i].id;
        while(top>0&&Tnode[stk[top-1]].pri>p)
            top--;
        Tnode[i].left=Tnode[stk[top-1]].right;
        Tnode[stk[top-1]].right=i;
        Tnode[i].right=-1;
        Tnode[i].value=v;
        Tnode[i].pri=p;
        Tnode[i].id=d;
        stk[top++]=i;
    }
    dfs(0);
    printf("YES\n");
    for(int i=1; i<=n; i++)
        printf("%d %d %d\n",ans[i][0],ans[i][1],ans[i][2]);
    return 0;
}

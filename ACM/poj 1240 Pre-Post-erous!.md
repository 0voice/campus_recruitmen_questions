# 题目
We are all familiar with pre-order, in-order and post-order traversals of binary trees. A common problem in data structure classes is to find the pre-order traversal of a binary tree when given the in-order and post-order traversals. Alternatively, you can find the post-order traversal when given the in-order and pre-order. However, in general you cannot determine the in-order traversal of a tree when given its pre-order and post-order traversals. Consider the four binary trees below:
```
    a   a   a   a

   /   /     \   \

  b   b       b   b

 /     \     /     \

c       c   c       c
```
All of these trees have the same pre-order and post-order traversals. This phenomenon is not restricted to binary trees, but holds for general m-ary trees as well.

输入描述
Input will consist of multiple problem instances. Each instance will consist of a line of the form<br>
m s1 s2<br>
indicating that the trees are m-ary trees, s1 is the pre-order traversal and s2 is the post-order traversal.All traversal strings will consist of lowercase alphabetic characters. For all input instances, 1

输出描述
For each problem instance, you should output one line containing the number of possible trees which would result in the pre-order and post-order traversals for the instance. All output values will be within the range of a 32-bit signed integer. For each problem instance, you are guaranteed that there is at least one tree with the given pre-order and post-order traversals.

输入例子
```
2 abc cba
2 abc bca
10 abc bca
13 abejkcfghid jkebfghicda
0
```
输出例子
```
4
1
45
207352860
```
# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
ll c[30][30];
int n;
ll dfs(char s1[],char s2[])
{
    ll ans=1;
    if(s1[0]==s2[0])
        return 1ll;
    int i,j,k,cnt=0,len=strlen(s1);
    for(i=1,j=0;i<len;)
    {
        k=1;
        while(s1[i]!=s2[j])
            j++,k++;
        cnt++;
        char t1[30],t2[30];
        strncpy(t1,s1+i,k);
        strncpy(t2,s2+j-k+1,k);
        t1[k]=t2[k]='\0';
        ans*=dfs(t1,t2);
        i+=k;
        j++;
    }
    return ans*c[n][cnt];
}
int main()
{
    c[0][0]=1;
    for(int i=1;i<=20;i++)
    {
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++)
        {
            c[i][j]=c[i-1][j]+c[i-1][j-1];
        }
    }
    while(scanf("%d",&n),n)
    {
        char s1[30],s2[30];
        scanf("%s%s",s1,s2);
        printf("%lld\n",dfs(s1,s2));
    }
    return 0;
}

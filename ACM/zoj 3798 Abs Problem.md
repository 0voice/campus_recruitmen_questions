# 题目
Alice and Bob is playing a game, and this time the game is all about the absolute value!

Alice has <var>N</var> different positive integers, and each number is not greater than <var>N</var>. Bob has a lot of blank paper, and he is responsible for the calculation things. The rule of game is pretty simple. First, Alice chooses a number <var>a1</var> from the <var>N</var> integers, and Bob will write it down on the first paper, that's <var>b1</var>. Then in the following <var>k</var>th rounds, Alice will choose a number <var>ak</var> (<var>2 ≤ k ≤ N</var>), then Bob will write the number <var>bk</var>=|<var>ak</var>-<var>bk-1</var>| on the <var>k</var>th paper. |<var>x</var>| means the absolute value of <var>x</var>.

Now Alice and Bob want to kown, what is the maximum and minimum value of <var>bN</var>. And you should tell them how to achieve that!

Input

The input consists of multiple test cases;

For each test case, the first line consists one integer <var>N</var>, the number of integers Alice have. (1 ≤ <var>N</var> ≤ 50000)

Output

For each test case, firstly print one line containing two numbers, the first one is the minimum value, and the second is the maximum value.

Then print one line containing <var>N</var> numbers, the order of integers that Alice should choose to achieve the minimum value. Then print one line containing <var>N</var> numbers, the order of integers that Alice should choose to achieve the maximum value.

Attention: Alice won't choose a integer more than twice.

Sample Input
```
2
```
Sample Output
```
1 1
1 2
2 1
```
# 参考答案
```c++
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
using namespace std;
#define up(i,x,y) for(i=x;i<=y;i++)
#define up2(i,x,y) for(i=x;y;i++)
#define down(i,x,y) for(i=x;i>=y;i--)
#define down2(i,x,y) for(i=x;y;i--)
#define pi acos(-1.0)
#define ll long long
#define s(a) scanf("%d",&a)
#define mem(a,b) memset(a,b,sizeof(a))
#define ads(a) (a<0?-a:a)
#define w(a) while(a)

void print(int l,int r,int m)
{
    int i=l,j=r;
    w(i<=j)
    {
        if(i==j)
        {
            printf("%d ",i);
            break;
        }
        else if(i+1>=j)
        {
            printf("%d %d ",i,j);
            break;
        }
        else if(i+2>=j)
        {
            printf("%d %d %d ",i,j,i+1);
            break;
        }
        printf("%d %d ",i,i+1);
        i+=2;
        printf("%d %d ",j,j-1);
        j-=2;
    }
    printf("%d",m);
}

int main()
{
    int n,sum,i,j;
    w(~s(n))
    {
        sum=0;
        up(i,1,n)
        sum+=i;
        printf("%d %d\n",sum%2,n-(sum-n)%2);
        if(n%2)
        {
            print(2,n,1);
            printf("\n");
            print(1,n-1,n);
            printf("\n");
        }
        else
        {
            print(3,n,2);
            printf(" 1\n");
            print(2,n-1,1);
            printf(" %d\n",n);
        }
    }
}

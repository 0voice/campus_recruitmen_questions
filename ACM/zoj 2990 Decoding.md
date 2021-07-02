# 题目
Chip and Dale have devised an encryption method to hide their (written) text messages. They first agree secretly on two numbers that will be used as the number of rows (R) and columns (C) in a matrix. The sender encodes an intermediate format using the following rules:

1.

The text is formed with uppercase letters [A-Z] and <space>.

2.

Each text character will be represented by decimal values as follows:
  
  !zoj_682desc_0[](http://uploadfiles.nowcoder.com/probs/acm/zoj_682desc_0.jpg)
  
<space> = 0, A = 1, B = 2, C = 3, ..., Y = 25, Z = 26 The sender enters the 5 digit binary representation of the characters' values in a spiral pattern along the matrix as shown below. The matrix is padded out with zeroes (0) to fill the matrix completely. For example, if the text to encode is: "ACM" and R=4 and C=4, the matrix would be filled in as follows:

A = 00001, C = 00011, M = 01101(one extra 0) The bits in the matrix are then concatenated together in row major order and sent to the receiver. The example above would be encoded as: 0000110100101100

Input

The first line of input contains a single integer N, (1 <= N <= 1000) which is the number of datasets that follow.

Each dataset consists of a single line of input containing R (1 <= R <= 21), a space, C (1 <= C <= 21), a space, and a string of binary digits that represents the contents of the matrix (R * C binary digits). The binary digits are in row major order.

Output

For each dataset, you should generate one line of output with the following values: The dataset number as a decimal integer (start counting at one), a space, and the decoded text message. You should throw away any trailing spaces and/or partial characters found while decoding.

Sample Input
```
4
4 4 0000110100101100
5 2 0110000010
2 6 010000001001
5 5 0100001000011010110000010
```
Sample Output
```
1 ACM
2 HI
3 HI
4 HI HO
```

# 参考答案
  ```c++
  #include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n,m;
int dir[4][2]={0,1,1,0,0,-1,-1,0};
char str[1010];
int bo[22][22];
int vis[22][22];
int check(int x,int y)
{
 if(x<0||y<0||x>=n||y>=m||vis[x][y])
 return 0;
 return 1;
}
int sum=0,limit;

int ans[1010];
void dfs(int x,int y,int d,int num,int po)
{
 vis[x][y]=1;
 int xx=x+dir[d][0],yy=y+dir[d][1];
 limit--;
 if(po==4)
 {
 ans[sum++]=num*2+bo[x][y];
 po=0;
 if(limit<=0)
 return;
 if(check(xx,yy))
 {
 dfs(xx,yy,d,0,0);
 }
 else
 {
 d=(d+1)%4;
 xx=x+dir[d][0],yy=y+dir[d][1];
 dfs(xx,yy,d,0,0);
 }

 }
 else
 {
 if(check(xx,yy))
 {
 dfs(xx,yy,d,num*2+bo[x][y],po+1);
 }
 else
 {
 d=(d+1)%4;
 xx=x+dir[d][0],yy=y+dir[d][1];
 dfs(xx,yy,d,num*2+bo[x][y],po+1);
 }
 }

}
int main()
{
 int ncase,time=0;
 scanf("%d",&ncase);
 while(ncase--)
 {
 scanf("%d%d",&n,&m);
 printf("%d ",++time);
 scanf("%s",str);
 sum=0;
 int len=n*m,i,j;
 limit=len/5*5;
 for(i=0;i<n;i++)
 {
 for(j=0;j<m;j++)
 bo[i][j]=str[i*m+j]-'0';
 }
 memset(vis,0,sizeof(vis));
 dfs(0,0,0,0,0);
 while(ans[sum-1]==0)sum--;
 for(i=0;i<sum;i++)
 {
 if(ans[i]==0)
 printf(" ");
 else
 printf("%c",ans[i]-1+'A');
 }
 printf("\n");
 }
 return 0;
}

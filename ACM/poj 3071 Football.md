# 题目
Consider a single-elimination football tournament involving 2 n teams, denoted 1, 2, …, 2 n . In each round of the tournament, all teams still in the tournament are placed in a list in order of increasing index. Then, the first team in the list plays the second team, the third team plays the fourth team, etc. The winners of these matches advance to the next round, and the losers are eliminated. After n rounds, only one team remains undefeated; this team is declared the winner.

Given a matrix P = [pij ] such that pij is the probability that team i will beat team j in a match determine which team is most likely to win the tournament.

输入描述

The input test file will contain multiple test cases. Each test case will begin with a single line containing n (1 ≤ n ≤ 7). The next 2 n lines each contain 2 n values; here, the jth value on the ith line represents pij . The matrix P will satisfy the constraints that pij = 1.0 − pji for all i ≠ j, and pii = 0.0 for all i. The end-of-file is denoted by a single line containing the number −1. Note that each of the matrix entries in this problem is given as a floating-point value. To avoid precision problems, make sure that you use either the double data type instead of float.

输出描述

The output file should contain a single line for each test case indicating the number of the team most likely to win. To prevent floating-point precision issues, it is guaranteed that the difference in win probability for the top two teams will be at least 0.01.

输入例子
* 2
* 0.0 0.1 0.2 0.3
* 0.9 0.0 0.4 0.5
* 0.8 0.6 0.0 0.6
* 0.7 0.5 0.4 0.0
* -1

输出例子
* 2

Hint

In the test case above, teams 1 and 2 and teams 3 and 4 play against each other in the first round; the winners of each match then play to determine the winner of the tournament. The probability that team 2 wins the tournament in this case is:

P(2 wins) 	= P(2 beats 1)P(3 beats 4)P(2 beats 3) + P(2 beats 1)P(4 beats 3)P(2 beats 4)

= p 21 p 34 p 23 + p 21 p 43 p 24

= 0.9 · 0.6 · 0.4 + 0.9 · 0.4 · 0.5 = 0.396.

The next most likely team to win is team 3, with a 0.372 probability of winning the tournament.

# 参考答案
    #include <iostream>
    #include <stdio.h>
    #include <algorithm>
    #include <string.h>
    #include <vector>

    #define cls(p) memset(p,0,sizeof(p))
    using namespace std;
    const int MAX=3e2;

    double dp[10][MAX];
    double ks[MAX][MAX];
    int N,M;

    void init()
    {
      cls(ks);
      cls(dp);
      for(int i=0;i<M+3;i++)
        dp[0][i]=1;
    }

    char s[MAX];

    int main()
    {
        while(~scanf("%d",&N))
      {
        if(N==-1) break;
        M=1<<N;
        init();
            for(int i=0;i<M;i++)
          for(int j=0;j<M;j++)
                    scanf("%lf",&ks[i][j]);
            int left,right,mid,L=1;
        for(int i=1;i<=N;i++)
        {
                for(left=0;left<M;left+=2*L)
          {
            mid=left+L;
            right=mid+L;
                    for(int k1=left;k1<mid;k1++)
              for(int k2=mid;k2<right;k2++)
              {
                            dp[i][k1]+=dp[i-1][k1]*dp[i-1][k2]*ks[k1][k2];
                            dp[i][k2]+=dp[i-1][k1]*dp[i-1][k2]*ks[k2][k1];
              }
          }
          L*=2;
        }
        int t;
                    double ans=0;
                    for(int i=0;i<M;i++) if(ans<dp[N][i])
        {
          ans=dp[N][i];
          t=i;
        }
        printf("%d\n",t+1);

      }
        return 0;
    }

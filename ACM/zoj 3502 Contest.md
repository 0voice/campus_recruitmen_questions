# 题目
Lazyman is going to join the programming contest! There are n problems in the contest. Because Lazyman is so lazy, he just tried each problem once and only once. However each problem in the contest may be not independent, it may have some relationship with other problems. So here is a propbility P n*n matrix. The jth element of the ith row is denoted by Pij . Suppose he have tried m problems, a1 ,a2 ,...am (No matter the problems are solved or not.) (1 ≤ a1 ,a2 ,...am ≤ n) If he tries the rth problems next, (r!=a1 ,a2 ,...am ) the propbility that he can solve it is the maximum value of the m + 1 values, Prr , Pa1r %, Pa2r %, ... Pamr %.

Help him to decide the order he tries the problems to make the expected number of the solved problems maximum.

Input

There are multiple test cases. The first line of input is an integer T (0 < T ≤ 100), indicating the number of test cases. Then T test cases follow. The first line of each test case is a positive integer n (0 < n ≤ 10). Then comes n lines. The jth element of the ith line is an integer Pij . (0 ≤ Pij ≤100 1 ≤ i,j ≤ n)

Output

For each test case, output 2 lines. The first line is the maxmum expected number of problems, accurated to the nearest 0.01. The second the order he should try each problems to achieve this expected number of problems. If there are several sequeces achieve the same maximum expected number, choose the lexicographically smallest one. Use capital letters to denote each problems please. (Start from A)

Sample Input
```
2
1
0
2
2 3
5 7
```
Sample Output
```
0.00
A
0.12
BA
```
Hint
```
For the 2nd sample, if the order is AB:
The probility of the result that he solves problem A is 0.02*(1-0.07)=0.0186
The probility of the result that he solves problem B is (1-0.02)*0.07=0.0686
The probility of the result that he solves problem A and B is 0.02*0.07=0.0014
So the expected number of the problem sovled is  1*0.0186+1*0.0686+2*0.0014=0.09

For the 2nd sample, if the order is BA:
The probility of the result that he solves problem A is (1-0.07)*0.05=0.0465
The probility of the result that he solves problem B is 0.07*(1-0.05)=0.0665
The probility of the result that he solves problem A and B is 0.07*0.05=0.0035
So the expected number of the problem sovled is  1*0.0465+1*0.0665+2*0.0035=0.12
```
# 参考答案
```c++
#include <algorithm>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <iomanip>
 
using namespace std;
 
#define int long long
 
#define ff first
#define ss second
#define mp make_pair
#define sqr(x) ((x)*(x))
 
typedef long long ll;
typedef pair <int, int> pie;
typedef pair <int, int> pii;
 
int n;
int mat[20][20];
pii dp[1<<15];
 
inline void main2(){
    cin >> n;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin >> mat[i][j];
    for (int i=0; i<(1<<n); i++)
        dp[i] = pii(-1,0);
    dp[0] = pii(0,0);
    for (int mask=1; mask<(1<<n); mask++){
        for (int i=0; i<n; i++) if (mask & (1<<i)){
            int maxi = 0;
            for (int j=0; j<n; j++) if (mask & (1<<j))
                maxi = max(maxi, mat[j][i]);
            dp[mask] = max(dp[mask], pii(dp[mask ^ (1<<i)].first + maxi, dp[mask ^ (1<<i)].second * 10 - i));
        }
    }
    cout << fixed << setprecision(2) << dp[(1<<n)-1].first/100.0 << endl;
    int cur = -dp[(1<<n)-1].second;
    string ret(n, 'A');
    for (int i=0; i<n; i++){
        ret[n-1-i] = char('A' + cur%10);
        cur/=10;
    }
    cout << ret << endl;
}
 
main() {
    ios::sync_with_stdio (false);
    int testCase; cin >> testCase;
    for (int o=1; o<=testCase; o++){
        main2();
    }  
    return 0;
}

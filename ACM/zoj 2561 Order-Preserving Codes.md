# 题目
Binary code is a mapping of characters of some alphabet to the set of finite length bit sequences. For example, standard ASCII code is a fixed length code, where each character is encoded using 8 bits.

Variable length codes are often used to compress texts taking into account the frequencies of occurence of different characters. Characters that occur more often get shorter codes, while characters occuring less often -- longer ones.

To ensure unique decoding of variable length codes so called prefix codes are usually used. In a prefix code no code sequence is a proper prefix of another sequence. Prefix code can be easily decoded scanning the encoded sequence from left to right, since no code is the prefix of another, one always knows where the code for the current character ends and the new character starts.

Among prefix codes, the optimal code is known, so called Huffman code. It provides the shortest possible length of the text among all prefix codes that separatly encode each character with an integer number of bits.

However, as many other codes, Huffman code does not preserve character order. That is, Huffman codes for lexicographically ordered characters are not necessarily lexicographicaly ordered.

In this problem you are asked to develop a prefix code that would be optimal for the given text among all order-preserving prefix codes. Code is called order-preserving if for any two characters the code sequence for the character that goes earlier in the alphabet is lexicographically smaller.

Since text itself is not essential for finding the code, only the number of occurences of each character is important, only this data is given.

Input:

The input consists of several test cases

For each test case, the first line contains n -- the number of characters in the alphabet (2 9). Characters are described in the alphabetical order.

Output:

For each test case, Output n bit sequences, one on a line -- the optimal order-preserving prefix code for the described text.

Sample Input:
```
5
1 8 2 3 1
```
Sample Output:
```
00
01
10
110
111
```

# 参考答案
```c++
#include<iostream>
#include<sstream>
#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<bitset>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cmath>
#include<ctime>
using namespace std;
const double eps(1e-8);
typedef long long lint;
#define clr(x) memset( x , 0 , sizeof(x) )
#define sz(v) ((int)(v).size())
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define repf(i, a, b) for (int i = (a); i <= (b); ++i)
#define repd(i, a, b) for (int i = (a); i >= (b); --i)
#define clrs( x , y ) memset( x , y , sizeof(x) )
const int Maxn = 2010;
int n;
lint f[Maxn][Maxn], sum[Maxn], x[Maxn];
int g[Maxn][Maxn];
bool v[Maxn][Maxn];
vector <int> ret[Maxn];
vector <int> tmp;

void Dfs(int l, int r) {
        if (v[l][r]) return;
        v[l][r] = true;

        if (l + 1 == r) {
            f[l][r] = sum[r] - sum[l - 1];
            g[l][r] = l;

            return;
        }
        if (l == r) {
            g[l][r] = 0;
            f[l][r] = 0;

            return;        
        }

        Dfs(l, r - 1);
        Dfs(l + 1, r);
        f[l][r] = -1;

        for (int i = g[l][r - 1]; i <= g[l + 1][r]; i ++) {
            if (i < l) continue;
            if (i > r - 1) continue;
            Dfs(l, i);
            Dfs(i + 1, r);

            if (f[l][i] + f[i + 1][r] + sum[r] - sum[l - 1] < f[l][r] || f[l][r] == -1) {
                f[l][r] = f[l][i] + f[i + 1][r] + sum[r] - sum[l - 1];
                g[l][r] = i;
            }           
        }                
}

void Search(int l, int r) {
        if (l == r) {
            ret[l] = tmp;
            return;
        }

        tmp.push_back(0);
        Search(l, g[l][r]);
        tmp.pop_back();

        tmp.push_back(1);
        Search(g[l][r] + 1, r);
        tmp.pop_back();
}

int main() {
        while (scanf("%d", &n) == 1) {
            sum[0] = 0;
            for (int i = 1; i <= n; i ++) {
                scanf("%lld", &x[i]);
                sum[i] = sum[i - 1] + x[i];
            }

            memset(v, 0, sizeof(v));
            Dfs(1, n);            

            tmp.clear();
            Search(1, n);

            for (int i = 1; i <= n; i ++) {
                for (int j = 0; j < (int)ret[i].size(); j ++)
                    printf("%d", ret[i][j]);
                printf("\n");
            }
        }

        return 0;
}

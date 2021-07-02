# 题目
The Sarcophagus itself is locked by a secret numerical code. When somebody wants to open it, he must know the code and set it exactly on the top of the Sarcophagus. A very intricate mechanism then opens the cover. If an incorrect code is entered, the tickets inside would catch fire immediately and they would have been lost forever. The code (consisting of up to 100 integers) was hidden in the Alexandrian Library but unfortunately, as you probably know, the library burned down completely.

But an almost unknown archaeologist has obtained a copy of the code something during the 18th century. He was afraid that the code could get to the "wrong people" so he has encoded the numbers in a very special way. He took a random complex number B that was greater (in absolute value) than any of the encoded numbers. Then he counted the numbers as the digits of the system with basis B. That means the sequence of numbers an, an-1, ..., a1, a0 was encoded as the number X = a0 + a1B + a2B2 + ...+ anBn.

Your goal is to decrypt the secret code, i.e. to express a given number X in the number system to the base B. In other words, given the numbers X and Byou are to determine the "digit" a0 through an.


Input

The input consists of T test cases. The number of them (T) is given on the first line of the input. Each test case consists of one single line containing four integer numbers Xr, Xi, Br, Bi (|Xr|,|Xi| <= 1000000, |Br|,|Bi| <= 16). These numbers indicate the real and complex components of numbers X and B, i.e. X = Xr + i.Xi, B = Br + i.Bi. B is the basis of the system (|B| > 1), X is the number you have to express.


Output

Your program must output a single line for each test case. The line should contain the "digits" an, an-1, ..., a1, a0, separated by commas. The following conditions must be satisfied:

for all i in {0, 1, 2, ...n}: 0 <= ai < |B|

X = a0 + a1B + a2B2 + ...+ anBn

if n > 0 then an <> 0

n <= 100

If there are no numbers meeting these criteria, output the sentence "The code cannot be decrypted.". If there are more possibilities, print any of them.


Sample Input
```
4
-935 2475 -11 -15
1 0 -3 -2
93 16 3 2
191 -192 11 -12
```

Sample Output
```
8,11,18
1
The code cannot be decrypted.
16,15
```
# 参考答案
```c++
#include <cmath>
#include <stack>
#include <cstdio>

using namespace std;

int main()
{
    int re;
    int r, i, xr, xi, br, bi, bb, b, a;

    scanf("%d", &re);
    while (re--) {
        scanf("%d%d%d%d", &xr, &xi, &br, &bi);
        bb = br * br + bi * bi;
        b = (int)(sqrt((double)bb) - 1e-6);
        stack<int> ans;
        do {
            for (a = 0; a <= b; a++) {
                r = (xr - a) * br - xi * (-bi);
                i = (xr - a) * (-bi) + xi * br;
                if (r % bb == 0 && i % bb == 0) {
                    xr = r / bb;
                    xi = i / bb;
                    ans.push(a);
                    break;
                }
            }
            if (a > b || ans.size() > 100) {
                break;
            }
        } while (xr != 0 || xi != 0);
        if (xr != 0 || xi != 0) {
            puts("The code cannot be decrypted.");
        }
        else {
            while(!ans.empty()) {
                printf("%d", ans.top());
                ans.pop();
                putchar(ans.empty() ? '\n' : ',');
            }
        }
    }

    return 0;
}


# 题目
There are two dice and there is one number on each side. The range of number is [0, 9].

Now, I want to know whether these dice are<br>
a) Same<br>
b) Reflection<br>
c) Different<br>

If two dice are both Same and Reflection, we just think they are Same.

Each Dice will be given in its stretch out view. Just like these situation, or their rotation, reflection.

![zoj_938desc_0](http://uploadfiles.nowcoder.com/probs/acm/zoj_938desc_0.jpg)

Input

First line is the number of cases. Each case gives two dice. Each one will be presented by a list of six numbers delimited with some spaces or line ends. But I promise it will always suit the situation which is given above. There are a blank line between two dice and two cases. And numbers in the same line are separated by one space.

Output

One line for each case, "Same", "Reflection" or "Different".

Sample Input
```
1
  1
2 3 4
  5
  6

  5
2 6 4
  1
  3
```
Sample Output
```
Same
```
# 参考答案
```c++
#include <cstring>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Dice {
    static int rot[6][6];

    static int opp[6];

    int a[6];

    void read() {
        static char buf[8][16];
        bool f;

        memset(buf, 0, sizeof(buf));
        for (int i = 0; gets(buf[i]) != NULL && buf[i][0] != '\0'; ++i) {
            for (int j = 0; j < 8; ++j) {
                buf[i][j] = buf[i][2 * j];
            }
        }
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                f = true;
                for (int k = 0; k < 4; ++k) {
                    if (!isdigit(buf[i][j + k])) {
                        f = false;
                        break;
                    }
                }
                if (f) {
                    for (int k = 0; k < 4; ++k) {
                        a[k] = buf[i][j + k] - '0';
                        if (isdigit(buf[i + 1][j + k])) {
                            a[4] = buf[i + 1][j + k] - '0';
                        }
                        if (isdigit(buf[i - 1][j + k])) {
                            a[5] = buf[i - 1][j + k] - '0';
                        }
                    }
                    return;
                }
            }
        }
        for (int i = 0; i < 8; ++i) {
            for (int j = i + 1; j < 8; ++j) {
                swap(buf[i][j], buf[j][i]);
            }
        }
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                f = true;
                for (int k = 0; k < 4; ++k) {
                    if (!isdigit(buf[i][j + k])) {
                        f = false;
                        break;
                    }
                }
                if (f) {
                    for (int k = 0; k < 4; ++k) {
                        a[k] = buf[i][j + k] - '0';
                        if (isdigit(buf[i + 1][j + k])) {
                            a[5] = buf[i + 1][j + k] - '0';
                        }
                        if (isdigit(buf[i - 1][j + k])) {
                            a[4] = buf[i - 1][j + k] - '0';
                        }
                    }
                    return;
                }
            }
        }
    }

    int cmp(const Dice& d) const {
        static int b[6];
        int ret = 2, s, r;

        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                b[j] = a[rot[i][j]];
            }
            for (int t = 0; t < 4; ++t) {
                s = r = 0;
                for (int j = 0; j < 6; ++j) {
                    if (b[j] == d.a[j]) {
                        ++s;
                    } else if (b[j] == d.a[opp[j]]) {
                        ++r;
                    }
                }
                if (s == 6) {
                    return 0;
                } else if (s == 4 && r == 2) {
                    ret = min(ret, 1);
                }
                s = b[0]; b[0] = b[1]; b[1] = b[2]; b[2] = b[3]; b[3] = s;
            }
        }

        return ret;
    }
} a, b;

int Dice::rot[6][6] = {
    {0, 1, 2, 3, 4, 5},
    {3, 2, 1, 0, 5, 4},
    {5, 1, 4, 3, 0, 2},
    {3, 4, 1, 5, 2, 0},
    {0, 5, 2, 4, 1, 3},
    {4, 2, 5, 0, 3, 1}
};

int Dice::opp[6] = {
    2, 3, 0, 1, 5, 4
};

int main() {
    int re;
    const char *s[3] = {"Same", "Reflection", "Different"};

    scanf("%d", &re);
    while (getchar() != '\n');
    for (int ri = 1; ri <= re; ++ri) {
        a.read();
        b.read();
        puts(s[a.cmp(b)]);
    }

    return 0;
}




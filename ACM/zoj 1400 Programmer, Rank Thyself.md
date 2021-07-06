# 题目
Implement a ranking program similar to the one used for this programming contest.
The input file contains one or more contests followed by a line containing only zero that signals the end of the file. Each contest begins with a line containing a positive integer c no greater than 20 indicating the number of teams in the contest, and is followed by c lines that contain a team name and the solution times for seven problems, separated by spaces. Team names consist of between one and ten letters. All team names within a contest are unique. Times are nonnegative integers no greater than 500.

As described in the Notes to Teams, teams are ranked first by greatest number of problems solved, then by least total time, then by least geometric mean of all nonzero times. Teams that are still tied are given the same numeric ranking and are listed in alphabetical order, using case-sensitive string comparison. The numeric ranking for a team is always one more than the number of teams ranked ahead of (not tied with) that team. For this problem all geometric means will be rounded to an integer as described below, and only the rounded value will be used when computing rankings and displaying results.

If all times are zero, then the geometric mean is also zero. Otherwise, if there are n nonzero times t1, ..., tn, then the geometric mean is defined to be

```
exp ((ln t1 + ln t2 + ... + ln tn) / n)
```

where exp x means ex and ln x means the natural logarithm of x. (There are other mathematically equivalent definitions of the geometric mean, but they may produce slightly different answers due to roundoff and/or overflow problems. Use this definition to get the same answers as the judges.) After computing the geometric mean, round it to an integer by adding 0.5 and truncating any fractional digits. (C/C++ and Java automatically truncate fractions when casting a floating-point type to an integral type. In Pascal use the trunc function.)

For each contest you must output the rankings in a table. All tables will have the same width, with the length equal to the number of teams entered in the contest. Use the exact format shown in the examples. Each contest has a numbered header followed by a table with one team entry per line. Each entry contains the ranking, team name, problems solved, total time, geometric mean, and then the individual solution times in the same order they appeared in the input. In the first example all values completely fill their fields. In general you may need to pad values with spaces (never tabs) so that they have the correct field width. The team name is left-justified, and all other fields are right-justified. The ranking always has two digits, including a leading zero if necessary. Spaces will never appear at the beginning or end of lines.


Sample Input
```
1
Plutonians 123 234 345 456 167 278 389
4
Xap 0 0 0 0 0 0 0
Foo 20 30 0 50 40 0 10
Bar 0 50 20 0 10 40 30
Baz 0 0 0 0 0 0 0
3
Venus 213 0 0 57 0 0 0
Neptune 0 0 0 117 153 0 0
Mars 0 150 0 0 0 0 120
0
```

Sample Output
```
CONTEST 1
01 Plutonians 7 1992 261 123 234 345 456 167 278 389
CONTEST 2
01 Bar        5  150  26   0  50  20   0  10  40  30
01 Foo        5  150  26  20  30   0  50  40   0  10
03 Baz        0    0   0   0   0   0   0   0   0   0
03 Xap        0    0   0   0   0   0   0   0   0   0
CONTEST 3
01 Venus      2  270 110 213   0   0  57   0   0   0
02 Mars       2  270 134   0 150   0   0   0   0 120
02 Neptune    2  270 134   0   0   0 117 153   0   0
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
struct rank {
    char name[12];
    int sol, tot, g, p[7], ind;
};
rank ranks[25];

int comp(const void *c, const void *d)
{
    rank *a = (rank *)c;
    rank *b = (rank *)d;
    if(a->sol > b->sol) return -1;
    else if(a->sol < b->sol) return 1;
    else {
        if(a->tot < b->tot) return -1;
        else if(a->tot > b->tot) return 1;
        else {
            if(a->g < b->g) return -1;
            else if(a->g > b->g) return 1;
            else {
                return strcmp(a->name, b->name);
            }
        }
    }

}

int main()
{
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    int n = 0, cnt = 1;
    while(scanf("%d", &n)) {
        if(!n) break;
        for(int i = 0; i < n; i++) {
            double t = 0;
            ranks[i].sol = 0, ranks[i].tot = 0, ranks[i].g = 0;
            scanf("%s", &ranks[i].name);
            for(int j = 0; j < 7; j++) {
                scanf("%d", &ranks[i].p[j]);
                if(ranks[i].p[j]) {
                    ranks[i].sol++;
                    ranks[i].tot += ranks[i].p[j];
                    t += log((double)ranks[i].p[j]);
                }
            }
            if(ranks[i].sol > 0) {
                ranks[i].g = exp(t/ranks[i].sol) + 0.5;
            }
        }
        qsort(ranks, n, sizeof(rank), comp);
        printf("CONTEST %d\n", cnt);
        cnt++;
        for(int i = 0; i < n; i++) {
            if(i < 9) {
                printf("0");
            }
            if(i > 0 && ranks[i].sol == ranks[i-1].sol && ranks[i].tot == ranks[i-1].tot && ranks[i].g == ranks[i-1].g) {
                ranks[i].ind = ranks[i-1].ind;
            }
            else {
                ranks[i].ind = i + 1;
            }
            printf("%d %-10s %d %4d %3d %3d %3d %3d %3d %3d %3d %3d\n", ranks[i].ind, ranks[i].name, ranks[i].sol, ranks[i].tot, ranks[i].g,
                   ranks[i].p[0], ranks[i].p[1], ranks[i].p[2], ranks[i].p[3], ranks[i].p[4], ranks[i].p[5], ranks[i].p[6]);

        }

    }
    return 0;
}

# 题目
Few weeks ago, a famous software company has upgraded its instant messaging software. A ranking system was released for user groups. Each member of a group has a level placed near his nickname. The level shows the degree of activity of a member in the group.

Each member has a score based his behaviors in the group. The level is determined by this method:
Level | Percentage  | The number of members in this level
----- | ----------  | -----------------------------------
LV1 | /	| All members whose score is zero
LV2	|/	|All members who can not reach level 3 or higher but has a positive score
LV3	|30%|	⌊(The number of members with a positive score) * 30%⌋
LV4	|20%|	⌊(The number of members with a positive score) * 20%⌋
LV5	|7%|	⌊(The number of members with a positive score) * 7%⌋
LV6	|3%|	⌊(The number of members with a positive score) * 3%⌋

⌊<var>x</var>⌋ is the maximum integer which is less than or equal to <var>x</var>.
 
 The member with the higher score will get the higher level. If two members have the same score, the earlier one who joined the group will get the higher level. If there is still a tie, the user with smaller ID will get the higher level.
Please write a program to calculate the level for each member in a group.

Input

There are multiple test cases. The first line of input is an integer <var>T</var> indicating the number of test cases. For each test case:

The first line contains an integer <var>N</var> (1 <= <var>N</var> <= 2000) indicating the number of members in a group.

The next <var>N</var> lines, each line contains three parts (separated by a space):

The ID of the i-th member <var>Ai</var> (0 <= <var>Ai</var> <= 1000000000). The ID of each member is unique.
The date of the i-th member joined the group, in the format of YYYY/MM/DD. The date will be in the range of [1900/01/01, 2014/04/06].
The score <var>Si</var> (0 <= <var>Si</var> <= 9999) of the i-th member.

Output

For each test case, output <var>N</var> lines. Each line contains a string represents the level of the i-th member.

Sample Input
* 1
* 5
* 123456 2011/03/11 308
* 123457 2011/03/12 308
* 333333 2012/03/18 4
* 555555 2014/02/11 0
* 278999 2011/03/18 308

Sample Output

* LV3
* LV2
* LV2
* LV1
* LV2

# 参考答案
    #include <iostream>
    #include <map>
    #include <stdio.h>
    #include <algorithm>

    using namespace std;

    const int MAX_N = 2000 + 100;
    int n, T, cnt;
    struct Rank
    {
        int ymd;
        int score;
        int id;
        string lv;
    };
    int y, m, d, id, score;
    Rank r[MAX_N];
    int a[MAX_N];
    int cmp(int m, int n)
    {
        if(r[m].score != r[n].score)
            return r[m].score > r[n].score;
        else if(r[m].score == r[n].score)
        {
            if(r[m].ymd != r[n].ymd)
                return r[m].ymd < r[n].ymd;
            else if(r[m].ymd == r[n].ymd)
                return r[m].id < r[n].id;
        }
    }
    int lv[6];

    int main()
    {
        scanf("%d", &T);
        while(T--)
        {
            scanf("%d", &n);
            int cnt = 0;
            for(int i = 0; i < n; i++)
            {
                scanf("%d %d/%d/%d %d", &r[i].id, &y, &m, &d, &r[i].score);
                r[i].ymd = y * 10000 + m * 100 + d;
                a[i] = i;
                if(r[i].score != 0)
                    cnt++;
            }
            sort(a, a + n, cmp);
            lv[6] = (int)(cnt * 0.03);
            lv[5] = (int)(cnt * 0.07);
            lv[4] = (int)(cnt * 0.2);
            lv[3] = (int)(cnt * 0.3);
            lv[2] = cnt - lv[6] - lv[5] - lv[4] - lv[3];
            lv[1] = n - cnt;
            for(int i = 0; i < n; i++)
            {
                if(lv[6] != 0)
                {
                    r[a[i]].lv = "LV6";
                    lv[6]--;
                }
                else if(lv[5] != 0)
                {
                    r[a[i]].lv = "LV5";
                    lv[5]--;
                }
                else if(lv[4] != 0)
                {
                    r[a[i]].lv = "LV4";
                    lv[4]--;
                }
                else if(lv[3] != 0)
                {
                    r[a[i]].lv = "LV3";
                    lv[3]--;
                }
                else if(lv[2] != 0)
                {
                    r[a[i]].lv = "LV2";
                    lv[2]--;
                }
                else
                    r[a[i]].lv = "LV1";
            }
            for(int i = 0; i < n; i++)
                cout << r[i].lv << endl;
        }
        return 0;
    }

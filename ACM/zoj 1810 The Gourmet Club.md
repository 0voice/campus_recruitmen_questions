# 题目
The gourmet club of ACM City has 16 members. They contracted the proprietor of the local French restaurant Chateau Java to arrange dinner parties for 5 consecutive evenings. They asked to be seated around 4 tables, 4 persons per table. They also stipulated that during the 5 evenings, every member of the club will share a table exactly once with each member of the club. Mr. I.B. Emm, the restaurateur, assigned his Maitre D' the task of scheduling the seating for the 5 evenings. On the first evening, the Maitre D' seated the members as they arrived and recorded their seating. Each subsequent evening, he carefully planned the seating to match the requirement that no member will be dining twice with some other member. Unfortunately, the Maitre D' disappeared on the morning of the fourth evening. Mr. Emm was left only with his notes which included the recorded seating arrangements during the previous 3 evenings. As he was trying to schedule the seating for the remaining evenings, it dawned on him that this task may not be that easy. He is asking for your help to try and see whether the remaining two evenings can be scheduled. The following is a sample of the Maitre D's seating arrangements during the first 3 evenings:
```
ABCD EFGH IJKL MNOP
AEIM BFJN CGKO DHLP
AFKP BGLM CHIN DEJO
```
The members of the gourmet club were identified by the letters A,B,C,...,P.

Each line represents one evening of seating with each set of four letters a single table. Thus on the first evening A dines with B, C and D etc. Write a program that will read from the input file the seating arrangement of the first three evenings and will either complete the schedule or determine that the Maitre D' screwed up.


Input

Each data set will be 3 lines. Each line will consist of four blocks, each 4 letters long. All letters will be in upper case. Blocks will be separated by "white space". Data sets will be separated by blank lines.


Output

For a successful schedule, echo the input and add two lines showing the successful schedule. If it is not possible to complete the schedule, do not echo the input, but print "It is not possible to complete this schedule." Separate output for each data set with a blank line.


Sample Input
```
ABCD EFGH IJKL MNOP
AEIM BFJN CGKO DHLP
AFKP BGLM CHIN DEJO
```

Sample Output

It is not possible to complete this schedule.
# 参考答案
```c++
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std; 
const int N = 25;
char str[N][N];
int g[N][N], sn, tmp[N], tn;

void build(int i) {
	for (int j = 0; j < 4; j++)
		for (int k = 0; k < 4; k++)
			g[str[i][j] - 'A'][str[i][k] - 'A'] = g[str[i][k] - 'A'][str[i][j] - 'A'] = 1;
}

bool check1(int i, int j) {
	int num = 0;
	if (g[j][i]) return false;
	for (int k = 0; k < 16; k++)
		if (g[i][k] + g[j][k] == 0) {
			str[12][num + 2] = k + 'A';
			num++;
		}
	return num == 2;
}

bool check2(int num) {
	tn = 0;
	for (int i = 0; i < 16; i++) {
		if (g[num][i]) continue;
		tmp[tn++] = i;
	}
	return tn == 3;
}

bool solve() {
	int i;
	for (i = 1; i < 16; i++) {
		if (g[0][i]) continue;
		if (!check1(0, i)) return false;
		str[12][0] = 'A'; str[12][1] = i + 'A';
		build(sn); sn++;
		break;
	}
	for (i = 0; i < 4; i++) {
		if (!check2(str[12][i] - 'A')) return false;
		str[16 + i][0] = str[12][i];
		for (int j = 0; j < tn; j++)
			str[16 + i][1 + j] = tmp[j] + 'A';
		build(16 + i);
		sn++;
	}
	for (i = 1; i < 4; i++) {
		if (!check2(str[16][i] - 'A')) return false;
		str[12 + i][0] = str[16][i];
		for (int j = 0; j < tn; j++)
			str[12 + i][1 + j] = tmp[j] + 'A';
		build(12 + i);
		sn++;
	}
	return true;
}

int main() {
	int bo = 0, i;
	memset(str, 0, sizeof(str));
	while (~scanf("%s", str[0])) {
		memset(g, 0, sizeof(g));
		for (i = 0; i < 16; i++)
			g[i][i] = 1;
		build(0); sn = 12;
		for (i = 1; i < 12; i++) {
			scanf("%s", str[i]);
			build(i);
		}
		if (!solve()) printf("It is not possible to complete this schedule.\n");
		else {
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 4; j++)
					printf("%c", str[i][j]);
				if ((i + 1) % 4 == 0)
					printf("\n");
				else printf("\t");
			}
		}
		printf("\n");
	}
	return 0;
}





/*
题目:
小蒜头又调皮了。这一次，姐姐的实验报告惨遭毒手。
姐姐的实验报告上原本记录着从 1 到 n 的序列，任意两个数字间用空格间隔。但是“坑姐”的蒜头居然把数字间的空格都给删掉了，整个数字序列变成一个长度为 1 到 100 的且首部没有空格的数字串。
现在姐姐已经怒了，蒜头找你写个程序快点把试验数据复原。
输入<br>
输入文件有一行，为一个字符串——被蒜头搞乱的实验数据。
字符串的长度在 1 到 100 之间。
输出
输出共一行，为姐姐的原始测试数据—— 1 到 n 的输出。
任意两个数据之间有一个空格。
如果有多组符合要求的正确解，输出其中任意一组即可。
样例1
输入：
4111109876532
输出：
4 1 11 10 9 8 7 6 5 3 2

思路:
因为字符串的长度不超过100，可以计算出 n 最大是 54，我们只需要枚举一位数和两位数。先通过字符串的长度计算出 n，开一个数组标记枚举过的数，只有没标记过的数并且小于等于 n 才会存下来继续往后搜。
*/

#include <iostream>
#include <algorithm>
#include <memory.h>
#include <vector>
#include <cstdio>
using namespace std;
char s[105];
int flag[105];
int visited[105];
vector<int> loc[60];
int ok = 0, len, maxnum;
void dfs(int num)
{
	if (num == 0)
	{
		ok = 1;
		int i = 0;
		do {
			printf("%c", s[i]);
			i++;
		} while (flag[i] != 1);

		while (i < len)
		{
			printf(" ");
			do {
				printf("%c", s[i]);
				i++;
			} while (flag[i] != 1);
		}
		printf("\n");
		return;
	}
	for (int i = 0; i < loc[num].size(); i++)
	{
		if (num < 10)
		{
			if (visited[loc[num][i]] == 0)
			{
				visited[loc[num][i]] = 1;
				flag[loc[num][i]] = 1;
				dfs(num - 1);
				if (ok)return;
				visited[loc[num][i]] = 0;
				flag[loc[num][i]] = 0;
			}

		}
		else
		{
			if (visited[loc[num][i]] == 0 && visited[loc[num][i] + 1] == 0)
			{
				visited[loc[num][i]] = 1;
				visited[loc[num][i] + 1] = 1;
				flag[loc[num][i]] = 1;
				dfs(num - 1);
				if (ok)return;
				visited[loc[num][i]] = 0;
				visited[loc[num][i] + 1] = 0;
				flag[loc[num][i]] = 0;
			}
		}
	}
}

int main()
{
	while (scanf("%s", s) != EOF)
	{
		ok = 0;
		// printf("%s\n", s);
		memset(visited, 0, sizeof(visited));
		memset(flag, 0, sizeof(flag));
		len = strlen(s);
		if (len <= 9)
			maxnum = len;
		else
			maxnum = (len - 9) / 2 + 9;
		// printf("%d\n", maxnum);
		for (int i = 1; i <= maxnum; i++)
		{
			loc[i].clear();
			if (i < 10) {
				for (int j = 0; j < len; j++) {
					if (int(s[j] - '0') == i)
						loc[i].push_back(j);
				}
			}
			else {
				for (int j = 0; j < len; j++) {
					if (j + 1 < len && int(s[j] - '0') * 10 + int(s[j + 1] - '0') == i)
						loc[i].push_back(j);
				}
			}
		}
		dfs(maxnum);
		memset(s, 0, sizeof(s));
	}
}


  

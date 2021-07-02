# 题目
Digital deletions is a two-player game. The rule of the game is as following.

Begin by writing down a string of digits (numbers) that's as long or as short as you like. The digits can be 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 and appear in any combinations that you like. You don't have to use them all. Here is an example:

![zoj_1104desc_1](http://uploadfiles.nowcoder.com/probs/acm/zoj_1104desc_1.jpg)

On a turn a player may either:<br>
Change any one of the digits to a value less than the number that it is. (No negative numbers are allowed.) For example, you could change a 5 into a 4, 3, 2, 1, or 0.<br>
Erase a zero and all the digits to the right of it.<br>

The player who removes the last digit wins.

The game that begins with the string of numbers above could proceed like this:

![zoj_1104desc_0](http://uploadfiles.nowcoder.com/probs/acm/zoj_1104desc_0.jpg)

Now, given a initial string, try to determine can the first player win if the two players play optimally both.

Input

The input consists of several test cases. For each case, there is a string in one line.

The length of string will be in the range of [1,6]. The string contains only digit characters.

Proceed to the end of file.

Output

Output Yes in a line if the first player can win the game, otherwise output No.

Sample Input
```
0
00
1
20
```
Sample Output
```
Yes
Yes
No
No
```

# 参考答案
```c++
#include <cstdlib> 
#include <cctype> 
#include <cstring> 
#include <cstdio> 
#include <cmath> 
#include <algorithm> 
#include <vector> 
#include <string> 
#include <iostream> 
#include <sstream> 
#include <map> 
#include <set> 
#include <queue> 
#include <stack> 
#include <numeric> 
#include <iomanip> 
#include <bitset> 
#include <list> 
#include <stdexcept> 
#include <functional> 
#include <utility> 
#include <ctime>
using namespace std;
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MEM(a,b) memset((a),(b),sizeof(a))
#define BLANK(a) for(int i = 0; i < (a); i ++) printf(" ")
const int N = 1000000;
int a[N];

void init()
{
	MEM(a,0);
	for(int i = 1; i < N; i++)
	{
		if(a[i]) continue;
		for(int j = 1; j <= i; j*=10)
		{
			int t = i/j%10;
			t = 9-t;
			for(int k = 1; k <= t; k++)
			{
				a[i+k*j] = 1;
			}
		}
		int n = i;
		for(int j = 10; n*j < N; j*=10)
		{
			for(int k = 0; k < j/10; k++)
			{
				a[n*j+k] = 1;
			}
		}
	}
}

int main()
{
	char c[10];
	init();
	while(scanf("%s",c)!=EOF)
	{
		if(c[0] == '0') 
		{
			puts("Yes");
			continue;
		}
		int n;
		sscanf(c,"%d",&n);
		if(a[n]) puts("Yes");
		else puts("No");
	}	
 return 0;
}





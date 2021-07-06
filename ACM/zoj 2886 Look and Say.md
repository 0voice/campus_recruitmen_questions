# 题目
The look and say sequence is defined as follows. Start with any string of digits as the first element in the sequence. Each subsequent element is defined from the previous one by "verbally" describing the previous element. For example, the string 122344111 can be described as "one 1, two 2's, one 3, two 4's, three 1's". Therefore, the element that comes after 122344111 in the sequence is 1122132431. Similarly, the string 101 comes after 1111111111. Notice that it is generally not possible to uniquely identify the previous element of a particular element. For example, a string of 112213243 1's also yields 1122132431 as the next element.

Input

The input consists of a number of cases. The first line gives the number of cases to follow. Each case consists of a line of up to 1000 digits.

Output

For each test case, print the string that follows the given string.

Sample Input
```
3
122344111
1111111111
12345
```
Sample Output
```
1122132431
101
1112131415
```
# 参考答案
```c++
#include "iostream"
#include "string.h"
#include "stdio.h"
using namespace std;

int main()
{
	int TestCase;
	cin >> TestCase;
	while (TestCase--)
	{
		string str;
		char first;
		int length, count = 0;
		cin >> str;
		length = str.size();
		first = str[0];
		for (int i = 0; i < length; i++)
		{
			if (str[i] == first)
			{
				count++;
				if (i == length - 1)
					printf("%d%c", count, first);
			}
			else
			{
				printf("%d%c", count, first);
				first = str[i];
				count = 1;
				if (i == length - 1)
					printf("%d%c", count, first);
			}
		}
		cout << endl;
	}
}

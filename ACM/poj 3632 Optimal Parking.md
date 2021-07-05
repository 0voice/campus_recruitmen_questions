# 题目
When shopping on Long Street, Michael usually parks his car at some random location, and then walks to the stores he needs. Can you help Michael choose a place to park which minimises the distance he needs to walk on his shopping round? Long Street is a straight line, where all positions are integer. You pay for parking in a specific slot, which is an integer position on Long Street. Michael does not want to pay for more than one parking though. He is very strong, and does not mind carrying all the bags around.

输入描述

The first line of input gives the number of test cases, 1 ≤ t ≤ 100. There are two lines for each test case. The first gives the number of stores Michael wants to visit, 1 ≤ n ≤ 20, and the second gives their n integer positions on Long Street, 0 ≤ x<sub>i</sub> ≤ 99.

输出描述

Output for each test case a line with the minimal distance Michael must walk given optimal parking.

输入例子
```
2
4
24 13 89 37
6
7 30 41 14 39 42
```
输出例子
```
152
70
```
# 参考答案
```c++
#include <cstdio>
using namespace std;
int main(){
	int nCase;
	scanf("%d",&nCase);
	while(nCase--){
		int max=0,min=200,n,a;
		scanf("%d",&n);
		while(n--){
			scanf("%d",&a);
			if(a>max)max=a;
			if(a<min)min=a;	
		}
		printf("%d\n",2*(max-min));
	}
	return 0;
}




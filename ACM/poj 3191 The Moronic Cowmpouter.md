# 题目
Inexperienced in the digital arts, the cows tried to build a calculating engine (yes, it's a cowmpouter) using binary numbers (base 2) but instead built one based on base negative 2! They were quite pleased since numbers expressed in base −2 do not have a sign bit.

You know number bases have place values that start at 1 (base to the 0 power) and proceed right-to-left to base^1, base^2, and so on. In base −2, the place values are 1, −2, 4, −8, 16, −32, ... (reading from right to left). Thus, counting from 1 goes like this: 1, 110, 111, 100, 101, 11010, 11011, 11000, 11001, and so on.

Eerily, negative numbers are also represented with 1's and 0's but no sign. Consider counting from −1 downward: 11, 10, 1101, 1100, 1111, and so on.

Please help the cows convert ordinary decimal integers (range -2,000,000,000..2,000,000,000) to their counterpart representation in base −2.

输入描述

Line 1: A single integer to be converted to base −2

输出描述

Line 1: A single integer with no leading zeroes that is the input integer converted to base −2. The value 0 is expressed as 0, with exactly one 0.

输入例子
```
-13
```
输出例子
```
110111
```
Hint

Explanation of the sample:

Reading from right-to-left:

1*1 + 1*-2 + 1*4 + 0*-8 +1*16 + 1*-32 = -13
# 参考答案
```c++
#include <iostream>
using namespace std;
int a[64];
int main()
{
	int cnt=0,n;
	scanf("%d",&n);	
	while(n){
		int x=n/-2;
		int y=n%-2;
		if(y<0){
			y+=2;
			x+=1;
		}
		a[++cnt]=y;			
		n=x;
	}
	if(cnt==0)
		printf("0");
	else{
		for(int i=cnt;i>=1;--i)
			printf("%d",a[i]);
	}
	return 0;	
}




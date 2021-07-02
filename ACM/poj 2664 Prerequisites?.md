# 题目
Freddie the frosh has chosen to take k courses. To meet the degree requirements, he must take courses from each of several categories. Can you assure Freddie that he will graduate, based on his course selection?

输入描述

Input consists of several test cases. For each case, the first line of input cont

输出描述

For each test case, output a line containing "yes" if Freddie's course selection meets the degree requirements; otherwise output "no".

输入例子
```
3 2
0123 9876 2222
2 1 8888 2222
3 2 9876 2222 7654 
3 2
0123 9876 2222
2 2 8888 2222
3 2 7654 9876 2222
0
```
输出例子
```
yes
no
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>

int main()
{
	int i,j,r,c;
	int k,m,a,b,flag;
	int map[10000];

	while(scanf("%d",&k)!=EOF,k)
	{
		memset(map,0,sizeof map);
		scanf("%d",&m);
		for(i=0;i<k;i++)
		{
			scanf("%d",&a);
			map[a]++;
		}
		flag=1;
		int count;
		for(i=0;i<m;i++)
		{
			scanf("%d %d",&r,&c);
			count=0;
			for(j=0;j<r;j++)
			{
				scanf("%d",&b);
				if(map[b]>0)//娌￠�
					count++;
			}
			if(count<c)
				flag=0;
		}
		if(flag==0)
			puts("no");
		else
			puts("yes");
	}

return 0;
}




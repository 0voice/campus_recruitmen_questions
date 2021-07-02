# 题目
As you know, writing programs is often far from being easy. Things become even harder if your programs have to be as fast as possible. And sometimes there is reason for them to be. Many large programs such as operating systems or databases have "bottlenecks" - segments of code that get executed over and over again, and make up for a large portion of the total running time. Here it usually pays to rewrite that code portion in assembly language, since even small gains in running time will matter a lot if the code is executed billions of times.

In this problem we will consider the task of automating the generation of optimal assembly code. Given a function (as a series of input/output pairs), you are to come up with the shortest assembly program that computes this function.

The programs you produce will have to run on a stack based machine, that supports only five commands: ADD, SUB, MUL, DIV and DUP. The first four commands pop the two top elements from the stack and push their sum, difference, product or integer quotient , respectively, on the stack. The DUP command pushes an additional copy of the top-most stack element on the stack.

So if the commands are applied to a stack with the two top elements a and b (shown to the left), the resulting stacks look as follows:

![poj_3329desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_3329desc_0.jpg)

At the beginning of the execution of a program, the stack will contain a single integer only: the input. At the end of the computation, the stack must also contain only one integer; this number is the result of the computation.

There are three cases in which the stack machine enters an error state:

A DIV-command is executed, and the top-most element of the stack is 0.

A ADD, SUB, MUL or DIV-command is executed when the stack contains only one element.

An operation produces a value greater than 30000 in absolute value.


输入描述
The input consists of a series of function descriptions. Each description starts with a line containing a single integer n (n<br>
The input is terminated by a test case starting with n = 0. This test case should not be processed.<br>
输出描述<br>
You are to find the shortest program that computes a function f , such that f(xi) = yi for all 1<br>
For each function description, output first the number of the description. Then print out the se- quence of commands that make up the shortest program to compute the given function. If there is more than one such program, print the lexicographically smallest. If there is no program of at most 10 statements that computes the function, print the string `` Impossible''. If the shortest program consists of zero commands, print ``Empty Sequence''.

Output a blank line after each test case.<br>
输入例子
```
4
1 2 3 4
0 -2 -6 -12
3
1 2 3
1 11 1998
1
1998
1998
0
```
输出例子
```
Program 1
DUP DUP MUL SUB

Program 2
Impossible

Program 3
Empty sequence
```
# 参考答案
```c++
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;
#define MAXV 30000
#define INF 999999
#define MAXN 11
#define MAXS 11
#define ADD 1
#define DIV 2
#define DUP 3
#define MUL 4
#define SUB 5
int S[MAXN][MAXS],atop[MAXN],y[MAXN];
int N,A[MAXN],CA[MAXN],minlen,mCount=1;

void Print(int c)
{
	switch(c)
	{
	case ADD:
		printf("ADD");
		break;
	case SUB:
		printf("SUB");
		break;
	case MUL:
		printf("MUL");
		break;
	case DUP:
		printf("DUP");
		break;
	case DIV:
		printf("DIV");
		break;
	}
}

void dfs(int len)
{
int i,j,a[MAXN],b[MAXN];
	if(len-1<minlen)
	{
		for(j=0;j<N;j++)
			if(S[j][0]!=y[j]||atop[j]!=0) break;
		if(j==N)
		{
			minlen=len-1;
			memcpy(A,CA,sizeof(A));
		}
	}
	if(len>minlen||len>10)
		return;
	for(i=1;i<=5;i++)
	{
		int con=-1; bool LastOneChanged=false;
		for(j=0;j<N&&con==-1;j++)
		{
			if(i!=DUP)
			{
				if(atop[j]==0)
				{
					con=j;
					break;
				}
				if(i==DIV&&S[j][atop[j]]==0)
				{
					con=j;
					break;
				}
				b[j]=S[j][atop[j]--];
				a[j]=S[j][atop[j]--];	
				switch(i)
				{
				case ADD:
					S[j][++atop[j]]=a[j]+b[j];
					break;
				case DIV:
					S[j][++atop[j]]=a[j]/b[j];
					break;
				case MUL:
					S[j][++atop[j]]=a[j]*b[j];
					break;
				case SUB:
					S[j][++atop[j]]=a[j]-b[j];
					break;
				}
				CA[len]=i;
				if(abs(S[j][atop[j]])>MAXV)
				{
					LastOneChanged=true;
					con=j;
					break;
				}
			}else{
				atop[j]++;
				S[j][atop[j]]=S[j][atop[j]-1];
				CA[len]=DUP;		
			}
		}
		if(con==-1)
			dfs(len+1);
		if(i!=DUP)
			for(j=0;j<N&&(con==-1||((LastOneChanged==false&&j<con)||(LastOneChanged==true&&j<=con)));j++)
			{
				S[j][atop[j]]=a[j];
				S[j][++atop[j]]=b[j];
			}
		else
			for(j=0;j<N&&(con==-1||((LastOneChanged==false&&j<con)||(LastOneChanged==true&&j<=con)));j++)
				atop[j]--;
	}
}

int main()
{
	int i;
	while(scanf("%d",&N)&&N)
	{
		for(i=0;i<N;i++)
			scanf("%d",&S[i][0]);
		for(i=0;i<N;i++)
			scanf("%d",&y[i]);
		memset(atop,0,sizeof(atop)); minlen=INF;
		dfs(1);
		printf("Program %d\n",mCount++);
		if(minlen==INF)
			printf("Impossible\n\n");
		else if(minlen==0)
			printf("Empty sequence\n\n");
		else
		{
			Print(A[1]);
			for(i=2;i<=minlen;i++)
			{
				printf(" "); Print(A[i]);
			}
			printf("\n\n");
		}
	}
	return 0;
}





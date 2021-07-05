# 题目
The author of an elementary school algebra text book has approached you to write a program to solve simple algebra equations. The author wants to use a program to avoid human errors in preparing the solutions manual. The text book author will provide a text file of the simple problems for your problem to solve. All of the problems will be in the form of an algebraic equality. The specific syntax of the problems will be an algebraic statement consisting of integer constants and the four basic arithmetic operators, an equal sign, and a variable. For example:

12 - 4 * 3 = x

For the solutions manual the problem is not just to be solved, but solved one step at a time. For the above input line, the corresponding output would be:

12 - 4 * 3 = x<br>
12 - 12 = x<br>
0 = x<br>

The simple problems your program is to solve are limited to integer values with multiplication, division, addition and subtraction operations. Note that, as in the above example, the computation must follow the standard order of precedence for arithmetic operations. All multiplications and divisions are performed, from left to right, before any additions and subtractions, and then all additions and subtractions are performed from left to right. You may assume that all divisions will result in integer values.

输入描述

The input will consist of several equations to be solved. Each equation will contain from 1 to 20 operations with 2 to 21 integer operands (there will, of course, always be one more operand than operators). Integer operators in the input may have a leading sign (i.e. may be preceded by a unary operator). Spaces in the input line are optional; that is, spaces may be present between operators and operands, or they may not. The variable names will consist of 1 to 8 alphabetic characters.

输出描述

Output for a problem should begin with the problem to be solved, then followed by one line of output after each operation. The spacing between the numbers and operations in the output is not critical. Having the correct answers and all the correct steps in the output is important.

A typical input will consist of multiple algebraic problems, each on a separate line. The output for each input problem should be separated by a single blank line in the output. The end of the file marks the end of the input.

输入例子
```
3 * 4 + 4 - 1 / 1 = xyzzy
12 + 2 * 12 / 2 - 1 = y
2 * -3 + -6 - +4 = r
2*-3+-6-+4=r
```
输出例子
```
3 * 4 + 4 - 1 / 1 = xyzzy
12 + 4 - 1 / 1 = xyzzy
12 + 4 - 1 = xyzzy
16 - 1 = xyzzy
15 = xyzzy

12 + 2 * 12 / 2 - 1 = y
12 + 24 / 2 - 1 = y
12 + 12 - 1 = y
24 - 1 = y
23 = y

2 * -3 + -6 - 4 = r
-6 + -6 - 4 = r
-12 - 4 = r
-16 = r

2 * -3 + -6 - 4 = r
-6 + -6 - 4 = r
-12 - 4 = r
-16 = r
```
# 参考答案
```c++
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 100005;
string expression;
char ex[N];
int values[N];
string lefts;
string rights;
char oper[N];
int sign[N];
int lval;
int lop;

void handle()
{
	int len = expression.length();
	int flag = 1;
	int ans = 0;
    rights = "";
	lval = 0;
	lop = 0;
	int ishavenum = 0;
	memset(sign,0,sizeof(sign));

	for(int i=0; i<len; i++)
	{
		if(expression[i] >= '0' && expression[i] <= '9')
		{
			ans = ans * 10 + expression[i] - '0';
			ishavenum = 1;
			flag = 0;
		}
		else if(expression[i] == ' ')
		{
			if(ishavenum)
			{
				values[lval] = (sign[lval] == -1)?-ans:ans;
				lval++;
			}
			ans = 0;
			//flag = 0;
			ishavenum = 0;
			//
		}
		else if(expression[i] == '=')
		{   
			if(ishavenum)
			{
				values[lval] = (sign[lval] == -1)?-ans:ans;
				lval++;
			}
			ans = 0;
			flag = 0;
			ishavenum = 0;

			rights = "= ";
			for(int j = i+1; j<len; j++)
				if(expression[j] == ' ') continue;
				else rights += expression[j];
			i = len;
		}
		else
		{
			if(ishavenum) 
			{
				if(ishavenum) values[lval] = (sign[lval] == -1)?-ans:ans;
				lval++;
				ans = 0;
				flag = 0;
				ishavenum = 0;
			}

			if(flag)
			{
				if(expression[i] == '+')
					sign[lval] = 1;
				else sign[lval] = -1;
				flag = 0;
			}
			else
			{
				oper[lop++] = expression[i];
				flag = 1;
			}
		}

	}
}

void Print(string l,int i,int preres)
{
    cout<<l;
	cout<<preres<<" ";

	for(int j = i+1; j<lop; j++)
	{
		cout<< oper[j]<<" ";
		//if(sign[j+1] == 1) cout<<"+";
		cout<<values[j+1]<<" ";
	}
	cout<<rights<<endl;
}
string convert(int num)
{
	string res = "";
	if(num < 0 ) {res = "-" ; num = -num;}
	int temp[N];
	int l = 0;
	if(num == 0) res = "0";
	while(num)
	{
		temp[l++] = num%10;
		num /= 10;
	}
	for(int i=l-1;i>=0;i--)
		res += temp[i]+'0';
	return res;
}
void printmulAndDiv()
{
	int pre = -2;
	int rlval = 0;
	int rlop = 0;
	int preres = 0;
	string l = "";

	for(int i=0; i< lop; i++)
	{
		if(oper[i] == '*')
		{
			if( pre == i-1)
			{
				preres = preres * values[i+1];
			}
			else
			{
				//values[rlval++] = preres;
				//if(l == "") l = 
				preres = values[i] * values[i+1];
			}
			pre = i;
			Print(l,i,preres);
		}
		else if(oper[i] == '/')
		{
			if(pre == i-1)
			{
				preres = preres / values[i+1];
			}
			else
			{
				preres = values[i] / values[i+1];
			}
			pre = i;
			Print(l,i,preres);
		}
		else
		{
			oper[rlop++] = oper[i];
			if( pre == i-1)
				values[rlval] = preres;
			else {values[rlval] = values[i];sign[rlval] = sign[i];}
			if(i != rlval) sign[i] = 0;
			//rlval++;

			l += convert(values[rlval++]);
			l += " ";
			l += oper[i];
			l += " ";

		}
	}
		if((pre == lop-1) && ((oper[lop-1] == '*') || (oper[lop-1] == '/')))
		{
			values[rlval] = preres;
		}
		else {values[rlval] = values[lop]; sign[rlval] = sign[lop];}
		//if(lop != rlval) sign[lop] = 0;
		rlval++;

	lop = rlop;
	lval = rlval;
}
void End()
{
	int res = values[0];
	for(int i=0; i< lop; i++)
	{
		if(oper[i] == '+')
			res = res + values[i+1];
		else res = res - values[i+1];

		printf("%d ",res);
		for(int j=i+1; j<lop; j++)
		{
			printf("%c ",oper[j]);
			//if(sign[j+1] == 1) printf("+");
			printf("%d ",values[j+1]);
		}
		cout<<rights<<endl;;
	}
}
int main()
{
	while(gets(ex) != NULL)
	{
		expression = ex;
		handle();
		Print("",-1,values[0]);
		printmulAndDiv();
		End();
		printf("\n");
	}
	return 0;
}




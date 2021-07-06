# 题目
You have typed the report of your term project in your personal computer. There are several one line arithmetic expressions in your report. There is no redundant parentheses in the expressions (omitting a pair of redundant matching parentheses does not change the value of the expression). In your absence, your little brother inserts some redundant matching parentheses in the expressions of your report. Assume that the expressions remain syntactically correct and evaluate to their original value (the value before inserting redundant parentheses). To restore your report to its original form, you are to write a program to omit all redundant parentheses.<br>
To make life easier, consider the following simplifying assumptions:<br>
The input file contains a number of expressions, each in one separate line.<br>
Variables in the expressions are only single uppercase letters.<br>
Operators in the expressions are only binary '+' and binary '-'.<br>

Note that the only transformation allowed is omission of redundant parentheses, and no algebraic simplification is allowed.

输入描述<br>
The input consists of several test cases. The first line of the file contains a single number M, which is the number of test ca

输出描述<br>
The output for each test case is the same expression without redundant parentheses. Notice that the order of operands in an input expression and its corresponding output should be the same. Each output expression must be on a separate line. Space characters should be omitted in the output expressions.

输入例子
```
3
(A-B + C) - (A+(B - C)) - (C-(D- E) )
  ((A)-( (B)))
A-(B+C)
```
输出例子
```
A-B+C-(A+B-C)-(C-(D-E))
A-B
A-(B+C)
```
# 参考答案
```c++
#include<cstdio>
 
#include<cstring>
 
using namespace std;
 
int main()
 
{
 
    int T;
 
    for(scanf("%d ",&T); T; T--)
 
    {
 
        char s[1000];
 
        char ans[1000];
 
        int st[1000];
 
        gets(s);
 
        int len,i,j,num=0;
 
        for(i=j=0; s[i]; i++)
 
        {
 
            if(s[i]==' ')
 
                continue;
 
            else if(s[i]=='(')
 
            {
 
                if(j>0&&ans[j-1]!='+'&&ans[j-1]!='(')
 
                    ans[j++]='(',st[num++]=1;
 
                else
 
                    st[num++]=-1;
 
            }
 
            else if(s[i]==')')
 
            {
 
                if(st[num-1]==-1)
 
                    num--;
 
                else if(ans[j-1]=='('||(j-2>=0&&ans[j-2]=='('))
 
                {
 
                    if(ans[j-1]=='(')
 
                        j--;
 
                    else
 
                        ans[j-2]=ans[j-1],j--;
 
                    num--;
 
                }
 
                else
 
                    ans[j++]=')',num--;
 
            }
 
            else
 
                ans[j++]=s[i];
 
        }
 
        ans[j]='\0';
 
        puts(ans);
 
    }
 
    return 0;
 
}


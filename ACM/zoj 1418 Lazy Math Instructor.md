# 题目

A math instructor is too lazy to grade a question in the exam papers in which students are supposed to produce a complicated formula for the question asked. Students may write correct answers in different forms which makes grading very hard. So, the instructor needs help from computer programmers and you can help.
You are to write a program to read different formulas and determine whether or not they are arithmetically equivalent.


Input

The first line of the input contains an integer N (1 <= N <= 20) that is the number of test cases. Following the first line, there are two lines for each test case. A test case consists of two arithmetic expressions, each on a separate line with at most 80 characters. There is no blank line in the input. An expression contains one or more of the following:

Single letter variables (case insensitive).

Single digit numbers.

Matched left and right parentheses.

Binary operators +, - and * which are used for addition, subtraction and multiplication respectively.

Arbitrary number of blank or tab characters between above tokens.

Note: Expressions are syntactically correct and evaluated from left to right with equal precedence (priority) for all operators. The coefficients and exponents of the variables are guaranteed to fit in 16-bit integers.


Output

Your program must produce one line for each test case. If input expressions for each test data are arithmetically equivalent, "YES", otherwise "NO" must be printed as the output of the program. Output should be all in upper-case characters.


Sample Input
```
3
(a+b-c)*2
(a+a)+(b*2)-(3*c)+c
a*2-(a+c)+((a+c+e)*2)
3*a+c+(2*e)
(a-b)*(a-b)
(a*a)-(2*a*b)-(b*b)
```

Sample Output
```
YES
YES
NO
```
# 参考答案
```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int count1,count2;
int opnd[200];  
char optr[200];  
char opp[9] = {'+','-','*','/','(',')','#','\0'};  
int h[7][7] = {{1,1,-1,-1,-1,1,1},{1,1,-1,-1,-1,1,1},{1,1,1,1,-1,1,1},
                   {1,1,1,1,-1,1,1},{-1,-1,-1,-1,-1,0,-2},{1,1,1,1,-2,1,1},{-1,-1,-1,-1,-1,-2,0}}; 

void push1(int x)  
{
    opnd[count1++] = x;
}
void push2(int x)  
{
    optr[count2++] = x;
}
int pop1()  
{
    count1--; 
    return opnd[count1];
}
char pop2()
{
    count2--;
    return optr[count2];
}
int computer(int x,int y, char ch)  
{
    switch(ch)
    {
        case '+':return x+y;
        case '-':return x-y;
        case '*':return x*y;
        case '/':return x/y;
    }
}
int record(char a,char b) 
{
    int ta,tb;
    int i;
    for(i=0; i<7; i++)
    {
        if( a == opp[i] )
           ta = i;
        if( b == opp[i] )
           tb = i;
    } 
    return h[ta][tb];
}
int result(char fir[],int plus) 
{
    char c,ch;
    int x,y,i = 0;
    count1 = 0;
    count2 = 0;
    push2('#');
    while( fir[i]!='#' || optr[count2-1]!='#')
    {
        c = fir[i];
        if( isdigit(c) )
        {
            push1(c-'0');
            i++;
            continue;
        }
        if( isalpha(c) )
        {
            push1(c-'a'+plus);
            i++;
            continue;
        }
        if(c == '+' || c== '-'||c=='*' || c=='('||c==')'||c=='#')
        {
            switch( record(optr[count2-1],c) )
            {

                case -1: push2(c); i++; break;
                case 0 : pop2(); i++; break;
                case 1 : ch = pop2();
                         y = pop1();
                         x = pop1(); 
                         push1(computer(x,y,ch));
                         break;
            }
        }
        else
            i++;
    }
return opnd[count1-1];
}
int main(void)
{
    char c,ch;
    int length,i,x,y,plus,result1,result2,ncases;
    int len1,len2,flag;
    char fir[90],sec[90];
    scanf("%d",&ncases);
    getchar();
    while(ncases--)
    {
        gets(fir);
        gets(sec);
        len1 = strlen( fir );
        len2 = strlen( sec );
        fir[len1] = '#';
        sec[len2] = '#';
        plus = 10;
        result1= result(fir,plus);
        result2= result(sec,plus);
        if( result1 != result2 )
            printf("NO\n");   
        else
            printf("YES\n");
    }
return 0;
}

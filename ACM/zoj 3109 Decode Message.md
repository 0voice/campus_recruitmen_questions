# 题目
Being in charge of the computer department of the Agency of International Espionage, you are asked to write a program that will allow a spy to decode their messages.

You can assume a spy's message is at most 400 characters long, and it includes all the uppercase letters of the English alphabet plus the space, any digit, and any of the following characters: ! , . : ; ? - The algorithm that the department will use to encode all their messages will be following:

They first encode the message with a simple code key. This simple code key is a one for one character substitution based upon a single arithmetic manipulation of the printable portion of the ASCII character set (0-126). This single arithmetic manipulation is the same for each character of the message. (We assume the code is 7, please see sample for more detail.)

After, they agree secretly on two numbers that will be used as the number of rows (R) and columns (C) in a matrix.

The department then enters the letters of the message encode in spiral pattern along the matrix.

For example, if the message is:

-CDC IS THE TRADEMARK OF THE CONTROL DATA CORPORATION.

and there R=9 and C=6, the department would write down.

Message encode:

4JKJ'PZ'[OL'[YHKLTHYR'VM'[OL'JVU[YVS'KH[H'JVYWVYH[PVU5

The matrix would be filled in as follows:
```
4	J	K	J	'	P
[	O	L	'	J	Z
'	V	Y	W	V	'
M	J	5	V	U	[
V	'	U	Y	[	O
'	H	V	H	Y	L
R	[	P	[	V	'
Y	H	K	'	S	[
H	T	L	K	H	Y
```
Input

There will be multiple datasets. Each dataset consist of two lines. The first line contain R (2<=R<=20), a space, C (2<=C<=20). The next line is a string of characters that represent the contents of the matrix (R X C characters). The characters are in row major order. The last input set is followed by a line containing two zeros (0 0). This line should not be processed.

Output

For each dataset, you should one line of output, giving the decoded message.

Sample Input
```
9 6
4JKJ'P[OL'JZ'VYWV'MJ5VU[V'UY[O'HVHYLR[P[V'YHK'S[HTLKHY
0 0
```
Sample Output
```
-CDC IS THE TRADEMARK OF THE CONTROL DATA CORPORATION.
```
# 参考答案
```c++
#include<stdio.h>

int main()
{
    int r, c;
    char a[20][20];
    while (scanf("%d %d", &r, &c), r && c)
    {
        getchar();
        int i, j, index = 0;
        for (i = 0; i < r; i++)
            for (j = 0; j < c; j++)
                a[i][j] = getchar();
        getchar();

        int isRow = 1, isOrder = 1, rb = 0, re = c - 1, cb = 0, ce = r - 1;
        while (1)
        {
            if (isRow)
            {
                if (rb > re)
                    break;

                if (isOrder)
                {
                    for (i = rb; i <= re; i++)
                        putchar(a[index][i] - 7);
                    index = re;
                    cb++;
                }
                else
                {
                    for (i = re; i >= rb; i--)
                        putchar(a[index][i] - 7);
                    index = rb;
                    ce--;
                }
                isRow = !isRow;
            }
            else
            {
                if (cb > ce)
                    break;

                if (isOrder)
                {
                    for (i = cb; i <= ce; i++)
                        putchar(a[i][index] - 7);
                    index = ce;
                    re--;
                }
                else
                {
                    for (i = ce; i >= cb; i--)
                        putchar(a[i][index] - 7);
                    index = cb;
                    rb++;
                }
                isOrder = !isOrder;
                isRow = !isRow;
            }
        }
        putchar('\n');
    }
    return 0;
}

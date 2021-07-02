# 题目
A regular palindrome is a string of numbers or letters that is the same forward as backward. For example, the string "ABCDEDCBA" is a palindrome because it is the same when the string is read from left to right as when the string is read from right to left.
A mirrored string is a string for which when each of the elements of the string is changed to its reverse (if it has a reverse) and the string is read backwards the result is the same as the original string. For example, the string "3AIAE" is a mirrored string because "A" and "I" are their own reverses, and "3" and "E" are each others' reverses.

A mirrored palindrome is a string that meets the criteria of a regular palindrome and the criteria of a mirrored string. The string "ATOYOTA" is a mirrored palindrome because if the string is read backwards, the string is the same as the original and because if each of the characters is replaced by its reverse and the result is read backwards, the result is the same as the original string. Of course, "A", "T", "O", and "Y" are all their own reverses.

A list of all valid characters and their reverses is as follows.
```
Character  Reverse  Character  Reverse  Character  Reverse  

    A         A         M         M         Y         Y
    B                   N                   Z         5
    C                   O         O         1         1
    D                   P                   2         S
    E         3         Q                   3         E
    F                   R                   4
    G                   S         2         5         Z
    H         H         T         T         6
    I         I         U         U         7
    J         L         V         V         8         8
    K                   W         W         9
    L         J         X         X
```
Note that O (zero) and 0 (the letter) are considered the same character and therefore ONLY the letter "0" is a valid character.


Input

Input consists of strings (one per line) each of which will consist of one to twenty valid characters. There will be no invalid characters in any of the strings. Your program should read to the end of file.


Output

For each input string, you should print the string starting in column 1 immediately followed by exactly one of the following strings.

" -- is not a palindrome."<br>
if the string is not a palindrome and is not a mirrored string<br>

" -- is a regular palindrome."<br>
if the string is a palindrome and is not a mirrored string

" -- is a mirrored string."<br>
if the string is not a palindrome and is a mirrored string

" -- is a mirrored palindrome."<br>
if the string is a palindrome and is a mirrored string<br>
Note that the output line is to include the -'s and spacing exactly as shown in the table above and demonstrated in the Sample Output below.

In addition, after each output line, you must print an empty line.


Sample Input
```
NOTAPALINDROME
ISAPALINILAPASI
2A3MEAS
ATOYOTA
```

Sample Output
```
NOTAPALINDROME -- is not a palindrome.

ISAPALINILAPASI -- is a regular palindrome.

2A3MEAS -- is a mirrored string.

ATOYOTA -- is a mirrored palindrome.
```
# 参考答案
```c++
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <map>
using namespace std;
char ss[]="E3JLS2Z5AHIMOTUVWXY18";
int slen;
bool ishave(char c)
{
    for(int i=0; i<slen; i++)
    {
        if(c==ss[i])
            return true;
    }
    return false;
}
char get(char c)
{
    switch(c)
    {
    case 'E':
        return '3';
    case 'J':
        return 'L';
    case 'S':
        return '2';
    case 'Z':
        return '5';
    case '3':
        return 'E';
    case 'L':
        return 'J';
    case '2':
        return 'S';
    case '5':
        return 'Z';
    default :
        break;
    }
    return c;
}
int main()
{
    char str[1000];
    slen=strlen(ss);
    while(scanf("%s",str)!=EOF)
    {
        int len = strlen(str);
        int i=0,j=len-1;
        bool ispalindrome=true;
        bool ismirrored  =true;
        while(i<j)//ispalindrome
        {
            if(str[i]!=str[j])
            {
                ispalindrome=false;
                break;
            }
            i++;
            j--;
        }
        char tmp[1000];
        strcpy(tmp,str);
        for(int i=0;i<len;i++)
        {
            if(ishave(tmp[i]))
                tmp[i]=get(tmp[i]);
            else
            {
                ismirrored=false;
                break;
            }
        }
        if(ismirrored)
        {
            for(int i=0,j=len-1;i<len;i++,j--)
            {
                if(str[i]!=tmp[j])
                {
                    ismirrored=false;
                    break;
                }
            }
        }
        if(ispalindrome)
        {
            if(ismirrored)// true true
            {
                printf("%s -- is a mirrored palindrome.\n",str);
            }
            else//true false
            {
                printf("%s -- is a regular palindrome.\n",str);
            }
        }
        else
        {
            if(ismirrored)
            {
                printf("%s -- is a mirrored string.\n",str);
            }
            else
            {
                printf("%s -- is not a palindrome.\n",str);
            }
        }
        printf("\n");
    }
    return 0 ;
}





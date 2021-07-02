# 题目
Many people like to solve hard puzzles some of which may lead them to madness. One such puzzle could be finding a hidden prime number in a given text. Such number could be the number of different substrings of a given size that exist in the text. As you soon will discover, you really need the help of a computer and a good algorithm to solve such a puzzle.

Your task is to write a program that given the size, N, of the substring, the number of different characters that may occur in the text, NC, and the text itself, determines the number of different substrings of size N that appear in the text.

As an example, consider N=3, NC=4 and the text "daababac". The different substrings of size 3 that can be found in this text are: "daa", "aab", "aba", "bab", "bac". Therefore, the answer should be 5.


Input

The first line of input consists of two numbers, N and NC, separated by exactly one space. This is followed by the text where the search takes place. You may assume that the maximum number of substrings formed by the possible set of characters does not exceed 16 Millions.


Output

The program should output just an integer corresponding to the number of different substrings of size N found in the given text.


This problem contains multiple test cases!

The first line of a multiple input is an integer N, then a blank line followed by N input blocks. Each input block is in the format indicated in the problem description. There is a blank line between input blocks.

The output format consists of N output blocks. There is a blank line between output blocks.


Sample Input
```
1
3 4
daababac
```
Sample Output
```
5
```
# 参考答案
```c++
#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;
const int N=16000005; 

const int NUM=300;
bool hash[N];
int m[NUM];
char str[1000000];
int main()
{
    int tt;
    cin>>tt;
    while(tt--)
    {
        int n,nc,i,j,sum,seed=0,ans=0;
        memset(hash,false,sizeof(hash));
        memset(m,0,sizeof(m));
        memset(str,'\0',sizeof(str));
        cin>>n>>nc>>str;
        for(i=0; '\0' != str[i]; ++i)
        {
            if(!m[str[i]]) 
                m[str[i]]=++seed;
            if(seed == nc)
                break;
        }
        int len=strlen(str);
        for(i=0; i<=len-n; ++i)
        {
            sum=0;
            for(j=0; j<n; ++j) 
                sum=sum*nc+m[str[i+j]]-1;
            if(!hash[sum])
            {
                hash[sum]=true;
                ++ans;
            }
        }
       if(tt)
        cout<<ans<<endl<<endl;
        else
        cout<<ans;
    }
    return 0;
}

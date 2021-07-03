# 题目
The relative frequency of characters in natural language texts is very important for cryptography. However, the statistics vary for different languages. Here are the top 9 characters sorted by their relative frequencies for several common languages:
```
English: ETAOINSHR
German:  ENIRSATUD
French:  EAISTNRUL
Spanish: EAOSNRILD
Italian: EAIONLRTS
Finnish: AITNESLOK
```
Just as important as the relative frequencies of single characters are those of pairs of characters, so called digrams. Given several text samples, calculate the digrams with the top relative frequencies.


Input

The input contains several test cases. Each starts with a number n on a separate line, denoting the number of lines of the test case. The input is terminated by n = 0. Otherwise, 1 <= n <= 64, and there follow n lines, each with a maximal length of 80 characters. The concatenation of these n lines, where the end-of-line characters are omitted, gives the text sample you have to examine. The text sample will contain printable ASCII characters only.


Output

For each test case generate 5 lines containing the top 5 digrams together with their absolute and relative frequencies. Output the latter rounded to a precision of 6 decimal places. If two digrams should have the same frequency, sort them in (ASCII) lexicographical order. Output a blank line after each test case.


Sample Input
```
2
Take a look at this!!
!!siht ta kool a ekaT
5
P=NP
 Authors: A. Cookie, N. D. Fortune, L. Shalom
 Abstract: We give a PTAS algorithm for MaxSAT and apply the PCP-Theorem [3]
 Let F be a set of clauses. The following PTAS algorithm gives an optimal
 assignment for F:
0
```

Sample Output
```
 a 3 0.073171
!! 3 0.073171
a  3 0.073171
 t 2 0.048780
oo 2 0.048780

 a 8 0.037209
or 7 0.032558
.  5 0.023256
e  5 0.023256
al 4 0.018605
```
# 参考答案
```c++
#include<iostream>
#include<map>
#include<stdio.h>
using namespace std;
int main()
{
    int n;
    while(cin >> n && n != 0)
    {
        string line,text;
        map<string,int> m;
        getline(cin,line);
        for(int i = 0; i < n; ++i)
        {
            getline(cin,line);
            text += line;
        }
        for(int i = 1; i < text.size(); ++i)
        {
            string dig = text.substr(i - 1,2);
            if(m.find(dig) != m.end())
                ++m[dig];
            else
                m[dig] = 1;
        }
        for(int i = 0; i < 5; ++i)
        {
            map<string,int>::iterator tmp;
            int ma = 0;
            for(map<string,int>::iterator p = m.begin(); p != m.end(); ++p)
            {
                if(p->second > ma)
                {
                    ma = p->second;
                    tmp = p;
                }
            }
            printf("%s %d %.6lf\n",(tmp->first).c_str(),tmp->second,1.0 * tmp->second / (text.size() - 1));
            m.erase(tmp);
        }
        printf("\n");
    }
    return 0;
}

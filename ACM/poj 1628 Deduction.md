# 题目
S is a set of 52 declarations, which is represented by lower case letters ('a', 'b', ..., 'z') and upper case letters ('A', 'B', ..., 'Z'). These declarations are not completely independent with each other, And from some of them, we can deduce some others. We denote this relation as "=>". For instance, a => b means from declaration a, we can deduce declaration b; b => c, means from declaration b, we can deduce declaration c. And from a => b and b =>c, we can also get a => bc, which means from a, we can deduce both b and c. Let's see some further examples: abc => de means from a, b, and c, we can deduce d and e. bc => fgh means from bc, we can deduce fgh. And from abc => de, bc => fhg, we can finally get abc => defgh, even more, we can get abc => abcdefgh.

Now given m deduction relations, which are represented in the form S1 => S2, S1 and S2 are subsets of S, and n queries, each contains a subset Q of S. Your job is to find all declarations can be deduced from Q according to the given relations.

输入描述<br>
Input will contain m + n + 1 lines. The first line contains two positive integers m, n. (m is less than 200, and n is less than 1000). Then m lines follow, each with a deduction relation. The last n lines each contains a query.

You can see that there is no space between declarations in S1, S2 and Q. And there is one space between S1 and "=>" and between "=>" and S2. And it is confirmed that the number of declarations in S1, S2 and Q will not exceed 52.

输出描述<br>
For each query, output the answer for the query. The element for the output should be in the order [a, b, c, ..., y, z, A, B, C, ..., Y, Z].<br>
输入例子
```
2 1
abc => de 
bcb => FGh
abc
```
输出例子
```
abcdehFG
```
# 参考答案
```c++
#include<iostream>
using namespace std;
struct Node {
     char s1[200],s2[200];       
}decl[250];
bool more,ur[128],visit[250];  
int  n,m,l,k ;     
char s[200],res[200]; 
int main()
{
     while(scanf("%d%d",&n,&m)!=EOF)  {
     for(int i=0;i<n;i++) 
       scanf("%s => %s",&decl[i].s1,&decl[i].s2);
     for(int i=0;i<m;i++) {
       scanf("%s",&s); 
       l = strlen(s) ; 
       memset(ur,false,sizeof(ur));  
       for(int j=0;j<l;j++) 
         ur[s[j]] = true ;   
       more = true ; 
       memset(visit,false,sizeof(visit)); 
       while(more) {
          more = false ;
          for(int j=0;j<n;j++) {
            if(visit[j]) continue ; 
            l = strlen(decl[j].s1);  
            for(k=0;k<l;k++)
              if(!ur[decl[j].s1[k]]) break ;    
            if(k==l)  {
              visit[j] = true ;        
              more = true ;  
              l = strlen(decl[j].s2);  
              for(k=0;k<l;k++) 
                  ur[decl[j].s2[k]] = true ;   
            }
          }     
       }
       for(char c='a';c<='z';c++) 
          if(ur[c]) printf("%c",c);  
       for(char c='A';c<='Z';c++)
          if(ur[c]) printf("%c",c);  
       puts("");
     } 
     }
     return 0;
}

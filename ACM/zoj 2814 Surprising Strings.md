# 题目
The <dfn>D-pairs</dfn> of a string of letters are the ordered pairs of letters that are distance D from each other. A string is <dfn>D-unique</dfn> if all of its D-pairs are different. A string is <dfn>surprising</dfn> if it is D-unique for every possible distance D.

Consider the string ZGBG. Its 0-pairs are ZG, GB, and BG. Since these three pairs are all different, ZGBG is 0-unique. Similarly, the 1-pairs of ZGBG are ZB and GG, and since these two pairs are different, ZGBG is 1-unique. Finally, the only 2-pair of ZGBG is ZG, so ZGBG is 2-unique. Thus ZGBG is surprising. (Note that the fact that ZG is both a 0-pair and a 2-pair of ZGBG is irrelevant, because 0 and 2 are different distances.)

Input: The input consists of one or more nonempty strings of at most 79 uppercase letters, each string on a line by itself, followed by a line containing only an asterisk that signals the end of the input.

Output: For each string of letters, output whether or not it is surprising using the exact output format shown below.

Acknowledgement: This problem is inspired by the "Puzzling Adventures" column in the December 2003 issue of Scientific American.

Example input: | Example output:
-------------- | ---------------
ZGBG | ZGBG is surprising.
X | X is surprising.
EE | EE is surprising.
AAB | AAB is surprising.
AABA | AABA is surprising.
AABB | AABB is NOT surprising.
BCBABCC | BCBABCC is NOT surprising.
/ | /

# 参考答案
    #include <iostream>
    #include <stdio.h>
    #include <string.h>
    using namespace std;

    int main()
    {
      char s[80];
      while(scanf("%s",s))
      {
        if(strcmp(s,"*")==0)
          return 0;
        else
        {
          int flag;
          for(int d = 1 ; d < strlen(s)-1; d++)
          {
            char **a = new char*[strlen(s)-d];
            for(int i = 0 ; i < strlen(s)-d; i++)
            {
              a[i] = new char[2];
              a[i][0] = s[i];
              a[i][1] = s[i+d];
            }
            flag = 0;
            for( int j = 0 ; j < strlen(s)-d; j++)
            {
              for(int k = j+1; k < strlen(s)-d; k++)
              {
                if(strcmp(a[j],a[k])==0)
                {
                  flag = 1;
                  break;
                }
              }
              if(flag == 1)	break;
            }	
            if(flag == 1)	break;
          }
          if(flag == 1)
            cout<<s<<" is NOT surprising."<<endl;
          else
            cout<<s<<" is surprising."<<endl;
        }
      }
      return 0;
    }

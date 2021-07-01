# 题目
River polution control is a major challenge that authorities face in order to ensure future clean water supply. Sewage treatment plants are used to clean-up the dirty water comming from cities before being discharged into the river.

As part of a coordinated plan, a pipeline is setup in order to connect cities to the sewage treatment plants distributed along the river. It is more efficient to have treatment plants running at maximum capacity and less-used ones switched off for a period. So, each city has its own treatment plant by the river and also a pipe to its neighbouring city upstream and a pipe to the next city downstream along the riverside. At each city's treatment plant there are three choices:

either process any water it may receive from one neighbouring city, together with its own dirty water, discharging the cleaned-up water into the river;

or send its own dirty water, plus any from its downstream neighbour, along to the upstream neighbouring city's treatment plant (provided that city is not already using the pipe to send it's dirty water downstream);

or send its own dirty water, plus any from the upstream neighbour, to the downstream neighbouring city's plant, if the pipe is not being used.

![poj_4307desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_4307desc_0.jpg)

The choices above ensure that:

every city must have its water treated somewhere and

at least one city must discharge the cleaned water into the river.

Let's represent a city discharging water into the river as "V" (a downwards flow), passing water onto its neighbours as ">" (to the next city on its right) or else ") and list the cities symbols in order. For example, two cities, A and B, can

each treat their own sewage and each discharges clean water into the river. So A's action is denoted V as is B's and we write "VV" ;

or else city A can send its sewage along the pipe (to the right) to B for treatment and discharge, denoted ">V";

or else city B can send its sewage to (the left to) A, which treats it with its own dirty water and discharges (V) the cleaned water into the river. So A discharges (V) and B passes water to the left (We could not have ">

So we have just 3 possible set-ups that fit the conditions:

           A    B       A > B       A          V    V           V       V             

    RIVER~ ~ ~ ~ ~     ~ ~ ~ ~ ~   ~ ~ ~ ~ ~RIVER

            "VV"        ">V"         "V
            
If we now consider three cities, we can determine 8 possible set-ups.

Your task is to produce a program that given the number of cities NC (or treatment plants) in the river bank, determines the number of possible set-ups, NS, that can be made according to the rules define above.

You need to be careful with your design as the number of cities can be as large as 100.

输入描述

The input consists of a sequence of values, one per line, where each value represents the number of cities.

输出描述

Your output should be a sequence of values, one per line, where each value represents the number of possible set-ups for the corresponding number of cities read in the same input line.

输入例子
* 2
* 3
* 20

输出例子
* 3
* 8
* 102334155

# 参考答案
    #include<iostream>
    #include<string>
    #include<algorithm>

    using namespace std;

    string add(string s1,string s2)
    {
      string result;
      result.reserve(1000);

      if(s1.length()<s2.length())
        s1.swap(s2);
      s2.insert(s2.begin(),s1.length()-s2.length(),'0');

      int g=0;
      for(int i=s1.length()-1;i>=0;i--)
      {
        g+=s1[i]+s2[i]-2*'0';
        result+=g%10+'0';
        g/=10;
      }
      if(g>0)
        result+=g+'0';
      reverse(result.begin(),result.end());

      return result;
    }

    string a[101];

    void Initial()
    {
      a[1]="1";
      for(int i=2;i<=100;i++)
      {
        string temp;
        temp="1";
        for(int k=1;k<i-1;k++)
          temp=add(temp,a[k]);
        string te=add(a[i-1],a[i-1]);
        temp=add(temp,te);

        a[i]=temp;
      }
    }

    int main(int argc, char* argv[])
    {
      Initial();

      int x;
      while(cin>>x)
        cout<<a[x]<<endl;
      return 0;
    }

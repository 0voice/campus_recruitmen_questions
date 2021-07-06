# 题目
ach employee of a bureaucracy has a job description - a few paragraphs that describe the responsibilities of the job. The employee's job description, combined with other factors, such as seniority, is used to determine his or her salary.
The Hay Point system frees the Human Resources department from having to make an intelligent judgement as to the value of the employee; the job description is merely scanned for words and phrases that indicate responsibility. In particular, job descriptions that indicate control over a large budget or management over a large number of people yield high Hay Point scores.

You are to implement a simplified Hay Point system. You will be given a Hay Point dictionary and a number of job descriptions. For each job description you are to compute the salary associated with the job, according to the system.

输入描述<br>
The first line of input contains 2 positive integ

输出描述<br>
For each job description, output the corresponding salary computed as the sum of the Hay Point values for all words that appear in the description. Words that do not appear in the dictionary have a value of 0.

输入例子
```
7 2
administer 100000
spending 200000
manage 50000
responsibility 25000
expertise 100
skill 50
money 75000
the incumbent will administer the spending of kindergarden milk money
and exercise responsibility for making change he or she will share
responsibility for the task of managing the money with the assistant
whose skill and expertise shall ensure the successful spending exercise
.
this individual must have the skill to perform a heart transplant and
expertise in rocket science
.
```
输出例子
```
700150
150
```
# 参考答案
```c++
#include<cstdio>
#include<iostream>
#include<string>
#include<map>
using namespace std;

map<string,int> ma;

int main(){
    int m,n;
    cin>>m>>n;
    while(m--){
        string a;
        int b;
        cin>>a;
        scanf("%d",&b);
        ma[a]=b;
    }
    while(n--){
        string a;
        int sum=0;
        while(cin>>a){
            if(a==".")  break;
            //cout<<"de:"<<ma[a]<<endl;
            sum+=ma[a];
        }
        printf("%d\n",sum);

    }
}

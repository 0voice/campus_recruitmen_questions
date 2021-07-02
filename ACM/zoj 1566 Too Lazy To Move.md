# 题目
As we all know, Hanoi Tower can be solved in 2^n-1 steps if there are n disks. We might adhere to such rules:<br>
1) When the step number is odd, move the smallest disk to the next pillar (in the order A->B->C->A��).<br>

2) When the step number is even, move one disk between the pillar without the smallest disk.

Here is an example:

Step 0 (Initial Step)<br>
A: 3 2 1<br>
B:<br>
C:<br>

Step 1<br>
A: 3 2<br>
B: 1<br>
C:<br>

Step 2<br>
A: 3<br>
B: 1<br>
C: 2<br>

Step 3<br>
A: 3<br>
B:<br>
C: 2 1<br>

Step 4<br>
A:<br>
B: 3<br>
C: 2 1<br>

Step 5<br>
A: 1<br>
B: 3<br>
C: 2<br>

Step 6<br>
A: 1<br>
B: 3 2<br>
C:<br>

Step 7<br>
A:<br>
B: 3 2 1<br>
C:<br>

End.

Now it is your task to find out the m-th configuration for a n-disk Hanoi Tower with the rules defined above.


Input

One test on each line, with two integers n (1 <= n <= 63) and m (0 <= m <= 2^n-1). Input is terminated with end of file.


Output

Print a configuration in three lines. Conform to the format in the sample. There should be one space after each colon. Each test is followed by a blank line.

Sample Input
```
3 0
3 1
3 2
3 7
63 9223372036854775807
```

Sample Output
```
A: 3 2 1
B:
C:

A: 3 2
B: 1
C:

A: 3
B: 1
C: 2

A:
B: 3 2 1
C:

A:
B: 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
C:
```

# 参考答案
```c++
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
typedef unsigned long long ullong;
int disknum;
ullong step;

void calc(int n, ullong step, vector<int> &a, vector<int> &b, vector<int> &c){
	if(n <=0)
		return;
	ullong lim = 1llu << (n-1);
	if(step < lim){
		a.push_back(n);
		calc(n-1,step,a,c,b);
	} else {
		c.push_back(n);
		calc(n-1,step-lim,b,a,c);
	}
}

void print(const char *str, vector<int> &v){
	cout<<str;
	vector<int>::iterator i;
	if(v.size()==0)
		cout<<" ";
	for(i=v.begin(); i!=v.end();i++){
		cout<<" "<<*i;
	}
	cout<<endl;
}

int fun(){
    vector<int> A,B,C;

	if(disknum %2 == 1)
		calc(disknum,step,A,C,B);
	else 
		calc(disknum,step,A,B,C);
	print("A:", A);
	print("B:", B);
	print("C:", C);
}

int main(){
	int tstcase = 0;
	while(cin>>disknum>>step){			
		fun();
		cout<<endl;
	}

    return 0;
}




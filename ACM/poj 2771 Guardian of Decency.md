# 题目
rank N. Stein is a very conservative high-school teacher. He wants to take some of his students on an excursion, but he is afraid that some of them might become couples. While you can never exclude this possibility, he has made some rules that he thinks indicates a low probability two persons will become a couple:<br>
Their height differs by more than 40 cm.<br>
They are of the same sex.<br>
Their preferred music style is different.<br>
Their favourite sport is the same (they are likely to be fans of different teams and that would result in fighting).<br>

So, for any two persons that he brings on the excursion, they must satisfy at least one of the requirements above. Help him find the maximum number of persons he can take, given their vital information.

输入描述<br>
The first line of the input consists of an integer T ≤ 100 giving the number of test cases. The first line of each test case consists of an integer N ≤ 500 giving the number of pupils. Next there will be one line for each pupil consisting of four space-separated data items:<br>
an integer h giving the height in cm;<br>
a character 'F' for female or 'M' for male;<br>
a string describing the preferred music style;<br>
a string with the name of the favourite sport.<br>

No string in the input will contain more than 100 characters, nor will any string contain any whitespace.

输出描述<br>
For each test case in the input there should be one line with an integer giving the maximum number of eligible pupils.<br>
输入例子<br>
```
2
4
35 M classicism programming
0 M baroque skiing
43 M baroque chess
30 F baroque soccer
8
27 M romance programming
194 F baroque programming
67 M baroque ping-pong
51 M classicism programming
80 M classicism Paintball
35 M baroque ping-pong
39 F romance ping-pong
110 M romance Paintball
```
输出例子
```
3
7
```
# 参考答案
```c++
#include"cstdio"
#include"string"
#include"iostream"
#include"algorithm"
using namespace std;
#define FOR(a,b,c) for(int a=b;a<c;a++)
const int N = 510;

int H[N]; char S[N]; string X[N],Y[N];
bool a[N][N],V[N]; int L[N];
int n;
bool can(int k) {
	FOR(i, 1, n + 1) if(!V[i] && a[k][i] && !L[i]) { L[i] = k; return 1; }
	FOR(i, 1, n + 1) if(!V[i] && a[k][i] &&  L[i]) {
		V[i] = 1; if(can(L[i])) { L[i] = k; return 1; } }
	return 0;
}
int main() {
	ios::sync_with_stdio(0);
	int T; cin>>T;
	while(T--) {
		cin>>n;
		FOR(i, 1, n + 1) cin>>H[i]>>S[i]>>X[i]>>Y[i];
		FOR(i, 1, n + 1) FOR(j, i, n + 1) 
			a[j][i] = a[i][j] = abs(H[i]-H[j])<=40 && S[i]!=S[j] && X[i]==X[j] && Y[i]!=Y[j];
		int ans = n;
		FOR(i, 1, n + 1) L[i] = 0;
		FOR(i, 1, n + 1) if(S[i] == 'M') {
			FOR(j, 1, n + 1) V[j] = 0;
			ans -= can(i); }
		cout<<ans<<endl; }
	return 0;
}

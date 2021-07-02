# 题目
In the kingdom of string, people like palindromic strings very much. They like only palindromic strings and dislike all other strings. There is a unified formula to calculate the score of a palindromic string. The score is calculated by applying the following three steps.

Since a palindromic string is symmetric, the second half(excluding the middle of the string if the length is odd) is got rid of, and only the rest is considered. For example, "abba" becomes "ab", "aba" becomes "ab" and "abacaba" becomes "abac".

Define some integer values for 'a' to 'z'.

Treat the rest part as a 26-based number <var>M</var> and the score is <var>M</var> modulo 777,777,777.

However different person may have different values for 'a' to 'z'. For example, if 'a' is defined as 3, 'b' is defined as 1 and c is defined as 4, then the string "accbcca" has the score (3×263+4×262+4×26+1) modulo 777777777=55537.

One day, a very long string <var>S</var> is discovered and everyone in the kingdom wants to know that among all the palindromic substrings of S, what the one with the <var>K</var>-th smallest score is.

Input

The first line contains an integer <var>T</var>(1 ≤ <var>T</var> ≤ 20), the number of test cases.

The first line in each case contains two integers <var>n, m</var>(1 ≤ <var>n</var> ≤ 100000, 1 ≤ <var>m</var> ≤ 20) where <var>n</var> is the length of <var>S</var> and <var>m</var> is the number of people in the kingdom. The second line is the string <var>S</var> consisting of only lowercase letters. The next <var>m</var> lines each containing 27 integers describes a person in the following format.

<var>Ki va vb ... vz</var>

where <var>va</var> is the value of 'a' for the person, <var>vb</var> is the value of 'b' and so on. It is ensured that the <var>Ki</var>-th smallest palindromic substring exists and <var>va, vb, ..., vz</var> are in the range of [0, 26). But the values may coincide.

Output

For each person, output the score of the <var>K</var>-th smallest palindromic substring in one line. Print a blank line after each case.

Sample Input
```
3
6 2
abcdca
3 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
7 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
4 10
zzzz
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 14
2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 14
3 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 14
4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 14
5 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 14
6 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 14
7 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 14
8 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 14
9 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 14
10 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 14
51 4
abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba
1 1 3 3 25 20 25 21 7 0 9 7 3 16 15 14 19 5 19 19 19 22 8 23 2 4 1
25 1 3 3 25 20 25 21 7 0 9 7 3 16 15 14 19 5 19 19 19 22 8 23 2 4 1
26 1 3 3 25 20 25 21 7 0 9 7 3 16 15 14 19 5 19 19 19 22 8 23 2 4 1
76 1 3 3 25 20 25 21 7 0 9 7 3 16 15 14 19 5 19 19 19 22 8 23 2 4 1
```
Sample Output
```
1
620

14
14
14
14
14
14
14
378
378
378

0
9
14
733665286
```
Hint

There are 7 palindromic substrings {"a", "a," "b", "c", "c", "d", "cdc"} in the first case. For the first person, the corresponding scores are {1, 1, 1, 1, 1, 1, 27}. For the second person, the corresponding scores are {25, 25, 24, 23, 23, 22, 620}.
# 参考答案
```C++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
const int Mod = 777777777;
const int N = 100015;
#define mp make_pair
char s[N];
UL hashMi[N], hashSum[N];
pair<int,int> ans[N*10];
int v[27];
int tot;

struct hashTable{
	const static int Mod = 500009;
	int gcnt;
	int ghead[Mod];
	struct hashList{
		int next;
		UL key;
		int len;
		int pos;
	} ele[N*10];

	void reset(){
		memset(ghead, -1, sizeof(ghead));
		gcnt = 0;
	}

	void ins(UL num, int len, int pos){
		int x = num%Mod;
		ele[gcnt].next = ghead[x];
		ele[gcnt].key = num;
		ele[gcnt].len = len;
		ele[gcnt].pos = pos;
		ghead[x] = gcnt++;
	}

	int find(UL num, int len){
		int x = num%Mod;
		for(int i = ghead[x]; i != -1; i = ele[i].next)
			if(ele[i].key == num &&ele[i].len == len) return ele[i].pos;
		return 0;
	}
} ha;

UL getHash(int l, int r){
	UL ret;
	ret = hashSum[r];
	if(l)
		ret -= hashSum[l-1]*hashMi[r-l+1];
	return ret;
}

struct Trie{
const static int CHILD_NUM = 26;
const static int MAX_NODE = N*3;
 int ID[128];
 int val[MAX_NODE];
 int chd[MAX_NODE][CHILD_NUM];
 int vi[MAX_NODE];
 int sz;
	Trie(){
		for(int i = 0; i < 26; ++i)
		ID[i+'a'] = i;
	}

	void reset(){
		memset(chd[0], 0, sizeof(chd[0]));
		memset(val, 0, sizeof(val));
		sz = 1;
	}

	void ins(char s[], int l, int r, int R, int nid){
		int j;
		UL num;
		for(int i = r; i >=l; --i){
			j = ID[s[i]];
			if(!chd[nid][j]){
				memset(chd[sz], 0, sizeof(chd[sz]));
				chd[nid][j] = sz++;
			}
			nid = chd[nid][j];
			num = getHash(i,R);
			ha.ins(num,R-i+1,nid);
		}
		++val[nid];
	}

	int dfs(int hash, int nid, int mi){
		int i, u, sum=val[nid];
		for(i = 0; i < CHILD_NUM; ++i){
			u = chd[nid][i];
			if(u){
				int nextHash = (hash+(LL)v[i]*mi)%Mod;
				sum += dfs(nextHash, u,(LL)mi*26%Mod);
			}
		}
		if(sum && nid) ans[tot++] = mp(hash,sum);
		return sum;
	}

} trie;

void palindrome(char cs[], int len[], int n) {
	for (int i = 0; i < n * 2; ++i) {
		len[i] = 0;
	}
	for (int i = 0, j = 0, k; i < n * 2; i += k, j = max(j - k, 0)) {
		while (i - j >= 0 && i + j + 1 < n * 2 && cs[(i - j) / 2] == cs[(i + j + 1) / 2])
			j++;
		len[i] = j;
		for (k = 1; i - k >= 0 && j - k >= 0 && len[i - k] != j - k; k++) {
			len[i + k] = min(len[i - k], j - k);
		}
	}
}

int ma[N<<2];
const int D = 173;
void go(){
	int len, i;
	len = strlen(s);
	palindrome(s, ma, len);
	hashSum[0] = s[0];
	for(i = 1; i < len; ++i)
		hashSum[i] = hashSum[i-1]*D + s[i];
 ha.reset();
 trie.reset();
	for(i = 0; i < len; ++i){
		for(int p=0;p<2;++p){
		 if(!ma[i<<1|p])continue;
			int l = i-(ma[i<<1|p]+1)/2+1, l1, pos;
			l1 = l;
			UL num = getHash(l,i);
			while(l<=i && !(pos=ha.find(num,i-l+1))){
			 ++l;
 num = getHash(l,i);
			}
			trie.ins(s,l1,l-1,i,pos);
		}
	}
}

int main(){
	int i, tt, Q;
	for(hashMi[0] = 1, i = 1; i < N; ++i)
		hashMi[i] = hashMi[i-1]*D;
	scanf("%d",&tt);
	while(tt--){
		scanf("%*d%d",&Q);
		scanf("%s",s);
		go();
		while(Q--){
		 LL k;
		 cin >> k;
			for(i=0;i<26;++i) scanf("%d",&v[i]);
			tot = 0;
			trie.dfs(0,0,1);
			sort(ans,ans+tot);
			for(i=0; i<tot; ++i)
				if(k>ans[i].second)
					k-=ans[i].second;
				else{
					printf("%d\n",ans[i].first);
					break;
				}
		}
		puts("");
	}
	return 0;
}





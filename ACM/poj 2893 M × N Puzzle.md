# 题目
The Eight Puzzle, among other sliding-tile puzzles, is one of the famous problems in artificial intelligence. Along with chess, tic-tac-toe and backgammon, it has been used to study search algorithms.

The Eight Puzzle can be generalized into an M × N Puzzle where at least one of M and N is odd. The puzzle is constructed with MN − 1 sliding tiles with each a number from 1 to MN − 1 on it packed into a M by N frame with one tile missing. For example, with M = 4 and N = 3, a puzzle may look like:

![2893_1.png](https://img11.360buyimg.com/ddimg/jfs/t1/196300/23/11083/4646/60dec05cEdd06f077/71368f76aaf5673a.png)

Let's call missing tile 0. The only legal operation is to exchange 0 and the tile with which it shares an edge. The goal of the puzzle is to find a sequence of legal operations that makes it look like:

![2893_2.png](https://img12.360buyimg.com/ddimg/jfs/t1/175188/18/17189/5801/60dec05cE9f2b0684/464a73f4e59547c5.png)

The following steps solve the puzzle given above.

![2893_3.png](https://img12.360buyimg.com/ddimg/jfs/t1/188915/19/11504/21627/60dec04dE1b050985/22d3babdeb811153.png)

Given an M × N puzzle, you are to determine whether it can be solved.

输入描述

The input consists of multiple test cases. Each test case starts with a line containing M and N (2 ≤ M, N ≤ 999). This line is followed by M lines containing N numbers each describing an M × N puzzle.

The input ends with a pair of zeroes which should not be processed.

输出描述

Output one line for each test case containing a single word <tt>YES</tt> if the puzzle can be solved and <tt>NO</tt> otherwise.

输入例子
```
3 3
1 0 3
4 2 5
7 8 6
4 3
1 2 5
4 6 9
11 8 10
3 7 0
0 0
```
输出例子
```
YES
NO
```
# 参考答案
```c++
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
int n,m,h0;
int i,j,g,h;
vector<int> map;

//merge sort
int countt;
vector<int> merge_tmp;
void merge_sort(vector<int>::iterator l,vector<int>::iterator r){
	if(l==r-1)
		return;
	vector<int>::iterator i,j,mid,now;
	mid = l+((r-l)>>1);
	merge_sort(l,mid);
	merge_sort(mid,r);
	merge_tmp.clear();
	for(i=l;i!=mid;i++)
		merge_tmp.push_back(*i);
	for(i=merge_tmp.begin(),j=mid,now=l;i!=merge_tmp.end() && j!=r;now++){
		if(*i <= *j){
			*now = *i;
			i++;
		}else{
			*now = *j;
			countt += merge_tmp.end()-i;
			j++;
		}
	}
	while(i!=merge_tmp.end())
		*(now++)=*(i++);
	while(j!=r)
		*(now++)=*(j++);
}

int main(){
	std::ios_base::sync_with_stdio(false);
	while(1){
		scanf("%d%d",&m,&n);
		//cin >> m >> n;
		if(m == 0 && n == 0)
			return 0;
		map.clear();
		for(i=0;i<m;i++)
			for(j=0;j<n;j++){
			//cin >> g;
			scanf("%d",&g);
			if(g == 0)
				h0=i;
			else
				map.push_back(g);
			}
		countt = 0;
		merge_sort(map.begin(),map.end());
		n &= 1;
		h0 = (m-h0-1)&1;
		//cout << "count" << countt << endl;
		countt &= 1;
		if(n==1){
			if(countt==0)
				printf("YES\n");
				//cout << "YES" << endl;
			else
				printf("NO\n");
				//cout << "NO" << endl;
		}
		if(n==0){
			if(countt ^ h0 == 0)
				printf("YES\n");
				//cout << "YES" << endl;
			else
				printf("NO\n");
				//cout << "NO" << endl;
		}
	}

}





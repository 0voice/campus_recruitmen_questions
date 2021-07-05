# 题目
"PATH" is a game played by two players on an N by N board, where N is a positive integer. (If N = 8, the board looks like a chess board.) Two players "WHITE" and "BLACK" compete in the game to build a path of pieces played on the board from the player's "home" edge to the player's "target" edge, opposite the home edge. WHITE uses white pieces and BLACK uses black pieces.
For this problem you will play the "referee" for the game, analyzing boards containing black and white pieces to determine whether either of the players has won the game or if one of the players can win by placing one of their pieces in an unfilled position. WHITE's turn is next.

A representation of a board on paper (and in a computer) is an N x N matrix of characters 'W', 'B', and 'U'; where W represents white pieces, B represents black pieces, and 'U' represents unfilled positions on the board.

When we view a matrix representation of the board on paper, WHITE's home edge is the left edge of the board (the first column), and WHITE's target edge is the right edge (the last column). BLACK's home edge is the top edge of the board (the first row), and BLACK's target edge is the bottom edge (the last row). Thus WHITE wants to build a path from left to right, and BLACK wants to build a path from top to bottom.

Two locations on the board are "adjacent" if one is immediately to the left, to the right above, or below the other. Thus an interior location on the board is adjacent to four other locations. For N > 1, corner locations each have two adjacent locations, and for N > 2, other border locations have three adjacent locations.

A path is a sequence of distinct positions on the board, L0, L1, ..., Lk, such that each pair Li and Li+1 are adjacent for i = 0, ..., k-1. A winning path for a player is a path L0, L1, ..., Lk filled with the player's pieces such that L0 is a position on the player's home edge and Lk is a position on the player's target edge. It is clear that if one player has a winning path then the other player is blocked from having a winning path. Thus if all the squares contain pieces, either there are no winning paths or exactly one of the players has at least one winning path.


Input

Input is a series of game board data sets. Each set begins with a line containing an integer specifying the size N, 0<N<81 of the (N * N) game board. This is followed by a blank line and then by N lines, one for each row of the game board, from the top row to the bottom row. Each line begins with character and consists of N adjacent characters from the set 'B', 'W', 'U'. A blank line separates each non-zero data set from the following data set. The input is terminated by a single line containing a board size of zero.


Output

As referee, for each game board in a series of game boards your program should report one of the five types of answers below:

White has a winning path.
Black has a winning path.
White can win in one move. (White can place a piece in an unfilled position)
Black can win in one move. (White can't win in one move AND Black can)
There is no winning path.


Sample Input
```
7

WBBUUUU
WWBUWWW
UWBBBWB
BWBBWWB
BWWBWBB
UBWWWBU
UWBBBWW

3

WBB
WWU
WBB

0
```

Sample Output
```
White has a winning path.
White can win in one move.
```

Discussion:

For the board, the shortest winning path for WHITE covers 15 locations. For the board, WHITE appears to have a path from top to bottom, but remember, WHITE wants a path from left to right.

# 参考答案
```c++
#include<queue>
#include<iostream>
#include<set>
#include<vector>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int N,A,B;
int board[84][84];
int eval[84][84];
struct Node {
	int x;
	int y;
	int step;
	struct cmp {
		int operator()(const Node &a, const Node &b){
			return a.step > b.step;
		}
	};
};
typedef priority_queue<Node,vector<Node>, Node::cmp> mypq;

void getInput(){
	int i,j;
	char ch;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			cin>>ch;
			if(ch=='W'){
				board[i][j] = 1;
			} else if(ch =='B'){
				board[i][j] = 2;
			} else { 
				board[i][j] = 0;
			}
		}
	}
}

void addNode(mypq &q, Node &one, int v){
	if(board[one.x][one.y] == v){
		if(eval[one.x][one.y] > one.step){
			eval[one.x][one.y] = one.step;
			q.push(one);
		}
	}else if(board[one.x][one.y] == 0){
		one.step ++;
		if(eval[one.x][one.y] > one.step ){
			eval[one.x][one.y] = one.step;
			q.push(one);
		}
	}
}

void getPathB(){
	mypq q;
	Node one;
	int i,j;

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			eval[i][j] = 99999999;
		}
	}

	one.x = 0;
	for(i=0;i<N;i++){
		one.y = i;
		if(board[0][i] == 2){
			one.step = 0;
			eval[0][i] = 0;
			q.push(one);
		} else if(board[0][i] == 0){
			one.step = 1;
			eval[0][i] = 1;
			q.push(one);
		}
	}
	while(!q.empty()){
		Node cur = q.top();
		if(cur.step > eval[cur.x][cur.y]){
			goto end;
		}
		if(cur.x == N-1){
			B = cur.step;
			return;
		}
		if(cur.x > 0){ 
			one.x = cur.x -1; one.y = cur.y;
			one.step = cur.step;
			addNode(q,one,2);
		}
		if(cur.x < N-1){ 
			one.x = cur.x + 1; one.y = cur.y;
			one.step = cur.step;
			addNode(q,one,2);
		}
		if(cur.y > 0){ 
			one.y = cur.y -1; one.x = cur.x;
			one.step = cur.step;
			addNode(q,one,2);
		}
		if(cur.y < N-1){ 
			one.y = cur.y + 1; one.x = cur.x;
			one.step = cur.step;
			addNode(q,one,2);
		}

	end:
		q.pop();
	}
	B = -1;
}

void getPathA(){
	mypq q;
	Node one;
	int i,j;

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			eval[i][j] = 99999999;
		}
	}

	one.y = 0;
	for(i=0;i<N;i++){
		one.x = i;
		if(board[i][0] == 1){
			one.step = 0;
			eval[i][0] = 0;
			q.push(one);
		} else if(board[i][0] == 0){
			one.step = 1;
			eval[i][0] = 1;
			q.push(one);
		}
	}
	while(!q.empty()){
		Node cur = q.top();
		if(cur.step > eval[cur.x][cur.y]){
			goto end;
		}
		if(cur.y == N-1){
			A = cur.step;
			return;
		}
		if(cur.x > 0){ 
			one.x = cur.x -1; one.y = cur.y;
			one.step = cur.step;
			addNode(q,one,1);
		}
		if(cur.x < N-1){ 
			one.x = cur.x + 1; one.y = cur.y;
			one.step = cur.step;
			addNode(q,one,1);
		}
		if(cur.y > 0){ 
			one.y = cur.y -1; one.x = cur.x;
			one.step = cur.step;
			addNode(q,one,1);
		}
		if(cur.y < N-1){ 
			one.y = cur.y + 1; one.x = cur.x;
			one.step = cur.step;
			addNode(q,one,1);
		}

	end:
		q.pop();
	}
	A = -1;
}

int main(){
	cin>>N;
	while(N){
		getInput();
		getPathA();
		if(A  != 0){
			getPathB();
		}
		if(A == 0){
			cout<<"White has a winning path."<<endl;
		} else if(B == 0){
			cout<<"Black has a winning path."<<endl;
		} else if(A == 1){
			cout<<"White can win in one move."<<endl;
		} else if (B == 1){
			cout<<"Black can win in one move."<<endl;
		} else {
			cout<<"There is no winning path."<<endl;
		}
		cin>>N;
	}

	return 0;
}




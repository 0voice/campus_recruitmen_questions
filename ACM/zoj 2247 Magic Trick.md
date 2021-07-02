# 题目
A magician invented a new card trick and presented it in the prestigious American Conference of Magicians (ACM). The trick was so nice it received the "Best Magic Award" at the conference. The trick requires three participants: the magician himself, a spectator and an assistant. During the trick the spectator is asked to shuffle a deck of 52 cards and pick randomly 5 cards out of the deck. The five cards are given to the assistant (without the magician seeing the cards) who looks at them and shows four of the five cards one by one to the magician. After seeing the four cards the magician magically guesses the missing fifth card!

The trick works because once the assistant has the five cards he can always choose four of them and use those to `code' information about the fifth one. The code is based on an ordering of the cards. Cards are ordered first by their suits and then by their face value. We will use the following order:
1. H 2. 1

Assume the spectator chose the cards JD, 8S, 7H, 8C, QH (Jack of Diamonds, 8 of Spades, 7 of Hearts, 8 of Clubs and Queen of Hearts). The strategy for the assistant is the following:

1. Find a suit s which appears at least twice in the set of chosen cards (Hearts in the example). If more than one suit appears two times, choose the one with lowest order.
2. Hide the card x with suit s that is at most six positions ahead in the cyclic order 1 
3. Show y to the magician. At this point the magician knows the suit of the hidden card, and also knows that the face value of the hidden card x is at most six positions in front of the face value of y.
4. With the three cards the assistant has left, he must code a number between 1 and 6. That can be done as follows. Say the three cards z1 , z2 , z3 are in the order z1 -- z1, z2, z3 means 1,
-- z1, z3, z2 means 2,
-- z2, z1, z3 means 3,
-- z2, z3, z1 means 4,
-- z3, z1, z2 means 5,
-- z3, z2, z1 means 6.

In this way, once the magician is shown the four cards one by one, he has enough information to "magically" guess the fifth one!

Your job is to develop a program that, given the four cards shown by the assistant, informs the magician which is the hidden card.

Input

The input contains several test cases. The first line in the input contains an integer N specifying the number of test cases (1 N

Output

For each test case in the input your program must produce one line of output, containing the description of the hidden card.

Sample Input
```
2
7H 8S 8C JD
TC 2D 1S 5H
```
Sample Input
```
QH
1C
```
# 参考答案
```c++
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<map>
using namespace std;
enum {
    SIZ = 3,
};
struct Node {
    int v;
    int t;
    bool operator<(const Node&rhs){
        if(t!=rhs.t){
            if(t < rhs.t)
                return true;
            return false;
        }
        if(v < rhs.v)
            return true;
        return false;
    }
};
Node tree[SIZ];
map<int,int> tab;
static char face[] = {'T','J','Q', 'K'};
static char suit[] = {'H','C','D', 'S'};
inline char v2f(char c){
    c += 12;
    c %= 13;
    c += 1;
    if(c<=9)
        return c +'0';
    c -= 10;
    return face[c];
}
inline char f2v(char c){
    if(c <= '9'){
        return c-'0';
    }
    for(int i=0;i<sizeof(face);i++){
        if(face[i] == c){
            return i + 10;
        }
    }
    return 0;
}
void convert(Node &one, string &s){
    int i;
    for(i=0;i<sizeof(suit);i++){
        if(s[1]== suit[i]){
            one.t = i;
            break;
        }
    }
    one.v = f2v(s[0]);
}

inline void insert(int a, int b, int v){
    int key = (a<<4)+b;
    tab[key] = v;
}
void init(){
    insert(0,2,1);
    insert(0,1,2);
    insert(1,2,3);
    insert(2,1,4);
    insert(1,0,5);
    insert(2,0,6);
}
char type, val;
void readIn(){
    string s;
    cin>>s;
    type = s[1];
    val = f2v(s[0]);
    for(int i=0;i<SIZ;i++){
        cin>>s;
        convert(tree[i], s);
    }
}
int getVal(){
    int a,b; 
    if(tree[0] < tree[1]){
        a = 1; b = 0;
    } else {
        a = 0, b= 1;
    }
    if(tree[a] < tree[2]){
        a = 2;
    } else if(tree[2] < tree[b]){
        b = 2;
    }
    int key = (b<<4) + a;
    return tab[key];
}

int fun(){
    int t=getVal();
    val += t;
    val --;
    val %= 13;
    val ++;
    val = v2f(val);
    cout<<val<<type<<endl;
}

int main(){
    init();
    int tstcase;
    cin>>tstcase;
    while(tstcase --){
        readIn();
        fun();
    }

    return 0;
}

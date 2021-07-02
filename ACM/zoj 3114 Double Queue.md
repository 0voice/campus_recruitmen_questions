# 题目
The new founded Balkan Investment Group Bank (BIG-Bank) opened a new office in Bucharest, equipped with a modern computing environment provided by IBM Romania, and using modern information technologies. As usual, each client of the bank is identified by a positive integer K and, upon arriving to the bank for some services, he or she receives a positive integer priority P. One of the inventions of the young managers of the bank shocked the software engineer of the serving system. They proposed to break the tradition by sometimes calling the serving desk with the lowest priority instead of that with the highest priority. Thus, the system will receive the following types of request:
```
0	The system needs to stop serving

1 K P	Add client K to the waiting list with priority P

2	Serve the client with the highest priority and drop him or her from the waiting list

3	Serve the client with the lowest priority and drop him or her from the waiting list
```
Your task is to help the software engineer of the bank by writing a program to implement the requested serving policy.

Input

Each line of the input contains one of the possible requests; only the last line contains the stop-request (code 0). You may assume that when there is a request to include a new client in the list (code 1), there is no other request in the list of the same client or with the same priority. An identifier K is always less than 106, and a priority P is less than 107. The client may arrive for being served multiple times, and each time may obtain a different priority.

Output

For each request with code 2 or 3, the program has to print, in a separate line of the standard output, the identifier of the served client. If the request arrives when the waiting list is empty, then the program prints zero (0) to the output.

Sample Input
```
2
1 20 14
1 30 3
2
1 10 99
3
2
2
0
```
Sample Output
```
0
20
30
10
0
```
# 参考答案
```c++
#include <cmath>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long LL;

struct Client {
 int id, val;
 Client() { }
 Client(int x, int y) : id(x), val(y) { }
};
struct great {
 bool operator ()(const Client& a, const Client& b) {
 return a.val > b.val;
 }
};
struct small {
 bool operator ()(const Client& a, const Client& b) {
 return a.val < b.val;
 }
};

set<Client, great> s1;
set<Client, small> s2;

int main() {
 int q;
 while (~scanf("%d", &q), q) {
 if (q == 1) {
 int p, q;
 scanf("%d%d", &p, &q);
 s1.insert(Client(p, q));
 s2.insert(Client(p, q));
 }
 if (q == 2) {
 if (s1.empty()) {
 printf("0\n");
 } else {
 Client ans = *(s1.begin());
 printf("%d\n", ans.id);
 s1.erase(ans);
 s2.erase(ans);
 }
 }
 if (q == 3) {
 if (s2.empty()) {
 printf("0\n");
 } else {
 Client ans = *(s2.begin());
 printf("%d\n", ans.id);
 s1.erase(ans);
 s2.erase(ans);
 }
 }
 }
 return 0;
}




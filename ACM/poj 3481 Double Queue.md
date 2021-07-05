# 题目
The new founded Balkan Investment Group Bank (BIG-Bank) opened a new office in Bucharest, equipped with a modern computing environment provided by IBM Romania, and using modern information technologies. As usual, each client of the bank is identified by a positive integer K and, upon arriving to the bank for some services, he or she receives a positive integer priority P. One of the inventions of the young managers of the bank shocked the software engineer of the serving system. They proposed to break the tradition by sometimes calling the serving desk with the lowest priority instead of that with the highest priority. Thus, the system will receive the following types of request:
```
0 	                The system needs to stop serving
1KP	                Add client K to the waiting list with priority P
2                   Serve the client with the highest priority and drop him or her from the waiting list
3 	                Serve the client with the lowest priority and drop him or her from the waiting list
```
Your task is to help the software engineer of the bank by writing a program to implement the requested serving policy.

输入描述

Each line of the input contains one of the possible requests; only the last line contains the stop-request (code 0). You may assume that when there is a request to include a new client in the list (code 1), there is no other request in the list of the same client or with the same priority. An identifier K is always less than 106, and a priority P is less than 107. The client may arrive for being served multiple times, and each time may obtain a different priority.

输出描述

For each request with code 2 or 3, the program has to print, in a separate line of the standard output, the identifier of the served client. If the request arrives when the waiting list is empty, then the program prints zero (0) to the output.

输入例子
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
输出例子
```
0
20
30
10
0
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#define MAXD 1000010
int T, node, key[MAXD], client[MAXD], left[MAXD], right[MAXD], size[MAXD];
void left_rotate(int &T)
{
    int k = right[T];
    right[T] = left[k];
    left[k] = T;
    size[k] = size[T];
    size[T] = size[left[T]] + size[right[T]] + 1;
    T = k;
}
void right_rotate(int &T)
{
    int k = left[T];
    left[T] = right[k];
    right[k] = T;
    size[k] = size[T];
    size[T] = size[left[T]] + size[right[T]] + 1;
    T = k;
}
void maintain(int &T, int flag)
{
    if(flag == 0)
    {
        if(size[left[left[T]]] > size[right[T]])
            right_rotate(T);
        else if(size[right[left[T]]] > size[right[T]])
            left_rotate(left[T]), right_rotate(T);
        else
            return ;
    }
    else
    {
        if(size[right[right[T]]] > size[left[T]])
            left_rotate(T);
        else if(size[left[right[T]]] > size[left[T]])
            right_rotate(right[T]), left_rotate(T);
        else
            return ;

    }
    maintain(left[T], 0);
    maintain(right[T], 1);
    maintain(T, 0);
    maintain(T, 1);
}
void add(int &T, int c, int v)
{
    T = ++ node;
    size[T] = 1;
    client[T] = c;
    key[T] = v;
    left[T] = right[T] = 0;
}
void Insert(int &T, int c, int v)
{
    if(T == 0)
    {
        add(T, c, v);
        return ;
    }
    ++ size[T];
    if(v < key[T])
        Insert(left[T], c, v);
    else
        Insert(right[T], c, v);
    maintain(T, v >= key[T]);
}
int Delete(int &T, int v)
{
    if(v == key[T] || (v < key[T] && left[T] == 0) ||(v > key[T] && right[T] == 0))
    {
        int k = key[T];
        if(left[T] == 0 || right[T] == 0)
            T = left[T] + right[T];
        else
            key[T] = Delete(left[T], key[T] + 1);
        return k;
    }
    if(v < key[T])
        return Delete(left[T], v);
    else
        return Delete(right[T], v);
}
void select(int &T, int k, int &c, int &v)
{
    int n = size[left[T]] + 1;
    if(n == k)
    {
        c = client[T];
        v = key[T];
        Delete(T, v);
        return ;
    }
    -- size[T];
    if(k < n)
        select(left[T], k, c, v);
    else
        select(right[T], k - n, c, v);
}
int main()
{
    int k, c, v;
    node = T = left[0] = right[0] = size[0] = 0;
    for(;;)
    {
        scanf("%d", &k);
        if(!k)
            break;
        if(k == 1)
        {
            scanf("%d%d", &c, &v);
            Insert(T, c, v);
        }
        else if(k == 2)
        {
            if(size[T])
            {
                select(T, size[T], c, v);
                printf("%d\n", c);
            }
            else
                printf("0\n");
        }
        else
        {
            if(size[T])
            {
                select(T, 1, c, v);
                printf("%d\n", c);
            }
            else
                printf("0\n");
        }
    }
    return 0;
}




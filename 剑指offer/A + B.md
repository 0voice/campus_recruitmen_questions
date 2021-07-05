# 题目
输入两个整数，求这两个整数的和是多少。

输入格式

输入两个整数A,B，用空格隔开，0≤A,B≤10的8次幂

输出格式

输出一个整数，表示这两个数的和

样例输入：
```
3 4
```
样例输出：
```
7
```

# 参考答案
### c++代码
```c++
#include <iostream>

using namespace std;

int main () {
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
    return 0;
}
```
### C 代码
```c
#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", a + b);
    return 0;
}
```
### Java 代码
```java
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String args[]) throws Exception {
        Scanner cin=new Scanner(System.in);
        var a = cin.nextInt();
        var b = cin.nextInt();
        System.out.println(a + b);
    }
}
```
### Python 代码
```Python
import sys

for line in sys.stdin:
    print sum(map(int, line.split()))
```
### Javascript 代码
```Javascript
var fs = require('fs');
var buf = '';

process.stdin.on('readable', function() {
  var chunk = process.stdin.read();
  if (chunk) buf += chunk.toString();
});

process.stdin.on('end', function() {
  buf.split('\n').forEach(function(line) {
    var tokens = line.split(' ').map(function(x) { return parseInt(x); });
    if (tokens.length != 2) return;
    console.log(tokens.reduce(function(a, b) { return a + b; }));
  });
});
```
### Go 代码
```Go
package main

import "fmt"

func main() {
  var a, b int
  for {
    n, _ := fmt.Scanf("%d %d", &a, &b)
    if n != 2 { break }
    fmt.Println(a + b)
  }
}
```

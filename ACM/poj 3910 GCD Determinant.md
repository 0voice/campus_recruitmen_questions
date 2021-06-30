# 题目
We say that a set S = {x1, x2, ..., xn} is factor closed if for any xi ∈ S and any divisor d of xi we have d ∈ S. Let’s build a GCD matrix (S) = (sij), where sij = GCD(xi, xj) – the greatest common divisor of xi and xj. Given the factor closed set S, find the value of the determinant:

<center>Errorr！</center>

输入描述

The input file contains several test cases. Each test case starts with an integer n (0 9. The input data set is correct and ends with an end of file.

输出描述

For each test case find and print the value Dn mod 1000000007.

输入例子

* 2 
* 1 2 
* 3 
* 1 3 9 
* 4 
* 1 2 3 6


输出例子
* 1 
* 12 
* 4

# 参考答案
    #include<iostream>
    using namespace std;

    int phi(int n){  
      int i,ans=n;
      for(i=2;i*i<=n;i++){
        if(n%i==0){
          ans=ans/i*(i-1);
          while(n%i==0) n/=i;
        }
      }
      if(n>1) ans=ans/n*(n-1);
      return ans;
    }

    int main(){
      int n,m;
      while(cin>>n){
        long long ans=1;
        while(n--){
          cin>>m;
          ans*=phi(m);
          if(ans>=1000000007) ans%=1000000007;
        }
        cout<<ans<<endl;
      }
      return 0;
    }

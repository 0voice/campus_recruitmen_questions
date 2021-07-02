# 题目
RSA is the best-known public key encryption algorithm. In this algorithm each participant has a private key that is shared with no one else and a public key which is published so everyone knows it. To send a secure message to this participant, you encrypt the message using the widely known public key; the participant then decrypts the messages using his or her private key. Here is the procedure of RSA:

First, choose two different large prime numbers P and Q, and multiply them to get N (= P * Q).<br>
Second, select a positive integer E (0 Third, compute the decryption key D such that 0<br>
Now the public key is constructed by the pair {E, N}, and the private key is {D, N}. P and Q can be discarded.<br>

Encryption is defined by C = (M ^ E) mod N, and decryption is defined by M = (C ^ D) mod N, here M, which is a non-negative integer and smaller than N, is the plaintext message and C is the resulting ciphertext.

To illustrate this idea, let’s see the following example:
We choose P = 37, Q = 23, So N = P * Q = 851, and T = 792. If we choose E = 5, D will be 317 ((5 * 317) mod 792 = 1). So the public key is {5, 851}, and the private key is {317, 851}. For a given plaintext M = 7, we can get the ciphertext C = (7 ^ 5) mod 851 = 638.

As we have known,for properly choosen very large P and Q, it will take thousands of years to break a key, but for small ones, it is another matter.
Now you are given the ciphertext C and public key {E, N}, can you find the plaintext M?<br>
输入描述<br>
The input will contain several test cases. Each test case contains three positive integers C, E<br>
输出描述<br>
Output the plaintext M in a single line.<br>
输入例子<br>
```
638 5 851
```
输出例子
```
7
```
# 参考答案
```c++
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef long long LL;
#define maxn 10000
const int S=20;

LL factor[maxn];
int tot;

LL muti_mod(LL a,LL b,LL c){    
    a%=c;
    b%=c;
    LL ret=0;
    while (b){
        if (b&1){
            ret+=a;
            if (ret>=c) ret-=c;
        }
        a<<=1;
        if (a>=c) a-=c;
        b>>=1;
    }
    return ret;
}

LL pow_mod(LL x,LL n,LL mod){  
    if (n==1) return x%mod;
    int bit[64],k=0;
    while (n){
        bit[k++]=n&1;
        n>>=1;
    }
    LL ret=1;
    for (k=k-1;k>=0;k--){
        ret=muti_mod(ret,ret,mod);
        if (bit[k]==1) ret=muti_mod(ret,x,mod);
    }
    return ret;
}

bool check(LL a,LL n,LL x,LL t){   
    LL ret=pow_mod(a,x,n),last=ret;
    for (int i=1;i<=t;i++){
        ret=muti_mod(ret,ret,n);
        if (ret==1&& last!=1&& last!=n-1) return 1;
        last=ret;
    }
    if (ret!=1) return 1;
    return 0;
}

bool Miller_Rabin(LL n){
    LL x=n-1,t=0;
    while ((x&1)==0) x>>=1,t++;
    bool flag=1;
    if (t>=1&& (x&1)==1){
        for (int k=0;k<S;k++){
            LL a=rand()%(n-1)+1;
            if (check(a,n,x,t)) {flag=1;break;}
            flag=0;
        }
    }
    if (!flag || n==2) return 0;
    return 1;
}

LL gcd(LL a,LL b){
    if (a==0) return 1;
    if (a<0) return gcd(-a,b);
    while (b){
        LL t=a%b; a=b; b=t;
    }
    return a;
}

LL Pollard_rho(LL x,LL c){
    LL i=1,x0=rand()%x,y=x0,k=2;
    while (1){
        i++;
        x0=(muti_mod(x0,x0,x)+c)%x;
        LL d=gcd(y-x0,x);
        if (d!=1&& d!=x){
            return d;
        }
        if (y==x0) return x;
        if (i==k){
            y=x0;
            k+=k;
        }
    }
}

void findfac(LL n){           
    if (!Miller_Rabin(n)){
        factor[tot++] = n;
        return;
    }
    LL p=n;
    while (p>=n) p=Pollard_rho(p,rand() % (n-1) +1);
    findfac(p);
    findfac(n/p);
}

void gcdExtend(long long a,long long b,long long &d,long long &x,long long &y)
{
     if(!b) {d=a;x=1;y=0;return;}
     gcdExtend(b,a%b,d,y,x);
     y-=a/b*x;
}

int main()
{
    LL C, E, N, T, M, D;
    LL x, y, d;
    while (~scanf("%lld%lld%lld", &C, &E, &N))
    {
        tot = 0;
        findfac(N);
        T = (factor[0] - 1) * (factor[1] - 1);
        gcdExtend(E, T, d, x, y);
        D = (x % T + T) % T;
        M = pow_mod(C, D, N);
        printf("%lld\n", M);
    }
    return 0;
}

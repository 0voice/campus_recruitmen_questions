# 题目
A bus ticket is called 'lucky', if in its number, which consists of 2n digits (the number may have leading zeros), the sum of the first n digits equals the sum of the last n digits. A passenger wants to certainly ride with a lucky ticket. He buys a ticket, checks its number, and then, if necessary, buys a few more tickets with successive numbers. How many additional tickets will the passenger have to buy, having spent the minimum sum of money?

1 <= n <= 10

Input

The input file contains a line of 2n digits, which may have several leading zeroes - the number of the first ticket.

Process to the end of file.


Output

The output file must contain a number - the amount of the additionally bought tickets.

Sample Input
```
025071
```

Sample Output
```
35
```
# 参考答案
```c++
#include <iostream>
#include <cstring>
using namespace std;
int main(){
	char input[21],temp[21],num[21];
	long n,sum[2],i,j,dif;
	while(cin>>input){
		strcpy(temp,input);
		n=strlen(input)/2;
		sum[0]=sum[1]=0;
		for(i=0;i<n;i++) 
			sum[0]+=input[i]-'0';
		j=2*n;
		for(;i<j;i++) 
			sum[1]+=input[i]-'0';
		i=2*n-1;
		while(sum[1]>sum[0]){
			sum[1]-=temp[i]-'0';
			temp[i]='0';
			j=i-1;
			while(temp[j]=='9'&&j>=n){
				sum[1]-=9;
				temp[j]='0';
				j--;
			}
			if(j==n-1){
				while(temp[j]=='9'){
					sum[0]-=9;
					temp[j]='0';
					j--;
				}
				temp[j]+=1;
				sum[0]++;
			}
			else{
				temp[j]+=1;
				sum[1]++;
			}
			i--;
		}
		dif=sum[0]-sum[1];
		i=2*n-1;
		while(1){
			if('9'-temp[i]>=dif){
				temp[i]+=dif;
				break;
			}
			else{
				dif-='9'-temp[i];
				temp[i]='9';
			}
			i--;
		}
		for(i=0;i<20;i++) num[i]='0';
		long carry(0);
		for(i=2*n-1;i>=0;i--){
			j=temp[i]-carry-input[i];
			if(j<0){
				num[i]=10+j+'0';
				carry=1;
			}
			else{
				num[i]=j+'0';
				carry=0;
			}
		}		
		j=2*n;
		for(i=0;i<j-1;i++){
		if(num[i]!='0') break;
		}
		for(;i<j;i++) cout<<num[i];
			cout<<endl;
	}
	return 0;
}




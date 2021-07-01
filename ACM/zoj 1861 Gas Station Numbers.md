# 题目
Many gas stations use plastic digits on an illuminated sign to indicate prices. When there is an insufficient quantity of a particular digit, the attendant may substitute another one upside down.

The digit "6" looks much like "9" upside down. The digits "0", "1" and "8" look like themselves. The digit "2" looks a bit like a "5" upside down (well, at least enough so that gas stations use it).
Due to rapidly increasing prices, a certain gas station has used all of its available digits to display the current price. Fortunately, this shortage of digits need not prevent the attendant from raising prices. She can simply rearrange the digits, possibly reversing some of them as described above.

Your job is to compute, given the current price of gas, the next highest price that can be displayed using exactly the same digits.

Input

The input consists of several lines, each containing between 2 and 30 digits (to account for future prices) and a decimal point immediately before the last digit. There are no useless leading zeroes; that is, there is a leading zero only if the price is less than 1.

Output

You are to compute the next highest price that can be displayed using the same digits and the same format rules. An input line containing a decimal point alone terminates the input. If the price cannot be raised, print "The price cannot be raised."

Sample Input

* 65.2
* 76.7
* 77.7
* .

Sample Output
* 65.5
* 77.6
The price cannot be raised.

# 参考答案
    #include<iostream>
    #include<vector>
    #include<string.h>
    #include<stdio.h>
    #include<algorithm>
    #include<cmath>
    using namespace std;
    enum {
        SIZ = 40,
    };

    char rep[10] = {0, 1, 5, 3, 4, 2, 9, 7, 8, 6};
    char dig[SIZ];
    int len;

    int fun(){
        int i, t = dig[len], hi;
        if(rep[t] > t){
            dig[len] = rep[t];
            return 1;
        }
        hi = t;
        for(i=len-1; i>=0; i--){
            t = dig[i];
            if(t < hi || rep[t] > t){
                int k=i;
                for(int j=i+1;j<=len;j++){
                    t = dig[j];
                    if(t > dig[i] && t <= hi){
                        hi = t;
                        k = j;
                    }
                    if(rep[t] > dig[i] && rep[t] <= hi){
                        hi = rep[t];
                        dig[j] = rep[t];
                        k = j;
                    }
                }
                t = dig[i];
                if(rep[t] > t && (hi < t || hi > rep[t])){
                    dig[i] = rep[t];
                } else {
                    swap(dig[i], dig[k]);
                }
                for(k= i+1; k<=len; k++){
                    dig[k] = min(dig[k], rep[dig[k]]);
                }
                sort(dig+i+1, dig+len+1);
                return 1;
            }
            hi = max(hi, t);
        }
        return 0;
    }

    void trim(){
        len = 0;
        for(int i=0; dig[i]; i++){
            if(dig[i]!='.'){
                dig[len++] = dig[i] - '0';
            }
        }
        dig[len--] = 0;
    }
    void output(int s){
        if(s <=0){
            printf("The price cannot be raised.\n");
            return ;
        }
        for(s=0; s<len; s++){
            printf("%d", dig[s]);
        }
        printf(".%d\n", dig[len]);
    }
    int main(){

        scanf("%s", dig);
        while(dig[0]!='.'){
            trim();
            output(fun());
            scanf("%s", dig);
        }
        return 0;
    }

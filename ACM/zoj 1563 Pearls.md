# 题目
In Pearlania everybody is fond of pearls. One company, called The Royal Pearl, produces a lot of jewelry with pearls in it. The Royal Pearl has its name because it delivers to the royal family of Pearlania. But it also produces bracelets and necklaces for ordinary people. Of course the quality of the pearls for these people is much lower then the quality of pearls for the royal family. In Pearlania pearls are separated into 100 different quality classes. A quality class is identified by the price for one single pearl in that quality class. This price is unique for that quality class and the price is always higher then the price for a pearl in a lower quality class.

Every month the stock manager of The Royal Pearl prepares a list with the number of pearls needed in each quality class. The pearls are bought on the local pearl market. Each quality class has its own price per pearl, but for every complete deal in a certain quality class one has to pay an extra amount of money equal to ten pearls in that class. This is to prevent tourists from buying just one pearl.

Also The Royal Pearl is suffering from the slow-down of the global economy. Therefore the company needs to be more efficient. The CFO (chief financial officer) has discovered that he can sometimes save money by buying pearls in a higher quality class than is actually needed. No customer will blame The Royal Pearl for putting better pearls in the bracelets, as long as the prices remain the same.

For example 5 pearls are needed in the 10 Euro category and 100 pearls are needed in the 20 Euro category. That will normally cost: (5+10)*10 + (100+10)*20 = 2350 Euro.

Buying all 105 pearls in the 20 Euro category only costs: (5+100+10)*20 = 2300 Euro.

The problem is that it requires a lot of computing work before the CFO knows how many pearls can best be bought in a higher quality class. You are asked to help The Royal Pearl with a computer program.

Given a list with the number of pearls and the price per pearl in different quality classes, give the lowest possible price needed to buy everything on the list. Pearls can be bought in the requested, or in a higher quality class, but not in a lower one.

Input

The first line of the input contains the number of test cases. Each test case starts with a line containing the number of categories c (1 <= c <= 100). Then, c lines follow, each with two numbers ai and pi. The first of these numbers is the number of pearls ai needed in a class (1 <= ai <= 1000). The second number is the price per pearl pi in that class (1 <= pi <= 1000). The qualities of the classes (and so the prices) are given in ascending order. All numbers in the input are integers.

Output

For each test case a single line containing a single number: the lowest possible price needed to buy everything on the list.

Sample Input
* 2
* 2
* 100 1
* 100 2
* 3
* 1 10
* 1 11
* 100 12

Sample Output
* 330
* 1344

# 参考答案
    #include <iostream>
    #include <cstdio>
    #include <cstdlib>
    #include <algorithm>
    #include <queue>
    #include <stack>
    #include <map>
    #include <cstring>
    #include <climits>
    #include <cmath>
    #include <cctype>

    typedef long long ll;
    using namespace std;

    struct pearls
    {
        int num;
        int price;
    }a[110];

    int dp[110];
    const int zui = 100000000;

    int main()
    {
        int t,n,i,j;
        scanf("%d",&t);
        while(t--)
        {
            memset(dp,0,sizeof(dp));
            scanf("%d",&n);
            for(i=1; i<=n; i++)//从1开始赋值，因为以后要用到dp[0]
            {
                scanf("%d%d",&a[i].num,&a[i].price);
            }
            dp[1] = (a[1].num+10)*a[1].price;
            int sum;
            for(i=2; i<=n; i++)
            {
                sum = a[i].num;
                dp[i] = dp[i-1] + (a[i].num + 10) * a[i].price;
                for(j=i-1; j>=1; j--)
                {
                    sum += a[j].num;
                    dp[i] = min(dp[i],(sum+10)*a[i].price+dp[j-1]);
                }
            }
            printf("%d\n",dp[n]);
        }
        return 0;
    }

# 题目
Estelle Bright goes to Casino & Bar Lavantar to gamble. Among all the games, playing Poker is most possible to make much money (which is called Mira here), so Estelle decide to play this. But gambling has never been easy. Fortunately, with the help of Scherazard Harvey, she can know the queue of coming cards. However, this's not enough. So she still need bright Klose Rinz, the smart and beautiful princess, to help her to find the best strategy.

The rules of playing Poker are as follows:

this game will use 4 * 13 = 52 kinds of cards, each infinity. At the beginning of each game, you should choose a bet in range 1 ~ 10 and you need to pay bet medals. You always begin with a rate 1

each round, you will be given 5 cards first, then you can choose some (0 ~ 5) of them to hold and change the other ones, at last the 5 cards make up your hand

after each round, according the category of your hand, the rate will multiply a different number. If your rate is 0, the game is over, or you can choose to continue playing or not. You will get bet * rate medals (1 Mira = 5 medals) at the end of the game

a hand always consists of five cards, here are the categories of the hands:
Category |	Bonus |	Definition
-|-----|-
No pair |	Rate* 0 |	A no pair hand is a poker hand in which no two cards have the same rank, the five cards are not in sequence, and the five cards are not all the same suit.
One pair |	Rate* 2 |	One pair is a poker hand which contains two cards of the same rank, plus three other unmatched cards.
Two pair |	Rate* 3	| A poker hand such as which contains two cards of the same rank, plus two cards of another rank (that match each other but not the first pair), plus one unmatched card, is called two pair.
Three of a kind	| Rate* 4	| Three of a kind is a poker hand which contains three cards of the same rank, plus two unmatched cards.
Straight	| Rate* 8	| A straight is a poker hand which contains five cards of sequential rank but in more than one suit. HA H2 H3 H4 D5 is not a straight.
Flush |	Rate* 10 |	A flush is a poker hand which contains five cards of the same suit, not in rank sequence.
Full house	| Rate* 15 |	A full house is a hand which contains three matching cards of one rank, and two matching cards of another rank.
Four of a kind |	Rate* 50	| Four of a kind is a poker hand such which contains no less than four cards of one rank, and an unmatched card of another rank.
Straight flush	| Rate* 100 |	A straight flush is a poker hand which contains five cards in sequence, all of the same suit.
Royal flush |	Rate* 500	| An ace-high straight flush such as HA HK HQ HJ HT is known as a royal flush

the rate can be 9999 at most, if it's turning to a number larger than 9999, then it will turn to 9999

Assuming that Estelle has 16 medals initially, how much medals can she has with the help of Klose after playing Poker once? Scherazard might cannot predict enough number of cards, Klose will never make a strategy that need unknown cards!

![zoj_2033desc_1](http://uploadfiles.nowcoder.com/probs/acm/zoj_2033desc_1.jpg)

Input

Each case begins with a number 16 <= n <= 160 indicating the size of the cards queue predicted by Scherazard. Then n string whose length is exactly 2 indicating the cards in order. Cards will be represented in format "suit rank" where suit is one of 'H', 'S', 'D', 'C' and rank is one of '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'.

Output

Output the maximum number of medals in a separate line.

Sample Input
```
32
HA SA DA CA H2 HK HQ HJ HT C3 D3 DQ C7 H9 S3 D4 C6 H8 ST DQ CA H5 S3 D9 C7 HJ SK D8 C6 H4 C2 DT
```
Sample Output
```
20006
```
Note<br>
Strategy of the sample:<br>
bet = 10<br>
get cards: HA SA DA CA H2; change cards: SA DA CA H2; get: HK HQ HJ HT<br>
hand: HA HK HQ HJ HT; royal flush; rate * 500<br>
continue<br>
get cards: C3 D3 DQ C7 H9; hold cards: C3 D3 *; change at leaset one card<br>
hand: C3 D3 S3 *; three of a kind; rate * 4<br>
don't continue<br>
The background comes from the famous RPG game the Legend of Heroes: Sora no Kiseki Second Chapter by Nihon Falcom Corporation.<br>

# 参考答案
```c++
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Hand;

class Card
{
        friend class Hand;
    private:
        int suit, rank;
    public:
        friend bool operator<(const Card& lhs, const Card& rhs)
        {
            return lhs.rank < rhs.rank;
        }
        friend istream& operator>>(istream& is, Card& c)
        {
            char ch;

            is >> ch;
            switch(ch) {
                case 'H': c.suit = 0; break;
                case 'S': c.suit = 1; break;
                case 'D': c.suit = 2; break;
                case 'C': c.suit = 3; break;
                default: throw "INVAILD_SUIT";
            }
            is >> ch;
            switch(ch) {
                case 'T': c.rank = 10; break;
                case 'J': c.rank = 11; break;
                case 'Q': c.rank = 12; break;
                case 'K': c.rank = 13; break;
                case 'A': c.rank = 14; break;
                default:
                    if (!(ch >= '2' && ch <= '9')) {
                        throw "INVALID_RANK";
                    }
                    c.rank = ch - '0'; break;
            }

            return is;
        }
};

class Hand
{
    private:
        vector<Card> vc;
        bool isflush()
        {
            for (size_t i = 1; i < 5; i++) {
                if (vc[i].suit != vc[0].suit) {
                    return false;
                }
            }
            return true;
        }
        bool isstraihgt()
        {
            for (size_t i = 1; i < 5; i++) {
                if (vc[i].rank != vc[0].rank + i) {
                    return false;
                }
            }
            return true;
        }
        bool has_4()
        {
            return vc[0].rank == vc[3].rank || vc[1].rank == vc[4].rank;
        }
        bool has_3_2()
        {
            return vc[0].rank == vc[2].rank && vc[3].rank == vc[4].rank ||
                vc[0].rank == vc[1].rank && vc[2].rank == vc[4].rank;
        }
        bool has_3()
        {
            for (int i = 2; i < 5; i++) {
                if (vc[i - 2].rank == vc[i].rank) {
                    return true;
                }
            }
            return false;
        }
        int cnt_2()
        {
            int ret = 0;

            for (int i = 1; i < 5; i++) {
                if (vc[i].rank == vc[i - 1].rank) {
                    ++ret;
                }
            }

            return ret;
        }
    public:
        void add(const Card& c)
        {
            vc.push_back(c);
        }
        int rate()
        {
            if (vc.size() != 5) {
                throw "INVALID_HAND";
            }
            sort(vc.begin(), vc.end());

            bool flush = isflush(), straihgt = isstraihgt();

            if (flush && straihgt) {
                return (vc[4].rank == 14) ? 500 : 100;
            }
            else if (has_4()) {
                return 50;
            }
            else if (has_3_2()) {
                return 15;
            }
            else if (flush) {
                return 10;
            }
            else if (straihgt) {
                return 8;
            }
            else if (has_3()) {
                return 4;
            }
            else {
                switch (cnt_2()) {
                    case 2: return 3;
                    case 1: return 2;
                    case 0: return 0;
                    default: throw "INVAILD_CNT_2";
                }
            }
        }
};

int rate(const vector<Card>& vc)
{
    int ret = 0;
    vector<bool> p(5, false);

    for (size_t i = vc.size() - 5; i < 5; i++) {
        p[i] = true;
    }
    do {
        Hand h;

        for (size_t i = 0; i < 5; i++) {
            if (p[i]) {
                h.add(vc[i]);
            }
        }
        for (size_t i = 5; i < vc.size(); i++) {
            h.add(vc[i]);
        }
        ret = max(ret, h.rate());
    } while (next_permutation(p.begin(), p.end()));

    return ret;
}

int main(void)
{
    int n;

    while (cin >> n) {
        vector<Card> vc(n);
        for (int i = 0; i < n; i++) {
            cin >> vc[i];
        }

        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 5; i <= n; i++) {
            for (int j = max(0, i - 10); j <= i - 5; j++) {
                dp[i] = max(dp[i], min(9999, dp[j] * rate(vector<Card>(vc.begin() + j, vc.begin() + i))));
            }
        }

        int ans = *max_element(dp.begin() + 5, dp.end());
        cout << 16 + ((ans == 0) ? -1 : (10 * (ans - 1))) << endl;
    }

    return 0;
}




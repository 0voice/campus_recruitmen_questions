# 题目
```
… Los babilonios se entregaron al juego. El que no adquiría suertes era considerado un pusilánime, un apocado. Con el tiempo, 
ese desdén justificado se duplicó.Era despreciado el que no jugaba, pero también era despreciados los perdedores que abonaban 
la multa …

Jorge Luis Borges, La lotería de Babilonia, Ficciones
```
People of Babylon were devoted to chance games and one of the most popular was a special kind of roulette. Recently, some old Babylonian tablets were found. They described details of the roulette game.

In modern terms, the rules of the game were as follows:

Roulette’s compartments had only six labels: -1, -2, -3,

        1, 2, 3.
      
The game was played by turns, during a day. Turns were numerated 0, 1, 2, ...<br>
Players could win or lose a multiple of the bet, a quantity of money that was constant along the day.<br>
At turn t there was an amount of money Pt , called the pot.<br>
At the start, there was an initial amount of money P 0 in the pot.<br>
P 0 and the bet were positive numbers arbitrarily defined by the King.<br>
In a turn, a player turned the roulette. A player could not play more than once in a day. Depending on the compartment where the ball came to rest, the player won (or lose, if the value was negative) an mount wt = L * bet of money, where L corresponded to the compartment’s label.
The won money was taken from the pot (or put in it if the player lose), i.e. the value of the pot in a given turn was determined by P<sub>t</sub> +1 = P<sub>t</sub> + w<sub>t</sub> .<br>
If as a result of the last rule P<sub>t</sub> +1 was a negative number the winner won only the maximum multiple of the bet that he could win without making a negative pot.<br>
If at some turn the pot was less than the bet, the game was ended for that day. If that was not the case the game continued till sunset.<br>
Beside the tablets that explained the rules some other tablets were found. These had lines with three numbers. Archeologists conjecture that each of these lines were part of a kind of accountability system for the game, where numbers represented, for a given day, the value of the pot at the beginning, the bet and the value of the pot at the end.

For example, a line with the number

10000 1500 11500

could mean that there was only one turn where the player won with label 1. Another possibility is that there were three turns with results 2, 1 and -2.

On the other hand, there were found other tablets with triplets of numbers that seem like the above described that, however, cannot represent results of a game day. There is no hypothesis of what they are.

Archeologists want to validate their hypothesis analyzing batches of tablets with triplets. They want to estimate the number of people that played in a day. To begin, they want to establish, for each triplet of numbers in a tablet that could represent a result of a game day, the minimal number of players that played that day. In the above example the answer to this question is 1. Tablets that cannot represent results should be identified. You are hired to help with this task.

输入描述<br>
The input file contains several test cases, each one of them in a separate line. Each test case is a triplet of non negative integers, indicating the initial pot, the bet and the final pot for a day. Each of the input numbers is less than 10<sup>8</sup>. The initial pot and the bet are greater than 0.
A line with a triplet of 0’s denotes the end of the input.

输出描述<br>
Output texts for each input case are presented in the same order that input is read. For each test case the answer must be a printed line.

If the test case cannot represent the result of a game day, the output line has the words No accounting tablet. In other case, the printed answer is one positive integer number telling the minimal number of players that could turn the roulette for the day corresponding to the annotations.

Hint

English translation of the Spanish preface:
```
… Babylonians flocked to buy tickets. The man who bought none was considered a pusillanimous wretch, a man with no spirit of adventure. In time, this justified contempt found a second target: not just the man who didn’t play, but also the man who lost and paid the fine. …

Jorge Luis Borges, The Lottery in Babylon
```
输入例子
```
10000 1000 22000
24 13 2
5100 700 200
54 16 158
360 6 72
25 10 5
0 0 0
```
输出例子
```
4
No accounting tablet
3
No accounting tablet
16
1
```
# 参考答案
```c++
#include"stdio.h"
#include"string.h"
int main()
{
	int pot;
	int bet;
	int fpot;
	while(scanf("%d%d%d",&pot,&bet,&fpot)!=-1,pot+bet+fpot)
	{
		if(pot>fpot)pot-=fpot;
		else pot=fpot-pot;
		if(pot%bet!=0)
			printf("No accounting tablet\n");
		else
		{
			pot=pot/bet;
			int ans;
			ans=0;
			ans+=pot/3;pot%=3;
			ans+=pot/2,pot%=2;
			ans+=pot;
			printf("%d\n",ans);
		}
	}
	return 0;
}




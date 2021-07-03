# 题目
Morse code represents characters as variable length sequences of dots and dashes. In practice, characters in a message are delimited by short pauses. The following table shows the Morse code sequences:

![1051.png](https://img12.360buyimg.com/ddimg/jfs/t1/189622/34/11211/11044/60dfd3fbE83598aad/fde93277acd54339.png)

Note that four dot-dash combinations are unassigned. For the purposes of this problem we will assign them as follows (these are not the assignments for actual Morse code):


underscore |	..-- |	period | ---.
-|-|-|-
comma	| .-.-	| question mark	| ----

Thus, the message "ACM_GREATER_NY_REGION" is encoded as:
```
.- -.-. -- ..-- --. .-. . .- - . .-. ..-- -. -.-- ..-- .-. . --. .. --- -.
```
M.E. Ohaver proposed an encryption scheme based on mutilating Morse code. Her scheme replaces the pauses between letters, necessary because Morse is a variable-length encoding that is not prefix-free, with a string that identifies the number of dots and dashes in each. For example, consider the message ".--.-.--". Without knowing where the pauses should be, this could be "ACM", "ANK", or several other possibilities. If we add length information, however, ".--.-.--242", then the code is unabiguous.
Ohaver's scheme has three steps, the same for encryption and decryption:

1. Convert the text to Morse code without pauses but with a string of numbers to indicate code lengths<br>
2. Reverse the string of numbers<br>
3. Convert the dots and dashes back into to text using the reversed string of numbers as code lengths<br>
As an example, consider the encrypted message "AKADTOF_IBOETATUK_IJN". Converting to Morse code with a length string yields ".--.-.--..----..-...--..-...---.-.--..--.-..--...----.232313442431121334242". Reversing the numbers and decoding yields the original message "ACM_GREATER_NY_REGION".

输入描述<br>
This problem requires that you implement Ohaver's encoding algorithm. The input will consist of several messages encoded with Ohaver's algorithm. The first line of the input is an integer n that specifies the number of test cases. The following n lines contain one message per line. Each message will use only the twenty-six capital letters, underscores, commas, periods, and question marks. Messages will not exceed 100 characters in length.
输出描述<br>
For each message in the input, output the line number starting in column one, a colon, a space, and then the decoded message. The output format must be adhered to precisely.
输入例子<br>
```
5
AKADTOF_IBOETATUK_IJN
PUEL
QEWOISE.EIVCAEFNRXTBELYTGD.
?EJHUT.TSMYGW?EJHOT
DSU.XFNCJEVE.OE_UJDXNO_YHU?VIDWDHPDJIKXZT?E
```
输出例子
```
1: ACM_GREATER_NY_REGION
2: PERL
3: QUOTH_THE_RAVEN,_NEVERMORE.
4: TO_BE_OR_NOT_TO_BE?
5: THE_QUICK_BROWN_FOX_JUMPS_OVER_THE_LAZY_DOG
```
# 参考答案
```c++
#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

map <char, string> morse;
map <string, char> remorse;
stack <int> num;
void init();

int main()
{
    int t, a, n;
    string s, s_morse, ans;
    init();
    cin>>t;
    for (int k = 1; k <= t; k++)
    {
        cin>>s;
        cout<<k<<": ";
        s_morse = "";
        num.empty();
        for (int i = 0; i < s.length(); i++)
        {
            s_morse = s_morse + morse[s[i]];
            num.push(morse[s[i]].length());
        }
        n = 0;
        while(!num.empty())
        {
            a = num.top();
            num.pop();
            ans = "";
            while(a--)
            {
                ans = ans + s_morse[n++];
            }
            cout<<remorse[ans];
        }
        cout<<endl;
    }
    return 0;
}

void init()
{
    morse['A'] = ".-";
    morse['B'] = "-...";
    morse['C'] = "-.-.";
    morse['D'] = "-..";
    morse['E'] = ".";
    morse['F'] = "..-.";
    morse['G'] = "--.";
    morse['H'] = "....";
    morse['I'] = "..";
    morse['J'] = ".---";
    morse['K'] = "-.-";
    morse['L'] = ".-..";
    morse['M'] = "--";
    morse['N'] = "-.";
    morse['O'] = "---";
    morse['P'] = ".--.";
    morse['Q'] = "--.-";
    morse['R'] = ".-.";
    morse['S'] = "...";
    morse['T'] = "-";
    morse['U'] = "..-";
    morse['V'] = "...-";
    morse['W'] = ".--";
    morse['X'] = "-..-";
    morse['Y'] = "-.--";
    morse['Z'] = "--..";
    morse['_'] = "..--";
    morse['.'] = "---.";
    morse[','] = ".-.-";
    morse['?'] = "----";

    remorse[".-"] = 'A';
    remorse["-..."] = 'B';
    remorse["-.-."] = 'C';
    remorse["-.."] = 'D';
    remorse["."] = 'E';
    remorse["..-."] = 'F';
    remorse["--."] = 'G';
    remorse["...."] = 'H';
    remorse[".."] = 'I';
    remorse[".---"] = 'J';
    remorse["-.-"] = 'K';
    remorse[".-.."] = 'L';
    remorse["--"] = 'M';
    remorse["-."] = 'N';
    remorse["---"] = 'O';
    remorse[".--."] = 'P';
    remorse["--.-"] = 'Q';
    remorse[".-."] = 'R';
    remorse["..."] = 'S';
    remorse["-"] = 'T';
    remorse["..-"] = 'U';
    remorse["...-"] = 'V';
    remorse[".--"] = 'W';
    remorse["-..-"] = 'X';
    remorse["-.--"] = 'Y';
    remorse["--.."] = 'Z';
    remorse["..--"] = '_';
    remorse["---."] = '.';
    remorse[".-.-"] = ',';
    remorse["----"] = '?';
}

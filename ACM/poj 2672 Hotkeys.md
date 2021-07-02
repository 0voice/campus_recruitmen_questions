# 题目
Tom is designing a menu system for a test editor. The menu consists of some menuitems, and each menuitem may contain some sub-menuitems (a sub-menuitem is also a menuitem) recursively, e.g., menuitem "File" may contain sub-menuitems "Open", "Save", "Save As", "Recent Files", "Send" and "Exit", and "Recent Files" may contain "Setting File", "Send" may contain "Mail" and "Fax". A menuitem may contain several words, and it is confirmed that the first letter in each word is a capital letter, and that the other letters are all small letters.

Each menuitem is associated with a hotkey, the menu is easier to use if the hotkeys are easier to remember. So Tom wants that the hotkey can only be a capital letter in a menuitem, which means the first letter in each word. Take "Save As" for example, the hotkey can only be 'S' or 'A'. It is clear that sub-menuitems of a menuitem can't be associated with the same hotkey, e.g., "Save" and "Save As" can't both use hotkey 'S', because they are both sub-menuitems of menu "File".

Since Tom believes press the same key twice is not convenient, he requests that the hotkeys of a menuitem and its sub-menuitems can't duplicate. In the previous example, "File" and "Recent Files" can't use the same hotkey 'F'. But this rule just affects the menuitem and its direct sub-menuitem, so "File" and "Setting File" can use the same hotkey 'F'.

Given a menu description, Tom wants to know whether it is possible to assign a hotkey for each menuitem or not.

输入描述

The menu is described as follows: a menuitem occupies a single line, and the sub-menuitems of a menuitem is listed just below this menu item. The description of the sub-menuitems starts with a "" after the last sub-menuitem. "" will take a whole line by itself. Since we may consider the menuitems in the top level belong to a global menu, there is always a "" at the end of the input.

Each menuitem may contain words and white spaces separating them. The length of a menuitem name is less than 50 characters.

There are no more than 10000 menuitems. It is confirmed that all the input are legal menuitems described above.

输出描述

A single line contains "Got It!" if a hotkey can be assigned to each menuitem; otherwise, output "No Solution".

输入例子
```
Exit
>
Edit

>
```
输出例子
```
No Solution
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<vector<int> > VVI;
VVI vt;
const int maxn = 26;
int match[maxn];
bool vis[maxn+1];
char buf[100];
bool dfs(int v){
    if(vis[v]) return false;
    vis[v] = true;
    for(int i = 0; i < (int)vt[v].size(); i ++){
        if(vt[v][i] == 0) continue;
        int t = match[i];
        if(t == -1 || dfs(t)){
            match[i] = v;
            return true;
        }
    }
    return false;
}
bool getX(VVI vec, vector<int>& ret){
    vt = vec;
    ret = vector<int>(26, 0);
    if(vec.size() > 26) return false;
    memset(match, -1, sizeof(match));

    for(int i = 0; i < (int)vt.size(); i ++){
        memset(vis, false, sizeof(vis));
        if(!dfs(i)) return false;
    }

    for(int i = 0; i < 26; i ++){
        if(match[i] == -1) ret[i] = 1;
        else{

            memset(vis, false, sizeof(vis));
            int v = match[i];

            match[i] = 26; vis[26] = true;
            if(dfs(v)){
                ret[i] = 1;
                match[i] = -1;
            }else match[i] = v;

        }
    }

    return true;
}
vector<int> getV(){

    vector<int> vec(26, 0);
    for(int i = 0; buf[i]; i ++){
        if(buf[i] >= 'A' && buf[i] <= 'Z') vec[buf[i]-'A'] = 1;
    }

    return vec;
}
void change(vector<int>& vec, vector<int> vec2){
    for(int i = 0; i < 26; i ++) vec[i] = vec[i] & vec2[i];
}
int solve(){
    vector<VVI> vec;
    vec.push_back(VVI());
    if(!gets(buf)) return -1;

    vector<int> tmp;
    while(1){
        gets(buf);
        if(strcmp(buf, "<") == 0){
            vec.push_back(VVI());
        }else if(strcmp(buf, ">") == 0){
            if(!getX(vec.back(), tmp)) return false;
            vec.pop_back();
            if(vec.size() == 0) return 1;
            change(vec.back().back(), tmp);
        }else{
            vec.back().push_back(getV());
        }

    }
    return 1;
}
int main() {

    int ans = solve();

    if(ans) printf("Got It!\n");
    else printf("No Solution\n");

    return 0;
}

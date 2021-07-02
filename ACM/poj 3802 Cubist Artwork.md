# 题目
International Center for Picassonian Cubism is a Spanish national museum of cubist artworks, dedicated to Pablo Picasso. The center held a competition for an artwork that will be displayed in front of the facade of the museum building. The artwork is a collection of cubes that are piled up on the ground and is intended to amuse visitors, who will be curious how the shape of the collection of cubes changes when it is seen from the front and the sides.

The artwork is a collection of cubes with edges of one foot long and is built on a ﬂat ground that is divided into a grid of one foot by one foot squares. Due to some technical reasons, cubes of the artwork must be either put on the ground, ﬁtting into a unit square in the grid, or put on another cube in the way that the bottom face of the upper cube exactly meets the top face of the lower cube. No other way of putting cubes is possible.

You are a member of the judging committee responsible for selecting one out of a plenty of artwork proposals submitted to the competition. The decision is made primarily based on artistic quality but the cost for installing the artwork is another important factor. Your task is to investigate the installation cost for each proposal. The cost is proportional to the number of cubes, so you have to ﬁgure out the minimum number of cubes needed for installation.

Each design proposal of an artwork consists of the front view and the side view (the view seen from the right-hand side), as shown in Figure 1.

![poj_3919desc_3](http://uploadfiles.nowcoder.com/probs/acm/poj_3919desc_3.jpg)

The front view (resp., the side view) indicates the maximum heights of piles of cubes for each column line (resp., row line) of the grid.

There are several ways to install this proposal of artwork, such as the following ﬁgures.

![poj_3919desc_1](http://uploadfiles.nowcoder.com/probs/acm/poj_3919desc_1.jpg)

In these ﬁgures, the dotted lines on the ground indicate the grid lines. The left ﬁgure makes use of 16 cubes, which is not optimal. That is, the artwork can be installed with a fewer number of cubes. Actually, the right one is optimal and only uses 13 cubes. Note that, a single pile of height three in the right ﬁgure plays the roles of two such piles in the left one.

Notice that swapping columns of cubes does not change the side view. Similarly, swapping rows does not change the front view. Thus, such swaps do not change the costs of building the artworks.

For example, consider the artwork proposal given in Figure 2.

![poj_3919desc_2](http://uploadfiles.nowcoder.com/probs/acm/poj_3919desc_2.jpg)

An optimal installation of this proposal of artwork can be achieved with 13 cubes, as shown in the following ﬁgure, which can be obtained by exchanging the rightmost two columns of the optimal installation of the artwork of Figure 1.

![poj_3919desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_3919desc_0.jpg)

输入描述<br>
The input is a sequence of datasets. The end of the input is indicated by a line containing two zeros separated by a space. Each dataset is formatted as follows.

w d<br>
h1 h2 ... hw<br>
h1 ' h2 ' ... hd '<br>

The integers w and d separated by a space are the numbers of columns and rows of the grid, respectively. You may assume 1 i (1 i i' (1 i'

输出描述
For each dataset, output a line containing the minimum number of cubes. The output should not contain any other extra characters.

You can assume that, for each dataset, there is at least one way to install the artwork.

输入例子
```
5 5
1 2 3 4 5
1 2 3 4 5
5 5
2 5 4 1 3
4 1 5 3 2
5 5
1 2 3 4 5
3 3 3 4 5
3 3
7 7 7
7 7 7
3 3
4 4 4
4 3 4
4 3
4 2 2 4
4 2 1
4 4
2 8 8 8
2 3 8 3
10 10
9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9
10 9
20 1 20 20 20 20 20 18 20 20
20 20 20 20 7 20 20 20 20
0 0
```
输出例子
```
15
15
21
21
15
13
32
90
186
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stack>
#include <cctype>
#include <utility>   
#include <map>
#include <string>  
#include <climits> 
#include <set>
#include <string> 
#include <sstream>
#include <utility>
#include <ctime>

using std::priority_queue;
using std::vector;
using std::swap;
using std::stack;
using std::sort;
using std::max;
using std::min;
using std::pair;
using std::map;
using std::string;
using std::cin;
using std::cout;
using std::set;
using std::queue;
using std::string;
using std::istringstream;
using std::make_pair;
using std::greater;

const int INFI((INT_MAX-1) >> 1);

bool mp[15][15];
int lim[2][15];
bool vis[2][15];
int cur[2], goal[2];

struct NODE
{
	int flag;
	int ind;
	int h;
	friend bool operator < (const NODE &op1, const NODE &op2)
	{
		return op1.h < op2.h;
	}
};

NODE node[30];

int main()
{
	int w, h;
	while(scanf("%d%d", &w, &h), w && h)
	{
		memset(mp, 0, sizeof(mp));
		memset(vis, 0, sizeof(vis));
		lim[0][0] = w;            
		lim[1][0] = h;	
		int count = 0;
		for(int i = 1; i <= w; ++i)
		{
			scanf("%d", lim[0]+i);
			node[++count].flag = 0;
			node[count].ind = i;
			node[count].h = lim[0][i];
		}

		for(int i = 1; i <= h; ++i)
		{
			scanf("%d", lim[1]+i);
			node[++count].flag = 1;
			node[count].ind = i;
			node[count].h = lim[1][i];
		}

		sort(node+1, node+1+count);
		int ans = 0;
		for(int i = count; i >= 1; --i)
			if(!vis[node[i].flag][node[i].ind])
			{
				int tf = node[i].flag, ti = node[i].ind, th = node[i].h;
				int tlim = lim[tf^1][0];
				cur[tf] = ti;
				goal[tf] = ti;
				int mh = INFI;
				for(int j = 1; j <= tlim; ++j)
					{
						cur[tf^1] = j;
						if(!mp[cur[0]][cur[1]] && th <= lim[tf^1][j]) 
						{
							if(lim[tf^1][j] == th && !vis[tf^1][j])    
							{
								goal[tf^1] = j;
								mh = th;
							}
							else
								if(lim[tf^1][j] < mh)   
								{
									goal[tf^1] = j;
									mh = th;
								}
						}					
					}
				vis[tf^1][goal[tf^1]] = true;
				vis[tf][ti] = true;
				mp[goal[0]][goal[1]] = true;                    
				ans += th;
			}
		printf("%d\n", ans);
	}
	return 0;
}





# 题目
Rocky Oil owns several rectangular oil fields in which it is drilling new wells. It wants to connect all wells in a field to a single East-West pipeline using straight North-South pipes. Your task is to write a program that first finds the location of the E-W pipeline such that the total length of the N-S pipes in the field is minimal; then it must draw a map of the oil field, if possible.
Each rectangular oil field is a grid 94 units long in the E-W direction and 73 units long in the N-S direction. The grid uses integer coordinates, with the SW corner at (1,1) and the NE corner at (94,73). Oil wells may be at any integer coordinates within the grid, and all wells will appear at different positions. The E-W pipeline will stretch across the entire field at an integer N-S coordinate. Wells with the same E-W coordinate share the same pipe. In case there are multiple positions for the E-W pipeline giving the same minimal length, always choose the one furthest south (i.e., with the lowest N-S coordinate).

Consider the first input example below. With the E-W pipeline at 11, the well at E-W position 1 is on the pipeline and has length zero. The two wells at E-W position 69 can share a single pipe of length 18. The total length for all three wells is 18. If the E-W pipeline were at 20 there would be two N-S pipes, one of length 9 at position 1 and another of length 9 at position 69, again with a total length of 18. In fact, any E-W pipeline located from 11 to 20 results in a total length of 18, which is minimal. Since there is more than one position for the pipeline that minimizes the length, choose the southernmost position, which is 11.

Any map drawn must occupy at most 69 columns and 19 rows (not counting borders and labels) so it fits on a standard-sized display. The map must include the E-W pipeline, all wells, and all N-S pipes. Only that portion of the field actually containing wells should be drawn, using the smallest bounding rectangle whose edges are multiples of 5. The E-W pipeline will always stretch across the entire map, regardless of its width. Wells must be inside the bounding rectangle, not on any of its edges. These constraints may make it impossible to draw some oil fields. The first input example shows the largest map possible.

The input consists of data for one or more oil fields, followed by a line containing 0 0 which signals the end of the input. Data for each oil field consists of one or more pairs of positive integers, one pair per line, representing the positions of oil wells in the field. The pair -1 -1 indicates the end of the data for a field.

For each oil field, output a line with a numbered header. Then output the map of the oil field, if possible. Otherwise, output a sentence with the location of the pipeline. Use the exact format shown below.

Use '@' to represent an oil well, '*' to represent a pipe, and '.' (a period) to represent an empty grid location. Wells take precedence over pipes, so if a well and a pipe occupy the same location, use '@'. Draw a border around the mapped oil field, using '|' (a vertical bar) for N-S edges and '-' (a dash) for E-W edges, but mark every 5th grid position with '+', as shown in the examples. Label each '+' with its position in the oil field. The label for each N-S '+' comes immediately before the '+' sign. The label for the northernmost '+' must start at the beginning of the first line of output. Labels for an E-W '+' must always have the most significant digit immediately below the '+'. Contrary to the usual output conventions, some of the lines in the map will have leading blanks.


Sample Input
```
1 11
69 29
69 20
-1 -1
35 35
-1 -1
1 1
94 73
1 73
94 1
-1 -1
2 2
3 7
4 4
6 1
-1 -1
0 0
```

Sample Output
```
OIL FIELD 1
30+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
  |....................................................................@|
  |....................................................................*|
  |....................................................................*|
  |....................................................................*|
25+....................................................................*+
  |....................................................................*|
  |....................................................................*|
  |....................................................................*|
  |....................................................................*|
20+....................................................................@+
  |....................................................................*|
  |....................................................................*|
  |....................................................................*|
  |....................................................................*|
15+....................................................................*+
  |....................................................................*|
  |....................................................................*|
  |....................................................................*|
  |@********************************************************************|
10+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
  0    5    10   15   20   25   30   35   40   45   50   55   60   65   70
OIL FIELD 2
40+----+----+
  |.........|
  |.........|
  |.........|
  |.........|
35+****@****+
  |.........|
  |.........|
  |.........|
  |.........|
30+----+----+
  30   35   40
OIL FIELD 3
Map is too big to draw for pipeline at 1
OIL FIELD 4
10+----+----+
  |.........|
  |.........|
  |..@......|
  |..*......|
 5+..*......+
  |..*@.....|
  |..**.....|
  |*@*******|
  |.....@...|
 0+----+----+
  0    5    10
  ```
# 参考答案
```c++
# include <cstdio>
# include <vector>
# include <cstring>
# include <algorithm>
using namespace std;
vector<int> data[100];
int x,y,minx,maxx,miny,maxy;
int GetMin(int pos)
{
	int ans=pos/5*5;
	if(ans==pos) ans-=5;
	return ans;
}
int GetMax(int pos)
{
	return (pos/5+1)*5;
}
int main() {
	int c=0;
	while(true)
	{

		scanf("%d%d",&x,&y);
		if(x==0&&y==0) break;
		for(int i=1;i<=94;i++) data[i].clear();
		data[x].push_back(y);
		minx=maxx=x;
		miny=maxy=y;
		while(true)
		{
			scanf("%d%d",&x,&y);
			if(x==-1&&y==-1) break;
			data[x].push_back(y);
			minx=min(minx,x);
			maxx=max(maxx,x);
			miny=min(miny,y);
			maxy=max(maxy,y);
		}
		for(int i=minx;i<=maxx;i++)
			sort(data[i].begin(),data[i].end());
		int total=0,ans=1;
		for(y=1;y<=73;y++)
		  if(y==1)
		  {
			for(int i=minx;i<=maxx;i++)
				if(!data[i].empty())
					{
						if(y>=data[i].front()&&y<=data[i].back()) total=data[i].back()-data[i].front();
						else if(y>data[i].back()) total=data[i].back()-data[i].front()+y-data[i].back();
						else total=data[i].back()-data[i].front()+data[i].front()-y;
					}
			ans=y;
		  }
		  else
		  {
			  int tmp=total;
			  for(int i=minx;i<=maxx;i++)
			  	if(!data[i].empty())
			  		{
			  			if(y>data[i].front()&&y<=data[i].back());
			  			else if(y<=data[i].front()) tmp--;
			  			else tmp++;
			  		}
			  if(tmp<total)
				  total=tmp,ans=y;
		  }

		printf("OIL FIELD %d\n",++c);
		int left=GetMin(minx),right=GetMax(maxx),down=GetMin(miny),up=GetMax(maxy);
		if(right-left>70||up-down>20) printf("Map is too big to draw for pipeline at %d\n",ans);
		else
		{
			char orimap[100][100];
			memset(orimap,'.',sizeof(orimap));
			char *map[100];
			for(int i=0;i<100;i++)
				map[i]=orimap[i];
			//draw left border&right border
			for(int i=down;i<=up;i++)
			{
				if((i-down)%5==0)
				{
					sprintf(map[up-i],"%2d+",i);
					sprintf(&orimap[up-i][right-left+2],"+");
				}
				else
				{
					sprintf(map[up-i],"  |");
					sprintf(&orimap[up-i][right-left+2],"|");
				}
				map[up-i]+=3;
				*map[up-i]='.';
			}

			sprintf(orimap[up-down+1],"  %-5d",left);
			map[up-down+1]+=7;
			for(int i=left+1;i<right;i++)
			{
				if((i-left)%5==0)
				{
					sprintf(map[up-down+1],"%-5d",i);
					map[up-down+1]+=5;
					*map[up-down]=*map[0]='+';
				}
				else
				{
					*map[up-down]=*map[0]='-';
				}
				map[up-down]++;
				map[0]++;
			}
			sprintf(map[up-down+1],"%d",right);

			for(int i=down+1;i<up;i++)
				map[up-i]+=minx-left-1;
			for(int i=minx;i<=maxx;i++)
			{
				if(!data[i].empty())
					for(int j=min(ans,data[i].front());j<=max(ans,data[i].back());j++)
						*map[up-j]='*';
				for(int j=down+1;j<up;j++)
					map[up-j]++;
			}

			for(int i=left+1;i<right;i++)
				orimap[up-ans][2+i-left]='*';

			for(int i=minx;i<=maxx;i++)
				for(int j=0;j<data[i].size();j++)
					orimap[up-data[i][j]][i-left+2]='@';
			for(int i=up;i>=down-1;i--)
				printf("%s\n",up<10?orimap[up-i]+1:orimap[up-i]);
		}
	}
	return 0;
}

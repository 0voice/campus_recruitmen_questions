# 题目
Attending a boring weekly session, our professor started drawing on a grid in a page of his calendar. He started at a boundary grid point P; note that P is a corner of one or two grid cells. He drew a diameter of one of those cells and continued on a straight line until reaching point Q on another edge of the grid. Then he started another line from Q, perpendicular to the line PQ until hitting another edge at point R. He kept drawing lines as above, until he could not draw a new line, either because a perpendicular line would not start with a cell diameter or it would fall on an already drawn line. Then he was puzzling how he would be able to count the number of minimal rectangles he has created on the grid. At this time, the chair of the session noticed him and asked him what he was doing. "Sorry, I was designing a problem for the ACM-ICPC Tehran site," he said.

![poj_4054desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_4054desc_0.jpg)

You are to write a program to, given the dimensions R and C of a grid, the coordinates x and y of a point P on one of the edges of the grid, and the direction (up, left), (down, left), (up, right), or (down, right) of the first line, help the professor to find out the number of minimal rectangles.

输入描述<br>
The input file contains multiple test cases. The first line of the input, contains t, the number of test cases that follow. Each of the following t blocks, describes a test case.

The first line of each block, contains two positive integers R and C, which are the number of horizontal and vertical gridlines, respectively (2<br>
* "DR", the first move is in the down-right direction,
* "DL", the first move is in the down-left direction,
* "UL", the first move is in the up-left direction,
* "UR", the first move is in the up-right direction.

输出描述<br>
For each test case, output one line containing the number of non-overlapping rectangles formed.

输入例子
```
2
4 5
2 1
DR
4 5
4 1
UR
```
输出例子
```
1
3
```
# 参考答案
```c++
#include<stdio.h>

#define range 1010

int flag[2][2][2]={ {{-1,1},{1,1}},{{-1,-1},{1,-1}} };

int total;
int arr,col;
int x0,y0;  
int x,y;  
int UD,LR;
char direc[5];
int calcu[range][range][1];

inline bool square();
void direcMade();
inline bool vertax();
void derecChange();
inline bool side();
void initial();

int main()
{
    int N;  scanf("%d",&N);
    while(N--)
    {

        scanf("%d%d",&arr,&col);
        scanf("%d%d",&x0,&y0);
        getchar();
        gets(direc);

        total=0; 
        direcMade();  
        x=y0,y=arr-x0+1;  
        initial();
        while(1)
        {

            do{
                ++calcu[x][y][0];
                x += flag[UD][LR][0];  y += flag[UD][LR][1];
            }while( !side() );
            if( vertax() || calcu[x][y][0] != 0)  

            { 
                ++calcu[x][y][0];
                break;
            }
            derecChange();
        }

        for(int i=0; i!=range; ++i)
        {
            for(int j=0; j!=range; ++j)
            {
                if(calcu[i][j][0]!=0)
                  total += calcu[i][j][0]-1;
            }
        }
        printf("%d\n",total);
    }
    return 0;

}

inline bool square()  
{
     if(arr==col)
      return true;
     else return false;
}

void direcMade()  
{
     if(direc[0] == 'D')
     {
         if(direc[1] == 'R')
         { UD=1; LR=1; }
         else
         { UD=1; LR=0; }
     }
     else
     {
         if(direc[1] == 'R')
         { UD=0; LR=1; }
         else
         { UD=0; LR=0; }
     }
     return ;
}

inline bool vertax()
{
    if( (x==1 || x==col) && (y==1 || y==arr) )
      return true;
    return false;
}

void derecChange()  
{
     if( vertax() )  
       return ;
     if( x==1 || x==col ) 
       LR=(LR+1)%2;
     if( y==1 || y==arr ) 
       UD=(UD+1)%2;
     return ;

}

inline bool side()  
{
    if( x==1 || x==col || y==1 || y==arr)
      return true;
    return false;
}

void initial()
{
     for(int i=0; i!=range; ++i)
       for(int j=0; j!=range; ++j)
       calcu[i][j][0]=0;
}

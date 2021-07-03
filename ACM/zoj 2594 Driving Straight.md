# 题目
The city where Peter lives has the form of the rectangle with M streets running from east to west and N streets running from north to south. Recently, because of preparations for the celebration of the city's 3141st birthday, some street sectors has been closed for driving.

Peter lives in the house next to point (1, 1) and works next to the point (N, M). He always drives from home to work by his car using the shortest possible path. Of course, he can't drive through closed sectors. Since there can be many shortest pathes between his house and his work, he may choose any.

But Peter doesn't like to turn (he is an inexperienced driver), so he wants to choose the path using the following algorithm: starting from the point (1, 1) he drives either northwards, or eastwards (wherever there is the shortest path available, if there are both, he may choose any). Whenever he comes to the junction he must decide where to go. If there is only one direction he can drive to stay on the shortest path, he must choose that direction. In the other case he would like to choose the direction giving priority to driving forward, that is, if he can drive forward and still stay on some shortest path, he would go forward. If he can't drive forward to stay on the shortest path, he would choose any available direction.

Help Peter to create the path from his house to his work using the rules described.


Input

The input contains multiple test cases. The first line of the input is a single integer T (1

The first line of each test case contains integer numbers M and N (2

Next 2M - 1 lines contain 2N - 1 characters each, representing the city map. House blocks are marked with spaces, junctions with '+', open sectors with '-' and '|', closed sectors with spaces. Peter's house is at the lower-left corner of the map, his work is at the upper-right corner.


Output

On the first line of each test case print the direction Peter should choose first, 'N' or 'E'. On the second line output the sequence of latin letters 'F', 'L' and 'R' representing Peter's behaivour on junctions - go forward, turn left or right respectively. If there are several paths Peter can choose from, output any. You must output Peter's action on the junction even if he has no choice due to closed streets. It is guaranteed that there will always be the way for Peter to get from home to work.

Two consecutive cases should be separated by a single blank line. No blank line should be produced after the last test case.


Sample Input
```
1

4 4
+-+ +-+
| |   |
+ +-+-+
|   |
+-+-+-+
|     |
+-+-+-+
```
Sample Output
```
N
RFLRL
```

# 参考答案
```c++
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

string a[800];
bool p[160005];
int d[160005],map[160005][5],T,m,n,tmp,tmp1,que[160000],head,tail,now,F;

int main()
{
	ios::sync_with_stdio(false);
	cin >> T ;
	while ( T-- )
	{
		cin >> n >> m ;
		cin.get();
		memset(p,false,sizeof(p));
		memset(d,0,sizeof(d));
		memset(map,0,sizeof(map));
		for ( int i = 2*m-1 ; i >= 1 ; --i )
			getline(cin,a[i]);
		for ( int i = 1 ; i <= m ; ++i )
		{
			for ( int j = 1 ; j <= n ; ++j )
			{
				if ( a[2*i-1][2*j-1] == '-' && j < n ) 
				{
					 tmp = (i-1)*n+j;
					 ++map[tmp][0];
					 tmp1 = map[tmp][0];
					 map[tmp][tmp1] = tmp+1 ;
					 ++map[tmp+1][0];
					 tmp1 = map[tmp+1][0];
					 map[tmp+1][tmp1] = tmp ; 
				}
				if ( a[2*i][2*j-1-1] == '|' && i < m ) 
				{
					tmp = (i-1)*n+j;
					++map[tmp][0];
					tmp1 = map[tmp][0];
					map[tmp][tmp1] = tmp+n ;
					++map[tmp+n][0];
					tmp1 = map[tmp+n][0];
					map[tmp+n][tmp1] = tmp ; 
				}
			}		
		}
 		que[0] = m*n ;
		d[m*n] = 0 ;		
		p[m*n] = true;
		head = 0 ;
		tail = 0 ;
		while ( head <= tail )
		{
			now = que[head];
			for ( int i = 1 ; i <= map[now][0] ; ++i )
			{
				if ( !p[map[now][i]] ) 
				{
					d[map[now][i]] = d[now]+1;
					p[map[now][i]] = true ;
					++tail;
					que[tail] = map[now][i];
					if ( que[tail] == 1 ) break;
				}
			}
			++head;
			if ( que[tail] == 1 ) break;
		}
		now = 1 ;
		if ( d[now+1]+1 == d[now] ) 
		{
			cout << "E" << endl;
			now = now+1;
			F = 2 ;
		}
		else
		{
			cout << "N" << endl;
			now = now+n;
			F = 1;
		}
		for ( int i = 2 ; i <= d[1] ; ++i )
		for ( int k = 1 ; k <= map[now][0] ; ++k )
		{
			if ( d[map[now][k]]+1 == d[now] ) 
			{
				if ( now+1 == map[now][k] ) 	
				{
					if ( F == 1 ) cout << "R" ;
					if ( F == 2 ) cout << "F" ;
					if ( F == 3 ) cout << "L" ;
					F = 2 ;
					now = map[now][k] ;
				}
				else if ( now-1 == map[now][k] )
				{
					if ( F == 1 ) cout << "L" ;
					if ( F == 3 ) cout << "R" ;
					if ( F == 4 ) cout << "F" ;
					F = 4 ;
					now = map[now][k] ;
				}
				else if ( now+n == map[now][k] )
				{
					if ( F == 1 ) cout << "F" ;
					if ( F == 2 ) cout << "L" ;
					if ( F == 4 ) cout << "R" ; 
					F = 1 ;
					now = map[now][k] ;
				}
				else if ( now-n == map[now][k] )
				{
					if ( F == 2 ) cout << "R" ;
					if ( F == 3 ) cout << "F" ;
					if ( F == 4 ) cout << "L" ;
					F = 3 ;
					now = map[now][k] ;
				}
				break;
			}
		}
		cout << endl;
		if ( T ) cout << endl;
	}
	return 0;
}

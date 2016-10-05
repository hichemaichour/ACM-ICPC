// if you are VC++ users, this will suppress some compilation warning messages
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>

#include <algorithm>

#include <vector>
#include <deque>
#include <list>
#include <stack>  
#include <queue> 
#include <set> 
#include <map>
#include <bitset>
#include <string>

#include <iterator>
#include <functional>
#include <complex>
#include <numeric>
#include <valarray>

#include <cmath>

using namespace std;

#define REP(i, a, b) 		for (i=a ; i<=b ; i++)
#define REPN(i, n)			REP(i, 0, n-1)
#define REPD(i, a, b)		for (i=a ; i>=b ; i--)
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)

#define All(v)				v.begin(),v.end()

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue
#define NL					numeric_limits

// Shortcuts for "common" data types in contests
typedef long long			LL;
typedef long double			LD;
typedef vector<int>			VI;
typedef vector<bool>		VB;
typedef vector<double>		VD;
typedef pair<int, int>		II;
typedef vector<II>			VII;

#define x first
#define y second

int N,X,Y;
II Start;
II End;
VII Bases;
vector<VI> Map;
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

void BFS_Map(){
	Map.clear();
	Map.resize(X,VI(Y,-1));

	int i;
	queue<II> q;
	for(i=0 ; i<N ; i++){
		Map[Bases[i].x][Bases[i].y] = 0;
		q.push(Bases[i]);
	}

	while(!q.empty()){
		II p = q.front(); q.pop();
		for(i=0 ; i<4 ; i++){
			II nxt = p;
			nxt.x += dx[i];
			nxt.y += dy[i];
			if(nxt.x<0 || nxt.x>=X || nxt.y<0 || nxt.y>=Y || Map[nxt.x][nxt.y]!=-1)
				continue;
			Map[nxt.x][nxt.y] = Map[p.x][p.y]+1;
			q.push(nxt);
		}
	}
}

bool BFS(int& ret,int mid){
	queue<II> q;
	queue<int> d;
	vector<VB> done(X,VB(Y));

	q.push(Start);
	d.push(0);
	done[Start.x][Start.y] = true;

	while(!q.empty()){
		II Pos = q.front(); q.pop();
		int dis = d.front(); d.pop();

		for(int i=0 ; i<4 ; i++){
			II nxt = Pos;
			nxt.x += dx[i];
			nxt.y += dy[i];
			if(nxt.x<0 || nxt.x>=X || nxt.y<0 || nxt.y>=Y || done[nxt.x][nxt.y] || Map[nxt.x][nxt.y]<mid)
				continue;

			if(nxt == End){
				ret = dis+1;
				return true;
			}

			done[nxt.x][nxt.y] = true;
			q.push(nxt);
			d.push(dis+1);
		}
	}
}

II BFS_Road(){
	if(Start == End)
		return II(Map[Start.x][Start.y],0);

	int hi = min(Map[Start.x][Start.y] , Map[End.x][End.y]);
	int lo = 0;
	int ret;
	while(lo!=hi){
		int mid = (hi+lo)/2 + 1;

		if(BFS(ret,mid))
			lo = mid;
		else
			hi = mid-1;
	}
	BFS(ret,lo);
	return II(lo,ret);
}

int main(){
	ifstream cin("in.h");
	int T;
	cin>>T;
	while(T--){
		Bases.clear();
		cin>>N>>X>>Y;
		cin >> Start.x>>Start.y >> End.x>>End.y;
		Bases.resize(N);
		for(int i=0 ; i<N ; i++)
			cin >> Bases[i].x >> Bases[i].y;

		BFS_Map();
		II p = BFS_Road();
		cout << p.x <<" "<< p.y <<endl;
	}
}
#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

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

#define REP(i, a, b) 		for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)		for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)				v.begin(),v.end()
#define Resize(v,N)			v.clear(); v.resize(N);

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(All(v),e) - v.begin() )

#define VI					vector<int>
#define VVI					vector<VI>

#define x					first
#define y					second
#define II					pair<int,int>
#define VII					vector<II>
#define VVII				vector<VII>

const int Inf = 1e7;

int N;
VVI Adj;
VVI G;
int s,t;

int bellman(){
	int i,j,k;
	int u,v;
	VI d(N,Inf);
	VI level(N);
	d[s] = 0;
	queue<int> Q;
	Q.push(s);

	while(!Q.empty()){
		if(d[s] < 0 || level[t] > N) // Negative Cycle
			return -Inf;

		u = Q.front(); Q.pop();
		level[u]++;
		if(level[u] > N) // Negative Cycle
			return -Inf;
		for(i=0 ; i<Adj[u].size() ; i++){
			v = Adj[u][i];
			if(d[v] > d[u]+G[u][v]){
				d[v] = d[u]+G[u][v];
				Q.push(v);
			}
		}
	}
	return d[t];
}

int W,H;
VI V;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

void Build_Graph(){
	int x0,x1,y0,y1;
	int i,j,k;
	int u,v;

	FOR(u,N){
		if(V[u] || u==t)
			continue;
		x0 = u%W;
		y0 = u/W;
		FOR(i,4){
			x1 = x0+dx[i];
			y1 = y0+dy[i];
			v = x1 + y1*W;
			if(x1<0 || y1<0 || x1>=W || y1>=H || V[v]==1)
				continue;
			Adj[u].push_back(v);
			G[u][v] = 1;
		}
	}
}

int main(){
	//ifstream cin("input.txt");
	for(int cnt=1 ; true ; cnt++){
		int i,j,k;
		int u,v;
		G.clear();
		Adj.clear();
		V.clear();

		cin >> W >> H;
		if(W==0)
			return 0;

		N = W*H;
		G.resize(N,VI(N));
		Adj.resize(N);
		V.resize(N);
		s = 0;
		t = N-1;

		int M;
		int x,y;
		cin >> M;
		FOR(i,M){
			cin >> x >> y;
			V[x + y*W] = 1;
		}

		int x0,x1,y0,y1,c;
		cin >> M;
		FOR(i,M){
			cin >> x0>>y0 >> x1>>y1 >> c;
			u = x0 + y0*W;
			v = x1 + y1*W;
			V[u] = 2;
			Adj[u].push_back(v);
			G[u][v] = c;
		}

		Build_Graph();

		int out = bellman();
		//cout << cnt <<" ";
		if(out == -Inf)
			cout << "Never" <<endl;
		else if(out == Inf)
			cout << "Impossible" <<endl;
		else
			cout << out <<endl;
	}
}
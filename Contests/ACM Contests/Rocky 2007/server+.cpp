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

#define REP(i, a, b) 	for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)	for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)		for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)		REP (i, 0, n-1)
#define FORD(i, n)		REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)		(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI				vector<int>
#define VVI				vector<VI>

#define x				first
#define y				second
#define II				pair<int,int>
#define VII				vector<II>
#define VVII			vector<VII>

#define VS				vector<string>
#define VVS				vector<VS>

const double EPS = 1e-3;
const int INF = 1<<29;

double L[2];
VVI Adj;
VI X;
VI Y;
int s,t;
int N;
double D;

double dist(int x0,int y0,int x1,int y1){
	double dx = x1 - x0;
	double dy = y1 - y0;
	return sqrt(dx*dx + dy*dy);
}

void BuildGraph(){
	int i,j;
	FOR(i, N) REP(j, i+1, N-1) {
		if (dist(X[i], Y[i], X[j], Y[j]) - D < EPS) {
			Adj[i].push_back(j);
			Adj[j].push_back(i);
		}
	}
}

int BFS(){
	int i,j,k;
	queue<int> Q;
	VI done(N);

	done[s] = 1;
	Q.push(s); Q.push(0);

	while(!Q.empty()){
		int u,v;
		int d;
		u=Q.front(); Q.pop();
		d=Q.front(); Q.pop();
		FOR(i,Adj[u].size()){
			v = Adj[u][i];
			if(done[v]) continue;
			if(v == t) return d+1;
			done[v] = 1;
			Q.push(v); Q.push(d+1);
		}
	}
	return INF;
}

int main(){
	ifstream cin("input.txt");
	int T;
	cin >> T;
	while(T--){
		int i,j,k;

		cin >> N >> s >> t >> L[0] >> L[1];
		s--; t--;
		D = L[0]+L[1];

		X.clear(); X.resize(N);
		Y.clear(); Y.resize(N);
		Adj.clear(); Adj.resize(N);

		FOR(i,N)
			cin >> X[i] >> Y[i];

		BuildGraph();

		int ans = BFS();

		if(ans != INF)
			cout << ans << endl;
		else
			cout <<"Impossible"<<endl;
	}
}
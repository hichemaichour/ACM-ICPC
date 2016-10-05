/*
ID: b0002141
PROG: cowtour
LANG: C++
*/

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
#define REPI(i, v)		for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)		REP (i, 0, n-1)
#define FORD(i, n)		REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)		(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI			vector<int>
#define VVI			vector<VI>

#define VD			vector<double>
#define VVD			vector<VD>

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII		vector<VII>

#define VS			vector<string>
#define VC			vector<char>

#define INF			1e9

int main(){
	//ifstream cin("input.txt");
	ifstream cin("cowtour.in");
	ofstream cout("cowtour.out");
	int i,j,k;
	int N;
	char c;
	VD X,Y;
	VVD D;
	VVI G;
	VVI Adj;

	cin >> N;
	X.resize(N); Y.resize(N);
	FOR(i,N) cin >> X[i] >> Y[i];
	G.clear(); G.resize(N,VI(N));
	Adj.clear(); Adj.resize(N);
	FOR(i,N) FOR(j,N){
		cin >> c;
		if(c == '0') continue;
		G[i][j] = 1;
		Adj[i].push_back(j);
	}

	D.clear(); D.resize(N,VD(N));
	FOR(i,N) FOR(j,N){
		double dx = X[i]-X[j];
		double dy = Y[i]-Y[j];
		D[i][j] = sqrt(dx*dx + dy*dy);
	}

	VI done(N);
	VVI V;
	FOR(i,N){
		if(done[i]) continue;
		V.resize(V.size()+1);
		queue<int> Q;
		Q.push(i);
		done[i] = 1;
		V.back().push_back(i);
		while(!Q.empty()){
			k = Q.front(); Q.pop();
			FOR(j,Adj[k].size()){
				if(done[Adj[k][j]]) continue;
				done[Adj[k][j]] = 1;
				Q.push(Adj[k][j]);
				V.back().push_back(Adj[k][j]);
			}
		}
	}

	VVD dist(N,VD(N,INF));
	FOR(i,N) dist[i][i] = 0;
	FOR(i,N) FOR(j,N) if(G[i][j]) dist[i][j] = D[i][j];

	FOR(k,N) FOR(i,N) FOR(j,N) dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);

	VD MAX(N);
	FOR(i,N) FOR(j,N) if(dist[i][j] < INF) MAX[i] = max(MAX[i],dist[i][j]);

	double Max = 0;
	FOR(i,N) Max = max(Max,MAX[i]);

	double ans = INF;
	FOR(i,N) REP(j,i+1,N-1){
		if(dist[i][j] < INF) continue;
		ans = min(ans , max(Max,MAX[i]+MAX[j]+D[i][j]));
	}

	char ANS[100];
	sprintf(ANS,"%.6f",ans);
	cout << ANS << endl;

	return 0;
}
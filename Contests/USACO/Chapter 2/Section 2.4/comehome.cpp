/*
ID: b0002141
PROG: comehome
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

int main(){
	//ifstream cin("input.txt");
	ifstream cin("comehome.in");
	ofstream cout("comehome.out");
	const int INF = 100000000;
	int i,j,k;
	int E;
	int c1,c2;
	char C1,C2;
	int cnt = 0;
	VI m(500,-1);
	VVI Adj;
	VVI G(100,VI(100,INF));
	VI V;

	cin >> E;
	FOR(i,E){
		cin >> C1 >> C2 >> k;
		c1 = C1; c2 = C2;
		if(c1 == c2)
			continue;
		if(m[c1] == -1){
			m[c1] = cnt++;
			Adj.resize(cnt);
			if(c1>='A' && c1<'Z')
				V.push_back(m[c1]);
		}
		if(m[c2] == -1){
			m[c2] = cnt++;
			Adj.resize(cnt);
			if(c2>='A' && c2<'Z')
				V.push_back(m[c2]);
		}
		if(G[m[c1]][m[c2]] == INF){
			Adj[m[c1]].push_back(m[c2]);
			Adj[m[c2]].push_back(m[c1]);
		}
		G[m[c1]][m[c2]] = min(k,G[m[c1]][m[c2]]);
		G[m[c2]][m[c1]] = G[m[c1]][m[c2]];
	}

	int N = cnt;
	FOR(k,N) FOR(i,N) FOR(j,N) if(G[i][k]+G[k][j]<G[i][j]) G[i][j] = G[i][k]+G[k][j];

	k = m['Z'-0];
	int ans = INF;
	int buf;
	FOR(i,V.size()){
		if(G[V[i]][k] < ans){
			ans = G[V[i]][k];
			buf = V[i];
		}
	}

	char ANS;
	FOR(i,m.size())
		if(m[i] == buf)
			ANS = i;

	cout << ANS <<" " << ans << endl;

	return 0;
}
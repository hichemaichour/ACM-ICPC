/*
ID: b0002141
PROG: agrinet
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

#define e			pair<int,II>

int NS;
int p[100];
int G[100][100];

int Find(int u){
	if(p[u] == u) return u;
	p[u] = Find(p[u]);
	return p[u];
}

bool Union(int u,int v){
	u = Find(u);
	v = Find(v);
	if(u == v) return false;
	if(u > v) swap(u,v);
	p[v] = u;
	NS--;
	return true;
}

int main(){
	//ifstream cin("input.txt");
	ifstream cin("agrinet.in");
	ofstream cout("agrinet.out");
	int i,j,k;
	int N;
	cin >> N;
	FOR(i,N) p[i] = i;
	NS = N;

	set<e> E;
	FOR(i,N) FOR(j,N){
		cin >> G[i][j];
		if(i==j) continue;
		E.insert(e(G[i][j],II(i,j)));
	}

	long long ans = 0;
	while(NS != 1){
		e buf = *E.begin();
		if(Union(buf.y.x,buf.y.y))
			ans += buf.x;
		E.erase(E.begin());
	}

	cout << ans << endl;

	return 0;
}
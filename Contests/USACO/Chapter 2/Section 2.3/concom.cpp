/*
ID: b0002141
PROG: concom
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

int main(){
	//ifstream cin("input.txt");
	ifstream cin("concom.in");
	ofstream cout("concom.out");

	int i,j,k;
	int E;
	int u,v;
	VVI Adj(100);
	VVI G(100,VI(100));

	cin >> E;
	FOR(i,E){
		cin >> u >> v >> k;
		u--; v--;
		Adj[u].push_back(v); G[u][v] = k;
	}

	VVI ans(100);

	FOR(i,100){
		// 2
		FOR(j,Adj[i].size()){
			u = i;
			v = Adj[i][j];
			if(G[u][v] > 50)
				ans[u].push_back(v);
		}

		// 3
		VI own(G[i]); // 1
		FOR(j,ans[i].size()){
			u = ans[i][j];
			FOR(k,Adj[u].size()){
				v = Adj[u][k];
				if(own[v] > 50)
					continue;
				own[v] += G[u][v];
				if(own[v] > 50)
					ans[i].push_back(v);
			}
		}
	}

	FOR(i,100)
		sort(All(ans[i]));

	FOR(i,100)
		FOR(j,ans[i].size())
			if(i != ans[i][j])
				cout << i+1 <<" "<< ans[i][j]+1 << endl;
}
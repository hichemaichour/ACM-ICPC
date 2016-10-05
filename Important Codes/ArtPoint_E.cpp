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

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII			vector<VII>

int N;		// Number of Nodes
VVI Adj;	// the Adjecency List
VI IsAP;	// Is this node AP
VI AP;		// all the Articulation Points
VI P;		// the parent in the DFS tree
VI dfs_low; // if the ith element is not in a cycle it is equal to its dfs_num
			// otherwise it's equal to the lowest dfs_num in the cycle
VI dfs_num; // the order of ith node in the DFS
VII B;		// the bridges
int NCR;	// number of children of the root
int root;	// the root of the DFS (anyone if it is a connected graph)
int cnt;	// the order in the DFS tree

void DFS(int u) {
	int i,j,k;
	dfs_low[u] = cnt;
	dfs_num[u] = cnt;
	cnt++;
	FOR(i,Adj[u].size()){
		int v = Adj[u][i];
		if(dfs_num[v] == -1){
			P[v] = u;
			if(u == root)
				NCR++;
			DFS(v);
			if(dfs_low[v] >= dfs_num[u] && !IsAP[u] && u!=root){
				IsAP[u] = true;
				AP.push_back(u);
			}
			if(dfs_low[v] > dfs_num[u])
				B.push_back(II(u,v));
			dfs_low[u] = min(dfs_low[u] , dfs_low[v]);
		}
		else if(v != P[u])
			dfs_low[u] = min(dfs_low[u] , dfs_num[v]);
	}
}

int ArtPoint(int s){
	IsAP.clear(); IsAP.resize(N);
	AP.clear();
	P.clear(); P.resize(N,-1);
	dfs_low.clear(); dfs_low.resize(N,-1);
	dfs_num.clear(); dfs_num.resize(N,-1);
	B.clear();

	NCR = 0;
	cnt = 0;
	root = s;
	DFS(root);
	if(NCR > 1){
		IsAP[root] = true;
		AP.push_back(root);
	}
	return AP.size();
}

int main() {
	int i, j, k;
	ifstream cin("input.txt");
	int M;
	while (true) {
		cin >> N;
		if(N==0)
			return 0;
		Adj.clear();
		Adj.resize(N);
		cin >> M;

		FOR(i, M) {
			cin >> j >> k;
			Adj[j].push_back(k);
			Adj[k].push_back(j);
		}

		cout << ArtPoint(0) << endl;
	}
	return 0;
}
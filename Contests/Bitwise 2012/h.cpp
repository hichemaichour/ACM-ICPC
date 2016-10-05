#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

#define VI				vector<int>
#define VVI				vector<VI>

#define Remove(V,n)		V.resize(remove(V.begin(),V.end(),n)-V.begin())

using namespace std;

int N;
VVI Adj;
VVI dp;
VI P;

int Cal(){
	VVI buf = Adj;

	int i,j,k;
	deque<int> L;
	int M = N;
	FOR(i,N)
		if(Adj[i].size() == 1)
			L.push_back(i);

	while(M > 2){
		int n = L.size();

		FOR(i,n){
			int u = L.front(); L.pop_front();
			M--;
			FOR(j,Adj[u].size()){
				k = Adj[u][j];
				Remove(Adj[k],u);
				if(Adj[k].size() == 1)
					L.push_back(k);
			}
		}
	}
	Adj = buf;

	dp.clear();
	dp.resize(N,VI(2,-1));
	P.clear();
	P.resize(N,-1);



	int ans = 0;
	return ans;
}

int main(){
	//ifstream cin("h.txt");
	int i,j,k;
	int u,v;
	cin >> N;
	Adj.clear(); Adj.resize(N);
	FOR(i,N-1){
		cin >> u >> v;
		u--; v--;
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}

	cout << Cal() << endl;

	return 0;
}
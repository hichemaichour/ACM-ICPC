#include <iostream>
#include <fstream>
#include <vector>

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

#define VI				vector<int>
#define VVI				vector<VI>

using namespace std;

int N;
int M;
int E;
VVI Adj;
int ans;

int Cal(int n){
	return (n*n + n)/2;
}

void FindAns(){
	int i,j,k;
	int u,v;

	VI Assign(N);
	VI NS(M);

	FOR(i,N){
		Assign[i] = Adj[i].front();
		NS[Adj[i].front()]++;
	}

	ans = 0;
	FOR(i,M)
		ans += Cal(NS[i]);

	FOR(i,N*1000){
		u = i%N;
		FOR(j,Adj[u].size()){
			v = Adj[u][j];
			if(Assign[u] == v)
				continue;

			k = ans;
			k -= Cal(NS[Assign[u]]) + Cal(NS[v]);
			k += Cal(NS[Assign[u]]-1) + Cal(NS[v]+1);

			if(k < ans){
				ans = k;
				NS[Assign[u]]--;
				NS[v]++;
				Assign[u] = v;
			}
		}
	}
}

int main(){
	int T;
	cin >> T;
	while(T--){
		int i,j,k;

		cin >> N >> M;
		cin >> E;

		Adj.clear(); Adj.resize(N);

		FOR(i,E){
			int u,v;
			cin >> u >> v;
			u--; v--;
			Adj[u].push_back(v);
		}

		FindAns();

		cout << ans << endl;
	}
}
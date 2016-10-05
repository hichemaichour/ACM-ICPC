#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

#define VI vector<int>
#define VVI vector<VI>

#define All(v) v.begin(),v.end()

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
		if(d[s] < 0 || level[t] > 2*N) // Negative Cycle
			return Inf;

		u = Q.front(); Q.pop();
		level[u]++;
		if(level[u] > 100*N) // Negative Cycle
			continue;
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

int main(){
	ifstream cin("input.txt");
	int T;
	cin >> T;
	bool b = false;
	for(int cnt=0 ; cnt<T ; cnt++){
		int i,j,k;
		if(b)
			cout << endl;
		b = true;

		cin >> N >> s >> t;
		G.clear(); G.resize(N,VI(N));
		Adj.clear(); Adj.resize(N);

		int M;
		cin >> M;
		for(i=0 ; i<M ; i++){
			cin >> j >> k;
			Adj[j].push_back(k);
			cin >> G[j][k];
		}
		for(i=0 ; i<N ; i++)
			sort(All(Adj[i]));

		int ans = bellman();

		if(ans == Inf)
			cout << "infinity" <<endl;
		else
			cout << ans << endl;
	}
}
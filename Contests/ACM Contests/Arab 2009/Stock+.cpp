#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

#define VI vector<int>
#define VVI vector<VI>
#define VB vector<bool>

int T;
int N;
VVI G;
VVI Adj;
VVI Done;

bool BFS(int St,int En){
	if(St == En || G[St][En])
		return false;

	VB done(N);
	VI P(N);
	queue<int> Q;
	Q.push(St);
	done[St] = true;
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		for(int i=0 ; i<Adj[u].size() ; i++){
			int v = Adj[u][i];

			if(v==En)	
				return false;

			if(done[v])
				continue;
			done[v] = true;

			G[St][v] = 1;
			Q.push(v);
		}
	}
	return true;
}

int main(){
	//ifstream cin("I.h");
	for(int cnt=1 ; true; cnt++){
		Adj.clear();
		G.clear();
		cin >> N >> T;
		if(N==0)
			return 0;

		Adj.resize(N);
		G.resize(N,VI(N));

		int i,j,k;
		int ret = 0;
		for(i=0 ; i<T ; i++){
			cin >> j >> k;
			j--; k--;
			if(BFS(k,j)){
				if(G[j][k] == 0){
					G[j][k] = 1;
					Adj[j].push_back(k);
				}
			}
			else
				ret++;
		}
		cout << cnt <<". "<<ret<<endl;
	}
}
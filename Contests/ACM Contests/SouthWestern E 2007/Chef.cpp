#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>

using namespace std;

#define REP(i, a, b) 		for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)		for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)				v.begin(),v.end()

#define VI					vector<int>
#define VVI					vector<VI>

#define II					pair<int,int>
#define x					first
#define y					second
#define VII					vector<II>
#define VVII				vector<VII>

const int Inf = 1e7;
int N;
int M;		
VI L;		// Elements of Left
VI R;		// Elements of Right
VI LR;		// Matching from L to R
VI RL;		// Matching from R to L
VI Match;	// Matching of elements
VVI Adj;	// Adjacency List
VVI G;		// Adjacency Matrix
VI cc;
VI V;

int DFS(int u){
	int v;
	if(u<0) return 1;
	if(V[u]) return 0;
	V[u] = 1;
	FOR(v,R.size()){
		if(G[L[u]][R[v]] >= Inf) // Or Inf
			continue;
		if(DFS(RL[v])){
			LR[u] = v;
			RL[v] = u;
			Match[L[u]] = R[v];
			Match[R[v]] = L[u];
			return 1;
		}
	}
}

int Find_Mate(int u){
	V.clear(); V.resize(N);
	return DFS(u);
}

int BiMatch(){
	LR.clear(); LR.resize(N,-1);
	RL.clear(); RL.resize(M,-1);
	Match.clear(); Match.resize(N+M,-1);
	int i;
	int ans = 0;
	FOR(i,N)
		if(LR[i] == -1)
			ans += Find_Mate(i);
	return ans;
}

int AugCycle(){
	int i,j,k;
	int u,v;
	VVI dt(N,VI(N));
	VVI fs(N,VI(N));
	FOR(u,N){
		FOR(v,N){
			i = L[u];
			j = R[LR[u]];
			k = R[LR[v]];
			dt[u][v] = G[i][j] - G[i][k];
			fs[u][v] = v;
		}
	}

	FOR(u,N){
		FOR(v,M){
			if(RL[v] != -1)
				continue;
			i = L[u];
			j = R[LR[u]];
			k = R[v];
			if(G[i][j] - G[i][k] > dt[u][u]){ // < if Max Profit
				dt[u][u] = G[i][j] - G[i][k];
				fs[u][u] = k;
			}
		}
	}

	FOR(k,N){
		FOR(i,N){
			FOR(j,N){
				if(dt[i][k] + dt[k][j] > dt[i][j]){ // Change to < for Max Profit
					dt[i][j] = dt[i][k] + dt[k][j];
					fs[i][j] = fs[i][k];
					if(i==j){
						cc.clear();
						do{
							cc.push_back(i);
							i = fs[i][j];
						}while(i!=j && i<N);
						if(i>=N)
							cc.push_back(i);
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

int BestMatch(){
	int i,j,k;
	int u,v;
	BiMatch();
	while(AugCycle()){
		j = LR[cc.front()];
		FOR(i,cc.size()-1){
			if(cc[i] > N)
				continue;
			else if(cc[i+1] < N){
				LR[cc[i]] = LR[cc[i+1]];
				Match[L[cc[i]]] = R[LR[cc[i]]];
				RL[LR[cc[i]]] = cc[i];
			}
			else{
				RL[LR[cc[i]]] = -1;
				LR[cc[i]] = cc[i+1]-N;
				Match[L[cc[i]]] = R[LR[cc[i]]];
				RL[LR[cc[i]]] = cc[i];
			}
		}
		if(cc[i] < N){
			LR[cc[i]] = j;
			Match[L[cc[i]]] = R[LR[cc[i]]];
			RL[LR[cc[i]]] = cc[i];
		}
	}
	int ret=0;
	FOR(i,N){
		u = L[i];
		v = R[LR[i]];
		ret += G[u][v];
	}
	return ret;
}

int main(){
	ifstream cin("G.txt");
	int T;
	cin >> T;
	bool b = false;
	for(int cnt=0 ; cnt<T ; cnt++){
		if(b)
			cout<<endl;
		b = true;
		int i,j,k;
		int u,v;
		cin >> N >> M;
		L.clear(); L.resize(N);
		R.clear(); R.resize(M);
		G.clear(); G.resize(N+M,VI(N+M,Inf));
		Adj.clear(); Adj.resize(N+M);

		FOR(i,N) L[i] = i;
		FOR(i,M) R[i] = N+i;

		int H;
		cin >> H;
		FOR(i,H){
			cin >> u >> v >> k;
			v += N;
			Adj[u].push_back(v); G[u][v] = k;
			Adj[v].push_back(u); G[v][u] = k;
		}

		cout << BestMatch() << endl;
	}
}
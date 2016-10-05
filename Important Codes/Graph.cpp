#include <h++.cpp>

#define NIL -1

int N;			// Number of Vertecis
int M;			// Number of Edges
VVI Adj;		// Adjecency List
VI C;			// Colors of vertecies
VVI G;			// Graph - Adjecncy Matrix
VI SubG;		// related subgraph
VI ET;			// Vertecis in Eular Tour
int s,t;		// Source & Distanation

bool IsEuler();

//bool EulerTour(){
//	ET.clear();
//	if(!IsEuler())
//		return false;
//
//	int i,j,k;
//	int u,v;
//	II e0,e1,e2;
//	queue<int> Q;
//	VI done(N);
//
//	Q.push(0);
//	done[0] = 1;
//
//	while(!Q.empty()){
//		u = Q.front(); Q.pop();
//		FOR(i,Adj[u].size()){
//			v = Adj[u][i];
//
//			while(v != u){
//				if(!done[v])
//					done[v] = 1;
//			}
//		}
//	}
//}

// ***********************************
// Find Sub-Connected-Graphs
// ***********************************

void DFS_SubG(int u,int sg){
	int i;
	SubG[u] = sg;
	FOR(i,Adj[u].size())
		DFS_SubG(Adj[u][i],sg);
}

bool Connected(){
	int i;
	SubG.clear();

	int N = Adj.size();
	SubG.resize(N,NIL);

	int sg = 0;
	FOR(i,N){
		if(SubG[i] != NIL)
			continue;
		DFS_SubG(i,sg);
		sg++;
	}
	return sg == 1;
}

// ***********************************
// Euler & Hamilton
// ***********************************

bool IsEuler(){
	if(!Connected())
		return false;
	for(int i=0 ; i<Adj.size() ; i++)
		if(Adj[i].size()%2 == 1)
			return false;
	return true;
}

bool IsHamilton(){
	if(!Connected())
		return false;
	for(int i=0 ; i<Adj.size() ; i++)
		for(int j=i+1 ; j<Adj.size() ; j++)
			if(find(All(Adj[i]),j) == Adj[i].end())
				if(Adj[i].size()+Adj[j].size() < Adj.size())
					return false;
	return true;
}

// ***********************************
// Floyd-Warshall
// ***********************************

VVI P;					// vertics before last one in the shortest path
VVI D;					// shortest distance between two nodes

void floyd(){
	int i,j,k;
	P.clear();
	P.resize(N,VI(N));
	D = G;
	FOR(i,N)
		FOR(j,N)
			P[i][j] = i;
	FOR(k,N){
		FOR(i,N){
			FOR(j,N){
				if(D[i][j] > D[i][k]+D[k][j]){
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = P[k][j];
				}
			}
		}
	}
}

// ***********************************
// Bellman-Ford
// ***********************************

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
		if(level[u] > 3*N) // Negative Cycle
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

// ***********************************
// Coloring - Chromatic Number
// ***********************************

int Coloring(){
	int i,j,k;
	int u;
	C.clear();

	int N = Adj.size();
	C.resize(N);
	queue<int> q;
	VVB cnt(N,vector<bool>(N));
	VB done(N);
	VB InQ(N);
	
	FOR(u,N){
		if(done[u])
			continue;
		q.push(u);
		InQ[u] = true;
		while(!q.empty()){
			k = q.front(); q.pop();
			
			FOR(i,Adj[k].size()){
				j = Adj[k][i];
				cnt[j][C[k]] = true;
			}

			FOR(i,Adj[k].size()){
				j = Adj[k][i];
				if(done[j])
					continue;
				while(cnt[j][C[j]])
					C[j]++;
				if(!InQ[j])
					q.push(j);
				InQ[j] = true;
			}

			done[k] = true;
		}
	}

	int ret = 0;
	FOR(i,N)
		ret = max(ret,C[i]);
	return ret+1;
}

// ***********************************
// Maximum Matching - Bipartite Graph
// ***********************************

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

// ***********************************
// Test Program
// ***********************************

int main(){
	int i,j,k;
	ifstream cin("input.h");
	cin >> N;
	Resize(Adj,N);
	G.clear();
	G.resize(N,VI(N));

	FOR(i,N){
		cin >> k;
		Resize(Adj[i],k);
		FOR(j,k){
			cin >> Adj[i][j];
			G[i][Adj[i][j]] = 1;
		}
	}

	EulerTour();

	cout << endl;

	return 0;
}
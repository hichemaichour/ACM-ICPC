#include "h.cpp"

VVI Adj;		// Adjecency List
VVI G;			// Graph
VVI AG;			// Augmented Graph
VVI F;			// Flow
VI e;			// Excess Water
VI h;			// Hight of vertecies
int s;			// Source
int t;			// Sink

void Init_Preflow(){
	int N = Adj.size();
	h.clear();
	e.clear();
	h.resize(N);
	e.resize(N);
	h[s] = N;

	F.clear();
	F.resize(N,VI(N));
	int i;
	FOR(i, Adj[s].size()){
		int u = Adj[s][i];
		F[s][u] = AG[s][u];
		F[u][s] = -AG[s][u];

		e[u] = AG[s][u];
		e[s] -= AG[s][u];

		AG[u][s] = AG[s][u];
		AG[s][u] = 0;
	}
}

void Push(int u,int v){
	int f = min(e[u],AG[u][v]);
	F[u][v] += f;
	F[v][u] = -F[u][v];
	e[u] -= f;
	e[v] += f;
	AG[u][v] -= f;
	AG[v][u] += f;
}

void Relabel(int u){
	int Min = INT_MAX;
	int i;
	FOR(i, Adj[u].size()){
		int v = Adj[u][i];
		if(AG[u][v]>0)
			Min = min(Min,h[v]);
	}
	h[u] = Min + 1;
}

int Max_Flow(){
	int u,i;
	AG = G;
	Init_Preflow();

	bool Still = true;
	while(Still){
		Still = false;
		FOR(u, e.size()){
			if(u==s || u==t || e[u]==0)
				continue;
			Still = true;
			while(e[u]){
				for(i=0 ; i<Adj[u].size() && e[u] ; i++){
					int v = Adj[u][i];
					if(AG[u][v] > 0 && h[u] == h[v]+1)
						Push(u,v);
				}
				if(e[u])
					Relabel(u);
			}
		}
	}

	int sum = 0;
	FOR(i, Adj[t].size()){
		u = Adj[t][i];
		sum += F[u][t];
	}
	return sum;
}

int main(){
	ifstream cin("input.h");
	int i,j;
	int N;
	cin>>N>>s>>t;

	G.clear();
	G.resize(N,VI(N));
	for(i=0 ; i<N ; i++)
		for(j=0 ; j<N ; j++)
			cin>>G[i][j];

	Adj.clear();
	Adj.resize(N);
	for(i=0 ; i<N ; i++){
		for(j=i+1 ; j<N ; j++){
			if(G[i][j] != 0 || G[j][i] != 0){
				Adj[i].push_back(j);
				Adj[j].push_back(i);
			}
		}
	}

	cout<<Max_Flow()<<endl;
	return 0;
}
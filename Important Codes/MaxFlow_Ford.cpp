#include "h.cpp"

#define NIL -1

VVI G;			// Adjecency Matrix of Graph G
VVI AG;			// Augmented Graph
VVI Adj;		// Adjecency list
VVI F;			// Flow in the network
int s;			// Source
int t;			// Sink
deque<int> Path;// Path

bool Path_Using_BFS(){
	Path.clear();

	queue<int> q;
	VB done(AG.size());
	VI Pre (AG.size(),NIL);

	q.push(s);
	done[s] = true;

	int i,u,v;
	while(!q.empty()){
		u = q.front(); q.pop();
		for(i=0 ; i<Adj[u].size() ; i++){
			v = Adj[u][i];

			if(done[v] || AG[u][v] == 0)
				continue;
			done[v] = true;

			Pre[v] = u;
			if(v == t){
				Path.push_front(v);
				while(Pre[v] != NIL){
					v = Pre[v];
					Path.push_front(v);
				}
				return true;
			}

			q.push(v);
		}
	}
	return false;
}

void Max_Flow(){
	int i,u,v;
	F.clear();
	F.resize(G.size(),VI(G.size()));
	AG = G; // Build the Augmented Graph
	while(Path_Using_BFS()){ // loop until there is no path

		// find the flow of the current path
		int f = INT_MAX;
		for(i=0 ; i<Path.size()-1 ; i++){
			u = Path[i];
			v = Path[i+1];
			f = min(f , AG[u][v]);
		}

		// update the path
		for(i=0 ; i<Path.size()-1 ; i++){
			u = Path[i];
			v = Path[i+1];

			AG[u][v] -= f;
			AG[v][u] += f;

			F[u][v] += f;
			F[v][u] = -F[u][v];
		}
	}

	return; // return whtsoever u want based on the augmented graph or the flow in the network
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

	Max_Flow();
	return 0;
}
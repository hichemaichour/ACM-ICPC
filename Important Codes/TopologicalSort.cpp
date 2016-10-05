#include "h++.cpp"

int N;
VVI Adj;
VI done;
VI order;
int pos;
int IsDAG;

void DFS(int u){
	int i,j,k;
	if(done[u] == 1) // done -> VI
		IsDAG = false;
	if(done[u])
		return;
	done[u] = 1;
	FOR(i,Adj[u].size())
		DFS(Adj[u][i]);
	done[u] = 2;
	order[pos] = u;
	pos--;
}

bool TopoSort(){
	int i,j,k;
	done.clear(); done.resize(N);
	order.resize(N);
	pos = N-1;
	IsDAG = true;
	FOR(i,N)
		if(!done[i])
			DFS(i);
	return IsDAG;
}

int main(){
	ifstream cin("input.txt");
	int i,j,k,n;
	cin >> N >> n;
	Adj.clear();
	Adj.resize(N);
	FOR(i,n){
		cin >> j >> k;
		Adj[j].push_back(k);
	}
	TopoSort();
	return 0;
}
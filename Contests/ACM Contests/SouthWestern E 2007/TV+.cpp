#include <iostream>
#include <map>
#include <functional>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

#define VI vector<int>
#define VVI vector<VI>

#define All(v) v.begin(),v.end()
#define Resize(v,N) v.clear(); v.resize(N);

#define FOR(i,N) for(i=0 ; i<(int)N ; i++)

#define II pair<int,int>
#define St pair<int,II>
#define Data pair<pair<string,string>,int>
#define x second.first
#define y second.second
#define str1 first.first
#define str2 first.second
#define n second

int N;
VVI Adj;
VVI G;
VVI T_Adj;
VI t;

int Find(int u){
	int i;
	VI V;
	while(t[u] != u){
		V.push_back(u);
		u = t[u];
	}
	FOR(i,V.size())
		t[V[i]] = u;
	return u;
}

int MST(){
	int i,j,k;
	int u,v;

	t.resize(N);
	FOR(i,N)
		t[i] = i;

	vector<St> V;
	FOR(i,N){
		FOR(j,Adj[i].size()){
			k = Adj[i][j];
			if(k>i)
				V.push_back(St(G[i][k] , II(i,k)));
		}
	}
	sort(All(V));

	int ret = 0;
	int cnt = 1;
	Resize(T_Adj,N);
	FOR(i,V.size()){
		if(cnt == N)
			break;
		u = V[i].x; v = V[i].y;
		j = Find(u); k = Find(v);
		if(j != k){
			t[k] = j;
			cnt++;
			ret += G[u][v];
			T_Adj[u].push_back(v);
			T_Adj[v].push_back(u);
		}
	}
	return ret;
}

int main(){
	ifstream cin("TV.h");
	int T;
	cin >> T;
	bool b=false;
	for(int cnt=0 ; cnt<T ; cnt++){
		int i,j,k;
		int u,v;
		if(b)
			cout<<endl;
		b=true;

		cin >> N;
		int E;
		cin >> E;

		Data data;
		vector<Data> V;
		vector<string> Names;
		for(i=0 ; i<E ; i++){
			cin >> data.str1 >> data.str2 >> data.n;
			V.push_back(data);
			Names.push_back(data.str1);
			Names.push_back(data.str2);
		}

		sort(All(Names));
		Names.resize(unique(All(Names)) - Names.begin());

		map<string,int> m;
		for(i=0 ; i<Names.size() ; i++)
			m[Names[i]] = i;

		Adj.clear(); Adj.resize(N);
		G.clear(); G.resize(N,VI(N));

		for(i=0 ; i<V.size() ; i++){
			u = m[V[i].str1]; v = m[V[i].str2];
			Adj[u].push_back(v); G[u][v] = V[i].n;
			Adj[v].push_back(u); G[v][u] = V[i].n;
		}

		cout << MST() << endl;
	}
}

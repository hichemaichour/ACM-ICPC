#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

#include <algorithm>

#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <string>

#include <iterator>
#include <functional>
#include <complex>
#include <numeric>
#include <valarray>

#include <cmath>

using namespace std;

#define REP(i, a, b) 		for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)		for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)				v.begin(),v.end()

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(ALL(v),e) - v.begin() )

typedef long long			LL;
typedef long double			LD;
typedef vector<int>			VI;
typedef vector<VI>			VVI;
typedef vector<bool>		VB;
typedef vector<VB>			VVB;
typedef vector<double>		VD;
typedef vector<VD>			VVD;
typedef pair<int, int>		II;
typedef vector<II>			VII;
typedef vector<VII>			VVII;
typedef vector<string>		VS;
typedef vector<VS>			VVS;

struct Info{
	int H;
	string G;
	string M;
	string S;
};

vector<Info> V;
VVI Adj;
VVI G;
VVI AG;
VVI F;
VI h;
VI e;
int s;
int t;

bool Connected(int i,int j){
	if( abs(V[i].H - V[j].H) > 40 )
		return true;
	if(V[i].G == V[j].G)
		return true;
	if(V[i].M != V[j].M)
		return true;
	return V[i].S == V[j].S;
}

void Build_Complement_Graph(){
	s = V.size();
	t = s + 1;
	Adj.clear();
	G.clear();
	Adj.resize(t+1);
	G.resize(t+1,VI(t+1));
	for(int i=0 ; i<V.size() ; i++){
		for(int j=i+1 ; j<V.size() ; j++){
			int u = i;
			int v = j;
			if(V[u].G == "F")
				swap(u,v);
			if(!Connected(u,v)){
				Adj[u].push_back(v);
				Adj[v].push_back(u);
				G[u][v] = 1;
			}
			Adj[s].push_back(u);
			Adj[u].push_back(s);
			G[s][u] = 1;

			Adj[t].push_back(v);
			Adj[v].push_back(t);
			G[v][t] = 1;
		}
	}
}

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

BG_MIS(){
	return Adj.size() - MaxFlow();
}

int main(){
	ifstream cin("in.h");
	int T;
	cin>>T;
	while(T--){
		int i;

		int N;
		cin>>N;
		V.clear();
		Adj.clear();
		m.clear();

		V.resize(N);
		Adj.resize(N);
		m.resize(N+2);

		for(i=0 ; i<N ; i++)
			cin >> V[i].H >> V[i].G >> V[i].M >> V[i].S;

		Build_Complement_Graph();

		cout<<BG_MIS()<<endl;
	}
}
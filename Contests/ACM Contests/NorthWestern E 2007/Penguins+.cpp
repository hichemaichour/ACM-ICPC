#include <iostream>
#include <fstream>
#include <sstream>

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

#define x first.first
#define y first.second
#define n second.first
#define m second.second
#define INF INT_MAX
const double EPS = 1e-9;

int N;
double D;
vector<pair<II,II> > vv;
vector<VI> Adj;
vector<VI> G;
vector<VI> AG;
deque<int> Path;
VI RET;
int s;
int t;
int NP;
vector<VI> F;
VI h;
VI e;

double dist(int i,int j){
	double X = vv[i].x - vv[j].x;
	double Y = vv[i].y - vv[j].y;
	return sqrt( X*X + Y*Y );
}

void Build_Graph(){
	Adj.clear();
	G.clear();

	Adj.resize(2*N + 1);
	G.resize(2*N+1 , VI(2*N+1));

	NP = 0;
	for(int i=0 ; i<N ; i++){
		Adj[2*i].push_back(2*i+1);
		Adj[2*i+1].push_back(2*i);
		G[2*i][2*i+1] = vv[i].m;

		for(int j=i+1 ; j<N ; j++){
			if(dist(i,j) <= D+EPS){
				Adj[2*i+1].push_back(2*j);
				Adj[2*j].push_back(2*i+1);
				G[2*i+1][2*j] = INF;
				Adj[2*j+1].push_back(2*i);
				Adj[2*i].push_back(2*j+1);
				G[2*j+1][2*i] = INF;
			}
		}

		if(vv[i].n != 0){
			Adj[2*N].push_back(2*i);
			Adj[2*i].push_back(2*N);
			G[2*N][2*i] = vv[i].n;
			NP += vv[i].n;
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

bool MF(){
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
	return sum == NP;
}

void Max_Flow(){
	RET.clear();
	s = 2*N;
	for(int i=0 ; i<N ; i++){
		t = 2*i;
		if(MF())
			RET.push_back(i);
	}
}

int main(){
	//ifstream cin("testdata.in");
	//ifstream cin("Penguins.h");
	int T;
	cin >> T;
	int hichem = 1;
	while(T--){
		if(hichem == 9)
			hichem = 1;
		hichem++;
		int i;
		cin>>N>>D;

		vv.clear();
		vv.resize(N);
		for(i=0 ; i<N ; i++)
			cin >> vv[i].x >> vv[i].y >> vv[i].n >> vv[i].m;

		Build_Graph();
		Max_Flow();

		if(RET.empty())
			cout<<-1<<endl;
		else{
			cout<<RET[0];
			for(i=1 ; i<RET.size() ; i++)
				cout<<" "<<RET[i];
			cout<<endl;
		}
	}
	return 0;
}
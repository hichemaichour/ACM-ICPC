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

#define Data pair<II,II>
#define x first.first
#define y first.second
#define n second.first
#define l second.second

const int INF = 20*20 + 5;

int D;				// Jump Distance
int X,Y;			// Size of Map
vector<Data> v;		// Data
int N;				// # of vertices
int NL;				// # of Lizards
VVI Adj;			// Adjacency List
VVI G;				// Weigthed Directed Graph
VVI AG;				// Augmented graph
int s;				// source
int t;				// sink
VVI F;				// Flow between vertecies
VI e;				// Excess flow
VI h;				// hight of vertecies

int dist(int i,int j){
	return abs(v[i].x - v[j].x) + abs(v[i].y - v[j].y);
}

void Build_Graph(){
	Adj.clear();
	G.clear();
	N = v.size();

	Adj.resize(2*N + 2);
	G.resize(2*N+2 , VI(2*N+2));
	s = 2*N;
	t = 2*N + 1;

	int i,j;
	NL = 0;
	FOR(i,N){
		// initialize the double vertex representation of each vertex
		Adj[2*i].push_back(2*i+1);
		Adj[2*i+1].push_back(2*i);
		G[2*i][2*i+1] = v[i].n;

		// find connection between vertices
		REP(j, i+1, N-1){
			if(dist(i,j) <= D){
				Adj[2*i+1].push_back(2*j);
				Adj[2*j].push_back(2*i+1);
				G[2*i+1][2*j] = INF;
				Adj[2*j+1].push_back(2*i);
				Adj[2*i].push_back(2*j+1);
				G[2*j+1][2*i] = INF;
			}
		}

		// connect to the source
		if(v[i].l != 0){
			Adj[s].push_back(2*i);
			Adj[2*i].push_back(s);
			G[s][2*i] = v[i].l;
			NL += v[i].l;
		}

		// connect to the sink
		if(v[i].x <= D || X-v[i].x <= D || v[i].y <= D || Y-v[i].y <= D){
			Adj[t].push_back(2*i+1);
			Adj[2*i+1].push_back(t);
			G[2*i+1][t] = INF;
		}
	}
}

void Init_Preflow(){
	int NN = Adj.size();
	h.clear();
	e.clear();
	h.resize(NN);
	e.resize(NN);
	h[s] = NN;

	F.clear();
	F.resize(NN,VI(NN));
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
	//ifstream cin("Lizards.h");
	int T,cnt;
	cin >> T;
	REP(cnt,1,T){
		v.clear();
		int i,j;
		cin >> X >> D;

		vector<string> s1(X);
		vector<string> s2(X);
		FOR(i, X)
			cin >> s1[i];
		FOR(i, X)
			cin >> s2[i];
		Y = s1[0].size();

		FOR(i, X){
			FOR(j, Y){
				if(s1[i][j] == '0')
					continue;
				v.push_back(Data( II(i+1,j+1) , II(s1[i][j]-'0' , s2[i][j]=='L')));
			}
		}

		X++; Y++;
		Build_Graph();
		int L = NL - Max_Flow();

		cout<<"Case #"<<cnt<<": ";
		if(L == 0)
			cout<<"no lizard was left behind.";
		else if(L == 1)
			cout<<"1 lizard was left behind.";
		else
			cout<<L<<" lizards were left behind.";
		cout<<endl;
	}
}
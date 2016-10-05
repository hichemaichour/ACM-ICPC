// if you are VC++ users, this will suppress some compilation warning messages
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>

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

#define REP(i, a, b) 		for (i=a ; i<=b ; i++)
#define REPN(i, n)			REP(i, 0, n-1)
#define REPD(i, a, b)		for (i=a ; i>=b ; i--)
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)

#define All(v)				v.begin(),v.end()

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue
#define NL					numeric_limits

// Shortcuts for "common" data types in contests
typedef long long			LL;
typedef long double			LD;
typedef vector<int>			VI;
typedef vector<bool>		VB;
typedef vector<double>		VD;
typedef pair<int, int>		II;
typedef vector<II>			VII;

#define x first.first
#define y first.second
#define n second.first
#define m second.second
#define INF -1
const double EPS = 1e-9;

int N;
double D;
vector<pair<II,II> > v;
vector<VI> Adj;
vector<VI> G;
vector<VI> AG;
deque<int> Path;
VI RET;
int s;
int t;
int NP;
vector<VI> F;


double dist(int i,int j){
	double X = v[i].x - v[j].x;
	double Y = v[i].y - v[j].y;
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
		G[2*i][2*i+1] = v[i].m;

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

		if(v[i].n != 0){
			Adj[2*N].push_back(2*i);
			Adj[2*i].push_back(2*N);
			G[2*N][2*i] = v[i].n;
			NP += v[i].n;
		}
	}
}

bool BFS(){
	int U,V;
	int i,j,k;
	Path.clear();
	VI Pre(2*N+1,INF);
	VB done(2*N+1);
	queue<int> q;
	q.push(s);
	done[s] = true;
	while(!q.empty()){
		U = q.front(); q.pop();
		for(i=0 ; i<Adj[U].size() ; i++){
			V = Adj[U][i];
			if(done[V] || AG[U][V]==0)
				continue;
			done[V] = true;
			Pre[V] = U;
			if(V == t){
				Path.push_front(V);
				while(Pre[V] != INF){
					V = Pre[V];
					Path.push_front(V);
				}
				return true;
			}
			q.push(V);
		}
	}
	return false;
}

int MF(){
	int i,j,k;

	while(BFS()){
		int Min=INT_MAX;
		for(i=0 ; i<Path.size()-1 ; i++){
			j = Path[i];
			k = Path[i+1];
			if(AG[j][k] != INF)
				Min = min(Min , AG[j][k]);
		}
		for(i=0 ; i<Path.size()-1 ; i++){
			j = Path[i];
			k = Path[i+1];
			AG[j][k] -= Min;
			AG[k][j] += Min;
			F[j][k] += Min;
			F[k][j] = -F[j][k];
		}
	}

	int sum = 0;
	for(i=0 ; i<Adj[t].size() ; i++){
		j = Adj[t][i];
		sum += F[j][t];
	}
	return sum == NP;
}

void Max_Flow(){
	RET.clear();
	s = 2*N;
	for(int i=0 ; i<N ; i++){
		t = 2*i;
		AG = G;
		F.clear();
		F.resize(2*N+1 , VI(2*N+1));
		if(MF())
			RET.push_back(i);
	}
}

int main(){
	ifstream cin("testdata.in");
	int T;
	cin >> T;
	int hichem = 1;
	while(T--){
		if(hichem == 9)
			hichem = 1;
		hichem++;
		int i;
		cin>>N>>D;

		v.clear();
		v.resize(N);
		for(i=0 ; i<N ; i++)
			cin >> v[i].x >> v[i].y >> v[i].n >> v[i].m;

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
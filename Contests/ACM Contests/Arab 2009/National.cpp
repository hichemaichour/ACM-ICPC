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
#define Resize(v,N)			v.clear(); v.resize(N);

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(All(v),e) - v.begin() )


typedef long long			LL;
typedef long double			LD;
typedef pair<int, int>		II;
typedef vector<int>			VI;
typedef vector<VI>			VVI;
typedef vector<bool>		VB;
typedef vector<VB>			VVB;
typedef vector<double>		VD;
typedef vector<VD>			VVD;
typedef vector<LL>			VLL;
typedef vector<VLL>			VVLL;
typedef vector<LD>			VLD;
typedef vector<VLD>			VVLD;
typedef vector<II>			VII;
typedef vector<VII>			VVII;
typedef vector<string>		VS;
typedef vector<VS>			VVS;

int dx[] = {-1,-2,-2,-1,1,2, 2, 1,-1,0,1, 0};
int dy[] = {-2,-1, 1, 2,2,1,-1,-2, 0,1,0,-1};
int N;
VI BL,BR;
int R,C;
VVI Adj;
VI V;
VI m;
VI M;
VI done;
int ret;

void Build_Graph() {
	int i, j, k;
	int u, v;
	int x, y;
	N = 0;
	m.resize(R*C, -1);
	BL.clear();
	BR.clear();
	FOR(i, R) {
		FOR(j, C) {
			u = i * C + j;
			if (V[u] == -1)
				continue;
			m[u] = N;
			if((i+j)%2)
				BL.push_back(N);
			else
				BR.push_back(N);
			N++;
		}
	}

	Adj.resize(N);
	FOR(i, R) {
		FOR(j, C) {
			u = i * C + j;
			if (V[u] == -1)
				continue;
			int buf = 1;
			FOR(k, 12) {
				if (!(buf & V[u])) {
					buf *= 2;
					continue;
				}
				x = i + dx[k];
				y = j + dy[k];
				v = x * C + y;
				if (x >= R || x < 0 || y >= C || y < 0 || V[v] == -1){
					buf *= 2;
					continue;
				}
				if((i+j)%2)
					Adj[m[u]].push_back(m[v]);
				else
					Adj[m[v]].push_back(m[u]);
				buf *= 2;
			}
		}
	}
	FOR(i,N)
		sort(All(Adj[i]));
}

int DFS(int u){
	int i,j,k;
	int v;
	FOR(i,Adj[u].size()){
		v = Adj[u][i];
		if(done[v] == -1){
			done[v] = 1;
			if(M[v] == -1 || DFS(M[v])){
				M[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int BiMatch(){
	M.clear(); M.resize(N,-1);
	int i,j;
	int ans = 0;
	FOR(i,BL.size()){
		j = BL[i];
		done.clear(); done.resize(N,-1);
		ans += DFS(j);
	}
	return ans;
}


int main(){
	ifstream cin("guards.in");
	for(int cnt=1 ; true ; cnt++){
		int i,j,k;
		int u,v;
		int x,y;
		Adj.clear();
		V.clear();
		m.clear();

		cin >> R >> C;
		if(R==0)
			return 0;

		V.resize(R*C);
		FOR(i,R){
			FOR(j,C){
				u = i*C + j;
				cin >> V[u];
			}
		}

		Build_Graph();

		cout << cnt <<". "<< BiMatch() << endl;
	}
}
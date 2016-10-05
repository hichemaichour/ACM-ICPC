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

int R,C;
int N;
VVI Adj;
VI nAdj;
VVI G;
int ret;
VB done;

void Rec(int u=0 , int sum=0 , int cnt=1){
	int i,j,k;
	int v;

	j = 1; k = C;
	if(done[j] && done[k] && cnt!=N)
		return;

	k = -1;
	FOR(i,Adj[u].size()){
		if(u == 0){
			k = 1;
			break;
		}
		if(cnt == N-1)
			break;
		v = Adj[u][i];
		if(done[v])
			continue;
		if(k != -1 && nAdj[v] == 1)
			return;
		if(nAdj[v] == 1)
			k = v;
	}

	if(k != -1){
		v = k;
		done[v] = true;
		FOR(j,Adj[v].size()){
			k = Adj[v][j];
			nAdj[k]--;
		}
		Rec(v , sum+G[u][v] , cnt+1);
		done[v] = false;
		FOR(j,Adj[v].size()){
			k = Adj[v][j];
			nAdj[k]++;
		}
		return;
	}

	FOR(i,Adj[u].size()){
		v = Adj[u][i];
		if(cnt == N && v == 0)
			ret = min(ret,sum+G[u][v]);
		if(done[v])
			continue;
		done[v] = true;
		FOR(j,Adj[v].size()){
			k = Adj[v][j];
			nAdj[k]--;
		}
		Rec(v , sum+G[u][v] , cnt+1);
		done[v] = false;
		FOR(j,Adj[v].size()){
			k = Adj[v][j];
			nAdj[k]++;
		}
	}
}

void Hamilton(){
	ret = INT_MAX;
	Resize(done,N);
	done[0] = true;
	Rec();
}

int main(){
	ifstream cin("Pipe.h");
	int T;
	cin >> T;
	while(T--){
		int i,j,k;
		cin >> R >> C;
		N = R*C;

		Resize(Adj,N);
		G.clear();
		G.resize(N,VI(N));

		string str;
		int n;
		char c;
		int u,v;
		FOR(i,R){
			if(i == 0)
				cin >> str;
			else{
				FOR(j,C){
					cin >> c >> c;
					u = (i-1)*C + j;
					v = i*C + j;
					Adj[u].push_back(v);
					Adj[v].push_back(u);
					G[u][v] = c - '0';
					G[v][u] = G[u][v];
				}
				cin >> c;
			}

			cin >> c;
			FOR(j,C-1){
				cin >> n;
				u = i*C + j;
				v = u+1;
				Adj[u].push_back(v);
				Adj[v].push_back(u);
				G[u][v] = n;
				G[v][u] = n;
			}
			cin >> c;
		}
		cin >> str;

		Resize(nAdj,N);
		FOR(i,N)
			nAdj[i] = Adj[i].size();
		Hamilton();

		cout << ret << endl;
	}
}
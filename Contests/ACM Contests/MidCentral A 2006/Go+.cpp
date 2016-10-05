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

#define NIL -1
#define Data pair<II,II>
#define ID first.first
#define x first.second
#define y second.first
#define z second.second

const double EPS = 1e-9;

int N;
VVI Adj;
vector<Data> V;

double Dist(int i,int j){
	double dx = V[i].x - V[j].x;
	double dy = V[i].y - V[j].y;
	double dz = V[i].z - V[j].z;
	return sqrt( dx*dx + dy*dy + dz*dz );
}

void Build_Graph(){
	Resize(Adj,N);
	int i,j,k;
	REP(i,1,N-1){
		double Min = 1e9 + 10;
		FOR(j,i){
			if(Dist(i,j)+EPS < Min){
				Min = Dist(i,j);
				k = j;
			}
		}
		Adj[i].push_back(k);
		Adj[k].push_back(i);
	}

	FOR(i,N)
		sort(All(Adj[i]));
}

II Tree_Center(){
	int i,j,k;
	deque<int> L;
	int M = N;
	FOR(i,N)
		if(Adj[i].size() == 1)
			L.push_back(i);

	while(M > 2){
		int n = L.size();

		FOR(i,n){
			int u = L.front(); L.pop_front();
			M--;
			FOR(j,Adj[u].size()){
				k = Adj[u][j];
				Remove(Adj[k],u);
				if(Adj[k].size() == 1)
					L.push_back(k);
			}
		}
	}

	if(M == 2)
		return II(L.front() , L.back());
	else
		return II(L.front() , NIL);
}

int main(){
	//ifstream cin("Go.h");
	while(true){
		int i,j,k;

		cin >> N;
		if(N==0)return 0;
		Resize(V,N);
		
		FOR(i,N)
			cin >> V[i].ID >> V[i].x >> V[i].y >> V[i].z;

		Build_Graph();
		II ret = Tree_Center();
		if(ret.second == NIL)
			cout << V[ret.first].ID << endl;
		else
			cout << V[ret.first].ID <<" "<< V[ret.second].ID << endl;
	}
}
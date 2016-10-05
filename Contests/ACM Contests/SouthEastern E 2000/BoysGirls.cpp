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

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(All(v),e) - v.begin() )

#define VI					vector<int>
#define VVI					vector<VI>

#define x					first
#define y					second
#define II					pair<int,int>
#define VII					vector<II>
#define VVII				vector<VII>

int N,M;
VI RL;
VI LR;
VVI AdjL;
VVI AdjR;
VVI G;

VI V;

int DFS(int u){
	if(u<0)
		return 1;
	if(V[u])
		return 0;
	V[u] = 1;
	int i;
	FOR(i,M){

	}
}

int Find_Mate(int u){
	V.clear(); V.resize(N);
	return DFS(u);
}

int BiMatch(){
	int ans;
	int i;
	LR.clear(); LR.resize(N,-1);
	RL.clear(); RL.resize(N,-1);
	FOR(i,N)
		if(LR[i]==-1)
			ans += Find_Mate(i);
	return ans;
}


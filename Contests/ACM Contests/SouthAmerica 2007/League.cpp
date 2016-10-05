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

#define NIL -1

int H,R;	// # of Heros + # of Relations
VVI Adj;	// Adjecency List
VVB G;		// Adjecency Matrix

bool func(II p1,II p2){
	return p1.second < p2.second;
}

bool Can(){
	int i,j;
	VII V;
	FOR(i,H)
		V.push_back( II(Adj[i].size() , i) );
	sort(All(V),greater<II>());

	FOR(i,H)
		if(V[i].first < i)
			break;
	V.resize(i);

	VI In;
	VI Out;
	sort(All(V),func);
	j=0;
	FOR(i,H){
		if(j<V.size() && V[j].second == i){
			In.push_back(i);
			j++;
		}
		else
			Out.push_back(i);
	}

	FOR(i,In.size())
		REP(j,i+1,In.size()-1)
			if(!G[In[i]][In[j]])
				return false;
	FOR(i,Out.size())
		REP(j,i+1,Out.size()-1)
			if(!G[Out[i]][Out[j]])
				return false;
	return true;
}

int main(){
	ifstream cin("League.h");
	for(int cnt=1 ; true ; cnt++){
		int i,j,k;
		G.clear();
		Adj.clear();
		cin>>H>>R;
		if(H==0)
			return 0;

		Adj.resize(H);
		G.resize(H,VB(H));

		FOR(i,R){
			cin>>j>>k;
			j--; k--;
			Adj[j].push_back(k);
			Adj[k].push_back(j);
			G[j][k] = true;
			G[k][j] = true;
		}

		cout<<cnt<<" ";
		if(Can())
			cout<<"Y"<<endl;
		else
			cout<<"N"<<endl;
	}
}
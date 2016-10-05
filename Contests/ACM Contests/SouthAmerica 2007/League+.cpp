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

#define REP(i, a, b) 		for (i=a ; i<=b ; i++)
#define REPD(i, a, b)		for (i=a ; i>=b ; i--)
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

typedef map<int,bool>		MB;
typedef map<int,MB>			MMB;
#define NIL -1

int H,R;	// # of Heros + # of Relations
VVI Adj;	// Adjecency List
MMB G;		// Adjecency Matrix
VII JL;		// Justice Leage

bool func(II p1, II p2){
	return p1.second < p2.second;
}

void Simplify_Graph(){
	map<int,int> m;
	int i,j;
	j=0;
	FOR(i,H+1){
		if(Adj[i].empty())
			continue;
		m[i] = j;
		Adj[j] = Adj[i];
		j++;
	}
	H = j;
	Adj.resize(j);
	FOR(i,H)
		FOR(j,Adj[i].size())
			Adj[i][j] = m[ Adj[i][j] ];

	G.clear();
	FOR(i,H)
		FOR(j,Adj[i].size())
			G[i][Adj[i][j]] = true;
}

bool C1(){
	int i;
	FOR(i,H)
		if(Adj[i].size() != H-1)
			return false;
	return true;
}

bool C2(){
	int i,j;
	int u,v;
	int Min = INT_MAX;
	JL.clear();
	FOR(i,H){
		if(Adj[i].size() < Min){
			Min = Adj[i].size();
			u = i;
		}
	}

	FOR(i,Adj[u].size()){
		REP(j,i+1,Adj[u].size()-1)
			if(!G[Adj[u][i]][Adj[u][j]])
				return false;
	}

	u = Adj[u].front();
	JL.push_back( II(Adj[u].size(),u) );
	FOR(i,Adj[u].size()){
		v = Adj[u][i];
		JL.push_back( II(Adj[v].size(),v) );
	}

	sort(All(JL),greater<II>());
	FOR(i,JL.size())
		if(JL[i].first < i)
			break;
	JL.resize(i);

	VI In;
	VI Out;
	sort(All(JL),func);
	j = 0;
	FOR(i,H){
		if(j < JL.size() && JL[j].second == i){
			j++;
			In.push_back(i);
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
			if(G[Out[i]][Out[j]])
				return false;

	return true;
}

bool Can(){
	if(C1())
		return true;
	return C2();
}

int main(){
	//ifstream cin("League.h");
	for(int cnt=1 ; true ; cnt++){
		int i,j,k;
		Adj.clear();
		cin>>H>>R;
		if(H==0)
			return 0;

		Adj.resize(H+1);

		FOR(i,R){
			cin>>j>>k;
			j; k;
			Adj[j].push_back(k);
			Adj[k].push_back(j);
		}
		/*for(i=0 ; i<Adj.size() ; i++)
			sort(All(Adj[i]));*/

		Simplify_Graph();

		//cout<<cnt<<" ";
		if(Can())
			cout<<"Y"<<endl;
		else
			cout<<"N"<<endl;
	}
}
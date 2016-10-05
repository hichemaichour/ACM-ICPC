/*
ID: b0002141
PROG: holstein
LANG: C++
*/

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
#define REPI(i, v)		for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)		REP (i, 0, n-1)
#define FORD(i, n)		REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)		(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI			vector<int>
#define VVI			vector<VI>

#define VD			vector<double>
#define VVD			vector<VD>

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII		vector<VII>

#define st			pair<double,II>
#define num			second.first
#define den			second.second
#define val			first

int N;
int V,G;
VI v;
VVI S;
VI In;
VI ret;

bool Ok(){
	int i,j,k;
	VI Tot(V);
	FOR(i,G){
		if(!In[i]) continue;
		FOR(j,V) Tot[j] += S[i][j];
	}

	FOR(i,V) if(Tot[i] < v[i]) return false;
	return true;
}

void Modify(int n){
	int i;
	N = n;
	ret.clear();
	FOR(i,G) if(In[i]) ret.push_back(i+1);
}

void Rec(int pos=0,int n=0){
	if(n>=N) return;
	if(pos==G) {
		if(Ok()) Modify(n);
		return;
	}

	In[pos] = 1;
	Rec(pos+1 , n+1);
	In[pos] = 0;
	Rec(pos+1 , n);
}

int main(){
	//ifstream cin("input.txt");
	ifstream cin("holstein.in");
	ofstream cout("holstein.out");
	int i,j,k;

	cin >> V;
	v.clear(); v.resize(V);
	FOR(i,V) cin >> v[i];

	cin >> G;
	S.clear(); S.resize(G,VI(V));
	FOR(i,G) FOR(j,V) cin >> S[i][j];

	N = G+1;
	In.clear();
	In.resize(G);
	Rec();

	cout << N;
	FOR(i,N) cout <<" "<< ret[i];
	cout << endl;
}
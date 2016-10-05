/*
ID: b0002141
PROG: prefix
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

#define VS			vector<string>
#define VC			vector<char>

string STR;
VS V;
VI dp;
VVI Adj;
VC C;

void Build_Graph(){
	int i,j,k;
	FOR(i,STR.size()){
		j = lower_bound(All(C),STR[i]) - C.begin();
		k = upper_bound(All(C),STR[i]) - C.begin();
		REP(j,j,k-1){
			if(V[j].size() > STR.size()-i) continue;
			if(V[j] == STR.substr(i,V[j].size()))
				Adj[i].push_back(V[j].size()+i);
		}
	}
}

int Rec(int pos=0){
	int i,j,k;
	if(pos==STR.size()) return pos;
	if(dp[pos] != -1) return dp[pos];

	dp[pos] = pos;
	FOR(i,Adj[pos].size()){
		k = Rec(Adj[pos][i]);
		dp[pos] = max(k,dp[pos]);
	}
	return dp[pos];
}

int main(){
	//ifstream cin("input.txt");
	ifstream cin("prefix.in");
	ofstream cout("prefix.out");
	int i,j,k;

	string str;
	while(true){
		cin >> str;
		if(str == ".") break;
		V.push_back(str);
	}
	STR = "";
	while(cin >> str) STR = STR+str;
	sort(All(V));

	Adj.resize(STR.size());
	C.resize(V.size());
	FOR(i,V.size()) C[i] = V[i][0];

	Build_Graph();

	dp.resize(STR.size(),-1);
	cout << Rec() << endl;

	return 0;
}
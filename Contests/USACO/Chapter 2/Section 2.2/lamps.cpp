/*
ID: b0002141
PROG: lamps
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

int N;
int C;
VI L;
VVI V(2);
VVI ret;

bool Check(VI v){
	int i,j,k;
	FOR(i,2) FOR(j,V[i].size()) if(v[V[i][j]-1] == i) return false;
	return true;
}

VI T(VI v,int n){
	int i,j,k;
	if(n==1) FOR(i,v.size()) v[i] = !v[i];
	if(n==2) FOR(i,v.size()) if(i%2==0) v[i] = !v[i];
	if(n==3) FOR(i,v.size()) if(i%2==1) v[i] = !v[i];
	if(n==4) FOR(i,v.size()) if(i%3==0) v[i] = !v[i];
	return v;
}

void func(){
	int i,j,k;
	if(C==0){if(Check(L)) ret.push_back(L);}
	else if(C==1){REP(i,1,4) if(Check(T(L,i))) ret.push_back(T(L,i));}
	else if(C==2) {
		REP(i,1,4) REP(j,i+1,4) if(Check(T(T(L,i),j))) ret.push_back(T(T(L,i),j));
		if(Check(L)) ret.push_back(L);
	}
	else if(C%2==1){
		REP(i,1,4) REP(j,i+1,4) REP(k,j+1,4) if(Check(T(T(T(L,i),j),k))) ret.push_back(T(T(T(L,i),j),k));
		REP(i,1,4) if(Check(T(L,i))) ret.push_back(T(L,i));
	}
	else{
		if(Check(T(T(T(T(L,1),2),3),4))) ret.push_back(T(T(T(T(L,1),2),3),4));
		REP(i,1,4) REP(j,i+1,4) if(Check(T(T(L,i),j))) ret.push_back(T(T(L,i),j));
		if(Check(L)) ret.push_back(L);
	}
}

int main(){
	//ifstream cin("input.txt");
	ifstream cin("lamps.in");
	ofstream cout("lamps.out");
	int i,j,k;

	cin >> N; L.resize(N,1);
	cin >> C;

	int buf;
	FOR(i,2){
		while(true){
			cin >> buf;
			if(buf==-1) break;
			V[i].push_back(buf);
		}
	}

	func();
	sort(All(ret));

	if(ret.size() == 0) cout <<"IMPOSSIBLE"<<endl;
	else {
		FOR(i,ret.size()) {
			FOR(j,N) cout <<ret[i][j];
			cout << endl;
		}
	}

	return 0;
}
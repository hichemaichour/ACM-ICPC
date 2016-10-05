/*
ID: b0002141
PROG: frac1
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

int main(){
	//ifstream cin("input.txt");
	ifstream cin("frac1.in");
	ofstream cout("frac1.out");
	int i,j,k;
	int N;
	cin >> N;
	vector<st> V;
	V.push_back(st(0,II(0,1)));
	V.push_back(st(1,II(1,1)));
	REP(i,2,N){
		REP(j,1,i-1){
			bool OK = i%j != 0 || j==1;
			REP(k,2,j-1) if(j%k==0 && i%k==0) OK=false;
			if(OK) V.push_back(st(j*1.0/i,II(j,i)));
		}
	}

	sort(All(V));

	FOR(i,V.size()) cout << V[i].num <<"/"<< V[i].den << endl;
}
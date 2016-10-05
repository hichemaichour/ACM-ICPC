/*
ID: b0002141
PROG: hamming
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

VI ret;
int N,B,D;

int dist(int x,int y){
	int buf = x^y;
	int ret = 0;
	while(buf){
		ret += buf%2;
		buf /=2;
	}
	return ret;
}

int Rec(int pos=0){
	int i,j,k;
	if(ret.size() == N)
		return 1;

	bool flg = true;
	FOR(i,ret.size()) if(dist(ret[i],pos)<D) flg = false;

	if(flg){
		ret.push_back(pos);
		flg = Rec(pos+1);
		if(flg) return 1;
		ret.pop_back();
	}
	return Rec(pos+1);
}

int main(){
	//ifstream cin("input.txt");
	ifstream cin("hamming.in");
	ofstream cout("hamming.out");
	int i,j,k;

	cin >> N >> B >> D;

	Rec();

	FOR(i,N) {
		if (i == N - 1 || (i + 1) % 10 == 0) cout << ret[i] << endl;
		else cout << ret[i] << " ";
	}
}
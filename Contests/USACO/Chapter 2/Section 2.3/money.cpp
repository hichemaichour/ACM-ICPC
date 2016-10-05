/*
ID: b0002141
PROG: money
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

#define VI			vector<long long>
#define VVI			vector<VI>

#define VD			vector<double>
#define VVD			vector<VD>

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII		vector<VII>

#define VS			vector<string>

int main(){
	//ifstream cin("input.txt");
	ifstream cin("money.in");
	ofstream cout("money.out");
	int i,j,k;
	int V,N;
	VI coin;
	VI dp;

	cin >> V >> N;

	coin.resize(V);
	FOR(i,V) 
		cin >> coin[i];
	
	dp.resize(N+1,0);
	dp[0] = 1;

	FOR(i,V){
		REP(j,0,N-coin[i])
			dp[j+coin[i]] += dp[j];
	}

	cout << dp[N] << endl;
}
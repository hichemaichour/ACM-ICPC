/*
ID: b0002141
PROG: nocows
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

#define MOD			9901

int dp[200][100];

int DP(int N,int K){
	if(dp[N][K] != -1)
		return dp[N][K];

	int i,j,k;
	dp[N][K] = 0;
	REP(i,1,N-2){
		int L = i;
		int R = N-i-1;
		dp[N][K] += (DP(L,K-1)-DP(L,K-2))*(DP(R,K-1)-DP(R,K-2));
		dp[N][K] += (DP(L,K-1)-DP(L,K-2))*DP(R,K-2);
		dp[N][K] += DP(L,K-2)*(DP(R,K-1)-DP(R,K-2));
		dp[N][K] %= MOD;
	}
	dp[N][K] += DP(N,K-1);
	dp[N][K] %= MOD;

	return dp[N][K];
}

int main(){
	//ifstream cin("input.txt");
	ifstream cin("nocows.in");
	ofstream cout("nocows.out");
	
	int i,j,k;
	FOR(i,200)FOR(j,100)
		dp[i][j] = -1;
	REP(i,1,99)
		dp[1][i] = 1;
	REP(i,2,199){
		dp[i][0] = 0;
		dp[i][1] = 0;
	}
	dp[1][0] = 0;

	int N,K;
	cin >> N >> K;
	int ans = DP(N,K)-DP(N,K-1);
	if(ans < 0)
		ans += MOD;
	ans %= MOD;
	cout << ans << endl;
}
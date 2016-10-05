#include <iostream>
#include <fstream>

#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <functional>

#define All(v)			v.begin(),v.end()

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		REP(i,0,N-1)

#define VI				vector<int>
#define VVI				vector<VI>

#define VD				vector<double>
#define VVD				vector<VD>

#define x				first
#define y				second
#define II				pair<int,int>
#define VII				vector<II>
#define VVII			vector<VII>

using namespace std;

long long a,b,c,N;
VI dp;
VI done;
long long cir;

int rec(int u){
	if(dp[u] != 0)
		return dp[u];
	if(done[u]){
		cir = u;
		return 0;
	}
	done[u] =  1;
	dp[u] = 1 + rec((a*u*u + b*u + c)%N);
	return dp[u];
}

void FIX(long long u){
	if(u == cir)
		return;
	dp[u] = dp[cir];
	FIX((a*u*u + b*u + c)%N);
}

void Find(int u){
	cir = -1;
	rec(u);
	if(cir != -1)
		FIX((a*cir*cir + b*cir + c)%N);
}

int main(){
	ifstream cin("input.txt");
	ofstream fout("g2.out");
	int T;
	cin >> T;
	int cnt;
	REP(cnt,1,T){
		int i,j,k;
		
		cin >> a >> b >> c >> N;

		dp.clear(); dp.resize(N);
		done.clear(); done.resize(N);
		FOR(i,N)
			if(!done[i])
				Find(i);

		int ans = 0;
		FOR(i,N)
			ans = max(ans,dp[i]);

		fout << ans << endl;
		cout << cnt << endl;
	}
}
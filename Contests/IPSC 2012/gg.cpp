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

void Find(int u){
	
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
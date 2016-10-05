#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define FOR(i,N)		for(i=0 ; i<(int)N ; i++)
#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define REPD(i,a,b)		for(i=(int)a ; i>=(int)b ; i--)

#define VI				vector<long long>
#define VVI				vector<VI>

#define All(v)			v.begin(),v.end()

using namespace std;

int N,B;
VI V;

long long DP(){
	int i,j,k;
	int ret = 0;
	FOR(i,N){
		VI dp(B+1);

		k = 0;
		FOR(j,i) k += V[j];
		if(k > B) break;

		dp[k] = 1;

		REP(j,i+1,N-1){
			REPD(k,B,V[j]) dp[k] += dp[k-V[j]];
		}

		k = max(1,(int)(B-V[i]+1));
		REP(j,k,B) ret += dp[j];
	}

	k = 0;
	FOR(i,N) k+=V[i];
	if(k <= B) ret++;

	return ret;
}

int main(){
	ifstream cin("input.txt");
    int T,cnt;
    cin >> T;
    REP(cnt,1,T){
		int i,j,k;

		cin >> N >> B;
		V.clear(); V.resize(N);

		FOR(i,N) cin >> V[i];
		sort(All(V));

		cout << cnt <<" "<< DP() << endl;
    }
}
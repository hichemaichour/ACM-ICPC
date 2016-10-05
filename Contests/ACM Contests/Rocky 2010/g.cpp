#include <iostream>

#define REP(i,a,b)		for(i=(int)a ; i<=(int)b ; i++)
#define FOR(i,N)		for(i=0 ; i<(int)N ; i++)

using namespace std;

int N1,N2;
int V1[1000];
int V2[1000];
int V [2000];
int dp[1001][1001];

int DP(int x,int y){
	if(dp[x][y] != -1)
		return dp[x][y];
	if(x != N1 && V1[x]==V[x+y]){
		if(DP(x+1,y))
			return 1;
	}
	if(y != N2 && V2[y]==V[x+y]){
		if(DP(x,y+1))
			return 1;
	}
	dp[x][y] = 0;
	return 0;
}

int main() {
	while(cin >> N1 >> N2 && N1){
		int i,j,k;
		FOR(i,N1) cin >> V1[i];
		FOR(i,N2) cin >> V2[i];
		FOR(i,N1+N2) cin >> V[i];
		
		FOR(i,N1+1) FOR(j,N2+1) dp[i][j] = -1;
		dp[N1][N2] = 1;
		
		if(DP(0,0))
			cout << "possible" << endl;
		else
			cout << "not possible" << endl;
	}
	return 0;
}


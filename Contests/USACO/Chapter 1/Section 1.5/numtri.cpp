/*
ID: b0002141
PROG: numtri
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define VI vector<int>
#define VVI vector<VI>
#define FOR(i,N) for(i=0 ; i<(int)N ; i++)
#define REP(i,a,b) for(i=(int)a ; i<=(int)b ; i++)

int main(){
    ifstream cin("numtri.in");
    ofstream cout("numtri.out");
    int N;
    int i,j,k;
    cin >> N;
    VVI V(N+1,VI(N));

    REP(i,1,N)
        FOR(j,i)
            cin >> V[i][j];

    VVI dp(N+1,VI(N));
    dp[1][0] = V[1][0];
    REP(i,1,N-1){
        FOR(j,i){
            dp[i+1][j] = max(dp[i+1][j] , dp[i][j]+V[i+1][j]);
            dp[i+1][j+1] = dp[i][j]+V[i+1][j+1];
        }
    }
    i = N;
    int ret = -1e9;
    FOR(j,i)
        ret = max(ret , dp[i][j]);

    cout << ret << endl;
}
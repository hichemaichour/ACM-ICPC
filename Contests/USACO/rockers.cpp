/*
ID: b0002541
PROG: rockers
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

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII			vector<VII>

int main(){
    //ifstream cin("input.txt");
    ifstream cin("rockers.in");
    ofstream cout("rockers.out");
    int i,j,k;
    int N,T,M;
    cin >> N >> T >> M;
    int V[22];
    FOR(i,N)
        cin >> V[i];
    int dp[22][22];
    FOR(i,22)
        FOR(j,22)
            dp[i][j] = 0;
    FOR(i,N){
        REP(j,1,M){
            if(i+1 < j)
                break;
            REPD(k,T,V[i])
                if(dp[j][k] < dp[j][k-V[i]] + 1)
                    dp[j][k] = dp[j][k-V[i]] + 1;
        }
        REP(j,1,M-1){
            int val = 0;
            REP(k,1,T)
                if(val < dp[j][k])
                    val = dp[j][k];
            dp[j+1][0] = val;
        }
    }

    int out = 0;
    FOR(i,M+1)
        FOR(j,T+1)
            if(out < dp[i][j])
                out = dp[i][j];

    cout << out << endl;
}
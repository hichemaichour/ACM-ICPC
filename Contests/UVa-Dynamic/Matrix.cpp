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

#define VS			vector<string>
#define VVS			vector<VS>

#define x			first
#define y			second
#define II			pair<int,int>
#define VII			vector<II>
#define VVII			vector<VII>

const int Inf = 1e9;

int N;
VI L;
VI R;
VVI M;
VVS S;

int main(){
	ifstream cin("input.txt");
	for(int cnt=1 ; true ; cnt++){
		int i,j,k;
		cin >> N;
		if(!N)
			return 0;
		L.resize(N); R.resize(N);
		M.clear(); M.resize(N,VI(N,Inf));
		S.clear(); S.resize(N,VS(N));
		FOR(i,N){
			cin >> L[i] >> R[i];
			char buf[10];
			sprintf(buf,"A%d\0",i+1);
			S[i][i] = buf;
			M[i][i] = 0;
		}

		REP(j,1,N-1){
			REP(i,0,N-1-j){
				REP(k,i,i+j-1){
					if(M[i][i+j] > M[i][k] + M[k+1][i+j] + L[i]*R[i]*R[i+j]){
						M[i][i+j] = M[i][k] + M[k+1][i+j] + L[i]*R[i]*R[i+j];
						S[i][i+j] = "(" + S[i][k] + " x " + S[k+1][i+j] + ")";
					}
				}
			}
		}

		cout <<"Case "<<cnt<<": "<<S[0][N-1]<<endl;
	}
}
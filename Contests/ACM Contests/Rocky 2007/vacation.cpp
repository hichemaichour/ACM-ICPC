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

#define REP(i, a, b) 	for (i=(int)a ; i<=(int)b ; i++)
#define REPD(i, a, b)	for (i=(int)a ; i>=(int)b ; i--)
#define REPI(i, v)		for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)		REP (i, 0, n-1)
#define FORD(i, n)		REPD(i, n-1, 0)

#define All(v)			v.begin(),v.end()
#define Resize(v,N)		v.clear(); v.resize(N);

#define IsIn(v,e)		(find(All(v),e) != v.end())
#define Remove(v,e)		v.resize( remove(All(v),e) - v.begin() )

#define VI				vector<int>
#define VVI				vector<VI>

#define x				first
#define y				second
#define II				pair<int,int>
#define VII				vector<II>
#define VVII			vector<VII>

#define VS				vector<string>
#define VVS				vector<VS>

const double EPS = 1e-3;
const int INF = 1<<29;
const double PI = acos(-1);

int D,N;
VVI V;
int s,t;
VI rooms;
VI st;
VI en;
VI ST;
VI EN;
VI ANS;
int ans;
int dp[120][40][120];

void rec(int d,int n,int psum=1){
	if(psum >= ans)
		return;
	if(d+1 == t){
		en.push_back(d+1);

		ans = psum;
		ANS = rooms;
		ST = st;
		EN = en;

		en.pop_back();
		return;
	}

	if(dp[d][n][psum])
		return;
	dp[d][n][psum] = 1;
	
	int i;
	if(V[d+1][n]){
		en.push_back(d+1);
		FOR(i,N){
				if(!V[d+1][i]){
					rooms.push_back(i);
					st.push_back(d+1);

					rec(d+1,i,psum+1);

					rooms.pop_back();
					st.pop_back();
				}
		}
		en.pop_back();
	}
	else
		rec(d+1,n,psum);
}

int main(){
	ifstream cin("input.txt");
	for(int cnt=1 ; true ; cnt++){
		char c;
		int i,j,k;
		cin >> D >> N;
		if(!D) break;
		else if(cnt != 1) cout << endl;

		V.clear();
		V.resize(D+2,VI(N));
		FOR(i,D){
			FOR(j,N){
				cin >> c;
				V[i][j] = c=='X';
			}
		}
		cin >> s >> t;
		s--; t--;

		ans = t-s + 10;
		st.clear(); en.clear(); rooms.clear();
		ST.clear(); EN.clear(); ANS.clear();
		FOR(i,110) FOR(j,30) FOR(k,110) dp[i][j][k] = 0;
		FOR(i,N){
			if(V[s][i]) continue;
			st.push_back(s);
			rooms.push_back(i);

			rec(s,i);

			st.pop_back();
			rooms.pop_back();
		}

		cout << "Case " << cnt << ":"<<endl<<endl;
		if(ans > t-s + 5)
			cout << "Not available" << endl;
		else{
			FOR(i,ans)
				cout << (char)('A'+ANS[i]) <<": "<< ST[i]+1<<"-"<<EN[i]+1 <<endl;
		}
	}
	return 0;
}
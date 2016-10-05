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
#define REPI(i, v)			for (i=v.begin() ; i!=v.end() ; i++)
#define FOR(i, n)			REP (i, 0, n-1)
#define FORD(i, n)			REPD(i, n-1, 0)

#define All(v)				v.begin(),v.end()
#define Resize(v,N)			v.clear(); v.resize(N);

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(All(v),e) - v.begin() )


typedef long long			LL;
typedef long double			LD;
typedef pair<int, int>		II;
typedef vector<int>			VI;
typedef vector<VI>			VVI;
typedef vector<bool>		VB;
typedef vector<VB>			VVB;
typedef vector<double>		VD;
typedef vector<VD>			VVD;
typedef vector<LL>			VLL;
typedef vector<VLL>			VVLL;
typedef vector<LD>			VLD;
typedef vector<VLD>			VVLD;
typedef vector<II>			VII;
typedef vector<VII>			VVII;
typedef vector<string>		VS;
typedef vector<VS>			VVS;

#define C first
#define pos second
#define NIL -1

int N,S,P;
VI UD;
VI Pos;

int Digestra(){
	int i,j,k;
	PQ<II,VII,greater<II> > Q;
	Q.push(II(0,0));
	int ret = INT_MAX;
	while(!Q.empty()){
		II h = Q.top(); Q.pop();
		if(h.C >= ret)
			return ret;

		II nxt;
		k = lower_bound(All(UD),h.pos) - UD.begin();
		REP(i,k,P-1){
			nxt = h;
			nxt.pos = Pos[UD[i]];
			nxt.C += ((UD[i]-j)+S-1)/S;
			Q.push(nxt);
		}
		ret = min(ret , h.C + ((N-h.pos)+S-1)/S );
	}
	return ret;
}

int main(){
	ifstream cin("UpDown.h");
	while(cin >> N >> S >> P){
		int i,j,k;
		Resize(Pos,N);
		FOR(i,N)
			Pos[i] = i;

		Resize(UD,P);
		FOR(i,P){
			cin >> j >> k;
			Pos[j] = k;
			UD[i] = j;
		}

		cout << Digestra() << endl;
	}
	return 0;
}
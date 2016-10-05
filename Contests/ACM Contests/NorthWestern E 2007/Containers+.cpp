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

#define PB					push_back
#define MP					make_pair

#define PQ					priority_queue

#define IsIn(v,e)			(find(All(v),e) != v.end())
#define Remove(v,e)			v.resize( remove(ALL(v),e) - v.begin() )


typedef long long			LL;
typedef long double			LD;
typedef pair<int, int>		II;
typedef vector<int>			VI;
typedef vector<VI>			VVI;
typedef vector<bool>		VB;
typedef vector<VB>			VVB;
typedef vector<double>		VD;
typedef vector<VD>			VVD;
typedef vector<II>			VII;
typedef vector<VII>			VVII;
typedef vector<LL>			VLL;
typedef vector<VLL>			VVLL;
typedef vector<string>		VS;
typedef vector<VS>			VVS;

#define L first
#define W second

pair<LL,LL> ret;

LL A(LL a,LL b){
	return 440*a*b + 88*a + 40*b + 8;
}

void func(LL N){
	LL Min = -1;
	LL d1;
	LL d2;
	for(LL a=sqrt((double)N) ; a>0 ; a--){
		LL b = (N+a-1)/a;
		if(Min == -1 || Min>A(a,b)){
			Min = A(a,b);
			d1 = a*44 + 4;
			d2 = b*10 + 2;
			ret.L = max(d1,d2);
			ret.W = min(d1,d2);
		}
		if(Min == A(a,b)){
			d1 = a*44 + 4;
			d2 = b*10 + 2;
			if(max(d1,d2)-min(d1,d2) < ret.L-ret.W){
				ret.L = max(d1,d2);
				ret.W = min(d1,d2);
			}
		}
	}
}

int main(){
	//ifstream cin("Containers.h");
	int T;
	cin >> T;
	while(T--){
		LL N;
		cin >> N;
		N = (N+4)/5;
		func(N);
		cout << ret.L <<" X "<< ret.W <<" = "<< ret.L*ret.W << endl;
	}
}